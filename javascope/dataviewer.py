from dash import Dash, html, dcc, callback, Output, Input, callback_context
import plotly.graph_objects as go
import pandas as pd
from plotly_resampler import FigureResampler

app = Dash(__name__)
fig = FigureResampler()
df = pd.DataFrame()


def load_dataframe(filename):
    if get_file_extension(filename) == 'parquet':
        loaded_df = pd.read_parquet(filename)
    else:
        loaded_df = pd.read_csv(filename, sep=';', low_memory=False)

    # Remove repeated header rows that may be embedded in concatenated log files.
    if 'time' in loaded_df.columns:
        loaded_df = loaded_df[loaded_df['time'].astype(str).str.strip() != 'time'].copy()

    for col in loaded_df.columns:
        loaded_df[col] = pd.to_numeric(loaded_df[col], errors='ignore')

    if 'time' in loaded_df.columns:
        loaded_df['time'] = pd.to_numeric(loaded_df['time'], errors='coerce')
        loaded_df = loaded_df.dropna(subset=['time']).copy()

    return loaded_df

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
        dcc.Graph(id='graph-content', style={'width': '100%', 'margin': '0 auto','height': '800px'})
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
    df = load_dataframe(filename)
    dropdown_options = [{'label': col, 'value': col} for col in df.columns]
    default_value = ['time'] if 'time' in df.columns else ([df.columns[0]] if dropdown_options else None)
    return dropdown_options, default_value

@app.callback(
    Output('graph-content', 'figure'),
    Input('dropdown-selection', 'value'),
    Input('upload-data', 'filename'),
    prevent_initial_call=True
)
def update_graph(value, filename):
    global fig
    global df
    fig.replace(go.Figure())  # Clear the existing figure
    if value and 'time' in df.columns:
        for col in value:
            if col == 'time' or col not in df.columns:
                continue
            plot_df = df[['time', col]].copy()
            plot_df[col] = pd.to_numeric(plot_df[col], errors='coerce')
            plot_df = plot_df.dropna(subset=['time', col])
            if plot_df.empty:
                continue
            fig.add_trace(go.Scattergl(name=col, x=plot_df['time'], y=plot_df[col]))

    fig.update_layout(template="simple_white", xaxis=dict(showgrid=True), yaxis=dict(showgrid=True))

    return fig

fig.register_update_graph_callback(app=app, graph_id="graph-content")

def get_file_extension(filename):
    # Split the filename by dot
    parts = filename.split('.')
    
    # If there's only one part, there's no extension
    if len(parts) == 1:
        return None
    
    # Otherwise, return the last part
    return parts[-1]

if __name__ == '__main__':
    app.run(debug=True)
