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

            # example:
            # send 201, 29 -> observe test variable
            # send 27, 0.5 -> observe test variable
            # variable changes to 0.5 on rpu and is read back from ethernet
            # set 1,0 -> led starts blinking faster
            # set 3,0 -> led blinks slower

            # Commands as per ipc_Control_func.c in baremetal:
            # id,value,command
            # 3,x,stop
            # 201,variable number, set variable number to channel 1
            # 202,variable number, set variable number to channel 2
            # 203,variable number, set variable number to channel 3
            # 204,variable number, set variable number to channel 4
            # 205,variable number, set variable number to channel 5
            # 206,variable number, set variable number to channel 6
            # 207,variable number, set variable number to channel 7
            # 208,variable number, set variable number to channel 8
            # 209,variable number, set variable number to channel 9
            # 210,variable number, set variable number to channel 10
            # 211,variable number, set variable number to channel 11
            # 212,variable number, set variable number to channel 12
            # 213,variable number, set variable number to channel 13
            # 214,variable number, set variable number to channel 14
            # 215,variable number, set variable number to channel 15
            # 216,variable number, set variable number to channel 16
            # 217,variable number, set variable number to channel 17
            # 218,variable number, set variable number to channel 18
            # 219,variable number, set variable number to channel 19
            # 220,variable number, set variable number to channel 20
            # 1,x,enable system
            # 2,x,enable control
            # 4,variable value, Set_Send_Field_1
            # 5,variable value, Set_Send_Field_2
            # 23,variable value, Set_Send_Field_20
            # 24,x, My_Button_1 (set error)
            # 27,variable value, My_Button_4 (test variable)

            # Javascope data:
            # enum JS_OberservableData {
            # 0    JSO_ZEROVALUE=0,
            # 1    JSO_ISR_ExecTime_us,
            # 2    JSO_ISR_Period_us,
            # 3    JSO_lifecheck,
            # 4    JSO_theta_mech,
            # 5    JSO_ua,
            # 6    JSO_ub,
            # 7    JSO_uc,
            # 8    JSO_ia,
            # 9    JSO_ib,
            # 10    JSO_ic,
            # 11    JSO_id,
            # 12    JSO_iq,
            # 13    JSO_ud,
            # 14    JSO_uq,
            # 15    JSO_Speed_rpm,
            # 16    JSO_el_Speed_rpm,
            # 17    JSO_LoadSpeed_rpm,
            # 18    JSO_volt_temp,
            # 19    JSO_SoC_init,
            # 20    JSO_Theta_el,
            # 21    JSO_Theta_mech,
            # 22    JSO_LoadTheta_mech,
            # 23    JSO_DeltaTheta_mech,
            # 24    JSO_Wtemp,
            # 25    JSO_Rs_mOhm,
            # 26    JSO_Ld_mH,
            # 27    JSO_Lq_mH,
            # 28    JSO_PsiPM_mVs,
            # 29    JSO_python_test_loopback,
            #     JSO_ENDMARKER
            # };

            id_input = int(input("Enter an ID (unsigned int32): ")) # Send 27 for setting test variable and 29 beforehand to observe it . 201,202,203 are the channel numbers. I.e., id=201, value=29 -> test variable is written to channel 1. Lifecheck is variable=3.
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
