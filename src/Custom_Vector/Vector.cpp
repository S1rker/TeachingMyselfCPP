#include "Vector.h"

Vector::Vector()
    : size(0),
      capacity(5),
      array(new int[capacity])
{
}

Vector::Vector(const Vector& rhs)
    : size(rhs.size),
      capacity(rhs.capacity),
      array(new int[capacity])
{
    for (int i = 0; i < rhs.Size(); ++i)
        array[i] = rhs.array[i];
}

Vector::Vector(int element, int value)
    : size(element),
      capacity(element > 0 ? element : 5),
      array(new int[capacity])
{
    for (int i = 0; i < size; ++i)
        array[i] = value;
}

Vector::~Vector()
{
    delete[] array;
}

void Vector::PushBack(int value)
{
    array[size];
    ++size;
}

bool Vector::Empty() const
{
    return size == 0;
}
 
int Vector::Size() const
{
    return size;
}

int Vector::Capacity() const
{   
    return capacity;
}

bool Vector::operator==(const Vector& rhs) const
{
    if(Size() != rhs.Size())
    {
        return false;
    }

    for (int i = 0; i < Size(); i++)
    {
        if(array[i] != rhs.array[i])
        {
            return false;
        }
    }
    return true;
    
}

bool Vector::operator!=(const Vector& rhs) const
{
    return !(*this == rhs);
}
