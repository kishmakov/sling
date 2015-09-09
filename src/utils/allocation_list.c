#include "utils/allocation_list.h"

#include "utils/diagnostics.h"
#include "utils/log.h"

#include <stdlib.h>
#include <string.h>

void allocation_list_insert(allocation_list_node_ptr* head_holder, const void * address)
{
    assert(address != NULL);
    assert(head_holder != NULL);

    allocation_list_node_ptr new_head = malloc(sizeof(allocation_list_node_type));
    new_head->next = *head_holder;
    new_head->allocated_address = address;
    *head_holder = new_head;
}

void allocation_list_remove(allocation_list_node_ptr* head_holder, const void* address)
{
    assert(address != NULL);
    assert(head_holder != NULL);
    assert(*head_holder != NULL);

    int count = 0;

    for (allocation_list_node_ptr* current = head_holder; *current != NULL; ) {
        if (address != (*current)->allocated_address) {
            current = &((*current)->next);
            continue;
        }

        allocation_list_node_ptr to_delete = *current;
        *current = (*current)->next;
        free(to_delete);
        count++;
    }

    assert(count == 1);
}

void allocation_list_to_string(allocation_list_node_cptr head, char* buffer, int max_size)
{
    char local_buffer[20];

    for (allocation_list_node_cptr current = head; current != NULL; current = current->next) {
        sprintf(local_buffer, " %zu", (size_t) current->allocated_address);
        if (strlen(buffer) + strlen(local_buffer) < max_size)
            strcat(buffer, local_buffer);
        else
            return;
    }
}

