====================================
Pseudorandom number generator (PRNG)
====================================

- PRNG create random 32-bit unsigned integer in a uniform distribution
- https://en.wikipedia.org/wiki/Pseudorandom_number_generator
- https://en.wikipedia.org/wiki/List_of_random_number_generators#cite_note-38
- Only non-cryptographically secure generators are of interests here
- IEEE Paper regarding different generators  https://ieeexplore.ieee.org/abstract/document/9132873

- Generators (all generate uniform distribution)

- https://en.wikipedia.org/wiki/Latin_hypercube_sampling (Mostly for experiement setup)

- Possibly hardware-accelerate number generation

    - https://link.springer.com/article/10.1007/s11265-012-0684-4

- Test suite for random generators:

    - "Dieharder"
    - http://simul.iro.umontreal.ca/testu01/install.html



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
    halton=pd.read_csv('uz_prng_halton/uz_prng_halton_uint32.csv', header=None, names=columns)

    fig, ax = plt.subplots(5,3,layout='constrained',figsize=(14,7))
    ax[0,0].hist([xoshiro.number[1:20] ], bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[0,1].hist([xoshiro.number[1:200]], bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[0,2].hist([xoshiro.number       ], bins=50,density=True, histtype='step', stacked=False, fill=True, label='xoshiro')
    ax[1,0].hist([twister.number[1:20] ],color="tab:orange", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[1,1].hist([twister.number[1:200]],color="tab:orange", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[1,2].hist([twister.number       ],color="tab:orange", bins=50,density=True, histtype='step', stacked=False, fill=True, label='MTwister')
    ax[2,0].hist([pcg.number[1:20] ],color="tab:green", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[2,1].hist([pcg.number[1:200]],color="tab:green", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[2,2].hist([pcg.number       ],color="tab:green", bins=50,density=True, histtype='step', stacked=False, fill=True, label='PCG')
    ax[3,0].hist([squares.number[1:20] ],color="tab:red", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[3,1].hist([squares.number[1:200]],color="tab:red", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[3,2].hist([squares.number       ],color="tab:red", bins=50,density=True, histtype='step', stacked=False, fill=True, label='Squares')
    ax[4,0].hist([halton.number[1:20] ],color="tab:purple", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[4,1].hist([halton.number[1:200]],color="tab:purple", bins=50,density=True, histtype='step', stacked=False, fill=True)
    ax[4,2].hist([halton.number       ],color="tab:purple", bins=50,density=True, histtype='step', stacked=False, fill=True, label='Halton')
    ax[0,0].set_title("$N=20$")
    ax[0,1].set_title("$N=200$")
    ax[0,2].set_title("$N=5000$")
    fig.legend(loc='outside right upper')
    fig.suptitle('Histogram of different PRNG for different number of samples')


Comparison 2D case
==================

.. plot:: mpsoc/software_framework/uz_prng/uz_prng_2d_compare.py



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

