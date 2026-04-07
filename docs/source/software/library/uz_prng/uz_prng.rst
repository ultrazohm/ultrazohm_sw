.. _uz_prng:

====================================
Pseudorandom number generator (PRNG)
====================================

This software module implements different pseudorandom number generators (PRNGs) [[#prng_wiki]_], [[#prng_wiki_list]_].
The implemented generators return uniformly distributed unsigned 32-bit integers.
All implemented generators are not cryptographically secure and are intended for engineering applications such as neural network initialization or random excitation for model identification.
Additional reading:

- Paper regarding different generators:  https://ieeexplore.ieee.org/abstract/document/9132873
- Possibly hardware-accelerate number generation: https://link.springer.com/article/10.1007/s11265-012-0684-
- *Dieharder* is a commonly used test suite for random generators: http://simul.iro.umontreal.ca/testu01/install.html

Implementation
==============

The module ``uz_prng`` is a generic implementation for PRNGs.
The actual generation of the random numbers is facilitated by the `Implemented generators`_, each with specific properties.
Other software modules can depend on ``uz_prng`` instead of the individual generators, which enables changing the generator for experiments without code changes.
In addition to generating uniform distributions of ``uint32_t`` type, different scaling methods and generation of bounded ``uint32_t`` as well as ``float`` are supported.

Seeds
-----

PRNGs use an initial condition called **seed** that determines the specific random number stream.
The sequence of random numbers is deterministic for a given seed, i.e., initializing ``uz_prng`` with a given seed and generator type always returns the same sequence.
The initialization of ``uz_prng`` passes the seed to the specific algorithm.
The details of each generator seed are as follows:

- ``uz_prng_squares``: if the seed is between 0 and 29, a pre-generated key is used (recommended). Otherwise, the value is used as the key.
- ``uz_prng_mtwister``: 32-bit seed. Since ``uz_prng_init`` uses 64-bit seeds, the upper 32-bits are ignored if Mersenne Twister is used.
- ``uz_prng_halton``: seed must be a prime number.
- ``uz_prng_pcg``: 64-bit random seed. The initial sequence controlling substreams is arbitrarily set to 54.
- ``uz_prng_xoshiro``: 64-bit random seed which is shuffled using splitmix64 as recommended by algorithm author.

Implemented generators
----------------------

..  toctree::
    :maxdepth: 1
    :glob:
  
    uz_prng_squares/uz_prng_squares
    uz_prng_mtwister/uz_prng_mtwister
    uz_prng_pcg/uz_prng_pcg
    uz_prng_xoshiro/uz_prng_xoshiro
    uz_prng_halton/uz_prng_halton


Distribution of PRNG [0,UINT32_MAX]
===================================

1D-Case
-------

The following figure compares the distributions of the different implemented PRNGs by showing the generated numbers' histogram after different sample sizes are drawn.
The distributions of the generated numbers tend towards a uniform distribution for an increasing number of samples.

.. plot:: 
    :caption: Histogram for different numbers of samples taken from the implemented generators. Samples are generated using ``uz_prng_X_get_uniform_uint32``, where X is the name of the specific generator. For an increasing number of taken samples, the distribution tends towards uniform data. However, for a small number of samples, the generated random numbers can deviate from a uniform distribution considerably (as is the case with *real* randomness, i.e., law of large numbers). As can be seen, the Halton sequence produces uniformly distributed values already for a low number of samples.
    
     import matplotlib.pyplot as plt
     import pandas as pd
     import matplotlib.ticker as mtick
     path_to_tests=''
     columns=['index','number']
     xoshiro=pd.read_csv(path_to_tests+'uz_prng_xoshiro/uz_prng_xoshiro_uint32.csv', header=None, names=columns)
     twister=pd.read_csv(path_to_tests+'uz_prng_mtwister/uz_prng_mtwister_uint32.csv', header=None, names=columns)
     pcg=pd.read_csv(path_to_tests+'uz_prng_pcg/uz_prng_pcg_uint32.csv', header=None, names=columns)
     squares=pd.read_csv(path_to_tests+'uz_prng_squares/uz_prng_squares_uint32.csv', header=None, names=columns)
     halton=pd.read_csv(path_to_tests+'uz_prng_halton/uz_prng_halton_uint32.csv', header=None, names=columns)
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

.. _uz_prng_2d_case:

2D Case
-------

Applications may require the generation of random numbers for n-dimensions.
One example is a random sampling of the possible operating range of an electrical machine, i.e., the rotational speed and output torque.
Other examples include the identification of model parameters, which might require a random excitation to yield transfer functions.
Random sampling for multiple dimensions using the :ref:`uz_prng_halton` requires special care.
If a 2D-Halton sequence is required, ``uz_prng`` can not be used; use ``uz_prng_halton`` directly.
The following figure shows the generated distributions of different PRNGs in the 2D case.

.. plot:: software/library/uz_prng/uz_prng_2d_compare.py
    :caption: Generated random values generated with ``uz_prng_get_uniform_uint32_zero_to_uint32_max`` using different generators plotted as 2-dimensional data. Using ``uz_prng_generator_halton`` does not yield a random pattern but a linear relationship between the generated values. Using ``uz_prng_halton_get_uniform_float_2d`` generates a proper Halton sequence for 2 dimensions.


Distributions for multiple seeds
================================

Bounded integer
---------------

The generation of bounded integer values is not straightforward.
Essentially, there are methods for scaling uniform distributions in the interval [0,UINT32_MAX] to [0,upper_bound], which are simple but slightly biased, and more complex methods that are not biased.
Bias and unbiased methods are implemented.
See the following for more information:

- https://www.pcg-random.org/posts/bounded-rands.html
- https://c-faq.com/lib/randrange.html
- https://github.com/imneme/bounded-rands

Note that the bias happens rarely.
I.e., in the Ceedling tests, 50000 random samples for different seeds and generators do not yield any difference between biased and unbiased transformation to bounded integers.
A loop generating random integers like so:

.. code-block:: c

    #pragma GCC push_options
    #pragma GCC optimize("O0")
    void test_uz_prng_ever_biased(void)
    {
        uz_prng_t *pcg = uz_prng_init(uz_prng_generator_pcg, uz_prng_float_scale_fp_multiply, 0U);
        volatile uint32_t unbiased = 0;
        volatile uint32_t biased = 0;

        for (uint32_t i = 0U; i < UINT32_MAX; i++)
        {
            unbiased = uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(pcg, 9);
            biased = uz_prng_get_uniform_uint32_zero_to_range_int_mult(pcg, 9);
            TEST_ASSERT_EQUAL_UINT32(unbiased, biased);
        }
    }
    #pragma GCC pop_options

Will fail the test, i.e., some random numbers differ between biased and unbiased versions.
Note that the GCC options are required to prevent that the loop is not executed since both variables are unused for the compiler.

.. plot:: software/library/uz_prng/density_plot_multipe_seeds_biased_uint1000.py
    :caption: Histogram of ``uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt(X,9U)`` (left) and ``uz_prng_get_uniform_uint32_zero_to_range_int_mult(X,9U)`` (right) for the implemented generators for 10 different random seeds. The different distributions of the generators, as well as the random seeds, result in varying distributions of random numbers. Within this test, no difference between the biased and unbiased versions is observed. Note that this bias is more pronounced for large numbers in the range.
    

Uniform distribution float [0,1)
--------------------------------

The following figure highlights the dependency of the different generators on the random seed.
A sample of 5000 values is taken from each generator for ten different random seeds.
As can be seen, the specific distribution generated varies for the given seed and the used generator.


.. plot:: software/library/uz_prng/density_plot_multiple_seeds.py
    :caption: Density distribution of each generator calculated using Matlab ksdensity for 10 random seeds each. Values generated by ``uz_prng_get_uniform_float_zero_to_one`` using ``uz_prng_float_scale_fp_multiply``.
    

Normal distribution
-------------------

Generating normal distributions is implemented by the polar method [[#polar_method]_], which is a variation of the Box-Muller transformation [[#box_mueller]_].


.. plot:: software/library/uz_prng/density_plot_normal_distribution.py
    :caption: Density distribution of 5000 samples generated by ``uz_prng_get_normal_float`` using ``uz_prng_generator_squares`` as PRNG. Comparison of three different random seeds.
    

Calculation time
================

The following calculation times are measured using the mean execution time required to generate one ``uint32_t`` for each generator.
Measurements are facilitated on the R5 of the UltraZohm.
The measurement principle uses :ref:`systemTimeR5` to log the execution time of the ISR.
The following code is used in the ISR.

.. code-block:: c

    if (current_state == control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
        for (uint32_t i = 0; i < NUMBER_OF_PRNG_RUNS_PER_ISR; i++)
        {
            rnd_numbers[i]=uz_prng_get_uniform_uint32_zero_to_uint32_max(generator);
        }
    }

If the system is not in the control state, the baseline execution without generating random values is :math:`16.2\,\mu s`.
This baseline is subtracted from execution time and divided by the number of generated PRNGs to yield the generation time for one value.
Note that the smallest difference between execution times by this method is :math:`10\,ns` due to the clock frequency of the global counter in the FPGA.
Therefore, the measurements should be used as a rough estimation.

Generate one rand [0,UINT32_MAX]
--------------------------------

The measurement is based on generating 20 values per ISR over 4000 ISR cycles by calling ``uz_prng_get_uniform_uint32_zero_to_uint32_max``.

Results:

- ``uz_prng_generator_xoshiro`` and ``uz_prng_generator_pcg`` are the fastest generators
- ``uz_prng_generator_mtwister`` has a low mean calculation time. However, the internal state is shuffled every 620 calls, resulting in a spike in calculation time. This shuffle of the state is inherent to the algorithm. Thus, ``uz_prng_generator_mtwister`` is not recommended for usage in the ISR.
- ``uz_prng_generator_halton`` seems to increase calculation time with the number of samples taken and approaches :math:`0.6\,\mu s` per random number, see `Halton timing`_.


.. plot::
    :caption: Measured execution time of ``uz_prng_get_uniform_uint32_zero_to_uint32_max`` for different generators.

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




Float [0,1)
-----------

- uz_prng_scale_to_float_zero_to_one_divide
- uz_prng_scale_to_float_zero_to_one_multiply = 10ns overhead
- uz_prng_scale_to_float_zero_to_one_shift_multiply = 8ns -> This is the fastest
- All three functions do not have a measurable difference in execution time
- Generating one float (0,1) using pcg takes 0.153 us
- Additional calculation time for float is approx. 10ns compared to uint32

The following table shows the calculation time of calling ``uz_prng_get_uniform_float_zero_to_one`` once and compares the different settings of ``uz_prng_float_scale_method``.
The results do not show a meaningful difference.
Measurements 

================ =====================
Method           Execution time
================ =====================
fp_muliply_mean  :math:`0.1985\,\mu s`
fp_divide_mean   :math:`0.1983\,\mu s`
shift_multi_mean :math:`0.1942\,\mu s`
================ =====================

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_float.csv")

    fig, ax = plt.subplots(1,3,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.fp_muliply)
    ax[0].set_title('Float multiply mean=$0.0.198\,\mu s$')
    ax[1].plot(df.fp_divide)
    ax[1].set_title('Float divide mean=$0.198\,\mu s$')
    ax[2].plot(df.shift_multi)
    ax[2].set_title('Shift multiply mean=$0.194\,\mu s$')

    ax[0].set_ylabel(r'Time in $\mu s$')
    fig.suptitle('Execution time to generate one random float [0,1)')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.set_ylim(0.19,0.2)
        ax.set_xlim(0,200)
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_xlabel('ISR sample')

The following figure shows the density distribution over 10000 samples of the execution times calculated using `Matlab ksdensity <https://de.mathworks.com/help/stats/ksdensity.html>`_.

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_float_density.csv")

    fig, ax = plt.subplots(1,3,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.fp_multiply_xi,df.fp_multiply_f)
    ax[0].set_title('Float multiply mean=$0.198\,\mu s$')
    ax[1].plot(df.fp_divide_xi,df.fp_divide_f)
    ax[1].set_title('Float divide mean=$0.198\,\mu s$')
    ax[2].plot(df.shift_multi_xi,df.shift_multi_f)
    ax[2].set_title('Shift multiply mean=$0.194\,\mu s$')
    ax[0].set_xlabel('probability density estimate')
    ax[1].set_xlabel('probability density estimate')
    ax[2].set_xlabel('probability density estimate')

    fig.suptitle('Execution time to generate one random float [0,1)')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_ylabel('probability density estimate')



uint32_t in range [0,range)
---------------------------

- int multi is the fastest but is biased
- unbiased opt is unbiased and faster than unbiased
- No reason to use float multiplication version
- Use unbiased mean if comparability with other Frameworks that use Lemire's method (https://arxiv.org/abs/1805.10941) is desired

================= =====================
Method            Execution time
================= =====================
float_mult_mean   :math:`0.1955\,\mu s`
int_mult_mean     :math:`0.1705\,\mu s`
unbiased_mean     :math:`0.2108\,\mu s`
unbiased_opt_mean :math:`0.1761\,\mu s`
================= =====================


.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_bounded_uint32_density.csv")

    fig, ax = plt.subplots(1,4,layout='constrained',figsize=(13,5),sharey=True)

    ax[0].plot(df.float_mult_xi,df.float_mult_f)
    ax[0].set_title('Float multiply mean=$0.196\,\mu s$')
    ax[1].plot(df.int_mult_xi,df.int_mult_f)
    ax[1].set_title('Integer multiply mean=$0.170\,\mu s$')
    ax[2].plot(df.unbiased_xi,df.unbiased_f)
    ax[2].set_title('Unbiased optimized mean=$0.176\,\mu s$')
    ax[3].plot(df.unbiased_opt_xi,df.unbiased_opt_f)
    ax[3].set_title('Unbiased mean=$0.211\,\mu s$')
    ax[0].set_ylabel('probability density estimate')

    fig.suptitle('Execution time to generate one random float [0,1)')

    for ax in ax.flat:
        ax.grid(True,which='both')
        ax.yaxis.set_minor_locator(AutoMinorLocator())
        ax.set_xlabel(r'Time in $\mu s$')

Halton timing
-------------

The calculation time for ``uz_prng_generator_halton`` increases with the number of samples taken from the Halton sequence.
This seems to be related to the fact that the implementation relies on a loop to find the nth value of the Halton sequence, which requires more passes for increasing numbers of :math:`n`.
The following figure shows the execution time of ``uz_prng_generator_halton`` for 874,821,900 samples, which did not result in a settled calculation time.
The seed is set to 7 in this experiment; the behavior probably depends on the starting prime number.
Usage of ``uz_prng_generator_halton`` in long-running applications (multiple days) should be handled carefully.

.. warning:: Halton generator draws the :math:`i-th` number of the Halton sequence of the starting prime number. Therefore, the internal counter will overflow after 4,294,967,295 (i.e., UINT32_MAX) drawn samples. Note that `unsigned integer wrap <https://www.gnu.org/software/autoconf/manual/autoconf-2.63/html_node/Integer-Overflow-Basics.html>`_, therefore, the Halton sequence will repeat after 2^32-1 calls.

.. plot::

    import matplotlib.pyplot as plt
    import pandas as pd
    import numpy as np
    from matplotlib.ticker import AutoMinorLocator, MultipleLocator

    df = pd.read_csv("generator_isr_halton_long_log.csv")

    fig, ax = plt.subplots(1,1,layout='constrained',figsize=(13,5))
    # Dataset is without offset and for 20 rand numbers -> subtract offset of 16.2us and divide by number of generated rand numbers
    ax.plot(df.Var1, (df.y-16.2)/20) 
    fig.suptitle('Execution time to generate one random uint32_t')
    ax.grid(True,which='both')
    ax.set_ylim(0,0.7)
    ax.yaxis.set_minor_locator(AutoMinorLocator())
    ax.set_xlabel('ISR sample')
    ax.set_ylabel(r'Time in $\mu s$')




Reference
=========

.. doxygentypedef:: uz_prng_t

.. doxygenenum:: uz_prng_generator

.. doxygenenum:: uz_prng_float_scale_method

.. doxygenfunction:: uz_prng_init

.. doxygenfunction:: uz_prng_get_uniform_uint32_zero_to_uint32_max

.. doxygenfunction:: uz_prng_get_uniform_uint32_zero_to_range_unbiased

.. doxygenfunction:: uz_prng_get_uniform_uint32_zero_to_range_unbiased_opt

.. doxygenfunction:: uz_prng_get_uniform_uint32_zero_to_range_float_mult

.. doxygenfunction:: uz_prng_get_uniform_uint32_zero_to_range_int_mult

.. doxygenfunction:: uz_prng_get_uniform_bool

.. doxygenfunction:: uz_prng_get_uniform_float_zero_to_one
    
.. doxygenfunction:: uz_prng_get_uniform_float_min_to_max

.. doxygenfunction:: uz_prng_get_normal_float



Implementation details
======================

This module uses a pointer of type ``void`` internally to be able to provide a generic interface for different generator types.
Specifically, each generator has a type, e.g., ``uz_prng_squares_t`` or ``uz_prng_pcg_t``.
The initialization function of these generators returns a pointer of type ``uz_prng_X_t``, with ``X`` being the specific generator.
This type is cast to void to store the pointer independent of the generator.
This approach decreases type safety, but enables flexibility.

Sources
=======

.. [#prng_wiki] https://en.wikipedia.org/wiki/Pseudorandom_number_generator
.. [#prng_wiki_list] https://en.wikipedia.org/wiki/List_of_random_number_generators#cite_note-38
.. [#polar_method] https://de.wikipedia.org/wiki/Polar-Methode
.. [#box_mueller] https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform

