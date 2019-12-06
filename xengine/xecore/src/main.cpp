

#include <iostream>

#include <xestring.h>
#include <linked_list.h>
#include <stack_linked_list.h>
#include <array.h>
#include <dyn_array.h>

int main(int argc, char **argv)
{
    xestring str("config");
    xestring stringnull("");
    
    char sym = str.find_at(6);
    char s = str[0];

    std::cout << str << std::endl;
  
    str.erase(3);

    str = str.substr(1, 3);

    int a = 213;

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
    
    xedyn_array<int32> dyn_ar;

    dyn_ar.push_back(1231);
    dyn_ar.push_back(12);
    dyn_ar.push_back(1);

    for (int i = 0; i < dyn_ar.size(); i++)
    {
        printf("%d\n", dyn_ar[i]);
    }

    int b = 3;

    return 0;
}
    
    