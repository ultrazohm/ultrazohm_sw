import asyncio
import socket
import struct
import numpy as np
import pandas as pd
from datetime import datetime
import pyarrow as pa
import pyarrow.parquet as pq

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

async def comms_task(reader, writer, cmd_queue, stop_event,from_ethernet_queue):
    while not stop_event.is_set():
        try:
            if not cmd_queue.empty():
                id_input, value_input = await cmd_queue.get()
                # print(f"Sending ID: {id_input}, Value: {value_input}")
            else:
                id_input, value_input = 0, 0.0

            packet = encode_id_value(id_input, value_input)
            writer.write(packet)
            await writer.drain()
            data = await reader.readexactly(1324)
            float_values = decode_floats(data)
            await from_ethernet_queue.put(float_values)
        except Exception as e:
            print(f"Communication error: {e}")
            stop_event.set()
            break


async def raw_to_table_task(stop_event, from_ethernet_queue):
            current_time = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            filename_fast = f"fast_{current_time}.csv"
            filename_slow = f"slow_{current_time}.csv"
            try:
                # Create an empty CSV file to start 
                df = pd.DataFrame()  # Create empty DataFrame
                df.to_csv(filename_fast, index=False, mode='w')
                df.to_csv(filename_slow, index=False, mode='w')
                print(f"Created log file: {filename_fast}")
                print(f"Created log file: {filename_slow}")
                print()
            except Exception as e:
                print(f"Error creating log file: {e}")

            try:
                while not stop_event.is_set():
                    try:
                        float_values = await from_ethernet_queue.get()
                        data_np = np.array(float_values)[1:]
                        reshaped_data = np.reshape(data_np, (-1, 15))
                        df_tmp = pd.DataFrame(reshaped_data.T)
                        fast_data = df_tmp.iloc[:, 1:-1]
                        slow_data = df_tmp.iloc[:, [0, -1]]
                        fast_data.to_csv(filename_fast, mode='a', header=False, index=False)
                        slow_data.to_csv(filename_slow, mode='a', header=False, index=False)
                    except Exception as e:
                        print(f"Error processing data: {e}")
            except Exception as e:
                print(f"Error in raw_to_table_task: {e}")

async def main():
    IP = '192.168.1.233'
    PORT = 1000
    cmd_queue = asyncio.Queue()
    from_ethernet_queue = asyncio.Queue()
    stop_event = asyncio.Event()
    
    try:
        reader, writer = await asyncio.open_connection(IP, PORT)
        print(f"Connected to {IP} on port {PORT}")
        writer.write(b"Hello, server!")
        await writer.drain()

        user_task = asyncio.create_task(user_input_task(cmd_queue, stop_event))
        comms = asyncio.create_task(comms_task(reader, writer, cmd_queue, stop_event,from_ethernet_queue))
        raw_to_table = asyncio.create_task(raw_to_table_task(stop_event,from_ethernet_queue))

        await asyncio.wait([user_task, comms,raw_to_table], return_when=asyncio.FIRST_COMPLETED)
        stop_event.set()
    except ConnectionRefusedError:
        print("Connection was refused.")
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        try:
            writer.close()
            await writer.wait_closed()
        except:
            pass
        print("Connection closed.")

if __name__ == "__main__":
    asyncio.run(main())
