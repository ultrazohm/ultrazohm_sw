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

        # Send 64 zeros to the server


        # Receive data from the server and print continuously
        while True:
            zeros = b'\x00' * 64
            client_socket.send(zeros)
            response = client_socket.recv(1324)
            float_values = decode_floats(response)
            data = np.array(float_values)
            data = data[1:]
            # Reshape the data
            reshaped_data = np.reshape(data, (-1, 15))
            # data = np.concatenate(reshaped_data, axis=0).reshape(-1, reshaped_data.shape[0]).T
            # Convert to DataFrame
            df_tmp = pd.DataFrame(reshaped_data.T)
            df = pd.concat([df, df_tmp], ignore_index=True)

            float_values[0]=0
            table = pa.Table.from_pandas(df)
            pq.write_table(table, filename)
            # print(float_values)
            # print(df.tail(1))

    except ConnectionRefusedError:
        print("Connection was refused.")
    except ConnectionError as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
