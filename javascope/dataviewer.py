import plotly.express as px
import plotly.graph_objects as go;
import numpy as np
from plotly_resampler import register_plotly_resampler

import pandas as pd

# https://github.com/predict-idlab/plotly-resampler
register_plotly_resampler(mode='auto')

df=pd.read_parquet('Log_2024-04-17_17-17-02.parquet')
# fig=px.line(df,x="time",y=df.iloc[:, 1])

f = go.Figure()
f.add_trace({"x": df.time,"y":df.iloc[:, 1]})
f.add_trace({"x": df.time,"y":df.iloc[:, 2]})
f.add_trace({"x": df.time,"y":df.iloc[:, 3]})
f.add_trace({"x": df.time,"y":df.iloc[:, 4]})
f.add_trace({"x": df.time,"y":df.iloc[:, 5]})
f.add_trace({"x": df.time,"y":df.iloc[:, 6]})
f.add_trace({"x": df.time,"y":df.iloc[:, 7]})
f.add_trace({"x": df.time,"y":df.iloc[:, 8]})
f.add_trace({"x": df.time,"y":df.iloc[:, 9]})
f.add_trace({"x": df.time,"y":df.iloc[:, 11]})
f.add_trace({"x": df.time,"y":df.iloc[:, 12]})
f.add_trace({"x": df.time,"y":df.iloc[:, 13]})
f.add_trace({"x": df.time,"y":df.iloc[:, 14]})
f.add_trace({"x": df.time,"y":df.iloc[:, 15]})
f.add_trace({"x": df.time,"y":df.iloc[:, 16]})
f.add_trace({"x": df.time,"y":df.iloc[:, 17]})
f.add_trace({"x": df.time,"y":df.iloc[:, 18]})
f.add_trace({"x": df.time,"y":df.iloc[:, 19]})
f.add_trace({"x": df.time,"y":df.iloc[:, 20]})
f.update_layout(height=1200)
f.show_dash()