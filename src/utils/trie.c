#include "utils/trie.h"

#include "utils/list.h"

#include <stdlib.h>
#include <stdio.h>

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

void trie_insert(trie_node_io node, const char* tag, void* value)
{
    assert(tag != NULL);
    assert(*tag != 0);
    assert(node != NULL);
    assert(trie_check(*node, tag) == NULL);

    while (1) {
        while (*node != NULL && (*node)->code != *tag)
            node = &((*node)->hor);

        if (*node == NULL)
            *node = trie_node_construct(*tag);

        (*node)->count++;

        if (*(++tag) == 0) {
            (*node)->value = value;
            break;
        }

        node = &((*node)->ver);
    }
}

void* trie_remove(trie_node_io node, const char* tag)
{
    assert(tag != NULL);
    assert(*tag != 0);
    assert(node != NULL);

    void* result = trie_check(*node, tag);
    if (result == NULL)
        return NULL;

    list_hld removed_nodes = NULL;

    while (1) {
        while (*node != NULL && (*node)->code != *tag)
            node = &((*node)->hor);

        assert((*node) != NULL);

        trie_node_mv next_ver = &((*node)->ver);
        result = (*node)->value;
        (*node)->value = *(++tag) == 0 ? NULL : result;

        if (--(*node)->count == 0) {
            assert((*node)->value == NULL || *tag == 0);
            list_insert(&removed_nodes, *node);
            *node = (*node)->hor;
        }

        node = next_ver;
        if (*tag == 0)
            break;
    }

    while (removed_nodes != NULL) {
        trie_node_hld to_remove = list_pop_front(&removed_nodes);
        to_remove->value = NULL;
        to_remove->ver = NULL;
        to_remove->hor = NULL;
        trie_node_destruct(&to_remove);
        assert(to_remove == NULL);
    }

    return result;
}

void* trie_check(trie_cref node, const char* tag)
{
    assert(tag != NULL);
    assert(*tag != 0);

    while (1) {
        while (node != NULL && node->code != *tag) {
            printf("%zu -v-> %zu, -h-> %zu\n", (size_t) node, (size_t) node->ver, (size_t) node->hor);
            node = node->hor;
        }

        printf("----\n");

        if (node == NULL)
            return NULL;

        if (*(++tag) == 0)
            return node->value;

        node = node->ver;
    }
}
