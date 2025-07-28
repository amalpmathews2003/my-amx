#pragma once

#include <amxc/amxc.h>
#include <amxp/amxp.h>
#include <amxd/amxd_dm.h>
#include <amxo/amxo.h>
#include <amxc/amxc_macros.h>

amxd_status_t _Person_say_my_name(amxd_object_t *greeter,
                                  UNUSED amxd_function_t *func,
                                  amxc_var_t *args,
                                  amxc_var_t *ret);
