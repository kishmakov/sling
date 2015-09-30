#include "utils/list.h"

#include <assert.h>
#include <stdlib.h>


list_hld list_insert(list_node_mv head, void* src)
{
    assert(src != NULL);
    assert(head != NULL);

    list_node_hld new_head = malloc(sizeof(list_node_type));
    new_head->next = *head;
    new_head->value = src;

    return new_head;
}

list_hld list_pop_front(list_node_mv head, out_param dst)
{
    assert(head != NULL);

    if (*head == NULL)
        return NULL;

    *dst = (*head)->value;
    list_hld next_head = (*head)->next;

    free(*head);
    *head = NULL;

    return next_head;
}
