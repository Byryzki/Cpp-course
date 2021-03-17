#include "array_operations.hh"
#include <algorithm>

int greatest_v1(int *itemptr, int size)
{
    int greatest = *itemptr ;
    for(int i = 0; i < size; ++i)
    {
        int current = *(itemptr + i);
        greatest = std::max(greatest, current);
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int current = *itemptr;
    for(;itemptr != endptr; ++itemptr)
    {
        current = std::max(current, *itemptr);
    }
    return current;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    for(;itemptr != endptr; ++itemptr, ++targetptr)
    {
        *targetptr = *itemptr;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    for(--rightptr;leftptr < rightptr; --rightptr, ++leftptr)
    {
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
    }
}
