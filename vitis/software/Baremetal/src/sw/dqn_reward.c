//#include "dqn_reward.h"
//#include <math.h>
//#include "../uz/uz_dqn_reward_scaling/uz_dqn_reward_scaling.h"
//
//float position_scaled = 0.0f;
//float angle_scaled = 0.0f;
//float angle_derivative_scaled = 0.0f;
//
//float lambda_angle = 10.0f;
//float lambda_position = 1.0f;
//float lambda_angle_derivative = 0.25f;
//float penalty = 1000.0f;
//bool penalty = true;
//
//float calculate_reward_pendulum(float control_frequency, float position, float angle, float angle_derivative, bool apply_penalty)
//{
//    position_scaled = uz_dqn_scaling_log(position, 350.0f);
//    angle_scaled = uz_dqn_scaling_log(angle, M_PI);
//    angle_derivative_scaled = uz_dqn_scaling_log(angle_derivative, 20.0f);
//
//    float scaled_reward = (1.0f / control_frequency) * ((lambda_position * position_scaled) + (lambda_angle * angle_scaled) + (lambda_angle_derivative * angle_derivative_reward));
//    if (apply_penalty)
//    {
//        scaled_reward = scaled_reward - penalty;
//    }
//    return scaled_reward;
//}
