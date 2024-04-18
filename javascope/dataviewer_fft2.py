from dash import Dash, html, dcc, callback, Output, Input, callback_context
import plotly.graph_objects as go
import pandas as pd
from plotly_resampler import FigureResampler
import numpy as np
from scipy.fft import fft

app = Dash(__name__)
fig = FigureResampler()

app.layout = html.Div([
    html.H1(children='UltraZohm Data Viewer', style={'textAlign': 'center'}),
    html.Div([
        dcc.Upload(
            id='upload-data',
            children=html.Button('Upload File', style={'background-color': '#4CAF50', 'color': 'white', 'border': 'none', 'padding': '10px 20px', 'text-align': 'center', 'text-decoration': 'none', 'display': 'inline-block', 'font-size': '16px', 'cursor': 'pointer', 'border-radius': '5px'}),
            style={'margin': 'auto', 'textAlign': 'center'}
        ),
    ], style={'width': '80%', 'margin': '20px auto'}),
    html.Div([
        dcc.Dropdown(
            id='dropdown-selection',
            multi=True,
            clearable=False,
            style={'width': '100%', 'margin': '20px auto'}
        ),
        dcc.Graph(id='graph-content', style={'width': '100%', 'margin': '0 auto'}),
        html.Div([
            dcc.Dropdown(
                id='fft-dropdown-selection',
                multi=True,
                clearable=False,
                style={'width': '100%', 'margin': '20px auto'}
            ),
            dcc.Graph(id='fft-content', style={'width': '100%', 'margin': '0 auto'})
        ])
    ], style={'width': '90%', 'margin': 'auto'})
], style={'max-width': '10000px', 'margin': '0 auto', 'padding': '20px'})

@app.callback(
    Output('dropdown-selection', 'options'),
    Output('dropdown-selection', 'value'),
    Input('upload-data', 'filename'),
    prevent_initial_call=True
)
def update_options(filename):
    global df 
    df = pd.read_parquet(filename)
    dropdown_options = [{'label': col, 'value': col} for col in df.columns]
    return dropdown_options, [df.columns[0]] if dropdown_options else None  # Select the first column by default if options available

@app.callback(
    Output('graph-content', 'figure'),
    Input('dropdown-selection', 'value'),
    Input('upload-data', 'filename'),
    prevent_initial_call=True
)
def update_graph(value, filename):
    global fig
    global df
    # df = pd.read_parquet(filename)
    fig.replace(go.Figure())  # Clear the existing figure
    fft_fig = go.Figure()

    if value:
        for col in value:
            fig.add_trace(go.Scattergl(name=col, x=df['time'], y=df[col]))

            # Calculate FFT
            signal = np.array(df[col])
            sampling_freq = 1 / (df['time'][1] - df['time'][0])  # Calculate sampling frequency
            freqs = np.fft.fftfreq(len(signal), d=1/sampling_freq)
            fft_vals = np.abs(fft(signal))

            fft_fig.add_trace(go.Scattergl(name=f'{col} FFT', x=freqs[:len(freqs)//2], y=fft_vals[:len(freqs)//2]))

        fig.update_layout(template="simple_white", xaxis=dict(showgrid=True), yaxis=dict(showgrid=True))
        fft_fig.update_layout(template="simple_white", xaxis=dict(showgrid=True), yaxis=dict(showgrid=True))

    return fig

@app.callback(
    Output('fft-content', 'figure'),
    Input('fft-dropdown-selection', 'value'),
    prevent_initial_call=True
)
def update_fft_graph(value):
    global df
    fft_fig = go.Figure()

    if value:
        for col in value:
            # Calculate FFT
            signal = np.array(df[col])
            sampling_freq = 1 / (df['time'][1] - df['time'][0])  # Calculate sampling frequency
            freqs = np.fft.fftfreq(len(signal), d=1/sampling_freq)
            fft_vals = np.abs(fft(signal))

            fft_fig.add_trace(go.Scattergl(name=f'{col} FFT', x=freqs[:len(freqs)//2], y=fft_vals[:len(freqs)//2]))

        fft_fig.update_layout(template="simple_white", xaxis=dict(showgrid=True), yaxis=dict(showgrid=True))
        fft_fig.update_layout(title='FFT')

    return fft_fig

fig.register_update_graph_callback(app=app, graph_id="graph-content")

if __name__ == '__main__':
    app.run_server(debug=True)
