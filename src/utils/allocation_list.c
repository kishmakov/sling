#include "utils/allocation_list.h"

#include "utils/log.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

void allocation_list_insert(allocation_list* node_holder, const void * address)
{
    assert(address != NULL);
    assert(node_holder != NULL);

    allocation_list_node_ptr new_head = malloc(sizeof(allocation_list_node_type));
    new_head->next = *node_holder;
    new_head->allocated_address = address;
    *node_holder = new_head;
}

void allocation_list_remove(allocation_list* node_holder, const void* address)
{
    assert(address != NULL);
    assert(node_holder != NULL);
    assert(*node_holder != NULL);

    int count = 0;

    for (; *node_holder != NULL; ) {
        if (address != (*node_holder)->allocated_address) {
            node_holder = &((*node_holder)->next);
            continue;
        }

        allocation_list_node_ptr to_delete = *node_holder;
        *node_holder = (*node_holder)->next;
        free(to_delete);
        count++;
    }

    assert(count == 1);
}

void allocation_list_to_string(const allocation_list* node_holder, char* buffer, int max_size)
{
    char local_buffer[20];

    for (; *node_holder != NULL; node_holder = &((*node_holder)->next)) {
        sprintf(local_buffer, " %zu", (size_t) (*node_holder)->allocated_address);
        if (strlen(buffer) + strlen(local_buffer) >= max_size)
            return;

        strcat(buffer, local_buffer);
    }
}

