.. _uz_prng_halton:

===============
Halton sequence
===============

Implements a Halton sequence [[#halton_paper]_], [[#halton_wiki]_] which is a low discrepancy sequence [[#low_discrepancy_wiki]_].
A Halton sequence is not a pseudo-random number generator such as :ref:`uz_prng_mtwister` but a quasi-random sequence.
Thus, the output of the Halton sequence appears random and typically the distribution of the generated numbers is more even compared to PRNGs.
Care has to be taken regarding multi-dimensional Halton sequence, see :ref:`uz_prng_2d_case`.
Specifically, one must not use a one-dimensional sequence for multi-dimensional applications since the distribution properties do not hold in this case.

Information:

- https://github.com/CarlosLunaMota/CLM_LIBS
- https://observablehq.com/@jrus/halton
- https://stackoverflow.com/questions/42661304/implementing-4-dimensional-halton-sequence
- https://people.sc.fsu.edu/~jburkardt/cpp_src/halton/halton.html
- https://people.sc.fsu.edu/~jburkardt/c_src/halton/halton.html

Distribution
============

.. plot::
  :caption: Distribution generated using the Halton sequence generating float values.

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('../../../../../../vitis/software/Baremetal/test/uz/uz_prng_halton/uz_prng_halton_float.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1,layout='constrained')
   axs[0].set_title("Random float\n numbers from\n uz_prng_halton")
   axs[0].plot(df.index,df.number,'o')

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of Halton Sequence\n with mean:" + title_string )


.. plot::
  :caption: Distribution generated using the Halton sequence generating uint32.

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('../../../../../../vitis/software/Baremetal/test/uz/uz_prng_halton/uz_prng_halton_uint32.csv', header=None, names=columns)
   mean=df.loc[:,'number'].mean()
   std=df.loc[:,'number'].std()
   var=df.loc[:,'number'].var()

   fig, axs = plt.subplots(2, 1,layout='constrained')
   axs[0].set_title("Random uint32\n numbers from\n uz_prng_halton")
   axs[0].plot(df.index,df.number,'o')

   axs[1].hist(df.number, bins=50, linewidth=0.5, edgecolor="white",density=True)
   title_string=str(mean)
   axs[1].set_title("Histogram\n of Halton Sequence\n with mean:" + title_string )


Reference
=========

.. doxygentypedef:: uz_prng_halton_t

.. doxygenfunction:: uz_prng_halton_init

.. doxygenfunction:: uz_prng_halton_get_uniform_float

.. doxygenfunction:: uz_prng_halton_get_uniform_float_2d

Sources
=======

.. [#halton_paper] Algorithm 247: Radical-inverse quasi-random point sequence, https://dl.acm.org/doi/10.1145/355588.365104
.. [#halton_wiki] https://en.wikipedia.org/wiki/Halton_sequence
.. [#low_discrepancy_wiki] https://en.wikipedia.org/wiki/Low-discrepancy_sequence

