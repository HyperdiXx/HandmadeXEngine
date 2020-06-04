#pragma once

#include "memory_allocate.h"

#ifndef BTREE_H
#define BTREE_H

struct BSTreeNode
{
    int value;
    BSTreeNode *left_node;
    BSTreeNode *right_node;
};


BSTreeNode* create_node(BSTreeNode *node, int d)
{
    if (!node)
    {
        node = (BSTreeNode*)allocate_memory(sizeof(BSTreeNode));

        node->value = d;
        node->left_node = nullptr;
        node->right_node = nullptr;
        return node;
    }

    if (node->value > d)
    {
        // Left node case
        node->left_node = create_node(node->left_node, d);
    }
    else
    {
        // Right node case
        node->right_node = create_node(node->right_node, d);
    }

    return node;
}

void rtaverse_tree_preorder(BSTreeNode *root)
{
    if (!root)
        return;

    printf("%d\n", root->value);

    rtaverse_tree_preorder(root->left_node);
    rtaverse_tree_preorder(root->right_node);
}

void postorder(BSTreeNode *root)
{
    if (!root)
        return;

    postorder(root->left_node);
    postorder(root->right_node);

    printf("%d\n", root->value);
}

void inorder(BSTreeNode *root)
{
    if (!root)
        return;

    inorder(root->left_node);
    printf("%d\n", root->value);
    inorder(root->right_node);
}

BSTreeNode *find(BSTreeNode *root, int d)
{
    if (!root)
        return nullptr;

    if (root->value == d)
        return root;

    if (root->value > d)
    {
        if (root->left_node)
        {
            find(root->left_node, d);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        if (root->right_node)
        {
            find(root->right_node, d);
        }
        else
        {
            return nullptr;
        }
    }
}

BSTreeNode *min(BSTreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    if (root->left_node == nullptr)
        return root;
    else
        return min(root->left_node);
}

BSTreeNode *max(BSTreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    if (root->right_node == nullptr)
        return root;
    else
        return min(root->right_node);
}



struct binary_search_tree
{
    BSTreeNode *root;

    void add_node(int val)
    {
        root = create_node(root, val);
    }
};


#endif
