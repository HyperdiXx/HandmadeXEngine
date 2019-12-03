

#include <iostream>

#include <xestring.h>
#include <linked_list.h>

int main(int argc, char **argv)
{
    xestring str("config");
    xestring stringnull("");
    char sym = str.find_at(6);
    char s = str[0];

    std::cout << str << std::endl;
  
    str.erase(3);

    xestring st = str.substr(1, 3);


    str.clear_str();

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

    int b = 3;

    return 0;
}
    
    