====================================
Pseudorandom number generator (PRNG)
====================================

- PRNG create random 32-bit unsigned integer in a uniform distribution
- https://en.wikipedia.org/wiki/Pseudorandom_number_generator
- https://en.wikipedia.org/wiki/List_of_random_number_generators#cite_note-38
- Only non-cryptographically secure generators are of interests here
- IEEE Paper regarding different generators  https://ieeexplore.ieee.org/abstract/document/9132873


- https://de.mathworks.com/help/stats/pseudorandom-and-quasi-random-number-generation.html?s_tid=CRUX_lftnav
- https://de.mathworks.com/help/stats/sobolset.html
- https://en.wikipedia.org/wiki/Sobol_sequence

- https://en.wikipedia.org/wiki/Low-discrepancy_sequence

- Generators (all generate uniform distribution):

- Algorithms to force better uniform distribution:

    - https://en.wikipedia.org/wiki/Halton_sequence
    - https://observablehq.com/@jrus/halton
    - https://stackoverflow.com/questions/42661304/implementing-4-dimensional-halton-sequence
    - https://people.sc.fsu.edu/~jburkardt/cpp_src/halton/halton.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/halton/halton.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/uniform/uniform.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/ziggurat/ziggurat.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/normal/normal.html

    - https://en.wikipedia.org/wiki/Latin_hypercube_sampling (Mostly for experiement setup)

- Possibly hardware-accelerate number generation

    - https://link.springer.com/article/10.1007/s11265-012-0684-4

- Test suite for random generators:

    - "Dieharder"
    - http://simul.iro.umontreal.ca/testu01/install.html


Halton Sequence
===============

- https://en.wikipedia.org/wiki/Halton_sequence

Comparison
==========

.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd
   import matplotlib.ticker as mtick

   columns=['index','number']
   xoshiro=pd.read_csv('uz_prng_xoshiro/uz_prng_xoshiro_uint32.csv', header=None, names=columns)
   twister=pd.read_csv('uz_prng_mtwister/uz_prng_mtwister_uint32.csv', header=None, names=columns)
   pcg=pd.read_csv('uz_prng_pcg/uz_prng_pcg_uint32.csv', header=None, names=columns)
   squares=pd.read_csv('uz_prng_squares/uz_prng_squares_uint32.csv', header=None, names=columns)

   legend=['xoshiro','MTwister','pcg','squares']
   fig, ax = plt.subplots(1,3,layout='constrained',figsize=(14,5))
   ax[0].hist([xoshiro.number[1:20], twister.number[1:20], pcg.number[1:20], squares.number[1:20]], bins=10, edgecolor="white",density=True)
   ax[1].hist([xoshiro.number[1:200], twister.number[1:200], pcg.number[1:200], squares.number[1:200]], bins=10, edgecolor="white",density=True)
   ax[2].hist([xoshiro.number, twister.number, pcg.number, squares.number], bins=10, edgecolor="white",density=True,label=legend)
   ax[0].set_title("$N=20$")
   ax[1].set_title("$N=200$")
   ax[2].set_title("$N=5000$")
   fig.legend(loc='outside right upper')
   fig.suptitle('Histogram of different PRNG for different number of samples')


Implemented generators
======================

..	toctree::
    :maxdepth: 1
    :glob:
  
    uz_prng_squares/uz_prng_squares
    uz_prng_mtwister/uz_prng_mtwister
    uz_prng_pcg/uz_prng_pcg
    uz_prng_xoshiro/uz_prng_xoshiro
    uz_prng_halton/uz_prng_halton


Generate bounded integer
========================

- https://c-faq.com/lib/randrange.html
- https://www.pcg-random.org/posts/bounded-rands.html
- https://github.com/imneme/bounded-rands



Generate bounded float values
==============================

Generate bounded float values
==============================

