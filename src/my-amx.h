#pragma once

#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxc/amxc_macros.h>

struct _my_amx_app
{
    amxd_dm_t *dm;
    amxo_parser_t *parser;
};
amxd_dm_t* my_amx_get_dm(void) ;

int _my_amx_main(int reason,
                 amxd_dm_t *dm,
                 amxo_parser_t *parser);

amxd_status_t _Person_say_my_name(amxd_object_t* greeter,
                           UNUSED amxd_function_t* func,
                           amxc_var_t* args,
                           amxc_var_t* ret);