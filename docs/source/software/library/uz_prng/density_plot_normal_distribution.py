import pandas as pd
import seaborn as sns

sns.set_theme(style='whitegrid')

columns=['index','number']
normal_dist_data_1=pd.read_csv('uz_prng_normal_distribution_1.csv',header=None, names=columns)
normal_dist_data_2=pd.read_csv('uz_prng_normal_distribution_2.csv',header=None, names=columns)
normal_dist_data_3=pd.read_csv('uz_prng_normal_distribution_3.csv',header=None, names=columns)

normal_dist_data_1=normal_dist_data_1.rename(columns={"number": "seed1"})
normal_dist_data_1=normal_dist_data_1.drop(columns={'index'})

normal_dist_data_2=normal_dist_data_2.rename(columns={"number": "seed2"})
normal_dist_data_2=normal_dist_data_2.drop(columns={'index'})

normal_dist_data_3=normal_dist_data_3.rename(columns={"number": "seed3"})
normal_dist_data_3=normal_dist_data_3.drop(columns={'index'})

norm_dist_data=pd.concat([normal_dist_data_1, normal_dist_data_2],axis=1)
norm_dist_data=pd.concat([norm_dist_data, normal_dist_data_3],axis=1)

sns.kdeplot(data=norm_dist_data,common_norm=False)