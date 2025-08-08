#include <stdio.h>

#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxc/amxc_macros.h>
#include <amxc/amxc_macros.h>
#include <amxc/amxc.h>
#include <amxd/amxd_object_event.h>
#include <amxd/amxd_transaction.h>
#include <amxd/amxd_action.h>
#include <amxd/amxd_object.h>
#include <amxb/amxb.h>

#include "my-amx-rpc.h"

amxd_status_t _test_rpc(UNUSED amxd_object_t *obj,
                        UNUSED amxd_function_t *func, 
                        UNUSED amxc_var_t *args, amxc_var_t *ret)
{
    amxd_status_t status = amxd_status_ok;

    printf("RPC Test Function Called\n");

    amxc_var_set(cstring_t, ret, "RPC Test Successful");



    return status;
}