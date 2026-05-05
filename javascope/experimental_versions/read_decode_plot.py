import socket
import struct
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime

def decode_floats(data):
    floats = []
    for i in range(0, len(data), 4):
        floats.append(struct.unpack('f', data[i:i+4])[0])
    return floats

def plot_data(data):
    plt.clf()  # Clear the current plot
    plt.plot(data)
    plt.pause(0.01)  # Pause for a short time to update the plot

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

        # Initialize the plot
        plt.ion()
        fig = plt.figure()
        ax = fig.add_subplot(111)

        # Receive data from the server and plot continuously
        while True:
            zeros = b'\x00' * 64
            client_socket.send(zeros)
            response = client_socket.recv(1324)
            float_values = decode_floats(response)
            data = np.array(float_values)
            data = data[1:]
            # Reshape the data
            reshaped_data = np.reshape(data, (-1, 15))
            # Convert to DataFrame
            df_tmp = pd.DataFrame(reshaped_data.T)
            df = pd.concat([df, df_tmp], ignore_index=True)

            # Plot the last row of data
            plot_data(df)

    except ConnectionRefusedError:
        print("Connection was refused.")
    except ConnectionError as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
