#ifndef STATS_H_
#define STATS_H_

#include "pmsis.h"

#define HOTTING 2
#define REPEAT  5

void print_stats(unsigned long _cycles, unsigned long _active, unsigned long _instr, unsigned long _ldstall,
                unsigned long _jrstall, unsigned long _imiss, unsigned long _ld, unsigned long _st,
                unsigned long _jump, unsigned long _branch, unsigned long _btaken, unsigned long _rvc,
                unsigned long _ld_ext, unsigned long _st_ext, unsigned long _ld_ext_cyc, unsigned long _st_ext_cyc,
                unsigned long _tcdm_cont);

#ifdef  STATS

#ifdef  CLUSTER

/**
 * @brief Initializes performance counters and begins the measurement loop.
 *
 * @note This macro must be called first, before START_STATS() and STOP_STATS().
 */
#define INIT_STATS()    \
    unsigned long _cycles       = 0;    \
    unsigned long _active       = 0;    \
    unsigned long _instr        = 0;    \
    unsigned long _ldstall      = 0;    \
    unsigned long _jrstall      = 0;    \
    unsigned long _imiss        = 0;    \
    unsigned long _ld           = 0;    \
    unsigned long _st           = 0;    \
    unsigned long _jump         = 0;    \
    unsigned long _branch       = 0;    \
    unsigned long _btaken       = 0;    \
    unsigned long _rvc          = 0;    \
    unsigned long _ld_ext       = 0;    \
    unsigned long _st_ext       = 0;    \
    unsigned long _ld_ext_cyc   = 0;    \
    unsigned long _st_ext_cyc   = 0;    \
    unsigned long _tcdm_cont    = 0;    \
                                        \
    for (int _k = 0; _k < HOTTING + REPEAT; _k++) { \
        pi_perf_conf( (1<<PI_PERF_CYCLES)           \
                    | (1<<PI_PERF_ACTIVE_CYCLES)    \
                    | (1<<PI_PERF_INSTR)            \
                    | (1<<PI_PERF_LD_STALL)         \
                    | (1<<PI_PERF_JR_STALL)         \
                    | (1<<PI_PERF_IMISS)            \
                    | (1<<PI_PERF_LD)               \
                    | (1<<PI_PERF_ST)               \
                    | (1<<PI_PERF_JUMP)             \
                    | (1<<PI_PERF_BRANCH)           \
                    | (1<<PI_PERF_BTAKEN)           \
                    | (1<<PI_PERF_RVC)              \
                    | (1<<PI_PERF_LD_EXT)           \
                    | (1<<PI_PERF_ST_EXT)           \
                    | (1<<PI_PERF_LD_EXT_CYC)       \
                    | (1<<PI_PERF_ST_EXT_CYC)       \
                    | (1<<PI_PERF_TCDM_CONT)        \
                    );                              \

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
            _jrstall    += pi_perf_read(PI_PERF_JR_STALL);      \
            _imiss      += pi_perf_read(PI_PERF_IMISS);         \
            _ld         += pi_perf_read(PI_PERF_LD);            \
            _st         += pi_perf_read(PI_PERF_ST);            \
            _jump       += pi_perf_read(PI_PERF_JUMP);          \
            _branch     += pi_perf_read(PI_PERF_BRANCH);        \
            _btaken     += pi_perf_read(PI_PERF_BTAKEN);        \
            _rvc        += pi_perf_read(PI_PERF_RVC);           \
            _ld_ext     += pi_perf_read(PI_PERF_LD_EXT);        \
            _st_ext     += pi_perf_read(PI_PERF_ST_EXT);        \
            _ld_ext_cyc += pi_perf_read(PI_PERF_LD_EXT_CYC);    \
            _st_ext_cyc += pi_perf_read(PI_PERF_ST_EXT_CYC);    \
            _tcdm_cont  += pi_perf_read(PI_PERF_TCDM_CONT);     \
        }                                                       \
                                                                \
        if (_k == HOTTING + REPEAT - 1) {                           \
            print_stats(_cycles, _active, _instr, _ldstall,         \
                        _jrstall, _imiss, _ld, _st, _jump,          \
                        _branch, _btaken, _rvc, _ld_ext, _st_ext,   \
                        _ld_ext_cyc, _st_ext_cyc, _tcdm_cont);      \
        }                                                           \
                                                                    \
    }

#else   /* CLUSTER */

/**
 * @brief Initializes performance counters and begins the measurement loop.
 *
 * @note This macro must be called first, before START_STATS() and STOP_STATS().
 */
#define INIT_STATS()    \
    unsigned long _cycles       = 0;    \
    unsigned long _active       = 0;    \
    unsigned long _instr        = 0;    \
    unsigned long _ldstall      = 0;    \
    unsigned long _jrstall      = 0;    \
    unsigned long _imiss        = 0;    \
    unsigned long _ld           = 0;    \
    unsigned long _st           = 0;    \
    unsigned long _jump         = 0;    \
    unsigned long _branch       = 0;    \
    unsigned long _btaken       = 0;    \
    unsigned long _rvc          = 0;    \
                                        \
    for (int _k = 0; _k < HOTTING + REPEAT; _k++) { \
        pi_perf_conf( (1<<PI_PERF_CYCLES)           \
                    | (1<<PI_PERF_ACTIVE_CYCLES)    \
                    | (1<<PI_PERF_INSTR)            \
                    | (1<<PI_PERF_LD_STALL)         \
                    | (1<<PI_PERF_JR_STALL)         \
                    | (1<<PI_PERF_IMISS)            \
                    | (1<<PI_PERF_LD)               \
                    | (1<<PI_PERF_ST)               \
                    | (1<<PI_PERF_JUMP)             \
                    | (1<<PI_PERF_BRANCH)           \
                    | (1<<PI_PERF_BTAKEN)           \
                    | (1<<PI_PERF_RVC)              \
                    );                              \

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
            _jrstall    += pi_perf_read(PI_PERF_JR_STALL);      \
            _imiss      += pi_perf_read(PI_PERF_IMISS);         \
            _ld         += pi_perf_read(PI_PERF_LD);            \
            _st         += pi_perf_read(PI_PERF_ST);            \
            _jump       += pi_perf_read(PI_PERF_JUMP);          \
            _branch     += pi_perf_read(PI_PERF_BRANCH);        \
            _btaken     += pi_perf_read(PI_PERF_BTAKEN);        \
            _rvc        += pi_perf_read(PI_PERF_RVC);           \
        }                                                       \
                                                                \
        if (_k == HOTTING + REPEAT - 1) {                           \
            print_stats(_cycles, _active, _instr, _ldstall,         \
                        _jrstall, _imiss, _ld, _st, _jump,          \
                        _branch, _btaken, _rvc, 0, 0, 0, 0, 0);     \
        }                                                           \
                                                                    \
    }

#endif  /* CLUSTER */

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
