#include <stdio.h>
#include <stdlib.h>


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

#include "my-amx-actions.h"

amxd_status_t _read_education(UNUSED amxd_object_t *object,
                              UNUSED amxd_param_t *param,
                              amxd_action_t reason,
                              UNUSED const amxc_var_t *const args,
                              amxc_var_t *const retval,
                              UNUSED void *priv)
{
    // list of eduatuions like btech,mtech,mca,bca
    // return a random education from the list
    static const char *educations[] = {
        "B.Tech",
        "M.Tech",
        "MCA",
        "BCA",
        "B.Sc",
    };
    amxd_status_t status = amxd_status_ok;
    // Generate a random index to select an education
    size_t index = rand() % (sizeof(educations) / sizeof(educations[0]));
    const char *education = educations[index];

    amxc_var_set(cstring_t,retval, education);

    return status;
}