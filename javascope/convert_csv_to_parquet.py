import os
import pandas as pd


def _normalize_column(series: pd.Series) -> pd.Series:
    if pd.api.types.is_numeric_dtype(series):
        return series

    cleaned = series.astype(str).str.strip()
    cleaned = cleaned.replace({"": pd.NA, "nan": pd.NA, "None": pd.NA})

    numeric = pd.to_numeric(cleaned, errors="coerce")
    non_na_count = cleaned.notna().sum()
    numeric_count = numeric.notna().sum()

    # Treat columns as numeric when almost all non-empty values are numbers.
    if non_na_count > 0 and numeric_count >= int(0.9 * non_na_count):
        return numeric

    return cleaned

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
    
    # Read the CSV file into a pandas DataFrame and normalize mixed-type columns
    df = pd.read_csv(
        os.path.join(csv_directory, csv_file),
        sep=';',
        low_memory=False
    )
    df = df.apply(_normalize_column)
    
    # Convert the DataFrame to Parquet format and save it
    df.to_parquet(parquet_path)

    print(f"{csv_file} converted to {parquet_file}")
