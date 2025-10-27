#include "LinkedList.h"

LinkedList::LinkedList()
	: Head(nullptr)

{
	//nothing here
}
LinkedList::~LinkedList()
{
	
}

void LinkedList::PushBack(int value)
{
	//
	if (Head == nullptr)
	{
		Head = new Node(value);
	}
	
}
