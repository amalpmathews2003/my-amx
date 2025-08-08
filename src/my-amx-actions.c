#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "my-amx.h"
#include "my-amx-actions.h"

#include <amxd/amxd_parameter.h>

amxd_status_t _read_education(UNUSED amxd_object_t *object,
                              UNUSED amxd_param_t *param,
                              UNUSED amxd_action_t reason,
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

    amxc_var_set(cstring_t, retval, education);

    return status;
}

int stricmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            break;
        }
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}


amxd_status_t _check_is_valid_organ(UNUSED amxd_object_t *object,UNUSED amxd_path_t *param,
                                    UNUSED amxd_action_t reason, const amxc_var_t *const args,
                                    UNUSED amxc_var_t *const retval, UNUSED void *priv)
{
   
    const char* organ = amxc_var_constcast(cstring_t, args);
    if (organ == NULL || organ[0] == '\0')
    {
        return amxd_status_ok;
    }
    printf("Validating organ: %s\n", organ);
    const char *organs[] = {
        "",
        "Heart",
        "Liver",
        "Kidney",
        "Lungs",
        "Brain",
    };

    for (size_t i = 0; i < sizeof(organs) / sizeof(organs[0]); i++)
    {
        if (stricmp(organ, organs[i]) == 0)
        {
            return amxd_status_ok;
        }
    }
    return amxd_status_invalid_value;
}