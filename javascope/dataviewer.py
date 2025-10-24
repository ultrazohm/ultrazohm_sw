from dash import Dash, html, dcc, callback, Output, Input, callback_context
import plotly.graph_objects as go
import pandas as pd
from plotly_resampler import FigureResampler

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
    filetype=get_file_extension(filename)
    if filetype=='parquet':
        df = pd.read_parquet(filename)
    else:
        df = pd.read_csv(filename,sep=';')
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
    if value:
        for col in value:
            fig.add_trace(go.Scattergl(name=col, x=df['time'], y=df[col]))

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
    app.run_server(debug=True)
