import os
import pandas as pd

# Get the current directory
current_directory = os.getcwd()

# Define the directory containing CSV files (current directory)
csv_directory = current_directory

# Define the directory to save Parquet files (current directory)
parquet_directory = current_directory

# Get a list of all CSV files in the directory
csv_files = [file for file in os.listdir(csv_directory) if file.endswith('.csv')]

# Loop through each CSV file
for csv_file in csv_files:
    # Define the filename for the Parquet file
    parquet_file = os.path.splitext(csv_file)[0] + '.parquet'
    
    # Define the full path for saving the Parquet file
    parquet_path = os.path.join(parquet_directory, parquet_file)
    
    # Check if the Parquet file already exists
    if os.path.exists(parquet_path):
        print(f"{parquet_file} already exists. Skipping conversion of {csv_file}")
        continue
    
    # Read the CSV file into a pandas DataFrame
    df = pd.read_csv(os.path.join(csv_directory, csv_file),sep=';')
    
    # Convert the DataFrame to Parquet format and save it
    df.to_parquet(parquet_path)

    print(f"{csv_file} converted to {parquet_file}")