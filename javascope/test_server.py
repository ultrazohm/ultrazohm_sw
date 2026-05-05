#!/usr/bin/env python3
import argparse
import configparser
import math
import os
import re
import socket
import struct
import threading
import time
from dataclasses import dataclass, field


DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 1000
DEFAULT_SAMPLE_RATE_HZ = 1000.0
MAX_SAMPLE_RATE_HZ = 10_000.0
DEFAULT_AMPLITUDE = 1.0
DEFAULT_CHANNELS = 20
DEFAULT_SAMPLES_PER_PACKET = 15
DEFAULT_BASE_FREQ_HZ = 50.0
DEFAULT_SLOW_DATA_COUNT = 17
DEFAULT_COMMAND_BYTES = 2048
POLE_PAIRS = 2.0

IDLE_STATE = 0
RUNNING_STATE = 1
CONTROL_STATE = 2
ERROR_STATE = 3

CMD_ENABLE_SYSTEM = 1
CMD_ENABLE_CONTROL = 2
CMD_STOP = 3
CMD_SET_SEND_FIELD_FIRST = 4
CMD_SET_SEND_FIELD_LAST = 23
CMD_MY_BUTTON_1 = 24
CMD_MY_BUTTON_2 = 25
CMD_MY_BUTTON_3 = 26
CMD_ERROR_RESET = 33
CMD_SELECT_DATA_CH_FIRST = 201
CMD_SELECT_DATA_CH_LAST = 220

OBS_ZERO = 0
OBS_ISR_EXEC_TIME_US = 1
OBS_ISR_PERIOD_US = 2
OBS_LIFECHECK = 3
OBS_THETA_MECH = 4
OBS_UA = 5
OBS_UB = 6
OBS_UC = 7
OBS_IA = 8
OBS_IB = 9
OBS_IC = 10
OBS_ID = 11
OBS_IQ = 12
OBS_UD = 13
OBS_UQ = 14
OBS_SPEED_RPM = 15
OBS_EL_SPEED_RPM = 16
OBS_LOAD_SPEED_RPM = 17
OBS_VOLT_TEMP = 18
OBS_SOC_INIT = 19
OBS_THETA_EL = 20
OBS_THETA_MECH_2 = 21
OBS_LOAD_THETA_MECH = 22
OBS_DELTA_THETA_MECH = 23
OBS_WTEMP = 24
OBS_RS_MOHM = 25
OBS_LD_MH = 26
OBS_LQ_MH = 27
OBS_PSIPM_MVS = 28

SLOW_ZERO = 0
SLOW_SECONDS = 1
SLOW_ISR_EXEC_US = 2
SLOW_ISR_PERIOD_US = 3
SLOW_FREQ_READBACK = 4
SLOW_MILLISECONDS = 5
SLOW_ADC_CONV_FACTOR = 6
SLOW_ERROR_CODE = 7
SLOW_UD = 8
SLOW_UQ = 9
SLOW_ID = 10
SLOW_IQ = 11
SLOW_SPEED = 12
SLOW_TORQUE = 13
SLOW_ENCODER_OFFSET = 14
SLOW_UD_REF = 15
SLOW_UQ_REF = 16

DEFAULT_SELECTED_OBSERVABLES = [
    OBS_ISR_EXEC_TIME_US,
    OBS_ISR_PERIOD_US,
    OBS_LIFECHECK,
    OBS_THETA_MECH,
    OBS_UA,
    OBS_UB,
    OBS_UC,
    OBS_IA,
    OBS_IB,
    OBS_IC,
    OBS_ID,
    OBS_IQ,
    OBS_UD,
    OBS_UQ,
    OBS_SPEED_RPM,
    OBS_EL_SPEED_RPM,
    OBS_LOAD_SPEED_RPM,
    OBS_VOLT_TEMP,
    OBS_SOC_INIT,
    OBS_THETA_EL,
]


