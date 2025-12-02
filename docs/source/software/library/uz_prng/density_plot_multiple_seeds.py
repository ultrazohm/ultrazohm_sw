import numpy as np
import pandas as pd
import glob
from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt


# ============================================================
# Helper functions taken from the second script
# ============================================================

def load_csv_group(pattern):
    """Loads all CSV files matching the pattern and vertically stacks them."""
    files = sorted(glob.glob(pattern))
    mats = [np.loadtxt(f, delimiter=",") for f in files]
    if len(mats) == 0:
        return None
    return np.vstack(mats)


def get_density(mat):
    """Computes kernel-density estimations for all columns except column 0."""
    cols = list(range(1, mat.shape[1]))
    
    xs, ys = [], []

    for c in cols:
        data = mat[:, c]
        kde = gaussian_kde(data, bw_method="scott")

        x_grid = np.linspace(0, 1, 200)
        y_grid = kde(x_grid)

        xs.append(x_grid)
        ys.append(y_grid)

    return xs, ys


# ============================================================
# Function that replaces "read_csv" in density_plot_multiple_seeds
# ============================================================

def load_density_from_seeds(folder_path, prefix):
    """
    Instead of reading a precomputed CSV, compute the density directly
    from all seed files in the folder.
    """
    pattern = f"{folder_path}/{prefix}_seed*.csv"
    mat = load_csv_group(pattern)

    if mat is None:
        raise ValueError(f"No files found for {pattern}")

    dx, dy = get_density(mat)

    # Return a structure similar to the DataFrame from the original CSV
    # but wrapped in a dict so that attribute access remains simple.
    result = {}
    for i in range(len(dx)):
        result[f"{prefix}_density_x_{i+1}"] = dx[i]
        result[f"{prefix}_density_y_{i+1}"] = dy[i]

    return result


# ============================================================
# Load all PRNG families using the new function
# ============================================================

folder = "density_plot_multipe_seeds_biased_uint1000"

mtwister = load_density_from_seeds(folder, "mtwister")
halton   = load_density_from_seeds(folder, "halton")
squares  = load_density_from_seeds(folder, "squares")
xoshiro  = load_density_from_seeds(folder, "xoshiro")
pcg      = load_density_from_seeds(folder, "pcg")


# ============================================================
# Plot (same layout as in the FIRST SCRIPT)
# ============================================================

fig, axs = plt.subplots(1, 5, layout="constrained")

def plot_family(ax, prefix, data_dict):
    ax.set_title(prefix.capitalize())
    i = 1
    while f"{prefix}_density_x_{i}" in data_dict:
        ax.plot(data_dict[f"{prefix}_density_x_{i}"],
                data_dict[f"{prefix}_density_y_{i}"])
        i += 1
    ax.grid(True, which="both")
    ax.set_ylim(0.85, 1.15)


plot_family(axs[0], "mtwister", mtwister)
plot_family(axs[1], "halton", halton)
plot_family(axs[2], "squares", squares)
plot_family(axs[3], "xoshiro", xoshiro)
plot_family(axs[4], "pcg", pcg)

plt.show()
