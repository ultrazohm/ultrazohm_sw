import glob
import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt     
import seaborn as sns
import numpy as np

def read_data(prng_name):
    path=pathlib.Path(__file__).parent.resolve()
    extension = 'csv'
    os.chdir(path)
    twister_training_filenames = glob.glob(prng_name+'_training_*.{}'.format(extension))

    train_log={}
    for x in range(len(twister_training_filenames)):
        train_log[x]=pd.read_csv(twister_training_filenames[x])
        train_log[x].insert(1,"episode",range(0,len(train_log[x])))
        train_log[x].insert(1,"seed",[x]*len(train_log[x]))
        train_log[x].insert(1,"prng",[prng_name]*len(train_log[x]))

    train_data=pd.concat(train_log)
    return train_data

twister=read_data('twister')
squares=read_data('squares')
pcg=read_data('pcg')
halton=read_data('halton')
xoshiro=read_data('xoshiro')
halton_mt=read_data('halton_mt')

train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro,halton_mt])

sns.set_theme(style='whitegrid')
palette = sns.color_palette("tab10")

fig, axs = plt.subplots(5, 1,layout='constrained',figsize=(14,13))
sns.lineplot(data=twister,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[0],legend=False)
sns.lineplot(data=squares,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[1],legend=False)
sns.lineplot(data=pcg,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[2],legend=False)
sns.lineplot(data=halton,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[3],legend=False)
sns.lineplot(data=xoshiro,x='episode',y='global_reward_metric',units='seed',estimator=None,hue='seed',palette=palette,ax=axs[4],legend=False)

fig, axs = plt.subplots(5, 1,layout='constrained',figsize=(14,13))
sns.lineplot(data=twister,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs[0],legend=False)
sns.lineplot(data=squares,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs[1],legend=False)
sns.lineplot(data=pcg,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs[2],legend=False)
sns.lineplot(data=halton,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs[3],legend=False)
sns.lineplot(data=xoshiro,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs[4],legend=False)

axs[0].title.set_text('MTwister')
axs[1].title.set_text('Squares')
axs[2].title.set_text('PCG')
axs[3].title.set_text('Halton')
axs[4].title.set_text('Xoshiro')

fig3, axs3 = plt.subplots(1, 5,layout='constrained',figsize=(14,13), sharey=True)
sns.lineplot(data=twister,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs3[0],legend=False)
sns.lineplot(data=squares,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs3[1],legend=False)
sns.lineplot(data=pcg,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs3[2],legend=False)
sns.lineplot(data=halton,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs3[3],legend=False)
sns.lineplot(data=xoshiro,x='episode',y='global_reward_metric',errorbar=("sd", 3),ax=axs3[4],legend=False)

axs3[0].title.set_text('MTwister')
axs3[1].title.set_text('Squares')
axs3[2].title.set_text('PCG')
axs3[3].title.set_text('Halton')
axs3[4].title.set_text('Xoshiro')

fig2, axs2 = plt.subplots(1, 1,layout='constrained',figsize=(14,13))
sns.lineplot(data=train_data_full,x='episode',y='global_reward_metric',errorbar=("sd", 1),ax=axs2,hue='prng')


sns.relplot(
    data=train_data_full, x="episode", y="global_reward_metric",
    col="prng", # hue="event", style="event",
    kind="line",errorbar=("sd", 1)
)