def load_properties(path: str) -> dict:
    config = configparser.ConfigParser()
    config.read_dict({"DEFAULT": {}})
    if os.path.exists(path):
        with open(path, "r", encoding="utf-8") as properties_file:
            content = properties_file.read()
        config.read_string("[DEFAULT]\n" + content)
    return dict(config["DEFAULT"])


def resolve_javascope_header() -> str | None:
    root_dir = os.path.dirname(__file__)
    candidates = [
        os.path.join(root_dir, "../vitis/software/Baremetal/src/include/javascope.h"),
        os.path.join(root_dir, "javascope.h"),
    ]
    for candidate in candidates:
        normalized = os.path.normpath(candidate)
        if os.path.exists(normalized):
            return normalized
    return None


def detect_slow_data_count() -> int:
    header_path = resolve_javascope_header()
    if header_path is None:
        return DEFAULT_SLOW_DATA_COUNT

    with open(header_path, "r", encoding="utf-8") as header_file:
        content = header_file.read()

    match = re.search(r"enum\s+JS_SlowData\s*\{(.*?)\};", content, re.DOTALL)
    if match is None:
        return DEFAULT_SLOW_DATA_COUNT

    entries = []
    for raw_line in match.group(1).splitlines():
        line = raw_line.split("//", 1)[0].strip().rstrip(",")
        if not line or not line.startswith("JSSD_"):
            continue
        entries.append(line.split("=", 1)[0].strip())

    filtered_entries = [entry for entry in entries if "ENDMARKER" not in entry]
    return len(filtered_entries) if filtered_entries else DEFAULT_SLOW_DATA_COUNT


def limit_sample_rate(sample_rate_hz: float) -> float:
    return min(sample_rate_hz, MAX_SAMPLE_RATE_HZ)


def calculate_packet_bytes(samples_per_packet: int, channel_count: int) -> int:
    return 4 + ((channel_count + 2) * samples_per_packet * 4)


def wrap_angle(angle: float) -> float:
    return math.atan2(math.sin(angle), math.cos(angle))


def dq_to_abc(d_value: float, q_value: float, theta: float) -> tuple[float, float, float]:
    phase_a = theta
    phase_b = theta - (2.0 * math.pi / 3.0)
    phase_c = theta + (2.0 * math.pi / 3.0)
    value_a = d_value * math.cos(phase_a) - q_value * math.sin(phase_a)
    value_b = d_value * math.cos(phase_b) - q_value * math.sin(phase_b)
    value_c = d_value * math.cos(phase_c) - q_value * math.sin(phase_c)
    return value_a, value_b, value_c


def smooth_value(current: float, target: float, dt: float, time_constant: float) -> float:
    if time_constant <= 0.0:
        return target
    alpha = 1.0 - math.exp(-dt / time_constant)
    return current + ((target - current) * alpha)


