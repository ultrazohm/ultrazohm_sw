.. _uz_prng_squares:

===========
Squares RNG
===========

Implements the Squares RNG generator [[#squares_paper]_].
Based on:

  - https://squaresrng.wixsite.com/rand (homepage of the author)
  - https://en.wikipedia.org/wiki/Middle-square_method
  - https://en.wikipedia.org/wiki/Counter-based_random_number_generator

Contrary to the other PRNG generators, the seed of this generator has to be chosen more carefully.
Two ways to initialize the generator are implemented:

  1. supply a seed between 0 and 29. This will initialize the generator with a specific key from the list supplied by the author of the algorithm. I.e., seed=3 takes the 3. seed in the author's key list.

  2. Supply a specific seed that is larger than 30. In this case, the supplied seed is used as a key. Only use keys that match the properties outlined in [[#squares_paper]_], using seeds from the algorithm's author is recommended (25,000 different seeds are supplied in ``keys.h`` available at https://squaresrng.wixsite.com/rand).

Distribution
============

The following figure shows an example distribution generated using the Squares PRNG.
Additionally, the histogram of the generated values is shown.

.. plot::
  :caption: Distribution generated using the Squares PRNG using seed 0.

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('../../../../../../vitis/software/Baremetal/test/uz/uz_prng_squares/uz_prng_squares_uint32.csv', header=None, names=columns)
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

.. doxygentypedef:: uz_prng_squares_t

.. doxygenfunction:: uz_prng_squares_init

.. doxygenfunction:: uz_prng_squares_get_uniform_uint32
  
.. doxygenfunction:: uz_prng_squares_reset


Sources
=======

.. [#squares_paper] https://arxiv.org/pdf/2004.06278.pdf

