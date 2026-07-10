import pandas as pd

input_file = "Log_2026-07-10_15-31-13.csv"
output_file = "output_data.csv"

data = pd.read_csv(input_file, sep=";")
output_data = data.loc[data["CH1=50)DQN_PT1_EVAL_PROFILE_EPISODE"] != 0]
output_data['time'] = output_data['time']*10000 # Make time to step k to match ceedling and python

output_data.to_csv(
    output_file,
    sep=";",
    index=False,
)