#include "utils/list.h"

#include <assert.h>
#include <stdlib.h>

void list_insert(list_node_io head, void_mv src)
{
    assert(src != NULL);
    assert(*src != NULL);
    assert(head != NULL);

    list_node_hld new_head = malloc(sizeof(list_node_type));
    new_head->next = *head;
    new_head->value = *src;

    *src = NULL;

    *head = new_head;
}

void_hld list_pop_front(list_node_io head)
{
    assert(head != NULL);

    if (*head == NULL)
        return NULL;

    void_hld result = (*head)->value;
    list_node_hld next_head = (*head)->next;

    free(*head);
    *head = next_head;

    return result;
}

void list_append(list_node_io dst, list_node_mv addition)
{
    assert(dst != NULL);
    assert(addition != NULL);

    if (*addition == NULL)
        return;

    list_node_hld* cur = dst;

    while (*cur != NULL)
        cur = &((*cur)->next);

    *cur = *addition;
    *addition = NULL;
}