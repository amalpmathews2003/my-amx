#pragma once

#include "my-amx.h"

amxd_status_t filter_params(amxc_var_t *dest,
                            amxc_var_t *src,
                            const char *filter);
