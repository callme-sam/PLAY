#include "play.h"

#include "pmsis.h"

#ifdef  CLUSTER

static int hello_world_parallel()
{
    int id;

    id = pi_core_id();
    printf("Hello world from cluster core %d =D\n", id);

#if NUM_CORES > 1
    pi_cl_team_barrier();
#endif

    return 0;
}

#else   /* CLUSTER */

static int hello_world_serial()
{
    printf("Hello world! =D\n");
    return 0;
}

#endif  /* CLUSTER */

int hello_world()
{
    int ret;

#ifdef  CLUSTER
    ret = hello_world_parallel();
#else   /* CLUSTER */
    ret = hello_world_serial();
#endif  /* CLUSTER */

    return ret;
}
