import socket
import struct
import pandas as pd
import os
from datetime import datetime

# Define constants
NETWORK_SEND_FIELD_SIZE = 15
VARIABLES_PER_TIMESTEP = 21
TOTAL_VARIABLES = NETWORK_SEND_FIELD_SIZE * VARIABLES_PER_TIMESTEP
NETWORK_SEND_STRUCT_SIZE = 4 + 4 * TOTAL_VARIABLES

def decode_data(data):
    unpack_string = 'I' + 'f' * TOTAL_VARIABLES
    decoded_data = struct.unpack(unpack_string, data)
    return decoded_data

def main():
    # IP address and port
    IP = '192.168.1.233'
    PORT = 1000

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Connect to the server
        client_socket.connect((IP, PORT))
        print(f"Connected to {IP} on port {PORT}")

        # Send data to the server
        message = "Hello, server!"
        client_socket.send(message.encode())



        # Create a new log file with a unique timestamp
        timestamp = datetime.now().strftime("%Y%m%d%H%M%S")
        log_file = f"log_{timestamp}.parquet"

        # Create a DataFrame to store the logged data
        columns = [f"Var_{i}" for i in range(VARIABLES_PER_TIMESTEP)]
        df = pd.DataFrame(columns=columns)

        # Receive data from the server and log it to the new log file
        while True:
            zeros = b'\x00' * 64
            client_socket.send(zeros)
            response = client_socket.recv(NETWORK_SEND_STRUCT_SIZE)
            if len(response) == NETWORK_SEND_STRUCT_SIZE:
                decoded_response = decode_data(response)
                for t in range(NETWORK_SEND_FIELD_SIZE):
                    row_data = decoded_response[t * VARIABLES_PER_TIMESTEP : (t + 1) * VARIABLES_PER_TIMESTEP]
                    df.loc[len(df)] = row_data

                # Write the DataFrame to the new log file
                df.to_parquet(log_file, index=False, compression=None)

    except ConnectionRefusedError:
        print("Connection was refused.")
    except ConnectionError as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
