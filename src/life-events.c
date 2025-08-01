#include "my-amx.h"
#include "life.h"
#include <amxd/amxd_action.h>
#include <string.h>

#define printf(...) fprintf(stderr, __VA_ARGS__)

static amxc_llist_t life_events;
static bool is_ll_initialized = false;

bool initLE()
{
    if (is_ll_initialized)
    {
        return amxd_status_ok;
    }
    amxc_llist_init(&life_events);
    is_ll_initialized = true;
    return true;
}

bool append_event(life_event_t *event)
{
    amxc_llist_append(&life_events, &event->it);
    return true;
}

life_event_t *retrieve_event(int index)
{
    if (index < 0 || index >= amxc_llist_size(&life_events))
    {
        return NULL; // Index out of bounds
    }
    amxc_llist_it_t *it = amxc_llist_get_at(&life_events, index);
    return amxc_container_of(it, life_event_t, it);
}

void print_events()
{
    int count = amxc_llist_size(&life_events);
    printf("Total Life Events: %d\n", count);

    amxc_llist_for_each(it, &life_events)
    {
        life_event_t *event = amxc_container_of(it, life_event_t, it);
        printf("Event Name: %s, Year: %d, Details: %s\n", event->event_name, event->year, event->details);
    }
}

amxd_status_t _initLE()
{
    initLE();
    return amxd_status_ok;
}

amxd_status_t _append_event()
{
    life_event_t *event = (life_event_t *)calloc(1, sizeof(life_event_t));
    snprintf(event->event_name, 20, "Graduation");
    event->year = 2023;
    snprintf(event->details, 50, "Graduated with honors");
    append_event(event);
    return amxd_status_ok;
}

amxd_status_t _retrieve_event()
{
    int index = 0;
    life_event_t *event = retrieve_event(index);
    return amxd_status_ok;
}

amxd_status_t _print_events()
{
    print_events();
    return amxd_status_ok;
}

void delete_event(amxc_llist_it_t *it)
{
    life_event_t *event = amxc_container_of(it, life_event_t, it);
    free(event->event_name);
    free(event->details);
    free(event);
}

amxd_status_t _clearLE()
{
    amxc_llist_clean(&life_events, delete_event);
    return amxd_status_ok;
}

amxd_status_t _delete_event(amxd_object_t *object, amxd_param_t *param,
                            amxd_action_t reason,
                            const amxc_var_t *const args,
                            amxc_var_t *const retval,
                            void *priv)
{

    amxc_llist_it_t *it = amxc_llist_get_at(&life_events, object->index - 1);
    if (it != NULL)
    {
        amxc_llist_it_clean(it,delete_event);
    }

    return amxd_action_object_del_inst(object, param, reason, args, retval, priv);
}

amxd_status_t _read_event(amxd_object_t *object, amxd_param_t *param,
                          amxd_action_t reason,
                          const amxc_var_t *const args,
                          amxc_var_t *const retval,
                          void *priv)
{

    // amxc_llist_it_t *it = amxc_llist_get_at(&life_events, object->index - 1);
    // if (it != NULL)
    // {
    //     life_event_t *event = amxc_container_of(it, life_event_t, it);
    //     if (strcmp(param->name, "name") == 0)
    //     {
    //         amxc_var_set(cstring_t, retval, event->event_name);
    //     }
    //     else if (strcmp(param->name, "year") == 0)
    //     {
    //         amxc_var_set(uint16_t, retval, event->year);
    //     }
    //     else if (strcmp(param->name, "details") == 0)
    //     {
    //         amxc_var_set(cstring_t, retval, event->details);
    //     }
    // }
    amxd_action_object_read(object, param, reason, args, retval, priv);
    return amxd_status_ok;
}

amxd_status_t _write_event_param(amxd_object_t *object, amxd_param_t *param,
                                 amxd_action_t reason,
                                 const amxc_var_t *const args,
                                 amxc_var_t *const retval,
                                 void *priv)
{

    amxc_llist_it_t *it = amxc_llist_get_at(&life_events, object->index - 1);
    life_event_t *event = amxc_container_of(it, life_event_t, it);

    if (strcmp(param->name, "name") == 0)
    {
        event->event_name[0] = '\0'; // Clear the string
        strncat(event->event_name, amxc_var_dyncast(cstring_t, args), sizeof(event->event_name) - 1);
    }
    else if (strcmp(param->name, "year") == 0)
    {
        event->year = amxc_var_dyncast(uint16_t, args);
    }
    else if (strcmp(param->name, "details") == 0)
    {
        event->details[0] = '\0'; // Clear the string
        strncat(event->details, amxc_var_dyncast(cstring_t, args), sizeof(event->details) - 1);
    }

    amxd_action_param_write(object, param, reason, args, retval, priv);

    return amxd_status_ok;
}

amxd_status_t _write_event(amxd_object_t *object, amxd_param_t *param,
                           amxd_action_t reason,
                           const amxc_var_t *const args,
                           amxc_var_t *const retval,
                           void *priv)
{

    life_event_t *event = (life_event_t *)calloc(1, sizeof(life_event_t));
    snprintf(event->event_name, 20, "");
    event->year = 0;
    snprintf(event->details, 50, "");

    append_event(event);

    return amxd_action_object_add_inst(object, param, reason, args, retval, priv);
}