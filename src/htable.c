#include "my-amx.h"
#include <amxc/amxc_htable.h>
#include <string.h>

static amxc_htable_t dict;
static bool dict_initialised = false;

typedef struct _entry
{
    char meaning[20];
    amxc_htable_it_t it;
} entry_t;

int _init_ht()
{
    if (dict_initialised)
        return 0;
    amxc_htable_init(&dict, 10);
    dict_initialised = true;
    return 0;
}

int add_word(const char *word, const char *meaning)
{
    entry_t *entry = calloc(1, sizeof(entry_t));
    strcpy(entry->meaning, meaning);

    amxc_htable_it_init(&entry->it);

    int status = amxc_htable_insert(&dict, word, &entry->it);
    printf("status %d\n", status);
    printf("capacity %ld\n", amxc_htable_capacity(&dict));
    // amxc_htable_it_t *it = amxc_htable_get(&dict, word);
    return 0;
}

char *get_meaning(const char *word)
{
    amxc_htable_it_t *it = amxc_htable_get(&dict, word);
    if (it != NULL)
    {
        entry_t *entry = amxc_container_of(it, entry_t, it);
        // printf("%s:%s\n", word, entry->meaning);
        return entry->meaning;
    }
    return NULL;
}
void _add_word(UNUSED amxd_object_t *object,
               UNUSED amxd_function_t *func,
               amxc_var_t *args,
               UNUSED amxc_var_t *ret)
{
    const char *word = GET_CHAR(args, "word");
    const char *meaning = GET_CHAR(args, "meaning");
    printf("Adding word: %s, meaning: %s\n", word, meaning);
    _init_ht();
    if (!word || !meaning)
    {
        printf("Invalid word or meaning\n");
        return;
    }
    add_word(word, meaning);
    // add_word("carrot", "vegitable");
}

void _get_meaning(UNUSED amxd_object_t *object,
                  UNUSED amxd_function_t *func,
                  amxc_var_t *args,
                  amxc_var_t *ret)
{
    const char *word = GET_CHAR(args, "word");
    const char *meaning = get_meaning(word);
    amxc_var_set_type(ret, AMXC_VAR_ID_HTABLE);
    amxc_var_add_key(cstring_t, ret, "word", meaning);

    amxc_var_dump(ret, 2);
    //    amxc_var_set(cstring_t,ret,meaning);
}
void _display_dict(UNUSED amxd_object_t *object,
                   UNUSED amxd_function_t *func,
                   UNUSED amxc_var_t *args,
                   UNUSED amxc_var_t *ret)
{

    amxc_htable_iterate(it, &dict)
    {
        entry_t *entry = amxc_container_of(it, entry_t, it);
        printf("Word: %s, Meaning: %s\n", it->key, entry->meaning);
    }
    printf(".....\n");
    amxc_htable_for_each(it, &dict)
    {
        entry_t *entry = amxc_container_of(it, entry_t, it);
        printf("Word: %s, Meaning: %s\n", it->key, entry->meaning);
    }

    printf("Dictionary contents displayed.\n");
}

amxd_status_t _add_word_instance(amxd_object_t *object, amxd_param_t *param,
                                 amxd_action_t reason,
                                 const amxc_var_t *const args,
                                 amxc_var_t *const retval,
                                 void *priv)
{
    amxc_var_t *parameters = GET_ARG(args, "parameters");
    const char *word = GET_CHAR(parameters, "word");
    const char *meaning = GET_CHAR(parameters, "meaning");
    printf("Adding word: %s, meaning: %s\n", word, meaning);
    _init_ht();
    if (!word || !meaning)
    {
        printf("Invalid word or meaning\n");
        return amxd_status_invalid_arg;
    }
    add_word(word, meaning);

    amxd_action_object_add_inst(object, param, reason, args, retval, priv);

    return amxd_status_ok;
}

// amxd_status_t _read_word(amxd_object_t *object, amxd_param_t *param,
//                          amxd_action_t reason,
//                          const amxc_var_t *const args,
//                          amxc_var_t *const retval,
//                          void *priv)
// {

// }