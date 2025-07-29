#pragma once

#include <amxc/amxc_macros.h>
#include <amxc/amxc.h>
#include <amxd/amxd_dm.h>

amxd_status_t _read_education(UNUSED amxd_object_t *object,
                              UNUSED amxd_param_t *param,
                              amxd_action_t reason,
                              UNUSED const amxc_var_t *const args,
                              amxc_var_t *const retval,
                              UNUSED void *priv);