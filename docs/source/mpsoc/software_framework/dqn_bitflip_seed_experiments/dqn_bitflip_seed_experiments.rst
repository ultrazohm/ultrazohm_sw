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


exp_uz_bitflip_10_seeds
=======================

- Individual PRNG for Exploration, Initialization, and Training
- Each Generator for each exp,init,train has a specific, individual seed -> 30 seeds total

.. Using tables for side by side figure:
.. list-table::

    * - 10 runs of different seeds for each generator ``exp_uz_bitflip_10_seeds``
         .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py plot_10_seeds
            :scale: 30

      - 10 runs of different seeds for each generator ``exp_uz_bitflip_10_other_seeds`` but a different set of seeds for Twister, Xoshiro128 and PCG (Squares and Halton have same seeds)
         .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py plot_10_other_seeds
            :scale: 30

      - 10 other seeds but each individual generator (exp, init, training) has the same seed, yielding the same random distribution
         .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py plot_10_other_seeds_wrong
            :scale: 30

      - 10 seeds but only one generator is used for exp., init., training
         .. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py plot_only_one_generator
            :scale: 30

- Plot 1 


.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py boxplots_for_all_experiments
            :scale: 30

- Plot 2

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py compare_boxplots
            :scale: 30

- Conclusion: it is not clear, what exactly influences the performance
- Mersenne Twister performance is bad, if the individual generators have the same random seed and if only one random seed is used
- PCG is best if only one generator is used for some reason
- Halton shows bad performance, probably due to problems with initialization
- "Which" set of random seeds is used does not seem to make much of a difference

Inverted ablation studies
=========================

Ablation studies take one characteristic of ML algorithms away and see if the behavior changes.
Inverted ablation study: test if using Halton sequences improve the behavior of the RL training, i.e., reduce the variance in the training.
Idea: Take one of the setup's and change only one of the generators.
Question: which one?
Since Mersenne Twister is default most of the time, all comparisons are done with 