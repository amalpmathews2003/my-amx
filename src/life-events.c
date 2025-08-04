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

amxd_status_t _append_event(amxd_object_t *object,
                            amxd_function_t *func,
                            amxc_var_t *args,
                            amxc_var_t *ret)
{
    amxd_status_t status = amxd_status_ok;
    initLE();
    const char *name = GET_CHAR(args, "name");
    uint16_t year = GET_INT32(args, "year");
    const char *details = GET_CHAR(args, "details");

    life_event_t *event = (life_event_t *)calloc(1, sizeof(life_event_t));
    snprintf(event->event_name, 20, "%s", name);
    event->year = year;
    snprintf(event->details, 50, "%s", details);
    append_event(event);

    amxc_var_set(uint16_t, ret, amxc_llist_size(&life_events));

    return status;
}

amxd_status_t _retrieve_event(amxd_object_t *object,
                            amxd_function_t *func,
                            amxc_var_t *args,
                            amxc_var_t *ret)
{
    int index = GET_INT32(args, "index");
    if (index < 0 || index >= amxc_llist_size(&life_events))
    {
        printf("Index out of bounds: %d\n", index);
        return amxd_status_unknown_error;
    }
    life_event_t *event = retrieve_event(index);
    if (event == NULL)
    {
        printf("Failed to retrieve event at index: %d\n", index);
        return amxd_status_unknown_error;
    }
    amxc_var_set(cstring_t, ret, event->event_name);
    amxc_var_set(uint16_t, ret, event->year);
    amxc_var_set(cstring_t, ret, event->details);
    printf("Retrieved Event - Name: %s, Year: %d, Details: %s\n", event->event_name, event->year, event->details);
    return amxd_status_ok;
}

amxd_status_t _print_events(amxd_object_t *object,
                            amxd_function_t *func,
                            amxc_var_t *args,
                            amxc_var_t *ret)
{
    print_events();

    // amxc_array_t arr;
    // amxc_array_init(&arr, amxc_llist_size(&life_events));


    // amxc_llist_for_each(it, &life_events)
    // {
    //     life_event_t *event = amxc_container_of(it, life_event_t, it);
        
    //     amxc_var_t event_json;
    //     amxc_var_init(&event_json);
    //     amxc_var_set_type(&event_json,AMXC_VAR_ID_HTABLE);
        
    //     amxc_var_add_key(cstring_t, &event_json, "name", event->event_name);
    //     amxc_var_add_key(uint16_t, &event_json, "year", event->year);
    //     amxc_var_add_key(cstring_t, &event_json, "details", event->details);

    //     amxc_array_append_data(&arr, &event_json);
    // }

    // amxc_var_init(ret);
    // amxc_var_add(amxc_llist_t, ret, &life_events);
    // amxc_var_add_new_amxc_llist_t(ret, &life_events);

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
        amxc_llist_it_clean(it, delete_event);
    }

    return amxd_action_object_del_inst(object, param, reason, args, retval, priv);
}

amxd_status_t _read_event(amxd_object_t *object, amxd_param_t *param,
                          amxd_action_t reason,
                          const amxc_var_t *const args,
                          amxc_var_t *const retval,
                          void *priv)
{

    amxc_llist_it_t *it = amxc_llist_get_at(&life_events, object->index - 1);
    if (it != NULL)
    {
        life_event_t *event = amxc_container_of(it, life_event_t, it);
        if (param && strcmp(param->name, "name") == 0)
        {
            amxc_var_set(cstring_t, retval, event->event_name);
        }
        else if (param && strcmp(param->name, "year") == 0)
        {
            amxc_var_set(uint16_t, retval, event->year);
        }
        else if (param && strcmp(param->name, "details") == 0)
        {
            amxc_var_set(cstring_t, retval, event->details);
        }    
    }
    printf("object->index: %d, param->name: %s\n", object->index, param ? param->name : "NULL");
    printf("args: %s\n", args ? amxc_var_dyncast(cstring_t, args) : "NULL");

    // amxd_action_object_read(object, param, reason, args, retval, priv);
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

    // amxd_action_param_write(object, param, reason, args, retval, priv);

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
