from dash import Dash, html, dcc, callback, Output, Input, callback_context, no_update
import plotly.express as px
import pandas as pd
import plotly.graph_objects as go;
import numpy as np
from plotly_resampler import FigureResampler

df=pd.read_parquet('Log_2024-04-17_17-17-02.parquet')

app = Dash(__name__)
fig: FigureResampler = FigureResampler()

app.layout = html.Div([
    html.H1(children='UltraZohm data viewer', style={'textAlign':'center'}),
    dcc.Dropdown(df.columns.values.tolist(), 'time', id='dropdown-selection',multi=True,clearable=False),
    dcc.Graph(id='graph-content')
])

@callback(
    Output('graph-content', 'figure'),
    Input('dropdown-selection', 'value')
)
def update_graph(value):
    ctx = callback_context
    global fig
    if value:
        if len(fig.data):
           # Replace the figure with an empty one to clear the graph
           fig.replace(go.Figure())
        # dff = df.iloc[:, value]
        # return px.line(df, x='time', y=value)
        # return fig.add_trace({"x": df.time,"y":df.iloc[:, 1]})
        # for x in value:
        # index=value[0]
        if isinstance(value, list):
            # Access the first element of the list
            first_element = value[0]
            for x in value:
                fig.add_trace(go.Scattergl(name="exp"), hf_x=df.time, hf_y=df[x])

        elif isinstance(value, str):
            # If the variable is a string, just assign it to first_element
            first_element = value
            fig.add_trace(go.Scattergl(name="exp"), hf_x=df.time, hf_y=df[first_element])

        fig.update_layout(template="simple_white")
        fig.update_layout(
            xaxis=dict(showgrid=True), 
            yaxis=dict(showgrid=True)
        )
    else:
        fig.data=[]
    
    
    return fig

fig.register_update_graph_callback(app=app, graph_id="graph-content")

if __name__ == '__main__':
    app.run(debug=True)
