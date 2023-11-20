===========
Squares RNG
===========

- Paper https://arxiv.org/pdf/2004.06278.pdf
- Web-page of the author: https://squaresrng.wixsite.com/rand
- https://en.wikipedia.org/wiki/Middle-square_method
- https://en.wikipedia.org/wiki/Counter-based_random_number_generator

- Two ways to initialize the generator

  1. supply a seed between 0 and 29. This will initialize the generator with a specific key from the list supplied by the author. I.e., seed=3 takes the 3. seed in the authors list

  2. Supply a specific seed that is larger than 30. In this case, the supplied seed is used as a key. Warning: you have to use keys that match the properties of the paper, thus only take seeds from the author (25000 are supplied on his homepage in ``keys.h``)



.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_squares_uint32.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1,layout='constrained')
   axs[0].set_title("Random uint32\n numbers from\n uz_prng_squares")
   axs[0].plot(df.index,df.number)

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of Squares\n with mean:" + title_string )




