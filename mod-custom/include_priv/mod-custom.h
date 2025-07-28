#pragma once

#include <amxc/amxc.h>
#include <amxc/amxc_macros.h>

#define MOD_NAME "mod-custom"

int custom_married_status_function(UNUSED const char *function_name,
                                   amxc_var_t *args,
                                   amxc_var_t *ret);