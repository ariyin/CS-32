//
//  RainfallList.hpp
//  Sequence
//
//  Created by Jenna Wang on 4/16/23.
//

#ifndef RainfallList_h
#define RainfallList_h

#include "Sequence.h"
#include <limits>

const unsigned long NO_RAINFALLS = std::numeric_limits<unsigned long>::max();

class RainfallList
{
  public:
    RainfallList();
    bool add(unsigned long rainfall);
    bool remove(unsigned long rainfall);
    int size() const;
    unsigned long minimum() const;
    unsigned long maximum() const;
//    void dump() const;
  private:
    Sequence list;
};


#endif /* RainfallList_h */