@dataclass
class UltraZohmModel:
    sample_rate_hz: float
    base_freq_hz: float
    amplitude: float
    slow_data_count: int
    selected_observables: list[int] = field(default_factory=lambda: list(DEFAULT_SELECTED_OBSERVABLES))
    send_fields: list[float] = field(default_factory=lambda: [0.0] * 21)
    current_state: int = IDLE_STATE
    ready_led: bool = False
    running_led: bool = False
    error_led: bool = False
    user_led: bool = False
    error_flag: bool = False
    js_enable_system: bool = False
    js_enable_control: bool = False
    js_stop: bool = False
    uptime_seconds: float = 0.0
    interrupt_counter: int = 0
    slow_data_index: int = 0
    last_status: int = 0
    mechanical_speed_rpm: float = 0.0
    electrical_speed_rpm: float = 0.0
    load_speed_rpm: float = 0.0
    mechanical_torque_nm: float = 0.0
    theta_mech: float = 0.0
    theta_elec: float = 0.0
    load_theta_mech: float = 0.0
    delta_theta_mech: float = 0.0
    u_d: float = 0.0
    u_q: float = 0.0
    i_d: float = 0.0
    i_q: float = 0.0
    u_a: float = 0.0
    u_b: float = 0.0
    u_c: float = 0.0
    i_a: float = 0.0
    i_b: float = 0.0
    i_c: float = 0.0
    volt_temp: float = 48.0
    soc_init: float = 0.85
    winding_temp_c: float = 26.0
    rs_mohm: float = 82.0
    ld_mh: float = 1.8
    lq_mh: float = 2.1
    psipm_mvs: float = 57.0
    encoder_offset: float = 0.12
    adc_conversion_factor: float = 10.0
    error_code: float = 0.0

    def process_command_bytes(self, payload: bytes) -> None:
        if len(payload) < 8:
            return
        command_id = struct.unpack_from("<I", payload, 0)[0]
        command_value = struct.unpack_from("<f", payload, 4)[0]
        self.apply_command(command_id, command_value)

    def apply_command(self, command_id: int, command_value: float) -> None:
        if command_id == 0:
            return
        if CMD_SELECT_DATA_CH_FIRST <= command_id <= CMD_SELECT_DATA_CH_LAST:
            channel_index = command_id - CMD_SELECT_DATA_CH_FIRST
            observable_index = int(command_value)
            if 0 <= channel_index < len(self.selected_observables) and 0 <= observable_index <= OBS_PSIPM_MVS:
                self.selected_observables[channel_index] = observable_index
            return
        if CMD_SET_SEND_FIELD_FIRST <= command_id <= CMD_SET_SEND_FIELD_LAST:
            field_index = command_id - CMD_SET_SEND_FIELD_FIRST + 1
            self.send_fields[field_index] = command_value
            return
        if command_id == CMD_ENABLE_SYSTEM:
            self.js_enable_system = True
        elif command_id == CMD_ENABLE_CONTROL:
            self.js_enable_control = True
        elif command_id == CMD_STOP:
            self.js_stop = True
        elif command_id == CMD_MY_BUTTON_1:
            self.error_flag = True
            self.error_code = 1.0
        elif command_id == CMD_MY_BUTTON_2:
            self.user_led = True
        elif command_id == CMD_MY_BUTTON_3:
            self.user_led = False
        elif command_id == CMD_ERROR_RESET:
            self.error_flag = False
            self.error_code = 0.0
        self.step_state_machine()

    def step_state_machine(self) -> None:
        stop_requested = self.js_stop
        enable_system = self.js_enable_system and not stop_requested
        enable_control = self.js_enable_control and not stop_requested and self.current_state == RUNNING_STATE
        self.js_enable_system = False
        self.js_enable_control = False
        self.js_stop = False

        if self.current_state == ERROR_STATE:
            if stop_requested:
                self.enter_idle_state()
            else:
                self.apply_led_state_for_current_mode()
            return
        if self.error_flag:
            self.enter_error_state()
            return
        if self.current_state == IDLE_STATE:
            if enable_system:
                self.enter_running_state()
            else:
                self.apply_led_state_for_current_mode()
            return
        if self.current_state == RUNNING_STATE:
            if stop_requested:
                self.enter_idle_state()
            elif enable_control:
                self.enter_control_state()
            else:
                self.apply_led_state_for_current_mode()
            return
        if self.current_state == CONTROL_STATE:
            if stop_requested:
                self.enter_idle_state()
            else:
                self.apply_led_state_for_current_mode()

    def enter_idle_state(self) -> None:
        self.current_state = IDLE_STATE
        self.error_flag = False
        self.error_code = 0.0
        self.apply_led_state_for_current_mode()

    def enter_running_state(self) -> None:
        self.current_state = RUNNING_STATE
        self.apply_led_state_for_current_mode()

    def enter_control_state(self) -> None:
        self.current_state = CONTROL_STATE
        self.apply_led_state_for_current_mode()

    def enter_error_state(self) -> None:
        self.current_state = ERROR_STATE
        self.user_led = False
        self.apply_led_state_for_current_mode()

    def apply_led_state_for_current_mode(self) -> None:
        if self.current_state == ERROR_STATE:
            self.ready_led = False
            self.running_led = False
            self.error_led = True
            return
        self.running_led = self.current_state == CONTROL_STATE
        self.error_led = False
        if self.current_state == IDLE_STATE:
            self.ready_led = int(self.uptime_seconds) % 2 == 1
        else:
            self.ready_led = int((self.uptime_seconds * 1000.0) % 200.0) > 100

    def advance_sample(self) -> None:
        dt = 1.0 / self.sample_rate_hz
        self.uptime_seconds += dt
        self.step_state_machine()

        speed_reference_rpm = self.send_fields[1] if self.send_fields[1] != 0.0 else (self.base_freq_hz * 60.0)
        torque_reference_nm = self.send_fields[2] if self.send_fields[2] != 0.0 else 2.0
        id_reference = self.send_fields[3]
        iq_reference = self.send_fields[4] if self.send_fields[4] != 0.0 else (torque_reference_nm * 1.2)
        ud_reference = self.send_fields[5] if self.send_fields[5] != 0.0 else 0.0
        uq_reference = self.send_fields[6] if self.send_fields[6] != 0.0 else (self.amplitude * 20.0)

        if self.current_state == IDLE_STATE:
            target_speed_rpm = 0.0
            target_torque_nm = 0.0
            target_id = 0.0
            target_iq = 0.0
            target_ud = 0.0
            target_uq = 0.0
        elif self.current_state == RUNNING_STATE:
            target_speed_rpm = speed_reference_rpm * 0.6
            target_torque_nm = torque_reference_nm * 0.5
            target_id = id_reference * 0.5
            target_iq = iq_reference * 0.5
            target_ud = ud_reference * 0.5
            target_uq = uq_reference * 0.5
        elif self.current_state == CONTROL_STATE:
            target_speed_rpm = speed_reference_rpm
            target_torque_nm = torque_reference_nm
            target_id = id_reference
            target_iq = iq_reference
            target_ud = ud_reference
            target_uq = uq_reference
        else:
            target_speed_rpm = 0.0
            target_torque_nm = 0.0
            target_id = 0.0
            target_iq = 0.0
            target_ud = 0.0
            target_uq = 0.0

        self.mechanical_speed_rpm = smooth_value(self.mechanical_speed_rpm, target_speed_rpm, dt, 0.25)
        self.mechanical_torque_nm = smooth_value(self.mechanical_torque_nm, target_torque_nm, dt, 0.15)
        self.i_d = smooth_value(self.i_d, target_id, dt, 0.05)
        self.i_q = smooth_value(self.i_q, target_iq, dt, 0.05)
        self.u_d = smooth_value(self.u_d, target_ud, dt, 0.04)
        self.u_q = smooth_value(self.u_q, target_uq, dt, 0.04)

        mechanical_speed_rps = self.mechanical_speed_rpm / 60.0
        self.theta_mech = wrap_angle(self.theta_mech + (2.0 * math.pi * mechanical_speed_rps * dt))
        self.load_speed_rpm = smooth_value(self.load_speed_rpm, self.mechanical_speed_rpm * 0.96, dt, 0.35)
        load_speed_rps = self.load_speed_rpm / 60.0
        self.load_theta_mech = wrap_angle(self.load_theta_mech + (2.0 * math.pi * load_speed_rps * dt))
        self.theta_elec = wrap_angle(self.theta_mech * POLE_PAIRS)
        self.delta_theta_mech = wrap_angle(self.theta_mech - self.load_theta_mech)
        self.electrical_speed_rpm = self.mechanical_speed_rpm * POLE_PAIRS

        self.u_a, self.u_b, self.u_c = dq_to_abc(self.u_d, self.u_q, self.theta_elec)
        self.i_a, self.i_b, self.i_c = dq_to_abc(self.i_d, self.i_q, self.theta_elec)

        active_factor = 1.0 if self.current_state in (RUNNING_STATE, CONTROL_STATE) else 0.0
        self.volt_temp = 48.0 + (active_factor * 3.0 * math.sin((2.0 * math.pi * self.base_freq_hz * 0.05) * self.uptime_seconds))
        self.winding_temp_c = 26.0 + (active_factor * 7.0) + (0.8 * math.sin((2.0 * math.pi * 0.02) * self.uptime_seconds))
        self.soc_init = max(0.0, min(1.0, 0.9 - (0.00002 * self.uptime_seconds)))
        self.interrupt_counter += 1
        self.last_status = self.build_status_word()

    def build_status_word(self) -> int:
        status_word = 0
        if self.ready_led:
            status_word |= 1 << 0
        if self.running_led:
            status_word |= 1 << 1
        if self.error_led:
            status_word |= 1 << 2
        if self.user_led:
            status_word |= 1 << 3
        return status_word

    def next_slow_data_sample(self) -> tuple[float, int]:
        slow_data_id = self.slow_data_index
        slow_data_value = self.get_slow_data_value(slow_data_id)
        self.slow_data_index += 1
        if self.slow_data_index >= self.slow_data_count:
            self.slow_data_index = 0
        return slow_data_value, slow_data_id

    def get_slow_data_value(self, slow_data_id: int) -> float:
        if slow_data_id == SLOW_ZERO:
            return 0.0
        if slow_data_id == SLOW_SECONDS:
            return self.uptime_seconds
        if slow_data_id == SLOW_ISR_EXEC_US:
            return 18.0 + (3.0 * math.sin((2.0 * math.pi * 0.5) * self.uptime_seconds))
        if slow_data_id == SLOW_ISR_PERIOD_US:
            return 1_000_000.0 / self.sample_rate_hz
        if slow_data_id == SLOW_FREQ_READBACK:
            return self.sample_rate_hz
        if slow_data_id == SLOW_MILLISECONDS:
            return self.uptime_seconds * 1000.0
        if slow_data_id == SLOW_ADC_CONV_FACTOR:
            return self.adc_conversion_factor
        if slow_data_id == SLOW_ERROR_CODE:
            return self.error_code
        if slow_data_id == SLOW_UD:
            return self.u_d
        if slow_data_id == SLOW_UQ:
            return self.u_q
        if slow_data_id == SLOW_ID:
            return self.i_d
        if slow_data_id == SLOW_IQ:
            return self.i_q
        if slow_data_id == SLOW_SPEED:
            return self.mechanical_speed_rpm
        if slow_data_id == SLOW_TORQUE:
            return self.mechanical_torque_nm
        if slow_data_id == SLOW_ENCODER_OFFSET:
            return self.encoder_offset
        if slow_data_id == SLOW_UD_REF:
            return self.send_fields[5]
        if slow_data_id == SLOW_UQ_REF:
            return self.send_fields[6]
        return 0.0

    def get_observable_value(self, observable_id: int) -> float:
        if observable_id == OBS_ZERO:
            return 0.0
        if observable_id == OBS_ISR_EXEC_TIME_US:
            return self.get_slow_data_value(SLOW_ISR_EXEC_US)
        if observable_id == OBS_ISR_PERIOD_US:
            return self.get_slow_data_value(SLOW_ISR_PERIOD_US)
        if observable_id == OBS_LIFECHECK:
            return float(self.interrupt_counter % 1000)
        if observable_id == OBS_THETA_MECH:
            return self.theta_mech
        if observable_id == OBS_UA:
            return self.u_a
        if observable_id == OBS_UB:
            return self.u_b
        if observable_id == OBS_UC:
            return self.u_c
        if observable_id == OBS_IA:
            return self.i_a
        if observable_id == OBS_IB:
            return self.i_b
        if observable_id == OBS_IC:
            return self.i_c
        if observable_id == OBS_ID:
            return self.i_d
        if observable_id == OBS_IQ:
            return self.i_q
        if observable_id == OBS_UD:
            return self.u_d
        if observable_id == OBS_UQ:
            return self.u_q
        if observable_id == OBS_SPEED_RPM:
            return self.mechanical_speed_rpm
        if observable_id == OBS_EL_SPEED_RPM:
            return self.electrical_speed_rpm
        if observable_id == OBS_LOAD_SPEED_RPM:
            return self.load_speed_rpm
        if observable_id == OBS_VOLT_TEMP:
            return self.volt_temp
        if observable_id == OBS_SOC_INIT:
            return self.soc_init
        if observable_id == OBS_THETA_EL:
            return self.theta_elec
        if observable_id == OBS_THETA_MECH_2:
            return self.theta_mech
        if observable_id == OBS_LOAD_THETA_MECH:
            return self.load_theta_mech
        if observable_id == OBS_DELTA_THETA_MECH:
            return self.delta_theta_mech
        if observable_id == OBS_WTEMP:
            return self.winding_temp_c
        if observable_id == OBS_RS_MOHM:
            return self.rs_mohm
        if observable_id == OBS_LD_MH:
            return self.ld_mh
        if observable_id == OBS_LQ_MH:
            return self.lq_mh
        if observable_id == OBS_PSIPM_MVS:
            return self.psipm_mvs
        return 0.0


