import socket
import struct
import threading
import time

HOST = '0.0.0.0'  # Listen on all interfaces
PORT = 1000       # Match the port in read_with_decode_send_receive

# Number of floats to send (1324 bytes / 4 bytes per float)
NUM_FLOATS = 331

# Helper to generate a test data packet
def generate_test_packet(counter=0):
    floats = [float(counter)] + [float(i) for i in range(1, NUM_FLOATS)]
    return struct.pack(f'{NUM_FLOATS}f', *floats)

def handle_client(conn, addr):
    print(f"Testbench: Connected by {addr}", flush=True)
    try:
        # Wait for initial handshake
        handshake = conn.recv(1024)
        print(f"Testbench: Received handshake: {handshake}", flush=True)
        counter = 0
        while True:
            # Wait for command (8 bytes: 4 for id, 4 for float)
            cmd = conn.recv(8)
            if not cmd:
                print("Testbench: Client disconnected.", flush=True)
                break
            print(f"Testbench: Received command: {cmd}", flush=True)
            # Send one data packet in response
            packet = generate_test_packet(counter)
            conn.sendall(packet)
            print(f"Testbench: Sent data packet #{counter}", flush=True)
            counter += 1
    except Exception as e:
        print(f"Testbench: Exception: {e}", flush=True)
    finally:
        conn.close()
        print(f"Testbench: Connection with {addr} closed.", flush=True)

def start_test_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen()
        print(f"Testbench: Listening on {HOST}:{PORT}", flush=True)
        while True:
            conn, addr = s.accept()
            print(f"Testbench: Accepted connection from {addr}", flush=True)
            client_thread = threading.Thread(target=handle_client, args=(conn, addr), daemon=True)
            client_thread.start()

if __name__ == "__main__":
    start_test_server()
