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


folder_name='10_seeds'
twister=read_data('twister',folder_name)
halton=read_data('halton',folder_name)
squares=read_data('squares',folder_name)
pcg=read_data('pcg',folder_name)
xoshiro=read_data('xoshiro',folder_name)

train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro])

sns.set_theme(style='whitegrid')
palette = sns.color_palette("tab10")

fig, axs = plt.subplots(5, 1,layout='constrained',figsize=(14,13))
sns.lineplot(data=twister,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[0],legend=False)
sns.lineplot(data=squares,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[1],legend=False)
sns.lineplot(data=pcg,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[2],legend=False)
sns.lineplot(data=halton,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[3],legend=False)
sns.lineplot(data=xoshiro,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[4],legend=False)
