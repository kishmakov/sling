#include "utils/list.h"

#include <assert.h>
#include <stdlib.h>


void list_insert(list_node_io head, void* src)
{
    assert(src != NULL);
    assert(head != NULL);

    list_node_hld new_head = malloc(sizeof(list_node_type));
    new_head->next = *head;
    new_head->value = src;

    *head = new_head;
}

void* list_pop_front(list_node_io head)
{
    assert(head != NULL);

    if (*head == NULL)
        return NULL;

    void* result = (*head)->value;
    list_node_hld next_head = (*head)->next;

    free(*head);
    *head = next_head;

    return result;
}
