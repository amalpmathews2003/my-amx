#pragma once

#include <amxc/amxc.h>

void _on_person_changed(const char *const event_name,
                        const amxc_var_t *const event_data,
                        void *const priv);

void _on_person_age_changed(const char *const event_name,
                            const amxc_var_t *const event_data,
                            void *const priv);

void _on_my_event(const char *const event_name,
                  const amxc_var_t *const event_data,
                  void *const priv);

void on_my_event2(const char *const event_name,
                  const amxc_var_t *const event_data,
                  void *const priv);

void _on_person_name_change(const char *const event_name,
                            const amxc_var_t *const event_data,
                            void *const priv);

void _on_married_status_change(const char *const event_name,
                               const amxc_var_t *const event_data,
                               void *const priv);