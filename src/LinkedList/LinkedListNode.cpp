#include "LinkedListNode.h"

Node::Node(int value, Node* Previous, Node* Next)
    : data(value),
      Previous(Previous),
      Next(Next)
{
}