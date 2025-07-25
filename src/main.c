// #include <amxs/amxs.h>
// #include <amxo/amxo.h>
// #include <amxb/amxb.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include "method.h"

// int main(int argc, char* argv[]) {
//     amxo_t xo;
//     amxs_model_t* model = NULL;

//     amxo_dm_init(&xo, NULL);

//     // Load ODL model
//     if (amxo_load_script(&xo, "model.odl") != 0) {
//         fprintf(stderr, "Failed to load model.odl\n");
//         return 1;
//     }

//     // Compile model into amxs_model
//     if (amxo_compile(&xo) != 0) {
//         fprintf(stderr, "Failed to compile model\n");
//         return 1;
//     }

//     model = amxo_get_model(&xo);
//     if (!model) {
//         fprintf(stderr, "Model pointer NULL\n");
//         return 1;
//     }

//     // Register your methods (optional)
//     register_methods(amxs_model_get_root(model));

//     // Bind to UBUS
//     amxb_bus_ctx_t* ubus = amxb_broker_new("ubus");
//     amxb_connect(ubus, NULL);
//     amxb_add_model(ubus, model);
//     amxb_broker_run(ubus);

//     // Cleanup
//     amxb_disconnect(ubus);
//     amxb_broker_free(ubus);
//     amxo_clean(&xo);

//     return 0;
// }

#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_types.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxs/amxs.h>
#include <amxrt/amxrt.h>

#define ODL_FILE "/etc/amx/my-amx/odl/my-amx.odl"

int main(int argc, char *argv[])
{
    int retval = 0;
    int index = 0;
    amxrt_new();

    amxc_var_t* config = amxrt_get_config();
    amxrt_config_init(argc,argv,&index,NULL);
    amxo_parser_t *parser = amxrt_get_parser();
    amxd_dm_t *dm = amxrt_get_dm();

    amxrt_config_scan_backend_dirs();

    amxo_parser_parse_file(parser, ODL_FILE, amxd_dm_get_root(dm));

    amxrt_connect();

    amxrt_el_create();
    amxrt_register_or_wait();

    amxrt_el_start();

    amxrt_stop();
    amxrt_delete();

    return retval;
}