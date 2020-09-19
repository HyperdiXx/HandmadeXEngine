
internal struct Node* createNode(Node data)
{  
    Node *node = NULL;//(Node*)AllocHeap(sizeof(Node));

     

    return node;
}

internal void fillNodeType(Node &type)
{
    switch (type.type_node)
    {
        case NodeType::NT_INT32:
        {
            //type. = (int32)int32_type;
        } break;
        case NodeType::NT_FLOAT32:
        {
            

        } break;
        default:
            break;
    }
}