def generate_packet(model: UltraZohmModel, samples_per_packet: int, channel_count: int) -> bytes:
    packet_bytes = calculate_packet_bytes(samples_per_packet, channel_count)
    packet = bytearray(packet_bytes)
    slow_data_content: list[float] = []
    slow_data_ids: list[float] = []
    channel_samples = [[0.0] * samples_per_packet for _ in range(channel_count)]

    for sample_index in range(samples_per_packet):
        model.advance_sample()
        slow_data_value, slow_data_id = model.next_slow_data_sample()
        slow_data_content.append(float(slow_data_value))
        slow_data_ids.append(float(slow_data_id))
        for channel_index in range(channel_count):
            observable_id = model.selected_observables[channel_index]
            channel_samples[channel_index][sample_index] = float(model.get_observable_value(observable_id))

    offset = 0
    struct.pack_into("<I", packet, offset, model.last_status)
    offset += 4
    for value in slow_data_content:
        struct.pack_into("<f", packet, offset, value)
        offset += 4
    for channel_index in range(channel_count):
        for sample_index in range(samples_per_packet):
            struct.pack_into("<f", packet, offset, channel_samples[channel_index][sample_index])
            offset += 4
    for value in slow_data_ids:
        struct.pack_into("<f", packet, offset, value)
        offset += 4
    return bytes(packet)


