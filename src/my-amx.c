#include <stdio.h>
#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxm/amxm.h>

#include "my-amx.h"
#include "my-amx-methods.h"

static struct _my_amx_app app;

amxd_dm_t *my_amx_get_dm(void)
{
    return app.dm;
}



void my_amx_init(amxd_dm_t *dm, amxo_parser_t *parser)
{

    app.dm = dm;
    app.parser = parser;

    amxb_bus_ctx_t *ctx = amxb_be_who_has("Person.");

    amxb_subscribe(ctx, "Person.",
                   "notification == 'my_event2' && path == 'Person.'",
                   on_my_event2, NULL);
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
