#include <iostream>
#include "LinkedListNode.h"

class LinkedList
{
	public:
		LinkedList();
		~LinkedList();

		void Clear();

		void PushBack(int value);
		void PopBack();

		friend std::ostream& operator <<(std::ostream& ostr, const LinkedList& rhs);

		double Front();
		double Back();

		bool empty();


	private:
		Node* Head;
};
