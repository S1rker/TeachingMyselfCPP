#include "LinkedListNode.h"

class LinkedList
{
	public:
		LinkedList();
		~LinkedList();

		void PushBack(int value);

	private:
		Node* Head;
};
