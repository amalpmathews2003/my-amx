#pragma once

#include <amxc/amxc.h>

typedef struct life_event {
    char event_name[20];
    int year;
    char details[50];
    amxc_llist_it_t it; // iterator for the linked list
} life_event_t;
