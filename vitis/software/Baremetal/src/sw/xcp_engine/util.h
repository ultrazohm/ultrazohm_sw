#pragma once
/*----------------------------------------------------------------------------
| File:
|   util.h
|
| Description:
|   A set of utility functions
|   1. Average and median filter
|   2. Linear regression filter
|   3. Pseudo random number generator
|   4. Clock synchronizer
|
|   Code released into public domain, no attribution required
 ----------------------------------------------------------------------------*/

#include <stdbool.h> /* bool   */
#include <stddef.h>  /* size_t */
#include <stdint.h>  /* int64_t, uint64_t */

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// Integer Median Filter

#define MEDIAN_FILTER_MAX_SIZE 31

typedef struct {
    int64_t samples[MEDIAN_FILTER_MAX_SIZE]; /* ring buffer (insertion order) */
    int order[MEDIAN_FILTER_MAX_SIZE];       /* indices sorted by value       */
    int size;                                /* window size (<= MAX_SIZE)  */
    int idx;                                 /* next write position        */
    int count;                               /* samples currently valid    */
} tMedianFilter;

void median_filter_init(tMedianFilter *f, size_t size);
int64_t median_filter_calc(tMedianFilter *f, int64_t v);
size_t median_filter_size(tMedianFilter *f);
size_t median_filter_count(tMedianFilter *f);

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// Integer Moving Average Filter

#define AVERAGE_FILTER_MAX_SIZE 60
typedef uint64_t tAverageFilterValue;

typedef struct average_filter {
    tAverageFilterValue a[AVERAGE_FILTER_MAX_SIZE]; // circular buffer for values
    tAverageFilterValue as;                         // running sum
    size_t size;                                    // filter window size (max samples)
    size_t ai;                                      // current index in circular buffer
    size_t count;                                   // current number of samples in buffer
} tAverageFilter;

void average_filter_init(tAverageFilter *f, size_t size);
tAverageFilterValue average_filter_calc(tAverageFilter *f, tAverageFilterValue v);
size_t average_filter_size(tAverageFilter *f);
size_t average_filter_count(tAverageFilter *f);
void average_filter_add(tAverageFilter *f, tAverageFilterValue offset);

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// Double Linreg filter

#define LINREG_FILTER_MAX_SIZE 120

typedef struct linreg_filter {
    double x[LINREG_FILTER_MAX_SIZE]; // circular buffer for x values
    double y[LINREG_FILTER_MAX_SIZE]; // circular buffer for y values
    size_t size;                      // filter window size (max samples)
    size_t ai;                        // current index in circular buffer
    size_t count;                     // current number of samples in buffer

    // State variables for interpolation
    double y_out; // last calculated y output value
    double slope; // last calculated slope
} tLinregFilter;

void linreg_filter_init(tLinregFilter *f, size_t size);
// slope_out is the calculated slope
// y_out is the interpolated y value at x (not the intercept!)
bool linreg_filter_calc(tLinregFilter *f, double x, double y, double *slope_out, double *y_out);
bool linreg_filter_compare(tLinregFilter *f1, tLinregFilter *f2, double x, double *slope_diff, double *y_diff);
size_t linreg_filter_size(tLinregFilter *f);
size_t linreg_filter_count(tLinregFilter *f);

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// Fast random number generation

// Seed the thread-local splitmix64 PRNG state (optional; auto-initialised)
void fast_rand_seed(uint64_t seed);

// Return a random number in [0, max)
uint64_t fast_rand(uint64_t max);

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
// Lightweight clock synchronizer

/*
 * Interpolates a target clock (t1) from a reference clock (t2) using consecutive (t1, t2) timestamp pairs.
 *
 * Synchronization modes:
 * SYNC_MODE_DEFAULT  Simple 2-point linear interpolation, no filtering.
 *                    Becomes synchronized after exactly two update pairs.
 *                    Suitable for low-jitter hardware timestamp sources.
 *
 * SYNC_MODE_PI       PI (proportional-integral) servo.
 *                    The proportional term corrects the current offset error
 *                    immediately; the integral term accumulates over many
 *                    cycles and tracks slowly changing drift caused by
 *                    oscillator temperature dependence.
 *                    Becomes synchronized after two pairs (same as DEFAULT)
 *                    and then continuously refines the drift estimate.
 *                    Suitable for jittery timestamp sources and applications
 *                    where drift is expected to change over time.
 */
#define SYNC_MODE_DEFAULT 0
#define SYNC_MODE_PI 1

/*
 * Parameters for SYNC_MODE_PI
 *   Kp = 1 / 2^kp_shift  [ppb per ns of offset error]
 *   Ki = 1 / 2^ki_shift  [ppb per ns of offset error per cycle]
 *
 *   At 1 Hz update rate the default values give:
 *     Kp = 1/4 = 0.25 ppb/ns  -> offset step converges in ~4 cycles
 *     Ki = 1/64               -> integral time constant ~64 s
 *
 *   Tune kp_shift down (larger Kp) for faster response.
 *   Tune ki_shift up  (smaller Ki) to reject more jitter in the integral.
 *   The gains can be overridden by writing kp_shift / ki_shift directly
 *   after syncInit() and before the first syncUpdate() call.
 */

/* Default PI gain exponents */
#define SYNC_PI_KP_SHIFT_DEFAULT 2 /* Kp = 1/4   ppb/ns                   */
#define SYNC_PI_KI_SHIFT_DEFAULT 6 /* Ki = 1/64  ppb/ns/cycle             */

