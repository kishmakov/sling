#include "utils/list.h"

#include <assert.h>
#include <stdlib.h>


list list_insert(list_mv list, void* value)
{
    assert(value != NULL);
    assert(head != NULL);

    list_node_ptr new_head = malloc(sizeof(list_node_type));
    new_head->next = *head;
    new_head->value = value;
    *head = new_head;
}

list list_pop_front(list_mv list, out_param value)
{
    assert(head != NULL);

    if (*head == NULL)
        return NULL;

    void* result = (*head)->value;
    list_node_ptr to_destruct = *head;
    *head = (*head)->next;

    free(to_destruct);

    return result;
}
