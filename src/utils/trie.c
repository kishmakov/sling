#include "utils/trie.h"

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

trie_hld trie_construct()
{
    return (trie_hld) calloc(1, sizeof(trie_type));
}

list_hld trie_destruct(trie_mv trie_ptr)
{
    trie_ref trie = *trie_ptr;

    list_hld values_left = NULL;

    if (trie->size > 0) {
        trie_node_hld* nodes = malloc(sizeof(trie_node_hld) * trie->size);

        uint32_t current_id = 0;
        uint32_t last_id = 0;
        nodes[last_id++] = trie->root;

        while (current_id < trie->size) {
            if (nodes[current_id]->hor != NULL)
                nodes[last_id++] = nodes[current_id]->hor;

            if (nodes[current_id]->ver != NULL)
                nodes[last_id++] = nodes[current_id]->ver;

            current_id++;
        }

        for (uint32_t id = 0; id < trie->size; id++) {
            nodes[id]->ver = NULL;
            nodes[id]->hor = NULL;
            if (nodes[id]->value != NULL) {
                list_insert(&values_left, &(nodes[id]->value));
                nodes[id]->value = NULL;
            }
            trie_node_destruct(&nodes[id]);
            assert(nodes[id] == NULL);
        }

        free(nodes);
    }

    free(trie);
    *trie_ptr = 0;

    return values_left;
}

void trie_insert(trie_ref trie, const char* tag, void_hld value)
{
    assert(trie != NULL);
    assert(tag != NULL);
    assert(*tag != 0);
    assert(trie_check(trie, tag) == NULL);

    trie_node_hld* node_ptr = &(trie->root);

    while (1) {
        while (*node_ptr != NULL && (*node_ptr)->code != *tag)
            node_ptr = &((*node_ptr)->hor);

        if (*node_ptr == NULL) {
            *node_ptr = trie_node_construct(*tag);
            trie->size++;
        }

        (*node_ptr)->count++;

        if (*(++tag) == 0) {
            (*node_ptr)->value = value;
            break;
        }

        node_ptr = &((*node_ptr)->ver);
    }
}

void_hld trie_remove(trie_ref trie, const char* tag)
{
    assert(trie != NULL);
    assert(tag != NULL);
    assert(*tag != 0);

    void_hld result = trie_check(trie, tag);
    if (result == NULL)
        return NULL;

    list_hld removed_nodes = NULL;

    trie_node_hld* node_ptr = &(trie->root);

    while (1) {
        while (*node_ptr != NULL && (*node_ptr)->code != *tag)
            node_ptr = &((*node_ptr)->hor);

        assert((*node_ptr) != NULL);

        trie_node_hld* next_ver = &((*node_ptr)->ver);
        result = (*node_ptr)->value;
        (*node_ptr)->value = *(++tag) == 0 ? NULL : result;

        if (--(*node_ptr)->count == 0) {
            assert((*node_ptr)->value == NULL || *tag == 0);
            void_hld backup = (void_hld) *node_ptr;
            *node_ptr = (*node_ptr)->hor;
            list_insert(&removed_nodes, &backup);
        }

        node_ptr = next_ver;
        if (*tag == 0)
            break;
    }

    while (removed_nodes != NULL) {
        trie_node_hld to_remove = (trie_node_hld) list_pop_front(&removed_nodes);
        to_remove->ver = NULL;
        to_remove->hor = NULL;
        assert(to_remove->value == NULL);
        trie_node_destruct(&to_remove);
        trie->size--;
        assert(to_remove == NULL);
    }

    return result;
}

void_ref trie_check(trie_cref trie, const char* tag)
{
    assert(trie != NULL);
    assert(tag != NULL);
    assert(*tag != 0);

    trie_node_cref node = trie->root;

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

