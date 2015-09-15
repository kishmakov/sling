#include "utils/trie.h"

#include "utils/list.h"

#include <stdlib.h>

DEBUG(allocation_list_node_ptr allocated_trie_nodes = NULL);

trie_node_ptr trie_node_construct(char code)
{
    trie_node_ptr result = malloc(sizeof(trie_node_type));
    result->ver = NULL;
    result->hor = NULL;
    result->value = NULL;
    result->count = 0;
    result->code = code;

    DEBUG(allocation_list_insert(&allocated_trie_nodes, result));

    return result;
}

void trie_node_delete(trie_node_ptr* node_holder)
{
    DEBUG(allocation_list_remove(&allocated_trie_nodes, *node_holder));

    assert((*node_holder)->hor == NULL);
    assert((*node_holder)->ver == NULL);
    assert((*node_holder)->value == NULL);

    free(*node_holder);
    *node_holder = NULL;
}

void trie_insert(trie* node_holder, const char* tag, void* value)
{
    assert(tag != NULL);
    assert(*tag != 0);
    assert(node_holder != NULL);
    assert(trie_check(node_holder, tag) == NULL);

    while (1) {
        while (*node_holder != NULL && (*node_holder)->code != *tag)
            node_holder = &((*node_holder)->hor);

        if (*node_holder == NULL)
            *node_holder = trie_node_construct(*tag);

        (*node_holder)->count++;

        if (*(++tag) == 0) {
            (*node_holder)->value = value;
            break;
        }

        node_holder = &((*node_holder)->ver);
    }
}

void* trie_remove(trie* node_holder, const char* tag)
{
    assert(tag != NULL);
    assert(*tag != 0);
    assert(node_holder != NULL);

    void* result = trie_check(node_holder, tag);
    if (result == NULL)
        return result;

    list removed_nodes = NULL;

    while (1) {
        while (*node_holder != NULL && (*node_holder)->code != *tag)
            node_holder = &((*node_holder)->hor);

        assert((*node_holder) != NULL);

        trie_node_ptr* next_ver = &((*node_holder)->ver);
        result = (*node_holder)->value;
        (*node_holder)->value = *(++tag) == 0 ? NULL : result;

        if (--(*node_holder)->count == 0) {
            assert((*node_holder)->value == NULL || *tag == 0);
            list_insert(&removed_nodes, *node_holder);
            *node_holder = (*node_holder)->hor;
        }

        node_holder = next_ver;
        if (*tag == 0)
            break;
    }

    while (removed_nodes != NULL) {
        trie_node_ptr node = list_pop_front(&removed_nodes);
        node->value = NULL;
        node->ver = NULL;
        node->hor = NULL;
        trie_node_delete(&node);
        assert(node == NULL);
    }

    return result;
}

void* trie_check(const trie* node_holder, const char* tag)
{
    assert(node_holder != NULL);
    assert(tag != NULL);
    assert(*tag != 0);

    while (1) {
        while (*node_holder != NULL && (*node_holder)->code != *tag)
            node_holder = &((*node_holder)->hor);

        if (*node_holder == NULL)
            return NULL;

        if (*(++tag) == 0)
            return (*node_holder)->value;

        node_holder = &((*node_holder)->ver);
    }
}
