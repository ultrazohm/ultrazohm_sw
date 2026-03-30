from uz_class_threads import ultrazohm
import time
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

def main():
    # Create an instance of ultrazohm (adjust IP/port as needed)
    uz = ultrazohm(ip='127.0.0.1', port=1000, cmd_queue_size=10, from_ethernet_queue_size=10, max_buffer_size=10000)
    uz.connect()
    print("Connected to UltraZohm.")
    uz.log_fast(True)  # Enable fast logging
    uz.start_communication(True, debug=False)
    time.sleep(1)  # Let it run for a bit
    uz.start_communication(False)

    data = uz.get_scope_buffer_data()
    if not data:
        print("No scope buffer data available.")
        return
    
    uz.disconnect()
    print("Disconnected.")

    arr = np.array(data)
    print(f"Scope buffer shape: {arr.shape}")
    # Save to debug.csv
    pd.DataFrame(arr).to_csv("debug.csv", header=False, index=False)
    print("Scope buffer data written to debug.csv")
    # Plot: each column is a channel, each row is a time step
    plt.figure(figsize=(10, 6))
    plt.plot(arr)
    plt.xlabel('Time step')
    plt.ylabel('Channel value')
    plt.title('UltraZohm Scope Buffer Data')
    plt.legend([f'Ch {i}' for i in range(arr.shape[1])], loc='upper right', fontsize='small')
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
