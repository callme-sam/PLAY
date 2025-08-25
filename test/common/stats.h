#ifndef STATS_H_
#define STATS_H_

#include "pmsis.h"

#define HOTTING 2
#define REPEAT  5

#ifdef STATS

/**
 * @brief Initializes performance counters and begins the measurement loop.
 *
 * @note This macro must be called first, before START_STATS() and STOP_STATS().
 */
#define INIT_STATS()    \
    unsigned long _cycles   = 0;    \
    unsigned long _active   = 0;    \
    unsigned long _instr    = 0;    \
    unsigned long _ldstall  = 0;    \
    unsigned long _imiss    = 0;    \
    unsigned long _ld       = 0;    \
    unsigned long _st       = 0;    \
                                    \
    for (int _k = 0; _k < HOTTING + REPEAT; _k++) { \
        pi_perf_conf( (1<<PI_PERF_CYCLES)           \
                    | (1<<PI_PERF_ACTIVE_CYCLES)    \
                    | (1<<PI_PERF_INSTR)            \
                    | (1<<PI_PERF_LD_STALL)         \
                    | (1<<PI_PERF_IMISS)            \
                    | (1<<PI_PERF_LD)               \
                    | (1<<PI_PERF_ST));             \

/**
 * @brief Resets and starts the performance counters.
 *
 * @note This macro must be called after INIT_STATS() within the measurement loop.
 */
#define START_STATS()       \
        pi_perf_reset();    \
        pi_perf_start();

/**
 * @brief Stops the performance counters, accumulates, and prints statistics.
 *
 * @note This macro must be called after START_STATS() within the measurement loop.
 */
#define STOP_STATS()    \
        pi_perf_stop(); \
                        \
        if (_k >= HOTTING) {                                    \
            _cycles     += pi_perf_read(PI_PERF_CYCLES);        \
            _active     += pi_perf_read(PI_PERF_ACTIVE_CYCLES); \
            _instr      += pi_perf_read(PI_PERF_INSTR);         \
            _ldstall    += pi_perf_read(PI_PERF_LD_STALL);      \
            _imiss      += pi_perf_read(PI_PERF_IMISS);         \
            _ld         += pi_perf_read(PI_PERF_LD);            \
            _st         += pi_perf_read(PI_PERF_ST);            \
        }                                                       \
                                                                \
        if (_k == HOTTING + REPEAT - 1) {                                               \
            int id = pi_core_id();                                                      \
            printf("[%d] number of cycles = %lu\n", id, _cycles/REPEAT);                \
            printf("[%d] number of active cycles = %lu\n", id, _active/REPEAT);         \
            printf("[%d] number of instruction executed = %lu\n", id, _instr/REPEAT);   \
            printf("[%d] number of load stall = %lu\n", id, _ldstall/REPEAT);           \
            printf("[%d] number of instruction misses = %lu\n", id, _imiss/REPEAT);     \
            printf("[%d] number of data stores = %lu\n", id, _st/REPEAT);               \
            printf("[%d] CPI = %f\n", id, (float) _cycles/_instr);                      \
        }                                                                               \
                                                                                        \
    }

#else   /* STATS */

/**
 * @brief Initializes performance counters and begins the measurement loop.
 *
 * @note This macro must be called first, before START_STATS() and STOP_STATS().
 */
#define INIT_STATS()

/**
 * @brief Resets and starts the performance counters.
 *
 * @note This macro must be called after INIT_STATS() within the measurement loop.
 */
#define START_STATS()

/**
 * @brief Stops the performance counters, accumulates, and prints statistics.
 *
 * @note This macro must be called after START_STATS() within the measurement loop.
 */
#define STOP_STATS()

#endif  /* STATS */

#endif  /* STATS_H_ */