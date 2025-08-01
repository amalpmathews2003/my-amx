#pragma once

#include <amxc/amxc_macros.h>
#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxd/amxd_object.h>
#include <amxd/amxd_object_event.h>
#include <amxd/amxd_transaction.h>
#include <amxd/amxd_action.h>
#include <amxo/amxo.h>
#include <amxm/amxm.h>

#define SAHTRACES_ENABLED true
#define SAHTRACES_LEVEL 500

#include <debug/sahtrace.h>
#include <debug/sahtrace_macros.h>


struct _my_amx_app
{
    amxd_dm_t *dm;
    amxo_parser_t *parser;
};

amxd_dm_t *my_amx_get_dm(void);

