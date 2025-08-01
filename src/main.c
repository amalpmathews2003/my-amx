#include "main.h"

#define ODL_FILE "/etc/amx/my-amx/my-amx.odl"

int main(int argc, char *argv[])
{
    int index = 0;
    amxrt_new();

    amxc_var_t* config = amxrt_get_config();
    amxo_parser_t *parser = amxrt_get_parser();
    amxd_dm_t *dm = amxrt_get_dm();
    amxo_parser_parse_file(parser, ODL_FILE, amxd_dm_get_root(dm));

    amxrt_config_scan_backend_dirs();

    amxrt_connect();
    amxrt_el_create();
    amxrt_register_or_wait();
    // printf("AMX application started\n");
    amxrt_el_start();

    amxrt_stop();
    amxrt_delete();

    return 0;
}