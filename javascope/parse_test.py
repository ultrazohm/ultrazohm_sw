import pandas as pd
from pathlib import Path


def parse_enum_to_dataframe(file_path, enum_name):
    with open(file_path, "r") as file:
        lines = file.readlines()

    enum_start = False
    enum_entries = []
    current_value = 0

    for line in lines:
        line = line.strip()
        if line.startswith(f"enum {enum_name}"):
            enum_start = True
            continue
        if enum_start:
            if line.startswith("};"):
                break
            if line.startswith("{") or line.startswith("}"):
                continue
            if line and not line.startswith("//"):
                entry = line.split(",")[0].strip()
                if "=" in entry:
                    name, value = entry.split("=")
                    name = name.strip()
                    current_value = int(value.strip())
                else:
                    name = entry
                enum_entries.append((name, current_value))
                current_value += 1

    # Create a DataFrame
    df_enum = pd.DataFrame(enum_entries, columns=["name", "number"])

    return df_enum


# Use pathlib to handle file paths
file_path = Path("../vitis/software/Baremetal/src/include/javascope.h").resolve()
enum_name = "JS_OberservableData"
df = parse_enum_to_dataframe(file_path, enum_name)
print(df)
