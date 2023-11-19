===============
Mersene Twister
===============


- Twister:
  - http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/TINYMT/index.html
  - https://github.com/MersenneTwister-Lab/TinyMT


MT19937
=======

.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_mtwister_uint32.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1)
   axs[0].set_title("Random uint32\n numbers from\n uz_prng_squares")
   axs[0].plot(df.index,df.number)

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of Squares\n with mean:" + title_string )


SIMD-oriented Fast Mersenne Twister (SFMT)
==========================================

  - http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/index.html#SFMT
  - Can not be used since the implementation relies on recursion, which is not allowed by MISRA and must not be used in ISR due to real-time requirements
