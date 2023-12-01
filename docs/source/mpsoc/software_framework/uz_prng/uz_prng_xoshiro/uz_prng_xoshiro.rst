============
Xoshiro128++
============

Implementation of Xoshiro128++[[#xoshiro_paper]_] random number generator.
This is a wrapper around the original source code of the paper authors [[#xoshiro_source]_]. 
Based on:

   - https://vigna.di.unimi.it/
   - https://github.com/svaarala/duktape/blob/master/misc/splitmix64.c
   - https://en.wikipedia.org/wiki/Xoroshiro128%2B


.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_xoshiro_uint32.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1,layout='constrained')
   axs[0].set_title("Random uint32\n numbers from\n uz_prng_squares")
   axs[0].plot(df.index,df.number,'o')

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of Squares\n with mean:" + title_string )

Reference
=========

.. doxygentypedef:: uz_prng_xoshiro_t

.. doxygenfunction:: uz_prng_xoshiro_init

.. doxygenfunction:: uz_prng_xoshiro_get_uniform_uint32

Sources
=======

.. [#xoshiro_paper] https://arxiv.org/abs/1805.01407
.. [#xoshiro_source] https://prng.di.unimi.it/xoshiro128plusplus.c