#include "../uz/uz_Trajectory/uz_Trajectory.h"
#include "../main.h"

  struct uz_Trajectory_config traj_speed = {
    .selection_interpolation = Linear,
    .selection_XAxis = Seconds,
    .StopStyle = ForceToZero,
    .RepeatStyle = Repeat_Inf,
    .Number_Sample_Points = 6U,
    .Sample_Amplitude_Y = {-200.0f, -200.0f, -600.0f, -600.0f, -600.0f, -200.0f},
    .Sample_Duration_X = {16.0f, 4.0f, 4.0f, 8.0f, 4.0f, 4.0f},
    .Repeats = 3U,
    .Stepwidth_ISR = (1.0f / UZ_PWM_FREQUENCY_RIGHT) * (Interrupt_ISR_freq_factor)
  };

  struct uz_Trajectory_config traj_current = {
    .selection_interpolation = Zero_Order_Hold,
    .selection_XAxis = Seconds,
    .StopStyle = ForceToZero,
    .RepeatStyle = Repeat_Inf,
    .Number_Sample_Points = 6U,
    .Sample_Amplitude_Y = {0.0f, 2.0f, 4.0f, 6.0f, 4.0f, 2.0f},
    .Sample_Duration_X = {4.0f, 4.0f, 4.0f, 16.0f, 4.0f, 8.0f},
    .Repeats = 3U,
    .Stepwidth_ISR = (1.0f / UZ_PWM_FREQUENCY_RIGHT) * (Interrupt_ISR_freq_factor)
  };



  uz_Trajectory_t* uz_trajectory_speed_init(void) {
	   return uz_Trajectory_init(traj_speed);
  }

  uz_Trajectory_t* uz_trajectory_current_init(void) {
	   return uz_Trajectory_init(traj_current);
  }
