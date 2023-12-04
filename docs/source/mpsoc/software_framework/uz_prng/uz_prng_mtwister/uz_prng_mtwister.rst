.. _uz_prng_mtwister:

================
Mersenne Twister
================

The Mersenne Twister [[#mtwister_paper]_] is a random number generator producing uniform pseudorandom numbers.
The implementation is based on the following resources:

  - https://github.com/ESultanik/mtwister/blob/master/mtwister.c
  - https://en.wikipedia.org/wiki/Mersenne_Twister
  - http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/TINYMT/index.html
  - https://github.com/MersenneTwister-Lab/TinyMT

In addition to the implemented Mersenne Twister, there exist multiple improvements including a SIMD-oriented Fast Mersenne Twister (SFMT) [[#fast_twister]_].
However, the implementation relies on recursion, which is not allowed within the UltraZohm project and not implemented.

.. warning:: Using the Mersenne Twister for real-time applications, especially in interrupts, is not recommended (see :ref:`uz_prng`).

MT19937 distribution
====================

The following figures shows the generation of 5000 random numbers using the Mersenne Twister.
Additionally, the Histogram of the generated values is shown.
The generated random values are uniformly distributed, but not in a perfect manner.
The specific pattern and distribution depends on the random seed.

.. plot::
  :caption: Distribution generated using the Mersenne Twister PRNG using seed 0.

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('../../../../../../vitis/software/Baremetal/test/uz/uz_prng_mtwister/uz_prng_mtwister_uint32.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1,layout='constrained')
   axs[0].set_title("Random uint32\n numbers from\n uz_prng_mtwister")
   axs[0].plot(df.index,df.number,'o')

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of MTwister\n with mean:" + title_string )


Reference
=========

.. doxygentypedef:: uz_prng_mtwister_t

.. doxygenfunction:: uz_prng_mtwister_init

.. doxygenfunction:: uz_prng_mtwister_get_uniform_uint32


Sources
=======

.. [#mtwister_paper] Mersenne twister: a 623-dimensionally equidistributed uniform pseudo-random number generator, https://dl.acm.org/doi/10.1145/272991.272995
.. [#fast_twister] http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/SFMT/index.html#SFMT