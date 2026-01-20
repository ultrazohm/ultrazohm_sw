import numpy as np
import pandas as pd
import glob
from scipy.stats import gaussian_kde
import matplotlib.pyplot as plt


# ------------------------------------------------------------
# Helper functions
# ------------------------------------------------------------

def get_stochastic_properties(mat):
    cols = list(range(1, mat.shape[1]))

    mean_values = [np.mean(mat[:, c]) for c in cols]
    median_values = [np.median(mat[:, c]) for c in cols]
    variance_values = [np.var(mat[:, c], ddof=1) for c in cols]
    std_values = [np.std(mat[:, c], ddof=1) for c in cols]

    return mean_values, median_values, variance_values, std_values


def get_density(mat):
    # all value columns except the index column
    cols = list(range(1, mat.shape[1]))
    
    xs = []
    ys = []

    for c in cols:
        data = mat[:, c]
        kde = gaussian_kde(data, bw_method="scott")

        x_grid = np.linspace(0, 1, 200)
        y_grid = kde(x_grid)

        xs.append(x_grid)
        ys.append(y_grid)

    return xs, ys



# ------------------------------------------------------------
# Load all files from patterns
# ------------------------------------------------------------

def load_csv_group(pattern):
    files = sorted(glob.glob(pattern))
    mats = [np.loadtxt(f, delimiter=",") for f in files]
    if len(mats) == 0:
        return None
    return np.vstack(mats)


halton_mat   = load_csv_group("density_plot_multipe_seeds_biased_uint1000/halton_seed*.csv")
pcg_mat      = load_csv_group("density_plot_multipe_seeds_biased_uint1000/pcg_seed*.csv")
squares_mat  = load_csv_group("density_plot_multipe_seeds_biased_uint1000/squares_seed*.csv")
mtwister_mat = load_csv_group("density_plot_multipe_seeds_biased_uint1000/mtwister_seed*.csv")
xoshiro_mat  = load_csv_group("density_plot_multipe_seeds_biased_uint1000/xoshiro_seed*.csv")


# ------------------------------------------------------------
# Get density plots
# ------------------------------------------------------------
halton_dx, halton_dy       = get_density(halton_mat)
pcg_dx, pcg_dy             = get_density(pcg_mat)
squares_dx, squares_dy     = get_density(squares_mat)
mtwister_dx, mtwister_dy   = get_density(mtwister_mat)
xoshiro_dx, xoshiro_dy     = get_density(xoshiro_mat)


# ------------------------------------------------------------
# Export density CSVs (example for one)
# ------------------------------------------------------------

def export_density(filename, dx, dy, prefix):
    cols = {}
    n = len(dx)   # number of available channels

    for i in range(n):
        cols[f"{prefix}_density_x_{i+1}"] = dx[i]

    for i in range(n):
        cols[f"{prefix}_density_y_{i+1}"] = dy[i]

    df = pd.DataFrame(cols)
    df.to_csv(filename, index=False)



export_density("squares_density.csv", squares_dx, squares_dy, "squares")
export_density("pcg_density.csv", pcg_dx, pcg_dy, "pcg")
export_density("mtwister_density.csv", mtwister_dx, mtwister_dy, "mtwister")
export_density("halton_density.csv", halton_dx, halton_dy, "halton")
export_density("xoshiro_density.csv", xoshiro_dx, xoshiro_dy, "xoshiro")


# ------------------------------------------------------------
# Statistical properties
# ------------------------------------------------------------

pcg_stats     = get_stochastic_properties(pcg_mat)
mtwister_stats = get_stochastic_properties(mtwister_mat)
squares_stats  = get_stochastic_properties(squares_mat)
halton_stats   = get_stochastic_properties(halton_mat)
xoshiro_stats  = get_stochastic_properties(xoshiro_mat)

df_stats = pd.DataFrame({
    "pcg_mean": pcg_stats[0],
    "pcg_median": pcg_stats[1],
    "pcg_variance": pcg_stats[2],
    "pcg_std_dev": pcg_stats[3],

    "mtwister_mean": mtwister_stats[0],
    "mtwister_median": mtwister_stats[1],
    "mtwister_variance": mtwister_stats[2],
    "mtwister_std_dev": mtwister_stats[3],

    "squares_mean": squares_stats[0],
    "squares_median": squares_stats[1],
    "squares_variance": squares_stats[2],
    "squares_std_dev": squares_stats[3],

    "halton_mean": halton_stats[0],
    "halton_median": halton_stats[1],
    "halton_variance": halton_stats[2],
    "halton_std_dev": halton_stats[3],

    "xoshiro_mean": xoshiro_stats[0],
    "xoshiro_median": xoshiro_stats[1],
    "xoshiro_variance": xoshiro_stats[2],
    "xoshiro_std_dev": xoshiro_stats[3],
})

df_stats.to_csv("prng_statistical_properties.csv", index=False)


# ------------------------------------------------------------
# Plot results
# ------------------------------------------------------------

fig, axes = plt.subplots(1, 5, figsize=(22, 4))

def plot_density(ax, dx, dy, title):
    n = len(dx)
    for i in range(n):
        ax.plot(dx[i], dy[i])
    ax.set_title(title)
    ax.grid(True)


plot_density(axes[0], mtwister_dx, mtwister_dy, "Mersenne Twister")
plot_density(axes[1], halton_dx, halton_dy, "Halton")
plot_density(axes[2], squares_dx, squares_dy, "Squares")
plot_density(axes[3], xoshiro_dx, xoshiro_dy, "Xoshiro")
plot_density(axes[4], pcg_dx, pcg_dy, "PCG")

plt.tight_layout()
plt.show()
