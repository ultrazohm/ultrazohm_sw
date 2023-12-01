===============
Halton sequence
===============

- https://de.mathworks.com/help/stats/pseudorandom-and-quasi-random-number-generation.html?s_tid=CRUX_lftnav
- https://de.mathworks.com/help/stats/sobolset.html
- https://en.wikipedia.org/wiki/Sobol_sequence

- https://en.wikipedia.org/wiki/Low-discrepancy_sequence

- https://en.wikipedia.org/wiki/Halton_sequence
- https://github.com/CarlosLunaMota/CLM_LIBS

- Algorithms to force better uniform distribution:

    - https://en.wikipedia.org/wiki/Halton_sequence
    - https://observablehq.com/@jrus/halton
    - https://stackoverflow.com/questions/42661304/implementing-4-dimensional-halton-sequence
    - https://people.sc.fsu.edu/~jburkardt/cpp_src/halton/halton.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/halton/halton.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/uniform/uniform.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/ziggurat/ziggurat.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/normal/normal.html

.. plot::

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_halton_float.csv', header=None, names=columns)
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

   import matplotlib.pyplot as plt
   import pandas as pd

   columns=['index','number']
   df=pd.read_csv('uz_prng_halton_uint32.csv', header=None, names=columns)
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

