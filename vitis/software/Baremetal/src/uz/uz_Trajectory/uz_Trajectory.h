#ifndef UZ_TRAJECTORY_H
#define UZ_TRAJECTORY_H
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Maximum number of samples that can be stored. Should be as small as possible to save resources.
 * 
 */
#define MAX_TRAJECTORY_SAMPLES 	20U

/*! enum for readable configuration of the interpolation type */
enum uz_Trajectory_interpolation_selection {
	Zero_Order_Hold = 0,
	Linear
};

/*! enum for readable configuration of the X-Axis-Style */
enum uz_Trajectory_XTicks_selection {
	ISR_Ticks = 0,
	MicroSeconds,
	MilliSeconds,
	Seconds
};
/*! enum for readable configuration of the repeat behavior*/
enum uz_Trajectory_Repeat_selection {
	Repeat_Times = 0,
	Repeat_Inf
};

/*! enum for readable configuration of the output behavior */
enum uz_Trajectory_Stop_Output_selection {
	ForceToZero = 0,
	HoldLast
};

/**
 * @brief configuration struct for a trajectory generator.
 *
 */
struct uz_Trajectory_config {
	enum uz_Trajectory_interpolation_selection selection_interpolation; /**< Interpolation type selection \n */
	enum uz_Trajectory_XTicks_selection selection_XAxis; /**< X-Axis-Style selection \n */
	enum uz_Trajectory_Stop_Output_selection StopStyle; /**< Defines the behavior when reaching the end or trajectory is stopped \n */
	enum uz_Trajectory_Repeat_selection RepeatStyle; /**< Defines whether the playback process is to be repeated x times or infinitely \n */
    uint32_t Number_Sample_Points; /**< Number of samples of the signal to be used. Can be used to display only the first X values. \n If this feature isn't needed, set his value to MAX_TRAJECTORY_SAMPLES \n */
	float Sample_Amplitude_Y[MAX_TRAJECTORY_SAMPLES]; /**< Y-Axis-Amplitude of the signal \n */
	float Sample_Duration_X[MAX_TRAJECTORY_SAMPLES]; /**< X-Axis-Duration of each Sample of the signal \n */
	uint32_t Repeats; /**< Number of repeats \n */
	float Stepwidth_ISR; /**< Time of the Stepwidth in with the Trajectory is called \n */
};

/**
 * @brief Object definition for uz_Trajectory_t
 *
 */
typedef struct uz_Trajectory_t uz_Trajectory_t;

/**
 * @brief Initialization of the Trajectory object
 *
 * @param config uz_Trajectory_config configuration struct
 * @return Pointer to uz_Trajectory_t object
 */
uz_Trajectory_t* uz_Trajectory_init(struct uz_Trajectory_config config);

/**
 * @brief Starts the trajectory.
 *
 * @param self pointer to uz_Trajectory_t object
 */
void uz_Trajectory_Start(uz_Trajectory_t* self);

/**
 * @brief Stops the trajectory.
 *
 * @param self pointer to uz_Trajectory_t object
 */
void uz_Trajectory_Stop(uz_Trajectory_t* self);

/**
 * @brief Resets the trajectory.
 *
 * @param self pointer to uz_Trajectory_t object
 */
void uz_Trajectory_Reset(uz_Trajectory_t* self);

/**
 * @brief Outputs the calculated trajectory.
 *
 * @param self pointer to uz_Trajectory_t object
 * @return float Returns current trajectory step
 */
float uz_Trajectory_Step(uz_Trajectory_t* self);


#endif // UZ_TRAJECTORY_H
