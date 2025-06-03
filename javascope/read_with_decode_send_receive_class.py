import asyncio
import socket
import struct
import numpy as np
import pandas as pd
from datetime import datetime
import pyarrow as pa
import pyarrow.parquet as pq
import threading
import matplotlib.pyplot as plt

# Helper functions
def decode_floats(data):
    return [struct.unpack('f', data[i:i+4])[0] for i in range(0, len(data), 4)]

def encode_id_value(id_input, value_input):
    return struct.pack('If', id_input, value_input)

async def user_input_task(cmd_queue, stop_event):
    loop = asyncio.get_event_loop()
    while not stop_event.is_set():
        try:
            id_input = await loop.run_in_executor(None, input, "Enter an ID (unsigned int32): ")
            value_input = await loop.run_in_executor(None, input, "Enter a value (float): ")
            id_input = int(id_input)
            value_input = float(value_input)
            await cmd_queue.put((id_input, value_input))
        except ValueError:
            print("Invalid input. Please enter a valid integer and float.")
        except (KeyboardInterrupt, EOFError):
            print("Exiting user input task.")
            stop_event.set()
            break

class ultrazohm:
    def __init__(self, ip, port, cmd_queue_size=100, from_ethernet_queue_size=1000000, max_buffer_size=1000):
        self.ip = ip
        self.port = port
        self.cmd_queue_size = cmd_queue_size
        self.from_ethernet_queue_size = from_ethernet_queue_size
        self.max_buffer_size = max_buffer_size
        self.scope_buffer = []
        self.scope_buffer_lock = threading.Lock()
        self.reader = None
        self.writer = None
        self.stop_event = None
        self.comms_task_handle = None
        self.raw_to_table_task_handle = None
        self.log_fast_enabled = False
        self.log_slow_enabled = False
        self.logfile_fast_name = None
        self.logfile_slow_name = None
        self.cmd_queue = None
        self.from_ethernet_queue = None

    async def connect(self, ip=None, port=None):
        if ip is not None:
            self.ip = ip
        if port is not None:
            self.port = port
        # Create asyncio objects in the current event loop
        self.cmd_queue = asyncio.Queue(maxsize=self.cmd_queue_size)
        self.from_ethernet_queue = asyncio.Queue(maxsize=self.from_ethernet_queue_size)
        self.stop_event = asyncio.Event()
        try:
            self.reader, self.writer = await asyncio.open_connection(self.ip, self.port)
            print(f"Connected to {self.ip} on port {self.port}")
            self.writer.write(b"Hello, server!")
            await self.writer.drain()
        except ConnectionRefusedError:
            print(f"Connection refused: {self.ip}:{self.port}")
            raise
        except Exception as e:
            print(f"Error connecting: {e}")
            raise

    async def disconnect(self):
        self.stop_event.set()
        if self.writer:
            self.writer.close()
            await self.writer.wait_closed()
        print("Connection closed.")

    def create_logfile_fast(self, filename=None):
        if filename is None:
            current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            filename = f"fast_{current_time}.csv"
        self.logfile_fast_name = filename
        df = pd.DataFrame()
        df.to_csv(filename, index=False, mode='w')
        print(f"Created log file: {filename}")
        return filename

    def create_logfile_slow(self, filename=None):
        if filename is None:
            current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            filename = f"slow_{current_time}.csv"
        self.logfile_slow_name = filename
        df = pd.DataFrame()
        df.to_csv(filename, index=False, mode='w')
        print(f"Created log file: {filename}")
        return filename

    def log_fast(self, enable, logfile=None):
        self.log_fast_enabled = enable
        if enable and logfile:
            self.create_logfile_fast(logfile)
        elif enable and not self.logfile_fast_name:
            self.create_logfile_fast()

    def log_slow(self, enable, logfile=None):
        self.log_slow_enabled = enable
        if enable and logfile:
            self.create_logfile_slow(logfile)
        elif enable and not self.logfile_slow_name:
            self.create_logfile_slow()

    async def comms_task(self):
        while not self.stop_event.is_set():
            try:
                if not self.cmd_queue.empty():
                    id_input, value_input = await self.cmd_queue.get()
                else:
                    id_input, value_input = 0, 0.0
                packet = encode_id_value(id_input, value_input)
                self.writer.write(packet)
                await self.writer.drain()
                data = await self.reader.readexactly(1324)
                float_values = decode_floats(data)
                await self.from_ethernet_queue.put(float_values)
            except Exception as e:
                print(f"Communication error: {e}")
                self.stop_event.set()
                break

    async def raw_to_table_task(self):
        try:
            while not self.stop_event.is_set():
                try:
                    float_values = await self.from_ethernet_queue.get()
                    data_np = np.array(float_values)[1:]
                    reshaped_data = np.reshape(data_np, (-1, 15))
                    df_tmp = pd.DataFrame(reshaped_data.T)
                    fast_data = df_tmp.iloc[:, 1:-1]
                    slow_data = df_tmp.iloc[:, [0, -1]]
                    # Append to scope buffer with lock
                    with self.scope_buffer_lock:
                        for _, row in fast_data.iterrows():
                            self.scope_buffer.append(row.tolist())
                        if len(self.scope_buffer) > self.max_buffer_size:
                            self.scope_buffer = self.scope_buffer[-self.max_buffer_size:]
                    if self.log_fast_enabled and self.logfile_fast_name:
                        fast_data.to_csv(self.logfile_fast_name, mode='a', header=False, index=False)
                    if self.log_slow_enabled and self.logfile_slow_name:
                        slow_data.to_csv(self.logfile_slow_name, mode='a', header=False, index=False)
                except Exception as e:
                    print(f"Error processing data: {e}")
        except Exception as e:
            print(f"Error in raw_to_table_task: {e}")

    async def start_communication(self, enable):
        if enable:
            self.stop_event.clear()
            self.comms_task_handle = asyncio.create_task(self.comms_task())
            self.raw_to_table_task_handle = asyncio.create_task(self.raw_to_table_task())
        else:
            self.stop_event.set()
            if self.comms_task_handle:
                await self.comms_task_handle
            if self.raw_to_table_task_handle:
                await self.raw_to_table_task_handle

    async def set_command(self, id_input, value_input):
        await self.cmd_queue.put((id_input, value_input))

    def get_scope_buffer_data(self):
        with self.scope_buffer_lock:
            return self.scope_buffer

    def set_cmd_queue_size(self, size):
        self.cmd_queue_size = size
        # If already connected, recreate the queue in the current event loop
        if self.cmd_queue is not None:
            self.cmd_queue = asyncio.Queue(maxsize=size)

    def get_cmd_queue_size(self):
        return self.cmd_queue_size

    def set_from_ethernet_queue_size(self, size):
        self.from_ethernet_queue_size = size
        if self.from_ethernet_queue is not None:
            self.from_ethernet_queue = asyncio.Queue(maxsize=size)

    def get_from_ethernet_queue_size(self):
        return self.from_ethernet_queue_size

    def set_max_buffer_size(self, size):
        self.max_buffer_size = size
        # Optionally trim the buffer if needed
        with self.scope_buffer_lock:
            if len(self.scope_buffer) > size:
                self.scope_buffer = self.scope_buffer[-size:]

    def get_max_buffer_size(self):
        return self.max_buffer_size

# Example usage of the ultrazohm class
async def example_usage():
    uz = ultrazohm(ip='192.168.1.233', port=1000, cmd_queue_size=10, from_ethernet_queue_size=10, max_buffer_size=1000)
    await uz.connect()  # Connect using constructor IP/port

    await uz.start_communication(True)  # Start communication and logging tasks
    # Example: send a command
    await uz.set_command(0, 3.14)
    await asyncio.sleep(2)  # Let it run for a bit
    await uz.set_command(1, 3.14)
    await asyncio.sleep(2)  # Let it run for a bit
    await uz.set_command(2, 3.14)
    await asyncio.sleep(2)  # Let it run for a bit
    await uz.set_command(3, 3.14)
    uz.log_fast(True)   # Enable fast logging (filename auto-generated)
    uz.log_slow(True)   # Enable slow logging (filename auto-generated)
    # ... do more work, or await asyncio.sleep(10) ...
    await asyncio.sleep(0.1)  # Let it run for a bit
    await uz.start_communication(False)  # Stop communication and logging
    await uz.disconnect()  # Disconnect from device

if __name__ == "__main__":
    asyncio.run(example_usage())
