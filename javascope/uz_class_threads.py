import socket
import struct
import numpy as np
import pandas as pd
from datetime import datetime, timezone
import pyarrow as pa
import pyarrow.parquet as pq
import multiprocessing
import queue
import matplotlib.pyplot as plt

# Helper functions
def decode_floats(data):
    return [struct.unpack('f', data[i:i+4])[0] for i in range(0, len(data), 4)]

def encode_id_value(id_input, value_input):
    return struct.pack('If', id_input, value_input)

class ultrazohm:
    def __init__(self, ip, port, cmd_queue_size=100, from_ethernet_queue_size=1000000, max_buffer_size=1000):
        self.ip = ip
        self.port = port
        self.cmd_queue_size = cmd_queue_size
        self.from_ethernet_queue_size = from_ethernet_queue_size
        self.max_buffer_size = max_buffer_size
        self.manager = multiprocessing.Manager()
        self.scope_buffer = self.manager.list()
        self.scope_buffer_lock = multiprocessing.Lock()
        self.sock = None
        self.stop_event = multiprocessing.Event()
        self.comms_process = None
        self.raw_to_table_process = None
        self.log_fast_enabled = False
        self.log_slow_enabled = False
        self.logfile_fast_name = None
        self.logfile_slow_name = None
        self.manager = multiprocessing.Manager()
        self.cmd_queue = self.manager.Queue(maxsize=cmd_queue_size)
        self.from_ethernet_queue = self.manager.Queue(maxsize=from_ethernet_queue_size)
        self.debug = False

    def connect(self, ip=None, port=None):
        if ip is not None:
            self.ip = ip
        if port is not None:
            self.port = port
        # Socket will be created in comms_task process
        print(f"Prepared to connect to {self.ip} on port {self.port}")

    def disconnect(self):
        self.stop_communication()
        print("Connection closed.")

    def create_logfile_fast(self, filename=None):
        if filename is None:
            current_time = datetime.now(timezone.utc).astimezone().strftime("%Y-%m-%d_%H-%M-%S")
            filename = f"fast_{current_time}.csv"
        self.logfile_fast_name = filename
        df = pd.DataFrame()
        df.to_csv(filename, index=False, mode='w')
        print(f"Created log file: {filename}")
        return filename

    def create_logfile_slow(self, filename=None):
        if filename is None:
            current_time = datetime.now(timezone.utc).astimezone().strftime("%Y-%m-%d_%H-%M-%S")
            filename = f"slow_{current_time}.csv"
        self.logfile_slow_name = filename
        df = pd.DataFrame()
        df.to_csv(filename, index=False, mode='w')
        print(f"Created log file: {filename}")
        return filename

    def log_fast(self, enable, logfile=None):
        self.log_fast_enabled = enable
        if enable and logfile:
            self.create_logfile_fast(logfile)
        elif enable and not self.logfile_fast_name:
            self.create_logfile_fast()

    def log_slow(self, enable, logfile=None):
        self.log_slow_enabled = enable
        if enable and logfile:
            self.create_logfile_slow(logfile)
        elif enable and not self.logfile_slow_name:
            self.create_logfile_slow()

    def comms_task(self, ip, port, cmd_queue, from_ethernet_queue, stop_event, debug):
        sock = None
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((ip, port))
            sock.settimeout(10.0)
            print(f"[Process] Connected to {ip} on port {port}")
            sock.sendall(b"Hello, server!")
            while not stop_event.is_set():
                try:
                    try:
                        id_input, value_input = cmd_queue.get(timeout=0.000001)
                    except queue.Empty:
                        id_input, value_input = 0, 0.0
                    packet = encode_id_value(id_input, value_input)
                    if debug:
                        print(f"[DEBUG] Sending packet: id={id_input}, value={value_input}, raw={packet.hex()}")
                    sock.sendall(packet)
                    data = b''
                    while len(data) < 1324:
                        chunk = sock.recv(1324 - len(data))
                        if not chunk:
                            raise ConnectionError("Socket connection lost.")
                        data += chunk
                    float_values = decode_floats(data)
                    try:
                        from_ethernet_queue.put(float_values, timeout=0.000001)
                    except queue.Full:
                        pass
                except Exception as e:
                    print(f"Communication error: {e}")
                    stop_event.set()
                    break
        except Exception as e:
            print(f"Error in comms_task: {e}")
        finally:
            if sock:
                sock.close()

    def raw_to_table_task(self, from_ethernet_queue, stop_event, scope_buffer, scope_buffer_lock, max_buffer_size, log_fast_enabled, logfile_fast_name, log_slow_enabled, logfile_slow_name):
        try:
            while not stop_event.is_set():
                try:
                    float_values = from_ethernet_queue.get(timeout=0.1)
                    data_np = np.array(float_values)[1:]
                    reshaped_data = np.reshape(data_np, (-1, 15))
                    df_tmp = pd.DataFrame(reshaped_data.T)
                    fast_data = df_tmp.iloc[:, 1:-1]
                    slow_data = df_tmp.iloc[:, [0, -1]]
                    # Append to scope buffer with lock
                    with scope_buffer_lock:
                        for _, row in fast_data.iterrows():
                            scope_buffer.append(row.tolist())
                        if len(scope_buffer) > max_buffer_size:
                            scope_buffer[:] = scope_buffer[-max_buffer_size:]
                    if log_fast_enabled and logfile_fast_name:
                        fast_data.to_csv(logfile_fast_name, mode='a', header=False, index=False)
                    if log_slow_enabled and logfile_slow_name:
                        slow_data.to_csv(logfile_slow_name, mode='a', header=False, index=False)
                except queue.Empty:
                    continue
                except Exception as e:
                    print(f"Error processing data: {e}")
        except Exception as e:
            print(f"Error in raw_to_table_task: {e}")

    def start_communication(self, enable, debug=False):
        self.debug = debug
        if enable:
            self.stop_event.clear()
            if self.comms_process is None or not self.comms_process.is_alive():
                self.comms_process = multiprocessing.Process(
                    target=self.comms_task,
                    args=(self.ip, self.port, self.cmd_queue, self.from_ethernet_queue, self.stop_event, self.debug),
                    daemon=True
                )
                self.comms_process.start()
            if self.raw_to_table_process is None or not self.raw_to_table_process.is_alive():
                self.raw_to_table_process = multiprocessing.Process(
                    target=self.raw_to_table_task,
                    args=(self.from_ethernet_queue, self.stop_event, self.scope_buffer, self.scope_buffer_lock, self.max_buffer_size, self.log_fast_enabled, self.logfile_fast_name, self.log_slow_enabled, self.logfile_slow_name),
                    daemon=True
                )
                self.raw_to_table_process.start()
        else:
            self.stop_communication()

    def stop_communication(self):
        self.stop_event.set()
        if self.comms_process is not None:
            self.comms_process.join(timeout=2)
            self.comms_process = None
        if self.raw_to_table_process is not None:
            self.raw_to_table_process.join(timeout=2)
            self.raw_to_table_process = None

    def set_command(self, id_input, value_input):
        try:
            self.cmd_queue.put((id_input, value_input), timeout=0.1)
        except queue.Full:
            print("Command queue is full. Command not sent.")

    def set_command_skip_queue(self, id_input, value_input):
        """Clears the command queue and puts only the new command in."""
        with self.cmd_queue.mutex:
            self.cmd_queue.queue.clear()
        self.set_command(id_input, value_input)

    def get_scope_buffer_data(self):
        with self.scope_buffer_lock:
            return list(self.scope_buffer)

    def set_cmd_queue_size(self, size):
        self.cmd_queue_size = size
        self.cmd_queue = self.manager.Queue(maxsize=size)

    def get_cmd_queue_size(self):
        return self.cmd_queue_size

    def set_from_ethernet_queue_size(self, size):
        self.from_ethernet_queue_size = size
        self.from_ethernet_queue = self.manager.Queue(maxsize=size)

    def get_from_ethernet_queue_size(self):
        return self.from_ethernet_queue_size

    def set_max_buffer_size(self, size):
        self.max_buffer_size = size
        # Optionally trim the buffer if needed
        with self.scope_buffer_lock:
            if len(self.scope_buffer) > size:
                self.scope_buffer = self.scope_buffer[-size:]

    def get_max_buffer_size(self):
        return self.max_buffer_size

# Example usage of the ultrazohm class
def example_usage():
    import time
    uz = ultrazohm(ip='127.0.0.1', port=1000, cmd_queue_size=10, from_ethernet_queue_size=10, max_buffer_size=1000)
    uz.connect()  # Connect using constructor IP/port
    uz.log_fast(True)   # Enable fast logging (filename auto-generated)
    uz.log_slow(True)   # Enable slow logging (filename auto-generated)
    uz.start_communication(True)  # Start communication and logging tasks
    time.sleep(1.0)
    uz.start_communication(False)  # Stop communication and logging
    uz.connect()  # Connect using constructor IP/port
    uz.start_communication(True)  # Start communication and logging tasks
    uz.set_command(0, 3.14)
    time.sleep(2)
    uz.set_command(1, 3.14)
    time.sleep(2)
    uz.set_command(2, 3.14)
    time.sleep(2)
    uz.set_command(3, 3.14)
    uz.disconnect()  # Disconnect from device

if __name__ == "__main__":
    example_usage()
