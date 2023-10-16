#ifndef UZ_TRAJECtory_H
#define UZ_TRAJECtory_H
#include <stdbool.h>

/**
 * @brief Maximum number of samples that can be stored. Should be as small as possible to save resources.
 * 
 */
#define Max_Trajectory_Samples	20

/*! enum for readable configuration of the interpolation type */
enum uz_Trajectory_interpolation_selection {
	Zero_Order_Hold = 0,
	Linear
};

/*! enum for readable configuration of the Y-Axis-Style */
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
	enum uz_Trajectory_XTicks_selection selection_YAxis; /**< X-Axis-Style selection \n */
	enum uz_Trajectory_Stop_Output_selection StopStyle; /**< Defines the behavior when reaching the end or trajectory is stopped \n */
	enum uz_Trajectory_Repeat_selection RepeatStyle; /**< Defines whether the playback process is to be repeated x times or infinitely \n */
    float Number_Sample_Points; /**< Number of samples of the signal to be used. Can be used to display only the first X values \n */
	float Sample_Amplitude_Y[Max_Trajectory_Samples]; /**< Y-Axis-Amplitude of the signal \n */
	float Sample_Duration_X[Max_Trajectory_Samples]; /**< X-Axis-Duration of each Sample of the signal \n */
	float Repeats; /**< Number of repeats \n */
	float Stepwidth_ISR; /**< Time of the Stepwidth in with the Trajecotrie is called \n */
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


#endif // UZ_TRAJECtory_H
