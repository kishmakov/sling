#include "utils/trie.h"

#include "utils/list.h"

#include <stdlib.h>

DEBUG(allocation_list_hld allocated_trie_nodes = NULL);

trie_node_hld trie_node_construct(char code)
{
    trie_node_hld result = malloc(sizeof(trie_node_type));
    result->ver = NULL;
    result->hor = NULL;
    result->value = NULL;
    result->count = 0;
    result->code = code;

    DEBUG(allocation_list_insert(&allocated_trie_nodes, result));

    return result;
}

void trie_node_destruct(trie_node_mv node)
{
    DEBUG(allocation_list_remove(&allocated_trie_nodes, *node));

    assert((*node)->hor == NULL);
    assert((*node)->ver == NULL);
    assert((*node)->value == NULL);

    free(*node);
    *node = NULL;
}

trie_hld trie_insert(trie_node_mv node, const char* tag, void* value)
{
    assert(tag != NULL);
    assert(*tag != 0);
    assert(node != NULL);
    assert(trie_check(*node, tag) == NULL);

    trie_hld new_head = NULL;

    if (*node != NULL)
        new_head = *node;

    while (1) {
        while (*node != NULL && (*node)->code != *tag)
            node = &((*node)->hor);

        if (*node == NULL) {
            *node = trie_node_construct(*tag);
            if (new_head == NULL)
                new_head = *node;
        }

        (*node)->count++;

        if (*(++tag) == 0) {
            (*node)->value = value;
            break;
        }

        node = &((*node)->ver);
    }

    return new_head;
}

trie_hld trie_remove(trie_mv node, const char* tag, out_param dst)
{
    assert(tag != NULL);
    assert(*tag != 0);
    assert(node != NULL);

    trie_node_hld* ptr_to_head = node;

    *dst = trie_check(*node, tag);
    if (*dst == NULL)
        return *ptr_to_head;

    list_hld removed_nodes = NULL;

    while (1) {
        while (*node != NULL && (*node)->code != *tag)
            node = &((*node)->hor);

        assert((*node) != NULL);

        trie_node_mv next_ver = &((*node)->ver);
        *dst = (*node)->value;
        (*node)->value = *(++tag) == 0 ? NULL : *dst;

        if (--(*node)->count == 0) {
            assert((*node)->value == NULL || *tag == 0);
            removed_nodes = list_insert(&removed_nodes, *node);
            *node = (*node)->hor;
        }

        node = next_ver;
        if (*tag == 0)
            break;
    }

    while (removed_nodes != NULL) {
        trie_node_hld node = NULL;
        removed_nodes = list_pop_front(&removed_nodes, (void*) &node);
        node->value = NULL;
        node->ver = NULL;
        node->hor = NULL;
        trie_node_destruct(&node);
        assert(node == NULL);
    }

    return *ptr_to_head;
}

void* trie_check(trie_cref node, const char* tag)
{
    assert(tag != NULL);
    assert(*tag != 0);

    while (1) {
        while (node != NULL && node->code != *tag)
            node = node->hor;

        if (node == NULL)
            return NULL;

        if (*(++tag) == 0)
            return node->value;

        node = node->ver;
    }
}
