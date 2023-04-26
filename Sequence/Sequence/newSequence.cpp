//
//  newSequence.cpp
//  Sequence
//
//  Created by Jenna Wang on 4/16/23.
//

#include "newSequence.h"
#include <iostream>

Sequence::Sequence()
    : itemSize(0), maxSize(DEFAULT_MAX_ITEMS)
{
    array = new ItemType[DEFAULT_MAX_ITEMS];
}

Sequence::Sequence(int size)
    : itemSize(0)
{
    if (size < 0)
    {
        exit(0);
    }
    
    maxSize = size;
    array = new ItemType[size];
}

Sequence::~Sequence()
{
    delete [] array;
}

// copy constructor
Sequence::Sequence(const Sequence& other)
    : itemSize(other.itemSize)
{
    array = new ItemType[other.maxSize];
    
    for (int i = 0; i < size(); i++)
    {
        array[i] = other.array[i];
    }
}

// assignment operator
Sequence& Sequence::operator = (const Sequence &rhs)
{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    
    return *this;
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const
{
    return (itemSize == 0);
}

// Return the number of items in the sequence.
int Sequence::size() const
{
    return itemSize;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one greater than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
int Sequence::insert(int pos, const ItemType& value)
{
    if ((0 <= pos) && (pos <= size()) && (size() + 1 <= maxSize))
    {
        for (int i = size(); i >= 0; i--)
        {
            if (i > pos)
            {
                array[i] = array[i-1];
            }
            
            if (i == pos)
            {
                array[i] = value;
            }
        }
        
        itemSize++;
        return pos;
    }
    
    return -1;
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item in position
// p.  The original item in position p and those that follow it end
// up at positions one greater than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value)
{
    if (size() == maxSize)
    {
        return -1;
    }
    
    int p;
    
    for (p = 0; p < size(); p++)
    {
        if (value <= array[p])
        {
            insert(p, value);
            return p;
        }
    }
    
    p = size();
    insert(p, value);
    return p;
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    if ((0 <= pos) && (pos < size()))
    {
        for (int i = 0; i < size() - 1; i++)
        {
            if (i >= pos)
            {
                array[i] = array[i+1];
            }
        }
        
        itemSize--;
        return true;
    }
    
    return false;
}
 
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int num = 0;
    
    for (int i = 0; i < size(); i++)
    {
        if (array[i] == value)
        {
            erase(i);
            num++;
            i--;
        }
    }
    
    return num;
}

// If 0 <= pos < size(), copy into value the item in position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const
{
    if ((0 <= pos) && (pos < size()))
    {
        value = array[pos];
        return true;
    }
    
    return false;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    if ((0 <= pos) && (pos < size()))
    {
        array[pos] = value;
        return true;
    }
    
    return false;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const
{
    for (int p = 0; p < size(); p++)
    {
        if (array[p] == value)
        {
            return p;
        }
    }
    
    return -1;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other)
{
    int temp;
    
    // swap itemSize
    temp = itemSize;
    itemSize = other.itemSize;
    other.itemSize = temp;
    
    // swap maxSize
    temp = maxSize;
    maxSize = other.maxSize;
    other.maxSize = temp;
      
    // swap array content
    ItemType *tempArray = array;
    array = other.array;
    other.array = tempArray;
}

//void Sequence::dump() const
//{
//    // display the sequence
//    for (int i = 0; i < size(); i++)
//    {
//        std::cerr << array[i] << " ";
//    }
//
//    std::cerr << std::endl;
//}

