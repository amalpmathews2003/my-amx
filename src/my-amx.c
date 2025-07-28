#include <stdio.h>
#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxm/amxm.h>

#include "my-amx.h"
#include "my-amx-methods.h"
#include "my-amx-events.h"

static struct _my_amx_app app;

amxd_dm_t *my_amx_get_dm(void)
{
    return app.dm;
}

int custom_married_status_function(UNUSED const char *function_name,
                                   amxc_var_t *args,
                                   amxc_var_t *ret)
{
    printf("Custom function called with args: %s\n",
           amxc_var_dyncast(cstring_t, args));

    amxc_var_set(cstring_t, ret, "Custom married status function executed");
    return 0;
}

void my_amx_init(amxd_dm_t *dm, amxo_parser_t *parser)
{

    app.dm = dm;
    app.parser = parser;

    amxb_bus_ctx_t *ctx = amxb_be_who_has("Person.");

    amxb_subscribe(ctx, "Person.",
                   "notification == 'my_event2' && path == 'Person.'",
                   on_my_event2, NULL);

    amxm_shared_object_t *so = amxm_so_get_current();
    amxm_module_t *mod = NULL;

    amxm_module_register(&mod, so, "my-amx");
    amxm_module_add_function(mod,
                             "custom_married_status_function",
                             custom_married_status_function);

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
