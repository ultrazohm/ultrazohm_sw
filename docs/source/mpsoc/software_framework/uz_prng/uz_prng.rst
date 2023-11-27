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

.. 
    .. plot:: 

    .. import matplotlib.pyplot as plt
    .. import pandas as pd
    .. import matplotlib.ticker as mtick

    .. columns=['index','number']
    .. xoshiro=pd.read_csv('uz_prng_xoshiro/uz_prng_xoshiro_uint32.csv', header=None, names=columns)
    .. twister=pd.read_csv('uz_prng_mtwister/uz_prng_mtwister_uint32.csv', header=None, names=columns)
    .. pcg=pd.read_csv('uz_prng_pcg/uz_prng_pcg_uint32.csv', header=None, names=columns)
    .. squares=pd.read_csv('uz_prng_squares/uz_prng_squares_uint32.csv', header=None, names=columns)
    .. halton=pd.read_csv('uz_prng_halton/uz_prng_halton_uint32.csv', header=None, names=columns)

    .. fig, ax = plt.subplots(5,3,layout='constrained',figsize=(14,7))
    .. ax[0,0].hist([xoshiro.number[1:20] ], bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[0,1].hist([xoshiro.number[1:200]], bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[0,2].hist([xoshiro.number       ], bins=50,density=True, histtype='step', stacked=False, fill=True, label='xoshiro')
    .. ax[1,0].hist([twister.number[1:20] ],color="tab:orange", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[1,1].hist([twister.number[1:200]],color="tab:orange", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[1,2].hist([twister.number       ],color="tab:orange", bins=50,density=True, histtype='step', stacked=False, fill=True, label='MTwister')
    .. ax[2,0].hist([pcg.number[1:20] ],color="tab:green", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[2,1].hist([pcg.number[1:200]],color="tab:green", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[2,2].hist([pcg.number       ],color="tab:green", bins=50,density=True, histtype='step', stacked=False, fill=True, label='PCG')
    .. ax[3,0].hist([squares.number[1:20] ],color="tab:red", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[3,1].hist([squares.number[1:200]],color="tab:red", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[3,2].hist([squares.number       ],color="tab:red", bins=50,density=True, histtype='step', stacked=False, fill=True, label='Squares')
    .. ax[4,0].hist([halton.number[1:20] ],color="tab:purple", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[4,1].hist([halton.number[1:200]],color="tab:purple", bins=50,density=True, histtype='step', stacked=False, fill=True)
    .. ax[4,2].hist([halton.number       ],color="tab:purple", bins=50,density=True, histtype='step', stacked=False, fill=True, label='Halton')
    .. ax[0,0].set_title("$N=20$")
    .. ax[0,1].set_title("$N=200$")
    .. ax[0,2].set_title("$N=5000$")
    .. fig.legend(loc='outside right upper')
    .. fig.suptitle('Histogram of different PRNG for different number of samples')


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

Biased
------


.. .. plot::

..     import matplotlib.pyplot as plt
..     import pandas as pd
..     import numpy as np
    
..     columns = ["index", "number"]
..     df = pd.read_csv("uz_prng_bounded_bias.csv", header=None, names=columns)
..     df_unbound = pd.read_csv("uz_prng_unbounded_bias.csv", header=None, names=columns)
..     df_unbias = pd.read_csv("uz_prng_unbounded_bias.csv", header=None, names=columns)
    
..     bins = np.arange(53) 
..     fig, axs = plt.subplots(3, 1, layout="constrained", figsize=(14, 5))
..     axs[0].hist(df_unbound.number, bins=52, linewidth=0.4, edgecolor="white")
..     axs[1].hist(df.number, bins=bins, linewidth=0.4, edgecolor="white")
..     axs[2].hist(df_unbias.number, bins=52, linewidth=0.4, edgecolor="white")
..     axs[1].set_xticks(range(54))
..     fig.show()
    
    


Generate bounded float values
==============================

Unit interval [0,1)
-------------------

- uz_prng_scale_to_float_zero_to_one_divide
- uz_prng_scale_to_float_zero_to_one_multiply = 10ns overhead
- uz_prng_scale_to_float_zero_to_one_shift_multiply = 8ns -> This is the fastest
- All three functions do not have a measureable difference in exectuion time
- Generating one float (0,1) using pcg takes 0.153 us
- Additional calculation time for float is approx. 10ns compared to uint32

Arbitrarily scaled
------------------

- 0.166us für uint32_t mit unbiased version, but the calculation time jitters a bit
- 0.16 für uint32_t mit biased version
- Does not seem to make much difference regarding jitter 



Seeds
=====

- Squares: Number between 0 und 29, which selects one pregenerated key
- MTwister: uint32_t seed
- Halton: prime number
- PCG: random seed, inital sequence is arbitrarily set to 54
- Xoshiro128: random seed, wird durch splitmix geschoben


Timing to generate one rand
===========================

Measurement setup to calculate mean execution time required to generate one uint32 for each generator.
Measurements on the R5 of the UltraZohm.
Calculated generating 20 values per ISR over 4000 ISR cycles.
Result in us.

.. code-block:: c

    if (current_state == control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
        for (uint32_t i = 0; i < NUMBER_OF_PRNG_RUNS_PER_ISR; i++)
        {
        	rnd_numbers[i]=uz_prng_get_uniform_float_zero_to_one(generator);
        }
    }

- Baseline of execution without generating random values is 16.2 us
- Baseline is substracted from executin time to yield the time required for calculting 20 rand values
- Results

  - xoshiro128 and pcg are the fastest generators
  - Halton sequence seems to increase calculation time with the number of samples taken and settles at arround 0.6 us per random number -> no ISR usage! -> Evtl. pendelt sich das auch ein? Oder doch nicht? Wirkt, als würde es bei 27.5us (bei 16.2 us ohne) einpendeln
  - MTwister ist auch schnell, außer alle 620 Ausführungen -> kein Twister


.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_measurement_uint32.csv")

    fig, ax = plt.subplots(1,5,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.index,df.halton_result)
    ax[0].set_title('Halton mean=$0.42\,\mu s$')
    ax[1].plot(df.index,df.mtwister_result)
    ax[1].set_title('MTwister mean=$0.16\,\mu s$')
    ax[2].plot(df.index,df.squares_result)
    ax[2].set_title('Squares mean=$0.2\,\mu s$')
    ax[3].plot(df.index,df.pcg_result)
    ax[3].set_title('PCG mean=$0.14\,\mu s$')
    ax[4].plot(df.index,df.xoshiro_result)
    ax[4].set_title('Xoshiro128 mean=$0.13\,\mu s$')

    ax[0].set_ylabel(r'Time in $\mu s$')
    fig.suptitle('Execution time to generate one random uint32_t')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.set_ylim(0,1)
        ax.set_xlim(0,200)
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_xlabel('ISR sample')


Halton timing
=============

- Calculation time increases with number of samples taken from halton sequence
- Evaluated for 874,821,900 samples, which did not result in a settled calculation time
- Used seed=7U, behavior probably depends on the starting prime number

.. warning:: Halton generator draws the :math:`i-th` number of the halton sequence of the starting prime number. Therefore, the internal counter will overflow after 4,294,967,295 (i.e., UINT32_MAX) drawn samples. Note that `unsigned integer wrap <https://www.gnu.org/software/autoconf/manual/autoconf-2.63/html_node/Integer-Overflow-Basics.html>`_, therefore, the Halton sequence will repeat after 2^32-1 calls.

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_halton_long_log.csv")

    fig, ax = plt.subplots(1,1,layout='constrained',figsize=(13,5))
    # Dataset is without offset and for 20 rand numbers -> substract offset of 16.2us and divide by number of generated rand numbers
    ax.plot(df.Var1, (df.y-16.2)/20) 
    fig.suptitle('Execution time to generate one random uint32_t')
    ax.grid(True,which='both')
    ax.set_ylim(0,0.7)
    ax.yaxis.set_minor_locator(AutoMinorLocator())
    ax.set_xlabel('ISR sample')


Float [0,1)
===========

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_float.csv")

    fig, ax = plt.subplots(1,3,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.fp_muliply)
    ax[0].set_title('Float multiply mean=$0.496\,\mu s$')
    ax[1].plot(df.fp_divide)
    ax[1].set_title('Float divide mean=$0.496\,\mu s$')
    ax[2].plot(df.shift_multi)
    ax[2].set_title('Shift multiply mean=$0.485\,\mu s$')

    ax[0].set_ylabel(r'Time in $\mu s$')
    fig.suptitle('Execution time to generate one random float [0,1)')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.set_ylim(0.48,0.5)
        ax.set_xlim(0,200)
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_xlabel('ISR sample')


fp_muliply_mean = 0.4960
fp_divide_mean = 0.4964
shift_multi_mean = 0.4851

Calculated using Matlab ksdensity function over 10000 samples.

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_float_density.csv")

    fig, ax = plt.subplots(1,3,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.fp_multiply_xi,df.fp_multiply_f)
    ax[0].set_title('Float multiply mean=$0.496\,\mu s$')
    ax[1].plot(df.fp_divide_xi,df.fp_divide_f)
    ax[1].set_title('Float divide mean=$0.496\,\mu s$')
    ax[2].plot(df.shift_multi_xi,df.shift_multi_f)
    ax[2].set_title('Shift multiply mean=$0.485\,\mu s$')

    ax[0].set_xlabel('probability density estimate')

    fig.suptitle('Execution time to generate one random float [0,1)')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_ylabel('probability density estimate')



uint32_t in range [0,range)
===========================

- int multi is the fastest but is biased
- unbiased opt is unbiased and faster than unbias
- No reason to use float multi version
- Use unbiased mean if comparability with other Frameworks that use Lemir's method is desired

float_mult_mean = 0.4889

int_mult_mean = 0.4262

unbiased_mean = 0.5270

unbiased_opt_mean = 0.4402

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_bounded_uint32_density.csv")

    fig, ax = plt.subplots(1,4,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.float_mult_xi,df.float_mult_f)
    ax[0].set_title('Float multiply mean=$0.49\,\mu s$')
    ax[1].plot(df.int_mult_xi,df.int_mult_f)
    ax[1].set_title('Integer multiply mean=$0.43\,\mu s$')
    ax[2].plot(df.unbiased_xi,df.unbiased_f)
    ax[2].set_title('Unbiased optimized mean=$0.44\,\mu s$')
    ax[3].plot(df.unbiased_opt_xi,df.unbiased_opt_f)
    ax[3].set_title('Unbiased mean=$0.53\,\mu s$')
    ax[0].set_ylabel('probability density estimate')

    fig.suptitle('Execution time to generate one random float [0,1)')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_xlabel(r'Time in $\mu s$')
