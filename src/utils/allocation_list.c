#include "utils/allocation_list.h"

#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void allocation_list_insert(allocation_list_io head, const void * address)
{
    assert(address != NULL);
    assert(head != NULL);

    allocation_list_node_hld new_head = malloc(sizeof(allocation_list_node_type));
    new_head->next = *head;
    new_head->allocated_address = address;
    *head = new_head;
}

void allocation_list_remove(allocation_list_io head, const void* address)
{
    assert(address != NULL);
    assert(head != NULL);

    if (*head == NULL)
        return;

    if ((*head)->allocated_address == address) {
        allocation_list_node_ref new_head = (*head)->next;
        free(*head);
        *head = new_head;
        return;
    }

    for (allocation_list_node_hld* cur = head; *cur != NULL; cur = &((*cur)->next))
        if ((*cur)->allocated_address == address) {
            allocation_list_node_hld to_destruct = *cur;
            *cur = (*cur)->next;
            free(to_destruct);
            to_destruct = NULL;
            break;
        }
}

void allocation_list_to_string(allocation_list_cref head, char* buffer, int max_size)
{
    char local_buffer[20];

    for (; head != NULL; head = head->next) {
        sprintf(local_buffer, " %zx", (size_t) head->allocated_address);
        if (strlen(buffer) + strlen(local_buffer) >= max_size)
            return;

        strcat(buffer, local_buffer);
    }
}

