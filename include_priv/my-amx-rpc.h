#pragma once

#include <amxc/amxc_macros.h>
#include <amxc/amxc.h>
#include <amxd/amxd_dm.h>

amxd_status_t _test_rpc(UNUSED amxd_object_t *obj,
                        UNUSED amxd_function_t *func, 
                        amxc_var_t *args, amxc_var_t *ret);