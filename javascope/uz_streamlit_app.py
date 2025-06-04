import streamlit as st
import numpy as np
import pandas as pd
from uz_class_threads import ultrazohm

st.set_page_config(page_title="UltraZohm Streamlit App", layout="wide")
st.title("UltraZohm Control & Scope Viewer")

# Session state for persistent objects
def get_uz():
    if 'uz' not in st.session_state:
        st.session_state.uz = None
    return st.session_state.uz

def set_uz(uz):
    st.session_state.uz = uz

def get_connected():
    return st.session_state.get('connected', False)

def set_connected(val):
    st.session_state['connected'] = val

def get_comm():
    return st.session_state.get('comm', False)

def set_comm(val):
    st.session_state['comm'] = val

# UI controls
col1, col2 = st.columns(2)

with col1:
    ip = st.text_input("IP Address", value="127.0.0.1")
    port = st.number_input("Port", value=1000, step=1)
    if st.button("Connect"):
        uz = ultrazohm(ip=ip, port=int(port), cmd_queue_size=10, from_ethernet_queue_size=10, max_buffer_size=10000)
        uz.connect()
        set_uz(uz)
        set_connected(True)
        st.success(f"Connected to {ip}:{port}")

    if get_connected():
        if st.button("Create Logfile (fast)"):
            uz = get_uz()
            uz.create_logfile_fast()
            st.success(f"Created logfile: {uz.logfile_fast_name}")
        if st.button("Enable Fast Log"):
            uz = get_uz()
            uz.log_fast(True)
            st.success("Fast logging enabled.")
        if st.button("Start Communication"):
            uz = get_uz()
            uz.start_communication(True)
            set_comm(True)
            st.success("Communication started.")
        if st.button("Stop Communication"):
            uz = get_uz()
            uz.start_communication(False)
            set_comm(False)
            st.info("Communication stopped.")
        if st.button("Disconnect"):
            uz = get_uz()
            uz.disconnect()
            set_connected(False)
            set_comm(False)
            set_uz(None)
            st.info("Disconnected.")

with col2:
    st.write("### Scope Buffer Plot")
    if get_connected():
        if st.button("Refresh Scope Data & Plot"):
            uz = get_uz()
            data = uz.get_scope_buffer_data()
            if data:
                arr = np.array(data)
                st.write(f"Scope buffer shape: {arr.shape}")
                import plotly.graph_objs as go
                import plotly.colors
                fig = go.Figure()
                n_channels = arr.shape[1] if arr.ndim > 1 else 1
                if n_channels == 1:
                    fig.add_trace(go.Scatter(y=arr.flatten(), mode='lines', name='Ch 0'))
                else:
                    for i in range(n_channels):
                        fig.add_trace(go.Scatter(y=arr[:, i], mode='lines', name=f'Ch {i}'))
                fig.update_layout(
                    xaxis_title='Time step',
                    yaxis_title='Channel value',
                    title='UltraZohm Scope Buffer Data',
                    legend=dict(orientation="h", yanchor="bottom", y=1.02, xanchor="right", x=1),
                    height=500,
                )
                st.plotly_chart(fig, use_container_width=True)
            else:
                st.warning("No scope buffer data available.")
        else:
            st.info("Click 'Refresh Scope Data & Plot' to update plot.")
    else:
        st.info("Connect to UltraZohm to enable plotting.")
