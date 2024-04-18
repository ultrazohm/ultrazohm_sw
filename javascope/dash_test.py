from dash import Dash, html, dcc, callback, Output, Input
import plotly.express as px
import pandas as pd
import plotly.graph_objects as go;
import numpy as np
from plotly_resampler import register_plotly_resampler
from plotly_resampler import FigureResampler, FigureWidgetResampler

df=pd.read_parquet('Log_2024-04-17_17-17-02.parquet')

app = Dash(__name__)
register_plotly_resampler(mode='auto')
fig = FigureResampler(px.line(df, x='time', y='time'))

app.layout = html.Div([
    html.H1(children='Title of Dash App', style={'textAlign':'center'}),
    dcc.Dropdown(df.columns.values.tolist(), 'time', id='dropdown-selection'),
    dcc.Graph(id='graph-content')
])

@callback(
    Output('graph-content', 'figure'),
    Input('dropdown-selection', 'value')
)
def update_graph(value):
    # dff = df.iloc[:, value]
    return px.line(df, x='time', y=value)
    # return fig.add_trace({"x": df.time,"y":df.iloc[:, 1]})


if __name__ == '__main__':
    app.run(debug=True)
