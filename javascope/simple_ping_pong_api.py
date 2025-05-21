import socket
import struct
import pandas as pd
import numpy as np
from datetime import datetime
from pathlib import Path


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
        process_data(client_socket, ch, var)


def main():
    # Use pathlib to handle file paths
    file_path = Path("../vitis/software/Baremetal/src/include/javascope.h").resolve()
    enum_name = "JS_OberservableData"
    observable_data = parse_enum_to_dataframe(file_path, enum_name)

    client_socket = None
    df = pd.DataFrame()

    while True:
        command = input("Enter a command (connect, write <id> <value>, show_observable, exit): ").strip().lower()

        if command == "connect":
            if client_socket:
                print("Already connected.")
                continue

            IP = '192.168.1.233'
            PORT = 1000

            try:
                client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                client_socket.connect((IP, PORT))
                print(f"Connected to {IP} on port {PORT}")
            except ConnectionRefusedError:
                print("Connection was refused.")
                client_socket = None
            except Exception as e:
                print(f"An error occurred: {e}")
                client_socket = None

        elif command.startswith("show_observable"):
            print("Observable variables")
            print(observable_data)

        elif command.startswith("observe"):
            if not client_socket:
                print("Not connected. Use 'connect' command first.")
                continue

            try:
                _, name, channel_number = command.split()
                print(name)
                channel_number = int(channel_number)
                if channel_number < 1 or channel_number > 20:
                    print("Channel number must be between 1 and 20.")
                    continue

                # Find the number corresponding to the name in the dataframe
                def get_number_from_observable_data(name):
                    result = observable_data.loc[observable_data['name'].str.lower() == name.lower(), 'number']
                    if result.empty:
                        raise ValueError(f"Name '{name}' not found in observable data.")
                    return result.iloc[0]

                number_of_name = get_number_from_observable_data(name)
                setup_scope_channels(client_socket, [channel_number], [number_of_name])
                print(f"Observation set for {name} on channel {channel_number}.")
            except ValueError as e:
                print(e)
            except Exception as e:
                print(f"An error occurred: {e}")

        elif command.startswith("write"):
            if not client_socket:
                print("Not connected. Use 'connect' command first.")
                continue
            try:
                readback_value = write_and_read(client_socket, 0, 0)
                df = pd.concat([df, readback_value], ignore_index=True)
                print(df)
            except ValueError:
                print("Invalid input. Usage: write <id> <value>")
            except Exception as e:
                print(f"An error occurred: {e}")

        elif command.startswith("read"):
            if not client_socket:
                print("Not connected. Use 'connect' command first.")
                continue
            try:
                readback_value = write_and_read(client_socket, 0, 0)
                df = pd.concat([df, readback_value], ignore_index=True)
                print(df)
            except Exception as e:
                print(f"An error occurred: {e}")

        elif command == "exit":
            if client_socket:
                client_socket.close()
            print("Exiting...")
            break

        else:
            print("Unknown command. Available commands: connect, write <id> <value>, show_observable, exit.")


if __name__ == "__main__":
    main()
