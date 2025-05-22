import socket
import struct
import pandas as pd
import numpy as np
from datetime import datetime
from pathlib import Path
import time


def parse_enum_to_dataframe(file_path, enum_name):
    with open(file_path, "r") as file:
        lines = file.readlines()

    enum_start = False
    enum_entries = []
    current_value = 0

    for line in lines:
        line = line.strip()
        if line.startswith(f"enum {enum_name}"):
            enum_start = True
            continue
        if enum_start:
            if line.startswith("};"):
                break
            if line.startswith("{") or line.startswith("}"):
                continue
            if line and not line.startswith("//"):
                entry = line.split(",")[0].strip()
                if "=" in entry:
                    name, value = entry.split("=")
                    name = name.strip()
                    current_value = int(value.strip())
                else:
                    name = entry
                enum_entries.append((name, current_value))
                current_value += 1

    # Create a DataFrame
    df_enum = pd.DataFrame(enum_entries, columns=["name", "number"])

    return df_enum

def decode_floats(data):
    floats = []
    for i in range(0, len(data), 4):
        floats.append(struct.unpack("f", data[i: i + 4])[0])
    return floats

def encode_id_value(id, value):
    return struct.pack("If", id, value)

def process_data(client_socket, id_input, value_input):
    zeros = encode_id_value(id_input, value_input)
    client_socket.send(zeros)
    response = client_socket.recv(1324)
    float_values = decode_floats(response)
    return float_values

def write_and_read(client_socket, id_input, value_input):
    float_values = process_data(client_socket, id_input, value_input)
    float_values = process_data(client_socket, 0, 0)
    float_values = process_data(client_socket, 0, 0)
    data = np.array(float_values)
    data = data[1:]
    reshaped_data = np.reshape(data, (-1, 15))
    df_tmp = pd.DataFrame(reshaped_data.T)
    df_tmp = df_tmp.iloc[[-1]]
    df_tmp = df_tmp.iloc[:, 1:-1]
    return df_tmp

def setup_scope_channels(client_socket, channel, variable_to_observe):
    assert isinstance(variable_to_observe, (list, np.ndarray)), "variable_to_observe must be a list or numpy array"
    assert isinstance(channel, (list, np.ndarray)), "channel must be a list or numpy array"
    assert len(channel) == len(variable_to_observe), "channel and variable_to_observe must have the same length"
    for ch, var in zip(channel, variable_to_observe):
        process_data(client_socket, ch+200, var)

def set_one_scope_channel_based_on_name(client_socket, channel_number, name, observable_data):
    number_of_name = get_number_from_observable_data(name, observable_data)
    setup_scope_channels(client_socket, [channel_number], [number_of_name])

def get_number_from_observable_data(name,observable_data):
    result = observable_data.loc[observable_data['name'].str.lower() == name.lower(), 'number']
    if result.empty:
        raise ValueError(f"Name '{name}' not found in observable data.")
    return result.iloc[0]

def read_all(client_socket):
    readback_value = write_and_read(client_socket, 0, 0)
    return readback_value

def set_variable(client_socket, name, value_input,command_data):
    number_of_name = get_number_from_observable_data(name, command_data)
    write_and_read(client_socket, number_of_name + 1000, value_input)  # magic 1000 required due to Javascope hack


def uz_stop(client_socket):
    write_and_read(client_socket, 3, 0)


def uz_enable_system(client_socket):
    write_and_read(client_socket, 1, 0)


def uz_enable_control(client_socket):
    write_and_read(client_socket, 2, 0)


def get_variable(client_socket, name, command_data, observable_data):
    set_one_scope_channel_based_on_name(client_socket, 1, name, observable_data)
    read = read_all(client_socket)
    read = read.iloc[0, 0]  # Extract the single float value from the DataFrame
    return read

# Use pathlib to handle file paths
file_path = Path("../vitis/software/Baremetal/src/include/javascope.h").resolve()
enum_name = "JS_OberservableData"
observable_data = parse_enum_to_dataframe(file_path, enum_name)
enum_name = "JS_CommandData"
command_data = parse_enum_to_dataframe(file_path, enum_name)
df = pd.DataFrame()

client_socket = None
IP = '192.168.1.233'
PORT = 1000
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((IP, PORT))
print(f"Connected to {IP} on port {PORT}")

setup_scope_channels(client_socket, [1], [30])

set_variable(client_socket, "COM_python_test_variable", 100, command_data)

set_one_scope_channel_based_on_name(client_socket, 1, "JSO_COM_python_test_variable", observable_data)

# Somehow, set channel does not work anymore, check
# print("Current values of all variables:")
# all=read_all(client_socket)
# print(all)

readback = get_variable(client_socket, "JSO_COM_python_test_variable", command_data, observable_data)
print("Value of JSO_COM_python_test_variable:", readback)
set_variable(client_socket, "COM_python_test_variable", 200, command_data)
readback = get_variable(client_socket, "JSO_COM_python_test_variable", command_data, observable_data)

print("Value of JSO_COM_python_test_variable:", readback)

uz_enable_system(client_socket)
time.sleep(0.5)
uz_enable_control(client_socket)
time.sleep(0.5)
uz_stop(client_socket)
time.sleep(0.5)

set_variable(client_socket, "COM_Ton", 1e-6, command_data)
readback = get_variable(client_socket, "JSO_Ton_from_ip", command_data, observable_data)

print("Value of JSO_Ton_from_ip:", readback)
