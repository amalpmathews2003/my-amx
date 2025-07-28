#pragma once

#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxc/amxc_macros.h>

struct _my_amx_app
{
    amxd_dm_t *dm;
    amxo_parser_t *parser;
};

amxd_dm_t *my_amx_get_dm(void);
