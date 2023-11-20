======
Halton
======


.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_halton_float.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1,layout='constrained')
   axs[0].set_title("Random float\n numbers from\n uz_prng_halton")
   axs[0].plot(df.index,df.number,'o')

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of Halton Sequence\n with mean:" + title_string )