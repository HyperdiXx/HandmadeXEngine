#pragma once

#ifndef LINKED_LIST
#define LINKED_LIST

#include "utilsh.h"
#include "node.h"

class linked_list
{    
public:
    linked_list() = default;
     
    void insert(Node *n, Node *prev)
    {
        if (prev == nullptr)
        {
            if (head != nullptr)
            {
                n->next = head;
            }
            else
            {
                n->next = nullptr;
               
            }

            head = n;
        }
        else
        {
            if (prev->next != nullptr)
            {
                n->next = prev->next;
                prev->next = n;
            }
            else
            {
                prev->next = n;
                n->next = nullptr;
            }
        }
    }
      
    void remove(Node *d, Node *prev)
    {
        if (prev == nullptr)
        {
            if (d->next = nullptr)
            {
                head = nullptr;
            }
            else
            {
                head = d->next;
            }
        }
        else
        {
            prev->next = d->next;
        }
    }
    
    void print_all_nodes()
    {    
        Node *node = head;
        while (node != nullptr)
        {
            printf("%d\n", node->data);
            node = node->next;
        }        
    }

public:
    Node *head;
};

#endif // !LINKED_LIST

