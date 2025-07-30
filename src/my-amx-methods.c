#include <stdio.h>

#include "my-amx.h"
#include "my-amx-methods.h"


amxd_status_t _handle_name_write(amxd_object_t *object, UNUSED amxd_param_t *param,
                                 amxd_action_t reason,
                                 const amxc_var_t *const args,
                                 amxc_var_t *const retval,
                                 UNUSED void *priv)
{
    return amxd_action_param_write(object, param, reason, args, retval, priv);
}

amxd_status_t _Person_say_my_name(amxd_object_t *greeter,
                                  UNUSED amxd_function_t *func,
                                  amxc_var_t *args,
                                  amxc_var_t *ret)
{
    char *name = amxd_object_get_value(cstring_t, greeter, "name", NULL);
    amxc_var_set(cstring_t, ret, name);
    return amxd_status_ok;
}

