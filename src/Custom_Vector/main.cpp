#include <iostream>

int* array;
int size=0;
int capacity=5;

void PushBack(int value)
{
    array[size] = value;
    ++size;
}

int main()
{
    capacity = 5;

    array = new int[capacity];
    PushBack(3);
    PushBack(5);

    delete [] array;

    return 0;
}