def recv_command(conn: socket.socket) -> bytes:
    return conn.recv(DEFAULT_COMMAND_BYTES)


def wait_for_next_packet(next_send_time: float) -> float:
    now = time.monotonic()
    if next_send_time > now:
        time.sleep(next_send_time - now)
        return next_send_time
    return now


def handle_client(
    conn: socket.socket,
    addr,
    samples_per_packet: int,
    channel_count: int,
    sample_rate_hz: float,
    amplitude: float,
    base_freq: float,
    slow_data_count: int,
) -> None:
    print(f"Testbench: Connected by {addr}", flush=True)
    model = UltraZohmModel(
        sample_rate_hz=sample_rate_hz,
        base_freq_hz=base_freq,
        amplitude=amplitude,
        slow_data_count=slow_data_count,
    )
    packet_interval_s = samples_per_packet / sample_rate_hz
    next_send_time = time.monotonic()
    try:
        next_send_time = wait_for_next_packet(next_send_time)
        conn.sendall(generate_packet(model, samples_per_packet, channel_count))
        next_send_time += packet_interval_s
        while True:
            command_payload = recv_command(conn)
            if not command_payload:
                print("Testbench: Client disconnected.", flush=True)
                break
            model.process_command_bytes(command_payload)
            next_send_time = wait_for_next_packet(next_send_time)
            conn.sendall(generate_packet(model, samples_per_packet, channel_count))
            next_send_time += packet_interval_s
    except Exception as exception:
        print(f"Testbench: Exception: {exception}", flush=True)
    finally:
        conn.close()
        print(f"Testbench: Connection with {addr} closed.", flush=True)


