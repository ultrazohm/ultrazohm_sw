# Run from this directory in an isolated Python environment.
# PyGWalker uses the Tornado server API from Streamlit before 1.57.
# uv run --no-project --python 3.12 --with 'pygwalker>=0.5.0.1' \
#   --with 'streamlit<1.57' streamlit run pywalker_test.py
from pygwalker.api.streamlit import StreamlitRenderer
import pandas as pd
import streamlit as st

# Adjust the width of the Streamlit page
st.set_page_config(
    page_title="Use Pygwalker In Streamlit",
    layout="wide"
)

# Add Title
st.title("Use Pygwalker In Streamlit")

# You should cache your pygwalker renderer, if you don't want your memory to explode
@st.cache_resource
def get_pyg_renderer() -> "StreamlitRenderer":
    df=pd.read_parquet('Log_2024-04-17_17-17-02.parquet')
    
    # If you want to use feature of saving chart config, set `spec_io_mode="rw"`
    return StreamlitRenderer(df, spec="./gw_config.json", spec_io_mode="rw")


renderer = get_pyg_renderer()

renderer.explorer()