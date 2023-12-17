import glob
import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt     
import seaborn as sns
import numpy as np
from matplotlib.ticker import AutoMinorLocator, MultipleLocator


def concat_data(folder_name):
    action=read_data('twister_halton_action',folder_name)
    epsilon=read_data('twister_halton_epsilon',folder_name)

    train_data_full=pd.concat( [action, epsilon])
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


def focus_halton_training():

    action=read_data('twister_halton_action','bitflip_ablation_halton_exploration_special')
    epsilon=read_data('twister_halton_epsilon','bitflip_ablation_halton_exploration_special')
    init_init=read_data('twister_init_init','bitflip_ablation_halton_exploration_special')
    seeds=read_data('twister','10_seeds')

    train_data_full=pd.concat( [action, epsilon,init_init,seeds])

    sns.set_theme(style='whitegrid')
    palette = sns.color_palette("tab10")

    fig, ax = plt.subplots(1, 1,layout='constrained',figsize=(14,13),sharey=True)
    g=sns.boxplot(data=train_data_full, x="folder_name", y="global_reward_metric",palette=palette, hue='prng')
    sns.move_legend(g, "lower left") 
