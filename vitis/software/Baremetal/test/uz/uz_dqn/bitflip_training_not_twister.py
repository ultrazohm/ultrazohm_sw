import glob
import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt     
import seaborn as sns
import numpy as np

def read_data(prng_name,folder_name):
    path='vitis/software/Baremetal/test/uz/uz_dqn/' #pathlib.Path(__file__).parent.resolve()
    extension = 'csv'
 #   os.chdir(path)
    twister_training_filenames = glob.glob(folder_name+'/'+prng_name+'_training_*.{}'.format(extension))

    train_log={}
    for x in range(len(twister_training_filenames)):
        train_log[x]=pd.read_csv(twister_training_filenames[x])
        train_log[x].insert(1,"episode",range(0,len(train_log[x])))
        train_log[x].insert(1,"seed",[x]*len(train_log[x]))
        train_log[x].insert(1,"prng",[prng_name]*len(train_log[x]))

    train_data=pd.concat(train_log)
    return train_data


folder_name='exploration_results_only_eps'
twister=read_data('twister',folder_name)
halton=read_data('halton',folder_name)
squares=read_data('squares',folder_name)
pcg=read_data('pcg',folder_name)
xoshiro=read_data('xoshiro',folder_name)
train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro])

sns.set_theme(style='whitegrid')
palette = sns.color_palette("tab10")

fig2, axs2 = plt.subplots(1, 1,layout='constrained',figsize=(14,13))
sns.lineplot(data=train_data_full,x='episode',y='global_reward_metric',errorbar=("sd", 1),ax=axs2,hue='prng')


sns.relplot(
    data=train_data_full, x="episode", y="global_reward_metric",
    col="prng", # hue="event", style="event",
    kind="line",errorbar=("sd", 1)
)
twister_training_filenames
fig3, axs3 = plt.subplots(1, 1,layout='constrained',figsize=(14,13))
sns.boxplot(data=train_data_full, x="prng", y="global_reward_metric",ax=axs3)

