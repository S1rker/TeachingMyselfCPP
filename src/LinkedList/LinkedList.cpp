#include "LinkedList.h"

LinkedList::LinkedList()
	: Head(nullptr)

{
	//nothing here
}
LinkedList::~LinkedList()
{
	Clear();
}
void LinkedList::Clear()
{
	Node* Current = Head;
	while (Current != nullptr)
	{
		Node* Temp = Current->Next;
		delete Current;
		Current = Temp;
	}
	Head = nullptr;

}

void LinkedList::PushBack(int value)
{
	//
	if (Head == nullptr)
	{
		Head = new Node(value);
	}
	else
	{
		Node* Current = Head;
		while (Current->Next != nullptr)
		{
			Current = Current->Next;
		}
		Node* Temp = new Node(value, Current);
		Current->Next = Temp;
	}
	
}


std::ostream& operator <<(std::ostream& ostr, const LinkedList& rhs)
{
	std::cout << "X";
	Node* Current = rhs.Head;
	while (Current != nullptr)
	{
		std::cout << Current->data << " ";
		Current = Current->Next;
	}
	std::cout << "X";

	return ostr;
}
void LinkedList::PopBack()
{
	if (Head == nullptr)
	{
		throw std::out_of_range("tried to open an empty list.");

	}

	if (Head->Next == nullptr)
	{
		delete Head;
		Head = nullptr;

	}
	else
	{
		Node* Current = Head;
		while (Current->Next != nullptr)
		{
			Current = Current->Next;
		}
		Current->Previous->Next = nullptr;
		delete Current;
	}

}

double LinkedList::Back()
{
	if (Head == nullptr)
	{
		throw std::out_of_range("tried to call back on an empty list.");

	}
	Node* Current = Head;
	while (Current->Next != nullptr)
	{
		Current = Current->Next;
	}
	return Current->data;
}

double LinkedList::Front()
{
	if (Head == nullptr)
	{
		throw std::out_of_range("tried to call front on an empty list.");

	}
	return Head->data;
}

bool LinkedList::empty()
{
	return Head == nullptr;
}
