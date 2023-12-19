import glob
import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt     
import seaborn as sns
import numpy as np


def calculate_iae(data):
    unique_runs=pd.unique(data.eval_run)
    number_of_eval_runs=len(unique_runs)


def concat_data(folder_name,read_eval):
    twister=read_data('twister',folder_name,read_eval)
    halton=read_data('halton',folder_name,read_eval)
    squares=read_data('squares',folder_name,read_eval)
    pcg=read_data('pcg',folder_name,read_eval)
    xoshiro=read_data('xoshiro',folder_name,read_eval)

    train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro])
    return train_data_full

def read_data(prng_name,folder_name,read_eval):
    path='vitis/software/Baremetal/test/uz/uz_dqn/' #pathlib.Path(__file__).parent.resolve()
    extension = 'csv'
 #   os.chdir(path)
    if read_eval==True:
        twister_training_filenames = glob.glob(folder_name+'/'+prng_name+'_eval_*.{}'.format(extension))
    else:
        twister_training_filenames = glob.glob(folder_name+'/'+prng_name+'_training_*.{}'.format(extension))

    train_log={}
    for x in range(len(twister_training_filenames)):
        train_log[x]=pd.read_csv(twister_training_filenames[x])
        train_log[x].insert(1,"episode",range(0,len(train_log[x])))
        train_log[x].insert(1,"seed",[x]*len(train_log[x]))
        train_log[x].insert(1,"prng",[prng_name]*len(train_log[x]))
        train_log[x].insert(1,"folder_name",[folder_name]*len(train_log[x]))

    train_data=pd.concat(train_log)
    return train_data

folder_name='pt1_only_one_generator'
twister=read_data('twister',folder_name,False)
eval_data=read_data('twister',folder_name,True)
halton=read_data('halton',folder_name,False)
squares=read_data('squares',folder_name,False)
pcg=read_data('pcg',folder_name,False)
xoshiro=read_data('xoshiro',folder_name,False)

one_generator=pd.concat( [twister,squares,pcg,halton,xoshiro])

folder_name='pt1_testrun'
twister=read_data('twister',folder_name,False)
eval_data=read_data('twister',folder_name,True)
halton=read_data('halton',folder_name,False)
squares=read_data('squares',folder_name,False)
pcg=read_data('pcg',folder_name,False)
xoshiro=read_data('xoshiro',folder_name,False)

seeds_10=pd.concat( [twister,squares,pcg,halton,xoshiro])
combined=pd.concat([one_generator,seeds_10])

sns.set_theme(style='whitegrid')
palette = sns.color_palette("tab10")

sns.relplot(
    data=one_generator, x="episode", y="global_reward_metric",
    col="seed",# hue="event", style="event",
    kind="line",errorbar=("sd", 1)
)

fig, axs = plt.subplots(4, 1,layout='constrained')
sns.lineplot(data=twister,hue='seed',x='episode',y='global_reward_metric',ax=axs[0],legend=False)
sns.lineplot(data=twister,hue='seed',x='episode',y='episode_loss',ax=axs[1],legend=False)
sns.lineplot(data=twister,hue='seed',x='episode',y='cumulative_reward',ax=axs[2],legend=False)
sns.lineplot(data=twister,hue='seed',x='episode',y='epsilon_per_epsiode',ax=axs[3],legend=False)

g=sns.FacetGrid(eval_data,col="eval_run",row="seed")
g.map(sns.lineplot,"eval_time_step","eval_output",color=palette[0])
g.map(sns.lineplot,"eval_time_step","eval_setpoint",color=palette[1])

sns.relplot(
    data=combined, x="episode", y="global_reward_metric",hue='seed',
    col="prng",kind="line",row="folder_name"
)

fig, axs = plt.subplots(1, 1,layout='constrained')
sns.boxplot(data=one_generator, x="prng", y="global_reward_metric",hue='prng',ax=axs)

fig, axs = plt.subplots(1, 1,layout='constrained')
sns.boxplot(data=seeds_10, x="prng", y="global_reward_metric",hue='prng',ax=axs)

fig, axs = plt.subplots(1, 1,layout='constrained')
sns.boxplot(data=combined, x="prng", y="global_reward_metric",hue='folder_name',ax=axs)


