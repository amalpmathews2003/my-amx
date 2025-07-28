#include <stdio.h>
#include <amxc/amxc.h>
#include <amxc/amxc_macros.h>
#include <amxm/amxm.h>

#include "mod-custom.h"

int call_custom_married_status_function(UNUSED const char *function_name,
                                   amxc_var_t *args,
                                   amxc_var_t *ret)
{
    printf("Custom function called with args: %s\n",
           amxc_var_dyncast(cstring_t, args));

    amxc_var_set(cstring_t, ret, "Custom married status function executed");
    return 0;
}

static AMXM_CONSTRUCTOR common_module_start(void) {
    printf("Initializing custom module\n");

    amxm_shared_object_t* so = amxm_so_get_current();
    amxm_module_t* mod = NULL;

    amxm_module_register(&mod, so, MOD_NAME);
    amxm_module_add_function(mod, "custom_married_status_function", call_custom_married_status_function);

    return 0;
}

static AMXM_DESTRUCTOR common_module_stop(void) {
    printf("Cleaning up custom module\n");
    return 0;
}