def start_server(
    host: str,
    port: int,
    samples_per_packet: int,
    channel_count: int,
    sample_rate_hz: float,
    amplitude: float,
    base_freq: float,
    slow_data_count: int,
) -> None:
    effective_sample_rate_hz = limit_sample_rate(sample_rate_hz)
    packet_rate_hz = effective_sample_rate_hz / samples_per_packet
    packet_bytes = calculate_packet_bytes(samples_per_packet, channel_count)
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind((host, port))
        server_socket.listen()
        print(f"Testbench: Listening on {host}:{port}", flush=True)
        print(
            f"Testbench: Output limited to {effective_sample_rate_hz:.1f} Hz sample rate ({packet_rate_hz:.1f} packets/s)",
            flush=True,
        )
        print(
            f"Testbench: TCP packet size = {packet_bytes} bytes, slow data entries = {slow_data_count}",
            flush=True,
        )
        print(
            "Testbench: Commands model Enable_System, Enable_Control, Stop, My_Button_1/2/3, Error_Reset, Set_Send_Field_1..20, and channel selection 201..220",
            flush=True,
        )
        while True:
            conn, addr = server_socket.accept()
            client_thread = threading.Thread(
                target=handle_client,
                args=(
                    conn,
                    addr,
                    samples_per_packet,
                    channel_count,
                    effective_sample_rate_hz,
                    amplitude,
                    base_freq,
                    slow_data_count,
                ),
                daemon=True,
            )
            client_thread.start()


