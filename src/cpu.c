#include "my-amx.h"

amxc_var_t * dm_describe_param(amxc_var_t *ht_params,
                                const char *name,
                                amxc_var_t *value)
{
    amxc_var_t *param = amxc_var_add_key(amxc_htable_t, ht_params, name, NULL);

    amxd_param_build_description(param, name, amxc_var_type_of(value),
                                 SET_BIT(amxd_pattr_read_only) | SET_BIT(amxd_pattr_variable), NULL);

    amxc_var_set_key(param, "value", value, AMXC_VAR_FLAG_COPY | AMXC_VAR_FLAG_UPDATE);
    
    return param;
}

amxd_status_t dm_filter_params(amxc_var_t *dest,
                               amxc_var_t *src,
                               const char *filter)
{
    amxd_status_t status = amxd_status_parameter_not_found;

    amxc_var_t description;
    amxc_var_init(&description);
    amxc_var_set_type(&description, AMXC_VAR_ID_HTABLE);

    amxp_expr_t expr;
    amxp_expr_status_t expr_status = amxp_expr_status_ok;

    if (filter != NULL)
    {
        amxp_expr_init(&expr, filter);
    }
    else
    {
        amxc_var_move(dest, src);
        status = amxd_status_ok;
        goto exit;
    }

    amxc_var_init(dest);
    amxc_var_set_type(dest, AMXC_VAR_ID_HTABLE);

    amxc_var_for_each(value, src)
    {
        const char *param_name = amxc_var_key(value);
        amxc_var_t *param = dm_describe_param(&description, param_name, value);

        if (!amxp_expr_eval_var(&expr, param, &expr_status))
        {
            amxc_var_delete(&param);
            continue;
        }
        amxc_var_delete(&param);
        amxc_var_set_key(dest, param_name, value, AMXC_VAR_FLAG_DEFAULT);
    }

exit:

    if (amxc_htable_is_empty(amxc_var_constcast(amxc_htable_t, dest)))
    {
        amxc_var_clean(dest);
    }
    amxc_var_clean(&description);
    return status;
}

amxd_status_t _cpu_read(amxd_object_t *object,
                        amxd_param_t *param,
                        amxd_action_t reason,
                        const amxc_var_t *const args,
                        amxc_var_t *const retval,
                        void *priv)
{
    amxd_status_t status = amxd_action_object_read(object, param, reason,
                                                   args, retval, priv);
    printf("hello");
    amxc_var_t temp;
    amxc_var_init(&temp);

    amxc_string_t filter;
    amxc_string_init(&filter, 0);

    when_true(status != amxd_status_ok, exit);
    when_true(amxd_object_get_type(object) != amxd_object_instance, exit);

    status = amxd_action_object_read_filter(&filter, args);

    uint16_t percetage = 12;
    amxc_var_add_key(uint16_t, &temp, "percentage", percetage);

    dm_filter_params(retval,&temp,amxc_string_get(&filter,0));

    if (amxc_var_is_null(retval))
    {
        status = amxd_status_parameter_not_found;
    }

exit:
    amxc_var_clean(&temp);
    amxc_string_clean(&filter);
    return status;
}