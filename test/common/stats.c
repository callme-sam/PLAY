#include "stats.h"

#include "utils.h"

#include <stdio.h>

void print_stats(unsigned long _cycles, unsigned long _active, unsigned long _instr,
                unsigned long _ldstall, unsigned long _jrstall, unsigned long _imiss,
                unsigned long _ld, unsigned long _st, unsigned long _jump,
                unsigned long _branch, unsigned long _btaken, unsigned long _rvc,
                unsigned long _ld_ext, unsigned long _st_ext, unsigned long _ld_ext_cyc,
                unsigned long _st_ext_cyc, unsigned long _tcdm_cont)
{
    int id;

    id = pi_core_id();
    if (id == 0)
        printf("INFO | Printing statistics:\n");

    barrier();

    printf("[%d] cycles:\t\t\t%lu\n", id, _cycles/REPEAT);
    printf("[%d] act cycles:\t\t\t%lu\n", id, _active/REPEAT);
    printf("[%d] instr execd:\t\t%lu\n", id, _instr/REPEAT);
    printf("[%d] load stall:\t\t\t%lu\n", id, _ldstall/REPEAT);
    printf("[%d] jump reg stall:\t\t%lu\n", id, _jrstall/REPEAT);
    printf("[%d] instr miss:\t\t\t%lu\n", id, _imiss/REPEAT);
    printf("[%d] loads execd:\t\t%lu\n", id, _ld/REPEAT);
    printf("[%d] stores execd:\t\t%lu\n", id, _st/REPEAT);
    printf("[%d] jump:\t\t\t%lu\n", id, _jump/REPEAT);
    printf("[%d] branches:\t\t\t%lu\n", id, _branch/REPEAT);
    printf("[%d] taken branches:\t\t%lu\n", id, _btaken/REPEAT);
    printf("[%d] comprssd inst execd:\t%lu\n", id, _rvc/REPEAT);
    printf("[%d] ext loads execd:\t\t%lu\n", id, _ld_ext/REPEAT);
    printf("[%d] ext loads cycles:\t\t%lu\n", id, _ld_ext_cyc/REPEAT);
    printf("[%d] ext stores execd:\t\t%lu\n", id, _st_ext/REPEAT);
    printf("[%d] ext stores cycles:\t\t%lu\n", id, _st_ext/REPEAT);
    printf("[%d] TDCM contentions:\t\t%lu\n", id, _tcdm_cont/REPEAT);
    printf("[%d] IPC:\t\t\t%f\n", id, (float) _instr/_cycles);

    char filename[100];
}
