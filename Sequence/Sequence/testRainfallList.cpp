//
//  testRainfallList.cpp
//  Sequence
//
//  Created by Jenna Wang on 4/16/23.
//

#include "RainfallList.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    RainfallList a;
    assert(a.size() == 0);

    assert(a.add(401) == 0);
    assert(a.add(1) == 1);
    a.add(2);
    a.add(3);
    a.add(2);
    assert(a.add(-5) == 0);
//    a.dump(); // 1, 2, 3, 2

    assert(a.remove(2) == 1);
    assert(a.remove(0) == 0);
    assert(a.size() == 3);
    assert(a.minimum() == 1);
    assert(a.maximum() == 3);
//    a.dump(); // 1, 3, 2

    RainfallList b;
    assert(b.minimum() == NO_RAINFALLS);
    assert(b.maximum() == NO_RAINFALLS);
    
    RainfallList c;
    for (int i = 1; i < 160; i++)
    {
        c.add(i);
    }
    
    assert(c.add(0) == 1);
    assert(c.add(0) == 0);

    cout << "All tests passed!" << endl;
}
