import socket
import pandas as pd
import pyarrow.parquet as pq
import pyarrow as pa
import numpy as np
from datetime import datetime

def main():
    # IP address and port
    IP = '192.168.1.233'
    PORT = 1000

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    df = []
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    filename = f"data_{current_time}.parquet"
    network_send_field_size = 60
        
    try:
        # Connect to the server
        client_socket.connect((IP, PORT))
        print(f"Connected to {IP} on port {PORT}")

        # Send data to the server
        zeros = b'\x00' * 64
        # client_socket.send(message.encode())

        # Send 64 zeros to the server
        received_data = b''
        channels = 500
        bytes_to_receive = channels * network_send_field_size * 4 + 2 * network_send_field_size * 4 + 4

        # Receive data from the server and print continuously
        i = 0
        data_list = []
        while i < 5000:
            received_data = b''
            while len(received_data) < bytes_to_receive:
                chunk = client_socket.recv(min(1024, bytes_to_receive - len(received_data)))
                if not chunk:
                    break
                received_data += chunk
            client_socket.send(zeros)
            float_values = np.frombuffer(received_data[4:], dtype=np.float32)
            data_list.append(float_values)
            i += 1
        
        client_socket.close()
        data_array = np.vstack(data_list)
        reshaped_data = np.reshape(data_array, (-1, network_send_field_size))
        b = []
        x, y = reshaped_data.shape
        y = channels
        y += 2

        for i in range(0, x, y):
            end_value = i + y - 1
            b.append(reshaped_data[i:end_value, :])

        b = np.concatenate(b, axis=1)
        b = b.T
        table = pa.Table.from_pandas(pd.DataFrame(b))
        pq.write_table(table, filename)

    except ConnectionRefusedError:
        print("Connection was refused.")
    except ConnectionError as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
