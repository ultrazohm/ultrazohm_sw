import dash
from dash import dcc, html, Output, Input, State
import plotly.graph_objs as go
import numpy as np
import threading
import time
from uz_class_threads import ultrazohm

# Shared state
uz = None
connected = False
comm_active = False
plot_mutex = threading.Lock()

# Streaming buffer for plotting (thread-safe)
stream_buffer = {
    'x': [],  # sample indices
    'y': []   # list of lists, one per channel
}
stream_buffer_size = 1000  # Number of points to keep in the plot

fetch_thread = None
fetch_thread_stop = threading.Event()

def fetch_data_loop():
    global uz, comm_active, stream_buffer
    while not fetch_thread_stop.is_set():
        try:
            if uz and comm_active:
                print('[DEBUG] Fetching data...')
                data = uz.get_scope_buffer_data()
                arr = np.array(data) if data is not None and len(data) else np.zeros((1, 1))
                with plot_mutex:
                    if arr.size > 1:
                        n_samples, n_channels = arr.shape
                        if not stream_buffer['y'] or len(stream_buffer['y']) != n_channels:
                            stream_buffer['x'] = []
                            stream_buffer['y'] = [[] for _ in range(n_channels)]
                        start_idx = stream_buffer['x'][-1] + 1 if stream_buffer['x'] else 0
                        for i in range(n_samples):
                            stream_buffer['x'].append(start_idx + i)
                            for ch in range(n_channels):
                                stream_buffer['y'][ch].append(arr[i, ch])
                        if len(stream_buffer['x']) > stream_buffer_size:
                            trim = len(stream_buffer['x']) - stream_buffer_size
                            stream_buffer['x'] = stream_buffer['x'][trim:]
                            for ch in range(n_channels):
                                stream_buffer['y'][ch] = stream_buffer['y'][ch][trim:]
            else:
                time.sleep(0.05)
        except Exception as e:
            print(f"Background thread error: {e}")
            time.sleep(0.1)

def start_fetch_thread():
    global fetch_thread
    if fetch_thread is None or not fetch_thread.is_alive():
        fetch_thread_stop.clear()
        fetch_thread = threading.Thread(target=fetch_data_loop, daemon=True)
        fetch_thread.start()
        print('[DEBUG] Fetch thread started')

def stop_fetch_thread():
    fetch_thread_stop.set()
    print('[DEBUG] Fetch thread stop signal sent')

app = dash.Dash(__name__)

app.layout = html.Div([
    html.H2("UltraZohm PyScope (Dash)"),
    html.Div([
        html.Label("IP:"),
        dcc.Input(id='ip_input', value='127.0.0.1', type='text'),
        html.Label("Port:"),
        dcc.Input(id='port_input', value=1000, type='number'),
        html.Button('Connect', id='connect_btn', n_clicks=0),
        html.Button('Disconnect', id='disconnect_btn', n_clicks=0),
        html.Button('Start Communication', id='comm_toggle', n_clicks=0, style={'backgroundColor': 'red'}),
        html.Button('Log Fast', id='log_fast_btn', n_clicks=0),
        html.Button('Log Slow', id='log_slow_btn', n_clicks=0),
        html.Br(),
        html.Label("Command ID:"),
        dcc.Input(id='cmd_id', value=0, type='number'),
        html.Label("Command Value:"),
        dcc.Input(id='cmd_value', value=0.0, type='number'),
        html.Button('Set Command', id='set_cmd_btn', n_clicks=0),
        html.Button('Set Command Skip Queue', id='set_cmd_skip_btn', n_clicks=0),
        html.Button('Create Logfile Fast', id='create_logfile_fast_btn', n_clicks=0),
        html.Button('Create Logfile Slow', id='create_logfile_slow_btn', n_clicks=0),
        html.Button('Get Scope Buffer Data', id='get_scope_buffer_btn', n_clicks=0),
    ], style={'display': 'flex', 'flexDirection': 'column', 'width': '300px'}),
    html.Div(id='log_window', style={'whiteSpace': 'pre-line', 'border': '1px solid #ccc', 'height': '200px', 'overflowY': 'scroll', 'marginTop': '10px'}),
    dcc.Graph(id='scope_plot', config={'responsive': True}),
    dcc.Interval(id='interval', interval=50, n_intervals=0)  # 20 Hz
])

