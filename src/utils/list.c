#include "utils/list.h"

#include <assert.h>
#include <stdlib.h>

void list_insert(list* node_holder, void* value)
{
    assert(value != NULL);
    assert(node_holder != NULL);

    list_node_ptr new_head = malloc(sizeof(list_node_type));
    new_head->next = *node_holder;
    new_head->value = value;
    *node_holder = new_head;
}

void* list_pop_front(list* node_holder)
{
    assert(node_holder != NULL);

    if (*node_holder == NULL)
        return NULL;

    void* result = (*node_holder)->value;
    list_node_ptr to_delete = *node_holder;
    *node_holder = (*node_holder)->next;

    free(to_delete);

    return result;
}
