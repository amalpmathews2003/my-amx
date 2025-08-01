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

amxd_status_t _say_my_name(amxd_object_t *greeter,
                           UNUSED amxd_function_t *func,
                           amxc_var_t *args,
                           amxc_var_t *ret)
{
    char *name = "Amal";
    printf("Hello, %s!\n", name);
    amxc_var_set(cstring_t, ret, name);
    return amxd_status_ok;
}

amxd_status_t _am_i_married(UNUSED amxd_object_t *object,
                            UNUSED amxd_function_t *func,
                            UNUSED amxc_var_t *args,
                            amxc_var_t *ret)
{
    amxd_dm_t *dm = my_amx_get_dm();
    amxd_object_t *person = amxd_dm_findf(dm, "%s", "Person.");
    bool married = amxd_object_get_value(bool, person, "married_status", NULL);

    amxc_var_set(cstring_t, ret, married ? "I'm married" : "I'm single");
    return amxd_status_ok;
}

// supposed to be in another file/so but for now, we keep it here
amxd_status_t _Car_is_Person_married(UNUSED amxd_object_t *object,
                                     UNUSED amxd_function_t *func,
                                     UNUSED amxc_var_t *args,
                                     amxc_var_t *ret)
{
    amxb_bus_ctx_t *ctx = amxb_be_who_has("Person.");

    amxb_call(ctx, "Person.", "am_i_married", NULL, ret, 1000);


    return amxd_status_ok;
}
