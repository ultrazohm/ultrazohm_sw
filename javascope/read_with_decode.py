import socket
import struct
import pandas as pd
import pyarrow.parquet as pq
from datetime import datetime
import pyarrow as pa
import numpy as np

def decode_floats(data):
    floats = []
    datalength=len(data)
    for i in range(0, datalength, 4):
        floats.append(struct.unpack('f', data[i:i+4])[0])
    return floats

# Decode binary data to floats

def main():
    # IP address and port
    IP = '192.168.1.233'
    PORT = 1000

    # Create a socket object
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    df = []
    current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    filename = f"data_{current_time}.parquet"
    network_send_field_size=15
        
    try:
        # Connect to the server
        client_socket.connect((IP, PORT))
        print(f"Connected to {IP} on port {PORT}")

        # Send data to the server
        zeros = b'\x00' * 64
        # client_socket.send(message.encode())

        # Send 64 zeros to the server
        received_data = b''
        channels=200
        bytes_to_receive = channels*network_send_field_size*4+2*network_send_field_size*4+4

        # Receive data from the server and print continuously
        i=0
        while i<1000:
            # response2 = client_socket.recv(1078+60)
            received_data = b''
            # received_data = client_socket.recv(bytes_to_receive) # receive length is determined using the len functions below to match the sending data which fills one package fully and puts the rest in the second package. 
            while len(received_data) <= bytes_to_receive:
                chunk = client_socket.recv(min(1024, bytes_to_receive - len(received_data)))
                if not chunk:
                    break
                received_data += chunk
            response_length=len(received_data)
            client_socket.send(zeros)
            float_values = decode_floats(received_data)
            data = np.array(float_values)
            data = data[1:] # 1:
            # Reshape the data
            reshaped_data = np.reshape(data, (-1, network_send_field_size))
            # data = np.concatenate(reshaped_data, axis=0).reshape(-1, reshaped_data.shape[0]).T
            # Convert to DataFrame
            df_tmp = reshaped_data.T
            if len(df)==0:
                df=df_tmp
            else:
                df = np.append(df,df_tmp, axis=0)
            # print(df)
            i=i+1
            # print(i)
            
        table = pa.Table.from_pandas(pd.DataFrame(df))
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
