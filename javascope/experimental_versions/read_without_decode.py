import socket

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

        # Send 64 zeros to the server


        # Receive data from the server and print continuously
        while True:
            zeros = b'\x00' * 64
            client_socket.send(zeros)
            response = client_socket.recv(1324)
            print("Received from server:", response)

    except ConnectionRefusedError:
        print("Connection was refused.")
    except ConnectionError as e:
        print(f"An error occurred: {e}")
    finally:
        # Close the connection
        client_socket.close()

if __name__ == "__main__":
    main()
