#include <iostream>
#include "LinkedList.h"


int main() {
    LinkedList a;
    a.PushBack(1);
    a.PushBack(2);
    std::cout << a << std::endl;
    return 0;
}
