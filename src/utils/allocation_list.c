#include "utils/allocation_list.h"

#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

allocation_list allocation_list_insert(allocation_list_mv head, const void * address)
{
    assert(address != NULL);
    assert(head != NULL);

    allocation_list_node_hld new_head = malloc(sizeof(allocation_list_node_type));
    new_head->next = *head;
    new_head->allocated_address = address;
    *head = NULL;

    return new_head;
}

allocation_list allocation_list_remove(allocation_list_mv head, const void* address)
{
    assert(address != NULL);
    assert(head != NULL);

    allocation_list result = NULL;

    if (*head == NULL)
        return result;

    if ((*head)->allocated_address == address) {
        result = (*head)->next;
        free(*head);
        *head = NULL;
        return result;
    }

    for (allocation_list_node_mv cur = head; *cur != NULL; cur = &((*cur)->next)) {
        if (address != (*cur)->allocated_address)
            continue;

        allocation_list_node_hld to_destruct = *cur;
        *cur = (*cur)->next;
        free(to_destruct);
        to_destruct = NULL;
    }

    result = *head;
    *head = NULL;

    return result;

}

void allocation_list_to_string(allocation_list_cref head, char* buffer, int max_size)
{
    char local_buffer[20];

    for (; head != NULL; head = head->next) {
        sprintf(local_buffer, " %zu", (size_t) head->allocated_address);
        if (strlen(buffer) + strlen(local_buffer) >= max_size)
            return;

        strcat(buffer, local_buffer);
    }
}

