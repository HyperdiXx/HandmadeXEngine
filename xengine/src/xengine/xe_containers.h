
enum NodeType
{
    NT_INT32,
    NT_FLOAT32
};

struct Node
{
    NodeType type_node;
    union
    {
        int32 int32_type;
        real32 float32_type;
    };
};

struct Graph
{

};

typedef struct BinarySearchTree
{
    Node data;
    Node *left;
    Node *right;
} BST;