/* Anti-windup clamp for the PI integral accumulator (ppb).
 * Limits the integral to ±500 ppm, far beyond any realistic oscillator
 * drift, preventing run-away after a long gap in update pairs.          */
#define SYNC_PI_INTEGRAL_CLAMP 500000LL

/* Default median pre-filter window size (must be odd).
 * Used by both SYNC_MODE_DEFAULT and SYNC_MODE_PI when use_median = true.
 * Override by calling median_filter_init(&s->median_filter, N) after
 * syncInit() and before the first syncUpdate() call.                    */
#define SYNC_MEDIAN_WINDOW_DEFAULT 7

/* Clock synchronizer state */
typedef struct {

    bool is_sync;         /* true once drift has been estimated (>= 2 pairs) */
    uint32_t cycle_count; /* total number of syncUpdate() calls              */
    uint8_t mode;         /* SYNC_MODE_DEFAULT or SYNC_MODE_PI               */

    /* Interpolation anchor: most recently accepted timestamp pair */
    uint64_t t1; /* target clock value at last update, ns           */
    uint64_t t2; /* reference clock value at last update, ns        */

    /*
     * Clock ratio expressed as drift in parts-per-billion (int64_t):
     *   drift_ppb = (dt1 - dt2) * 1_000_000_000 / dt2
     * Positive  -> t1 runs faster than t2.
     * Zero      -> clocks advance at exactly the same rate.
     */
    int64_t drift_ppb;

    /*
     * Last value returned by syncInterpolateT1FromT2().
     * Used to guarantee a monotonically increasing output even across anchor
     * transitions caused by syncUpdate().
     * NOTE: not thread-safe; protect externally if called from multiple threads.
     */
    uint64_t last_t1_out;

    /* PI servo state (SYNC_MODE_PI only) ----------------------------------- */

    /*
     * Raw error accumulator in ns.
     * Errors are summed here before dividing by 2^ki_shift to derive
     * pi_drift.  Accumulating raw values avoids a dead zone: if errors were
     * divided before accumulation, any |error| < 2^ki_shift would truncate
     * to zero and the integral would never respond to small persistent offsets.
     * Clamped to +/- (SYNC_PI_INTEGRAL_CLAMP << ki_shift) for anti-windup.
     */
    int64_t pi_error_accum;

    /*
     * Integral output in ppb, derived from pi_error_accum each cycle:
     *   pi_drift = pi_error_accum / 2^ki_shift
     * Tracks the long-term frequency offset between t1 and t2 clocks.
     */
    int64_t pi_drift;

    uint8_t kp_shift; /* P gain exponent: Kp = 1/2^kp_shift  [ppb/ns]       */
    uint8_t ki_shift; /* I gain exponent: Ki = 1/2^ki_shift  [ppb/ns/cycle]  */
    /* Median pre-filter (both modes) -------------------------------------- */

    /*
     * When use_median is true, each raw drift_ppb estimate (DEFAULT mode) or
     * each error_ns value (PI mode) is passed through the median filter
     * before entering the main estimator.  This rejects outlier pairs caused
     * by e.g. occasional software-fallback timestamps mixed with hardware
     * timestamps, without affecting steady-state accuracy.
     *
     * Default: false (disabled). Enable by setting use_median = true after
     * syncInit().  The window size is SYNC_MEDIAN_WINDOW_DEFAULT by default;
     * override with median_filter_init(&s->median_filter, N).
     */
    bool use_median;
    tMedianFilter median_filter;
} tClockSynchronizer;

/* Initialize (or reset) a clock synchronizer.
 * mode: SYNC_MODE_DEFAULT or SYNC_MODE_PI.
 * median_filter_size: Set to 0 for no filtering
 */
void syncInit(tClockSynchronizer *s, uint8_t mode, size_t median_filter_size);

/* Return true if the synchronizer has received at least two timestamp pairs
 * and is ready to interpolate.                                          */
bool syncState(const tClockSynchronizer *s);

/* Interpolate t1 (target clock) from t2 (reference clock).
 *
 * All arithmetic is performed in int64_t for precision and speed.
 * Large PTP epoch values in t2 have no impact on precision because only
 * the delta from the last anchor is used.
 *
 * The output is guaranteed to be monotonically increasing.
 *
 * Precondition: syncState(s) == true                                    */
uint64_t syncInterpolateT1(tClockSynchronizer *s, uint64_t t2);

/* Feed a new (t1, t2) timestamp pair.
 *
 * t1 - target clock timestamp (e.g. NIC hardware clock) in ns
 * t2 - reference wallclock clock timestamp (e.g. CLOCK_REALTIME) in ns
 *
 * Both clocks must use nanosecond resolution.
 * Epochs may be arbitrary and independent -- they do not need to match.
 * Timestamps within each clock must be monotonically increasing.
 * Expected call rate: approximately once per second.                    */
void syncUpdate(tClockSynchronizer *s, uint64_t t1, uint64_t t2);

/* ---------------------------------------------------------------------------
 * syncSet
 *
 * Feed a new (t1, t2) timestamp anchor and set drift parameters directly.
 * Used for testing and simulation of clock properties
 * -------------------------------------------------------------------------*/
void syncSet(tClockSynchronizer *s, uint64_t t1, int64_t t2, int64_t drift_ppb);

#ifdef __cplusplus
}
#endif
