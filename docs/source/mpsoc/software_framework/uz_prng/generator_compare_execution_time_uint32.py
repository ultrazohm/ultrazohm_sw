import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.ticker import AutoMinorLocator, MultipleLocator

df = pd.read_csv("generator_isr_measurement_uint32.csv")

fig, ax = plt.subplots(1,5,layout='constrained',figsize=(13,5),sharey=True)

ax[0].plot(df.index,df.halton_result)
ax[0].set_title('Halton mean=$0.42\,\mu s$')
ax[1].plot(df.index,df.mtwister_result)
ax[1].set_title('MTwister mean=$0.16\,\mu s$')
ax[2].plot(df.index,df.squares_result)
ax[2].set_title('Squares mean=$0.2\,\mu s$')
ax[3].plot(df.index,df.pcg_result)
ax[3].set_title('PCG mean=$0.14\,\mu s$')
ax[4].plot(df.index,df.xoshiro_result)
ax[4].set_title('Xoshiro128 mean=$0.13\,\mu s$')

ax[0].set_ylabel(r'Time in $\mu s$')
fig.suptitle('Execution time to generate one random uint32_t')

for ax in ax.flat:
    ax.grid(True,which='both')
    ax.set_ylim(0,1)
    ax.set_xlim(0,200)
    ax.yaxis.set_minor_locator(AutoMinorLocator())
    ax.set_xlabel('ISR sample')