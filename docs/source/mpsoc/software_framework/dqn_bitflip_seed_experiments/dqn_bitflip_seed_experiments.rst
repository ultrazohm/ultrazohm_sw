============================
DQN Bitflip seed experiments
============================

The following plots show the results of an experiment with the Bitflip enviroment using 4 bits.
For each generator, Mersenne Twister, Halton, PCG, Squares, and Xoshiro128++, the training is started for 10 different random seeds.
For the enviroment, Mersenne Twister and 10x the same random seed are used.
Thus, any variation is due to the agent behavior and not related to the enviroment.
Ideally, the reward is as close to 1 as possible and the deviation is as low as possible.
As can be seen, PCG performs best in this experiment.
Halton shows a really bad performance, failing to solve the Bitflip environment and having a large standard distribution.
This is likely to the fact that each generator uses the same seed for each run and 3 generators are used.
Therefore, the random numbers are not independent of each other.


.. Using tables for side by side figure:
.. list-table::

    * - .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_multiple_bitflip_seeds_individual_runs.py
            :caption: Individual runs of different generators
            :scale: 30

      - .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_multiple_bitflip_seeds_errorbar_individual.py
            :caption: Mean over 10 runs for each generator and standard deviation (3 sigma) for each generator.
            :scale: 30

      - .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_multiple_bitflip_seeds_boxplot.py
            :caption: Boxplot over 10 runs for each generator. 
            :scale: 30