def main() -> None:
    props = load_properties(os.path.join(os.path.dirname(__file__), "properties.ini"))
    parser = argparse.ArgumentParser(description="JavaScope UltraZohm behavior test server")
    parser.add_argument("--host", default=DEFAULT_HOST)
    parser.add_argument("--port", type=int, default=DEFAULT_PORT)
    parser.add_argument(
        "--samples-per-packet",
        type=int,
        default=int(props.get("measurements_per_tcp_packet", DEFAULT_SAMPLES_PER_PACKET)),
    )
    parser.add_argument(
        "--channels",
        type=int,
        default=int(props.get("scopechannelnumber", DEFAULT_CHANNELS)),
    )
    smallest_step_usec = float(props.get("smallesttimestepusec", 100))
    sample_rate_default = 1_000_000.0 / smallest_step_usec if smallest_step_usec > 0 else DEFAULT_SAMPLE_RATE_HZ
    parser.add_argument(
        "--sample-rate",
        type=float,
        default=sample_rate_default,
        help="Requested sample rate in Hz. The server clamps this to 10000 Hz.",
    )
    parser.add_argument("--amplitude", type=float, default=DEFAULT_AMPLITUDE)
    parser.add_argument("--base-freq", type=float, default=DEFAULT_BASE_FREQ_HZ)
    args = parser.parse_args()
    start_server(
        host=args.host,
        port=args.port,
        samples_per_packet=args.samples_per_packet,
        channel_count=args.channels,
        sample_rate_hz=args.sample_rate,
        amplitude=args.amplitude,
        base_freq=args.base_freq,
        slow_data_count=detect_slow_data_count(),
    )


if __name__ == "__main__":
    main()