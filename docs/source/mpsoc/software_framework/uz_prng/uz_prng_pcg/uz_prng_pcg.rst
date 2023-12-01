=================
PCG Random Number
=================


- https://www.pcg-random.org/
- Implementation based on
- https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.h
- https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.c
- Has the ability to create independent sub-streams, i.e., use one generator instance with different id's instead of multiple generators with different seeds. Using different id's is more efficient w.r.t. memory usage (no multiple instances of the module and state required). However, we do not use this feature to keep it consistent with different generators and have a unified usage  


  - https://en.wikipedia.org/wiki/Permuted_congruential_generator

    - https://www.pcg-random.org/pdf/hmc-cs-2014-0905.pdf
    - https://www.pcg-random.org/
    - https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.c



.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_pcg_uint32.csv', header=None, names=columns)
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

.. doxygentypedef:: uz_prng_pcg_t

.. doxygenfunction:: uz_prng_pcg_init

.. doxygenfunction:: uz_prng_pcg_get_uniform_uint32
