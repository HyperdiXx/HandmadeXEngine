

#include <iostream>

#include <xestring.h>
#include <linked_list.h>
#include <stack_linked_list.h>
#include <array.h>
#include <dyn_array.h>
#include <xemap.h>

#include <string_parser.h>

#include "stack_allocator.h"

void stack_allocator_test()
{
    StackAllocator* stack = new StackAllocator(1024);

    void *m_block = stack->get_memory_block(256, 16);


}

int main(int argc, char **argv)
{
    stack_allocator_test();



    ///////////////////////////////////
    xestring str("config");
    xestring stringnull("");
    xestring parsed_string("project xengine x64 release v01 project game x64 release project val fasihujbf fbahsjfb jhkfshak hfhajhskfh jksfah fkjha sjkfh kajsfh jkash jkfhaks hkj");
    
    string_parser::skip_whitespaces(&parsed_string);

    std::cout << parsed_string << "\n";

    char sym = str.find_at(6);
    char s = str[0];

    std::cout << str << std::endl;  

    linked_list ll;

    Node node1;
    Node node2;
    Node node3;

    node1.data = 1;
    node1.next = nullptr;
    node2.data = 2;
    node2.next = nullptr;
    node3.data = 3;
    node3.next = nullptr;

    ll.head = &node1;

    ll.insert(&node3, &node1);
    ll.insert(&node2, &node3);
    
    ll.print_all_nodes();

    stack_linked_list stl;

    stl.push(&node1);
    stl.push(&node2);
    stl.push(&node3);

    Node *erased = stl.pop_val();
    
    if(erased != nullptr)
        printf("%d\n", erased->data);

    xearray<int32> art;

    art.push_back(5);
    art.push_back(2761);
    art.push_back(105);
    
    auto f = art.first();
    auto l = art.last();

    art.pop();
    art.pop();
    
    art.push_back(421);
    art.push_back(4211);
    art.push_back(4421421);

    int32 check = art[2];

    art.insert(1778, 1);
    
    xedyn_array<int32> vector;

    for (int i = 0; i < 5; ++i)
    {
        vector.push_back(i);
    }

    vector.insert(2, 21284);

    printf("Before pop\n");
    for (uint32 i = 0; i < vector.size(); i++)
    {
        printf("%d\n", vector[i]);
    }

    vector.remove(21284);
    vector.pop();

    printf("After deleting\n");
    for (uint32 i = 0; i < vector.size(); i++)
    {
        printf("%d\n", vector[i]);
    }

    int b = 3;

    return 0;
}
    
    