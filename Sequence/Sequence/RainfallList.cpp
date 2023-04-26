//
//  RainfallList.cpp
//  Sequence
//
//  Created by Jenna Wang on 4/16/23.
//

#include "RainfallList.h"
#include <iostream>

// Create an empty rainfall list.
RainfallList::RainfallList()
    : list()
{

}

// If the rainfall is valid (a value from 0 to 400) and the rainfall list
// has room for it, add it to the rainfall list and return true.
// Otherwise, leave the rainfall list unchanged and return false.
bool RainfallList::add(unsigned long rainfall)
{
    return ((0 <= rainfall && rainfall <= 400) && (list.insert(list.size(), rainfall) != -1));
}

// Remove one instance of the specified rainfall from the rainfall list.
// Return true if a rainfall was removed; otherwise false.
bool RainfallList::remove(unsigned long rainfall)
{
    if (list.find(rainfall) != -1)
    {
        list.erase(list.find(rainfall));
        return true;
    }
    
    return false;
}

// Return the number of rainfalls in the list.
int RainfallList::size() const
{
    return list.size();
}

// Return the lowest-valued rainfall in the rainfall list.  If the list is
// empty, return NO_RAINFALLS.
unsigned long RainfallList::minimum() const
{
    if (list.empty())
    {
        return NO_RAINFALLS;
    }
    
    unsigned long lowest = 400;
    for (int i = 0; i < list.size(); i++)
    {
        unsigned long num;
        list.get(i, num);
        if (num < lowest)
        {
            lowest = num;
        }
    }
    
    return lowest;
}

// Return the highest-valued rainfall in the rainfall list.  If the list is
// empty, return NO_RAINFALLS.
unsigned long RainfallList::maximum() const
{
    if (list.empty())
    {
        return NO_RAINFALLS;
    }
    
    unsigned long highest = 0;
    for (int i = 0; i < list.size(); i++)
    {
        unsigned long num;
        list.get(i, num);
        if (num > highest)
        {
            highest = num;
        }
    }
    
    return highest;
}

//void RainfallList::dump() const
//{
//    // display the sequence
//    for (int i = 0; i < size(); i++)
//    {
//        unsigned long value;
//        list.get(i, value);
//        std::cerr << value << " ";
//    }
//
//    std::cerr << std::endl;
//}

