#include <stdio.h>
#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxm/amxm.h>

#include "my-amx.h"

static struct _my_amx_app app;

amxd_dm_t* my_amx_get_dm(void) {
    return app.dm;
}

void my_amx_init(amxd_dm_t *dm,amxo_parser_t *parser){

    // amxm_shared_object_t *so = amxm_get_so("self");
    
    amxd_object_t *root = amxd_dm_get_root(dm);
    amxd_object_t *person = amxd_dm_findf(dm, "%s","Person.");


    // printf("%s",so->name);
    printf("%p\n",dm);
    printf("%p\n",person);
    
    app.dm=dm;
    app.parser=parser;
}



int _my_amx_main(int reason,
                 amxd_dm_t *dm,
                 amxo_parser_t *parser)
{

    switch (reason)
    {
    case AMXO_START:
        my_amx_init(dm, parser);
        printf("AMXO_START: Initializing my-amx\n");
        break;
    case AMXO_STOP:
        app.dm = NULL;
        app.parser = NULL;
        printf("AMXO_STOP: Cleaning up my-amx\n");
    default:
        break;
    }

    return 0;
}

