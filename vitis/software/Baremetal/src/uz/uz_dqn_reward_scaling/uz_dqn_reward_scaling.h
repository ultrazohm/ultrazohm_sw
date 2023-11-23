#ifndef UZ_DQN_REWARD_SCALING_H
#define UZ_DQN_REWARD_SCALING_H

/**
 * @brief Calculates reward between 0..1 based on input x between +-inf using sigmoid function.
 *        x_bad_performance determines the value of x that is bad performance, which maps to 0.05.
 *        Good performance is assumed to be x=0, which maps to reward=0.95.
 *        -> x is typically the error between set-point and actual value, absolute is calculated internally
 *
 * @param x Performance criteria for which a reward is calculated
 * @param x_bad_performance Value of x that is bad performance (=> reward=0.05)
 * @return float Reward scaled [0...0.95]
 */
float uz_dqn_scaling_log(float x, float x_bad_performance);

#endif // UZ_DQN_REWARD_SCALING_H