@app.callback(
    Output('log_window', 'children'),
    Output('comm_toggle', 'style'),
    Input('connect_btn', 'n_clicks'),
    Input('disconnect_btn', 'n_clicks'),
    Input('comm_toggle', 'n_clicks'),
    Input('log_fast_btn', 'n_clicks'),
    Input('log_slow_btn', 'n_clicks'),
    Input('set_cmd_btn', 'n_clicks'),
    Input('set_cmd_skip_btn', 'n_clicks'),
    Input('create_logfile_fast_btn', 'n_clicks'),
    Input('create_logfile_slow_btn', 'n_clicks'),
    Input('get_scope_buffer_btn', 'n_clicks'),
    State('ip_input', 'value'),
    State('port_input', 'value'),
    State('cmd_id', 'value'),
    State('cmd_value', 'value'),
    prevent_initial_call=True
)
def handle_buttons(connect, disconnect, comm_toggle, log_fast, log_slow, set_cmd, set_cmd_skip, create_logfile_fast, create_logfile_slow, get_scope_buffer, ip, port, cmd_id, cmd_value):
    global uz, connected, comm_active
    ctx = dash.callback_context
    log = ""
    style = {'backgroundColor': 'red'}
    if not ctx.triggered:
        return dash.no_update, style
    button_id = ctx.triggered[0]['prop_id'].split('.')[0]
    try:
        if button_id == 'connect_btn':
            if not connected:
                uz = ultrazohm(ip=ip, port=int(port),debug=True)
                uz.connect()
                connected = True
                log = "Connected."
                start_fetch_thread()
            else:
                log = "Already connected."
        elif button_id == 'disconnect_btn':
            if uz:
                uz.disconnect()
                connected = False
                comm_active = False
                log = "Disconnected."
                stop_fetch_thread()
        elif button_id == 'comm_toggle':
            if uz:
                comm_active = not comm_active
                uz.start_communication(comm_active)
                log = f"Communication {'started' if comm_active else 'stopped'}."
                style = {'backgroundColor': 'green' if comm_active else 'red'}
            else:
                log = "Not connected."
        elif button_id == 'log_fast_btn':
            if uz:
                uz.log_fast(True)
                log = "Fast logging enabled."
        elif button_id == 'log_slow_btn':
            if uz:
                uz.log_slow(True)
                log = "Slow logging enabled."
        elif button_id == 'set_cmd_btn':
            if uz:
                uz.set_command(int(cmd_id), float(cmd_value))
                log = f"set_command({cmd_id}, {cmd_value}) sent."
        elif button_id == 'set_cmd_skip_btn':
            if uz:
                uz.set_command_skip_queue(int(cmd_id), float(cmd_value))
                log = f"set_command_skip_queue({cmd_id}, {cmd_value}) sent."
        elif button_id == 'create_logfile_fast_btn':
            if uz:
                uz.create_logfile_fast()
                log = f"Fast logfile created: {uz.logfile_fast_name}"
        elif button_id == 'create_logfile_slow_btn':
            if uz:
                uz.create_logfile_slow()
                log = f"Slow logfile created: {uz.logfile_slow_name}"
        elif button_id == 'get_scope_buffer_btn':
            if uz:
                data = uz.get_scope_buffer_data()
                log = f"Scope buffer data: {data}"
    except Exception as e:
        log = f"Error: {e}"
    return log, style

@app.callback(
    Output('scope_plot', 'figure'),
    Input('interval', 'n_intervals')
)
def update_plot(n):
    with plot_mutex:
        x = stream_buffer['x'].copy()
        y_list = [ch.copy() for ch in stream_buffer['y']]
    fig = go.Figure()
    if x and y_list:
        for ch, y in enumerate(y_list):
            fig.add_trace(go.Scatter(x=x, y=y, mode='lines', name=f'Ch {ch}'))
        fig.update_layout(title='UltraZohm Scope Buffer Data (Streaming)', xaxis_title='Sample Index', yaxis_title='Channel value')
    else:
        fig.update_layout(title='UltraZohm Scope Buffer Data (Streaming)', xaxis_title='Sample Index', yaxis_title='Channel value')
    return fig

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0')