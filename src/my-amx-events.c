#include "my-amx-events.h"
#include <stdio.h>
#include "my-amx.h"

#include <amxd/amxd_dm.h>
#include <amxd/amxd_object_event.h>
#include <amxc/amxc.h>
#include <amxd/amxd_transaction.h>
#include <amxd/amxd_action.h>
#include <debug/sahtrace.h>
#include <debug/sahtrace_macros.h>
#include <amxd/amxd_object.h>
#include <amxm/amxm.h>

#define printf(...) fprintf(stderr, __VA_ARGS__)

void _on_person_changed(const char *const event_name,
                        const amxc_var_t *const event_data,
                        void *const priv)
{
    printf("AMXO_EVENT: Event triggered with data: \n");

    char *data_str = amxc_var_dyncast(cstring_t, event_data);
    // printf("Event data: %s\n", data_str ? data_str : "NULL");

    amxd_dm_t *dm = my_amx_get_dm();
    amxd_object_t *root = amxd_dm_get_root(dm);
    amxd_object_t *person = amxd_dm_findf(dm, "%s", "Person.");

    amxc_var_t data;
    amxc_var_init(&data);
    amxc_var_set(cstring_t, &data, "Person data changed");
    // amxd_object_send
    amxd_object_emit_signal(person, "my_event", &data);

    amxc_var_clean(&data);
}

void _on_person_age_changed(const char *const event_name,
                            const amxc_var_t *const event_data,
                            void *const priv)
{
    printf("AMXO_EVENT: Age changed event triggered with data: \n");

    amxd_dm_t *dm = my_amx_get_dm();
    amxd_object_t *root = amxd_dm_get_root(dm);
    amxd_object_t *person = amxd_dm_findf(dm, "%s", "Person.");

    amxc_var_t data;
    amxc_var_init(&data);
    amxc_var_set(cstring_t, &data, "happy birthday");

    amxd_object_emit_signal(person, "my_event2", &data);
}

void _on_my_event(const char *const event_name,
                  const amxc_var_t *const event_data,
                  void *const priv)
{
    printf("AMXO_MY_EVENT: Custom event '%s' triggered with data: \n", event_name);

    char *data_str = amxc_var_dyncast(cstring_t, event_data);

    // printf("Event data: %s\n", data_str ? data_str : "NULL");
}

void on_my_event2(const char *const event_name,
                  const amxc_var_t *const event_data,
                  void *const priv)
{
    printf("AMXO_MY_EVENT2: Custom event '%s' triggered with data: \n", event_name);

    char *data_str = amxc_var_dyncast(cstring_t, event_data);

    // printf("Event data: %s\n", data_str ? data_str : "NULL");
}

void _on_person_name_change(const char *const event_name,
                            const amxc_var_t *const event_data,
                            void *const priv)
{
    printf("Person name changed\n", event_name);
    amxd_object_t *person = amxd_dm_findf(my_amx_get_dm(), "%s", "Person.");

    char *name = amxd_object_get_value(cstring_t, person, "name", NULL);

    amxd_trans_t trans;
    amxd_trans_init(&trans);
    amxd_trans_set_attr(&trans, amxd_tattr_change_ro, true);
    amxd_trans_select_object(&trans, person);
    amxd_trans_set_cstring_t(&trans, "shadow_name", name);
    amxd_trans_apply(&trans, my_amx_get_dm());
}



void _on_married_status_change(const char *const event_name,
                                  const amxc_var_t *const event_data,
                                  void *const priv)
{
    amxd_object_t *person = amxd_dm_findf(my_amx_get_dm(), "%s", "Person.");

    bool married_status = amxd_object_get_value(bool, person, "married_status", NULL);
    printf("Happy for you, you are %s!\n", married_status ? "married" : "single");


    amxc_var_t data,ret;
    amxc_var_init(&data);
    amxc_var_set(cstring_t, &data, "married_status changed");
    amxc_var_init(&ret);

    amxm_shared_object_t *so = amxm_so_get_current();
    
    amxm_execute_function(so->name,"my-amx","custom_married_status_function",&data, &ret);

    printf("Function returned: %s\n", amxc_var_dyncast(cstring_t, &ret));
    amxc_var_clean(&data);
    amxc_var_clean(&ret);
}