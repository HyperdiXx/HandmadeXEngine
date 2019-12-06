#pragma once

#ifndef STACKLINKEDLIST_H
#define STACKLINKEDLIST_H

#include "utilsh.h"
#include "node.h"

class stack_linked_list
{
public:

    stack_linked_list() = default;

    void push(Node *node)
    {
        node->next = head;
        head = node;
    }

    void pop()
    {
        head = head->next;
    }

    Node *pop_val()
    {
        Node *last = head;
        head = head->next;
        return last;
    }

    Node* head;
};

#endif // !STACKLINKEDLIST_H

