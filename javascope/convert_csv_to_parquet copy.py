import os
import pandas as pd

# Define a list of CSV filenames to be converted
# csv_filenames = [
#     'ebm_foc_real_flux_prediction_3.csv',
#     'ebm_foc_real_flux_prediction_2.csv',
#     'ebm_foc_real_flux_prediction.csv',
#     'ebm_foc_real_linear_decoupling_3.csv',
#     'ebm_foc_real_linear_decoupling_2.csv',
#     'ebm_foc_real_linear_decoupling.csv',
# ]

csv_filenames = [
    # 'brose_foc_real_10a_flux_decoupling.csv',
    # 'brose_foc_real_10a_linear_decoupling.csv',
    # "buehler_fixed_current_a289_cil.csv",
    # "buehler_fixed_current_a255_cil.csv"
    # "buehler_fixed_current_a234_cil.csv",
    # "buehler_fixed_current_a221_cil.csv",
    # "buehler_fixed_current_a255_real",
    # "buehler_fixed_current_a221_real.csv",
    # "brose_fixed_observation_a252_cil.csv",
    "d1_current_a.csv",
    # "buehler_fixed_observation_foc_cil.csv",
]


# 'brose_fixed_observation_a287_real'
# 'brose_fixed_observation_foc_real'
# 'brose_fixed_observation_a287_cil'
# 'brose_fixed_observation_a252_real'
# 'brose_fixed_observation_a211_cil'
# 'brose_fixed_observation_foc_cil'
# 'brose_fixed_observation_a211_real'
# 'brose_fixed_observation_a252_cil'
# 'brose_fixed_observation_a214_cil'

# Get the current directory
current_directory = os.getcwd()

# Define the directory containing CSV files (current directory)
csv_directory = current_directory
# csv_filenames = [file for file in os.listdir(csv_directory) if file.startswith("brose_fixed_observation_")]

# Loop over each filename in the list
for csv_filename in csv_filenames:
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(csv_filename, sep=";")
    # Clean up the column names
    df.columns = [col.split("=")[-1] if "=" in col else col for col in df.columns]

    # Optionally, replace any unwanted characters (like trailing numbers or parentheses)
    df.columns = [col.split(")")[1] if ")" in col else col for col in df.columns]

    # Drop the last column if it is empty (due to trailing ";")
    df.drop(df.columns[len(df.columns)-1], axis=1, inplace=True)
    
    # Create the output filename by replacing '.csv' with '.parquet'
    parquet_filename = csv_filename.replace('.csv', '.parquet')
    
    # Convert the DataFrame to Parquet format and save it
    df.to_parquet(parquet_filename)
    
    print(f"Converted {csv_filename} to {parquet_filename}")
