class Vector
{
    public:
        Vector();
        Vector(const Vector& rhs);
        Vector(int element, int value=0);


        ~Vector();

        void PushBack(int value);

        bool Empty() const;
        int Size() const;
        int Capacity() const;

        bool operator==(const Vector& rhs) const;
        bool operator!=(const Vector& rhs) const;

    private:
        int size;
        int capacity;
        int* array;



};