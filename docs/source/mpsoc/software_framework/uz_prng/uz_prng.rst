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

  - Philox

    - https://github.com/efficient/fasst/blob/master/mica2/src/mica/util/philox/philox_random.h

  - Mersenne Twister

    - https://en.wikipedia.org/wiki/Mersenne_Twister
    - https://github.com/ESultanik/mtwister/blob/master/mtwister.c
    - 

  - https://en.wikipedia.org/wiki/Well_equidistributed_long-period_linear

  - https://en.wikipedia.org/wiki/Permuted_congruential_generator

    - https://www.pcg-random.org/pdf/hmc-cs-2014-0905.pdf
    - https://www.pcg-random.org/
    - https://github.com/imneme/pcg-c-basic/blob/master/pcg_basic.c



- Algorithms to force better uniform distribution:

    - https://en.wikipedia.org/wiki/Halton_sequence
    - https://observablehq.com/@jrus/halton
    - https://stackoverflow.com/questions/42661304/implementing-4-dimensional-halton-sequence
    - https://people.sc.fsu.edu/~jburkardt/cpp_src/halton/halton.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/halton/halton.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/uniform/uniform.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/ziggurat/ziggurat.html
    - https://people.sc.fsu.edu/~jburkardt/c_src/normal/normal.html
    - 

    - https://en.wikipedia.org/wiki/Latin_hypercube_sampling (Mostly for experiement setup)
    - 

- Possibly hardware-accelerate number generation

    - https://link.springer.com/article/10.1007/s11265-012-0684-4
    - 

- Test suite for random generators:

    - "Dieharder"
    - http://simul.iro.umontreal.ca/testu01/install.html
    

Implemented generators
----------------------

..	toctree::
    :maxdepth: 1
    :glob:
  
    uz_prng_squares/uz_prng_squares
    uz_prng_mtwister/uz_prng_mtwister