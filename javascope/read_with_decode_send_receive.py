import socket
import struct
import pandas as pd
import pyarrow.parquet as pq
from datetime import datetime
import pyarrow as pa
import numpy as np

def decode_floats(data):
    floats = []
    for i in range(0, len(data), 4):
        floats.append(struct.unpack('f', data[i:i+4])[0])
    return floats

# Decode binary data to floats

def encode_id_value(id, value):
    # Pack the id (uint32) and value (float) into binary data
    return struct.pack('If', id, value)

def process_data(client_socket, id_input, value_input):
    zeros = encode_id_value(id_input, value_input)
    client_socket.send(zeros)
    response = client_socket.recv(1324)
    print(f"Number of bytes in response: {len(response)}")
    print(f"Number of bytes sent to UZ: {len(zeros)}")
    float_values = decode_floats(response)
    print(float_values)
    return float_values
    
def main():
    # IP address and port
    IP = '192.168.1.233'
    PORT = 1000

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    df = pd.DataFrame()
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    filename = f"data_{current_time}.parquet"
        
    try:
        # Connect to the server
        client_socket.connect((IP, PORT))
        print(f"Connected to {IP} on port {PORT}")

        # Send data to the server
        message = "Hello, server!"
        client_socket.send(message.encode())

        # Manual mode for user interaction
        while True:
            id_input = int(input("Enter an ID (unsigned int32): "))
            value_input = float(input("Enter a value (float): "))
            float_values = process_data(client_socket, id_input, value_input)
            data = np.array(float_values)
            data = data[1:]
            # Reshape the data
            reshaped_data = np.reshape(data, (-1, 15))
            # Extract the first and last column into a dedicated dataframe
            # Convert to DataFrame
            df_tmp = pd.DataFrame(reshaped_data.T)
            df_slow = pd.concat([df_tmp.iloc[:, 0], df_tmp.iloc[:, -1]], axis=1)
            df_tmp = df_tmp.iloc[:, 1:-1]
            df = pd.concat([df, df_tmp], ignore_index=True)
            print(df)
            print(df_slow)


    except ConnectionRefusedError:
        print("Connection was refused.")
    except ConnectionError as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
