import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt

def read_data(distribution_name):
    base_path='density_plot_multipe_seeds_biased_uint1000/'
    ending_string='_seed_index_'
    
    data={}
    seeds=range(0,10)
    for x in seeds:
        load_string=base_path + distribution_name+ ending_string + str(seeds[x]) + '.csv'
        columns=['index','number']
        data[x]=pd.read_csv(load_string,header=None, names=columns)
        data[x]=data[x].rename(columns={"number": "seed_"+str(seeds[x])})
        data[x]=data[x].drop(columns={'index'})

    concated_data=data[0]
    for x in range(1,len(seeds)):
        concated_data=pd.concat([concated_data, data[x]],axis=1)
    
    return concated_data


sns.set_theme(style='whitegrid')


halton_biased=read_data('halton_biased1000')
squares_biased=read_data('squares_biased1000')
pcg_biased=read_data('pcg_biased1000')
mtwister_biased=read_data('mtwister_biased1000')
xoshiro_biased=read_data('xoshiro_biased1000')

halton_unbiased=read_data('halton_unbiased1000')
squares_unbiased=read_data('squares_unbiased1000')
pcg_unbiased=read_data('pcg_unbiased1000')
mtwister_unbiased=read_data('mtwister_unbiased1000')
xoshiro_unbiased=read_data('xoshiro_unbiased1000')


fig, axs = plt.subplots(5, 2,layout='constrained',figsize=(14,7))
sns.histplot(data=mtwister_unbiased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[0,0],legend=False)
sns.histplot(data=halton_unbiased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[1,0],legend=False)
sns.histplot(data=squares_unbiased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[2,0],legend=False)
sns.histplot(data=xoshiro_unbiased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[3,0],legend=False)
sns.histplot(data=pcg_unbiased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[4,0],legend=False)

sns.histplot(data=mtwister_biased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[0,1],legend=False)
sns.histplot(data=halton_biased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[1,1],legend=False)
sns.histplot(data=squares_biased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[2,1],legend=False)
sns.histplot(data=xoshiro_biased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[3,1],legend=False)
sns.histplot(data=pcg_biased,common_norm=False,palette=sns.color_palette("tab10"),stat='density',ax=axs[4,1],legend=False)

axs[0,0].title.set_text('MTwister unbiased')
axs[1,0].title.set_text('Halton unbiased')
axs[2,0].title.set_text('Squares unbiased')
axs[3,0].title.set_text('Xoshiro unbiased')
axs[4,0].title.set_text('PCG unbiased')

axs[0,1].title.set_text('MTwister biased')
axs[1,1].title.set_text('Halton biased')
axs[2,1].title.set_text('Squares biased')
axs[3,1].title.set_text('Xoshiro biased')
axs[4,1].title.set_text('PCG biased')

for axs in axs.flat:
    axs.set_ylim(0.4,0.6)

# axs[0].set_ylim([0.45, 0.55])
# sns.move_legend(axs[0], "upper left", bbox_to_anchor=(1, 1))

