import glob
import os
import pathlib
import pandas as pd
import matplotlib.pyplot as plt     
import seaborn as sns

path=pathlib.Path(__file__).parent.resolve()
extension = 'csv'
os.chdir(path)
twister_eval_filenames = glob.glob('twister_eval_*.{}'.format(extension))
twister_training_filenames = glob.glob('twister_training_*.{}'.format(extension))

eval_log={}
for x in range(len(twister_eval_filenames)):
    eval_log[x]=pd.read_csv(twister_eval_filenames[x])

train_log={}
for x in range(len(twister_eval_filenames)):
    train_log[x]=pd.read_csv(twister_training_filenames[x])

plt.plot(train_log[0]["global_reward_metric"])
plt.plot(train_log[1]["global_reward_metric"])
plt.show()
