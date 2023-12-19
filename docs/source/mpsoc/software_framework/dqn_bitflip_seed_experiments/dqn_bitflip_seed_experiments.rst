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

Open Questions:

- How unrelated are multiple streams of random numbers for different streams in the different PRNGs?
- Is non-uniformity actually better for Init?
- Maybe, because symmetry is broken?


todos:

- Eval Runs plotten
- Zusammenfassung finden
- Tests wiederholen für schwerere Probleme (mehr bits in Bitflip)
- Auf PT1 Training übertragen
- Philox implementieren?

Notes:

- bitflip with 20.000 epsioden statt 5.000 episoden bei Buffersize 50000U sorgt dafür, dass die Performance über die Zeit schlechter wird
- Buffersize auf 200000U erhöht -> Wirkt nicht, als hätte es etwas gebracht - ggf. experiment gar nicht funktioniert?



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

- Plot 3

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_experiments.py boxplots_for_all_experiments_reordered
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
Use ``exp_uz_bitflip_10_seeds`` as base.
Change the init generator for each to Halton, rest of the experiment stays the same.

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_halton_ablation.py compare_boxplots
            :scale: 30
            :caption: Boxplot over perofrmance for ``10_seeds`` and using Halton sequence for init, exploration, or training sampliöng. As can be seen, using Halton sequence for exploration or initialization is decremental to performance.

- Conclusion: Twister seems really solid
- Using Halton in Training might be beneficial, probably because sampling uniform instead of skewed sampling is just really good (obv.)
- Halton for init makes no sense due to large dimensions
- Using 1-D Halton sequence for exploration might suffer since exploration requires 2 random numbers (if exploration should occur and what action should be choosen)

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_halton_ablation.py focus_halton_training
            :scale: 30
            :caption: Boxplot over performance for ``10_seeds`` vs using Halton for training sampling

Halton special test
-------------------

- Special test: using Halton in exploration only for calculation of epsilon or for determining an action
- uz_dqn has to be changed for this experiment
- For ``twister_halton_action``, uz_prng_get_uniform_float_zero_to_one is done with Twitster re-using the init PRNG instance
- For ``twister_halton_epsilon``, uz_prng_get_uniform_uint32_zero_to_range_int_mult is done with Twitster re-using the init PRNG instance
- 10-seeds experiment with all twister is used for comparison

.. code-block::

      if (uz_prng_get_uniform_float_zero_to_one(self->rand_instance_exploration) < self->epsilon)
      {
          actionind = uz_prng_get_uniform_uint32_zero_to_range_int_mult(self->rand_instance_exploration, self->number_of_actions);
      }
      else
      {
          actionind = uz_matrix_get_max_index(outputcritic);
      }

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_halton_special.py focus_halton_training
            :scale: 30
            :caption: Boxplot over 10 random seeds for Twister everything from 10 seeds (red), calculation of epsilon with Halton (orange), determination of random action with Halton (blue), reusing init PRNG for epsilon calculation and action selection (green). Not sure why re-use of init makes stuff worse in ``init_init``.

- Somehow halton does not improve anything? Twister everything is just super good with individual generators


Different generators for exploration, init, and training
--------------------------------------------------------

- Using Mersenne Twister for everything, except for one of the tasks

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_ablation_different_generators.py compare_boxplots_hue_prng
            :scale: 30
            :caption: Each group compares using each generator either for training sampling, init, or exploration. Everything except halton improves when used for training sampling. Everything is kind of close, except for the initialization.

- Look into what is going on with the initialization of the networks when not using Twister.



Twister for Init, different PRNG for other 
------------------------------------------

- Using Mersenne Twister for init, other PRNG for exploration and training

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_different_prng_but_twister_init.py compare_boxplots_hue_prng
            :scale: 30
            :caption: Using Squares or PCG for everything except for Init seems to improve behavior.

- Why is init with Twister so good?

.. plot:: ../../vitis/software/Baremetal/test/uz/uz_dqn/plot_bitflip_different_prng_but_twister_init.py plot_individual
            :scale: 30
            :caption: Plot all individual runs

