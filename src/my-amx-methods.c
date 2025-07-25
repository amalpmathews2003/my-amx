#include <stdio.h>
#include "my-amx-methods.h"
#include "my-amx.h"
#include <amxd/amxd_object_event.h>
#include <amxc/amxc.h>

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

int _on_read_name()
{
    printf("AMXO_READ: Reading name\n");
    return 0;
}

int _on_read_person()
{
    printf("AMXO_READ: Reading person\n");
    return 0;
}

int _on_write()
{
    printf("AMXO_WRITE: Writing data\n");
    return 0;
}

amxd_status_t _Person_say_my_name(amxd_object_t *greeter,
                                  UNUSED amxd_function_t *func,
                                  amxc_var_t *args,
                                  amxc_var_t *ret)
{
    printf("AMXO_SAY_MY_NAME: My name is MyAMX!\n");

    amxc_var_set(cstring_t, ret, "MyAMX");

    return amxd_status_ok;
}