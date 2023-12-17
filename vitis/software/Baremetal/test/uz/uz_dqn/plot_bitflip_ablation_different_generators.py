import glob
import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt     
import seaborn as sns
import numpy as np
from matplotlib.ticker import AutoMinorLocator, MultipleLocator


def concat_data(folder_name):
    twister=read_data('twister',folder_name)
    halton=read_data('halton',folder_name)
    squares=read_data('squares',folder_name)
    pcg=read_data('pcg',folder_name)
    xoshiro=read_data('xoshiro',folder_name)

    train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro])
    return train_data_full

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
        train_log[x].insert(1,"folder_name",[folder_name]*len(train_log[x]))

    train_data=pd.concat(train_log)
    return train_data

def plot_individual_runs(folder_name):
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

def plot_errorbar(folder_name):
    twister=read_data('twister',folder_name)
    halton=read_data('halton',folder_name)
    squares=read_data('squares',folder_name)
    pcg=read_data('pcg',folder_name)
    xoshiro=read_data('xoshiro',folder_name)

    train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro])
    sns.set_theme(style='whitegrid')
    palette = sns.color_palette("tab10")

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

def plot_boxplot(folder_name):
    twister=read_data('twister',folder_name)
    halton=read_data('halton',folder_name)
    squares=read_data('squares',folder_name)
    pcg=read_data('pcg',folder_name)
    xoshiro=read_data('xoshiro',folder_name)

    train_data_full=pd.concat( [twister,squares,pcg,halton,xoshiro])

    sns.set_theme(style='whitegrid')
    palette = sns.color_palette("tab10")

    fig3, axs3 = plt.subplots(1, 1,layout='constrained',figsize=(14,13))
    sns.boxplot(data=train_data_full, x="prng", y="global_reward_metric",ax=axs3)

def compare_boxplots_hue_prng():
    seeds_10=concat_data('10_seeds')
    training=concat_data('bitflip_different_prng_training')
    init=concat_data('bitflip_different_prng_init')
    exploration=concat_data('bitflip_different_prng_exploration')
    train_data_full=pd.concat( [seeds_10,training,init,exploration])

    sns.set_theme(style='whitegrid')
    palette = sns.color_palette("tab10")

    fig, ax = plt.subplots(1, 1,layout='constrained',figsize=(14,13),sharey=True)
    g=sns.boxplot(data=train_data_full, x="folder_name", y="global_reward_metric", hue='prng')
    sns.move_legend(g, "lower left") 

def compare_boxplots_hue_experiment():
    seeds_10=concat_data('10_seeds')
    training=concat_data('bitflip_different_prng_training')
    init=concat_data('bitflip_different_prng_init')
    exploration=concat_data('bitflip_different_prng_exploration')
    train_data_full=pd.concat( [seeds_10,training,init,exploration])

    sns.set_theme(style='whitegrid')
    palette = sns.color_palette("tab10")

    fig, ax = plt.subplots(1, 1,layout='constrained',figsize=(14,13),sharey=True)
    g=sns.boxplot(data=train_data_full, x="prng", y="global_reward_metric", hue='folder_name')
    sns.move_legend(g, "lower left") 



def plot_individual():
    seeds_10=concat_data('10_seeds')
    training=concat_data('bitflip_different_prng_training')
    init=concat_data('bitflip_different_prng_init')
    exploration=concat_data('bitflip_different_prng_exploration')
    train_data_full=pd.concat( [seeds_10,training,init,exploration])

    sns.set_theme(style='whitegrid')
    palette = sns.color_palette("tab10")

    fig, axs = plt.subplots(4, 1,layout='constrained',figsize=(14,13),sharey=True)
    sns.lineplot(data=training.query("prng == 'twister'"),x='episode',y='global_reward_metric',ax=axs[0],units="seed",estimator=None,hue="seed")
    sns.lineplot(data=training.query("prng == 'pcg'"),x='episode',y='global_reward_metric',ax=axs[0],units="seed",estimator=None,hue="seed")
    sns.lineplot(data=training.query("prng == 'squares'"),x='episode',y='global_reward_metric',ax=axs[0],units="seed",estimator=None,hue="seed")
    sns.lineplot(data=training.query("prng == 'xoshiro'"),x='episode',y='global_reward_metric',ax=axs[0],units="seed",estimator=None,hue="seed")
    sns.lineplot(data=training.query("prng == 'halton'"),x='episode',y='global_reward_metric',ax=axs[0],units="seed",estimator=None,hue="seed")

