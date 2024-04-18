from dash import Dash, html, dcc, callback, Output, Input, callback_context
import plotly.graph_objects as go
import pandas as pd
from plotly_resampler import FigureResampler

app = Dash(__name__)
fig = FigureResampler()

app.layout = html.Div([
    html.H1(children='UltraZohm data viewer', style={'textAlign': 'center'}),
    dcc.Upload(
        id='upload-data',
        children=html.Button('Select File')
    ),
    dcc.Dropdown(
        id='dropdown-selection',
        multi=True,
        clearable=False
    ),
    dcc.Graph(id='graph-content')
])

@app.callback(
    Output('dropdown-selection', 'options'),
    Output('dropdown-selection', 'value'),
    Input('upload-data', 'filename'),
    prevent_initial_call=True
)
def update_options(filename):
    df = pd.read_parquet(filename)
    dropdown_options = [{'label': col, 'value': col} for col in df.columns]
    return dropdown_options, [df.columns[0]]  # Select the first column by default

@app.callback(
    Output('graph-content', 'figure'),
    Input('dropdown-selection', 'value'),
    Input('upload-data', 'filename'),
    prevent_initial_call=True
)
def update_graph(value, filename):
    global fig
    df = pd.read_parquet(filename)
    fig.replace(go.Figure())  # Clear the existing figure
    for col in value:
        fig.add_trace(go.Scattergl(name=col, x=df['time'], y=df[col]))

    fig.update_layout(template="simple_white")
    fig.update_layout(xaxis=dict(showgrid=True), yaxis=dict(showgrid=True))

    return fig

fig.register_update_graph_callback(app=app, graph_id="graph-content")


if __name__ == '__main__':
    app.run_server(debug=True)
