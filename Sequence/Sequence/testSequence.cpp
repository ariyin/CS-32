//
//  testSequence.cpp
//  Sequence
//
//  Created by Jenna Wang on 4/14/23.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a;

    assert(a.empty() == 1);
    assert(a.size() == 0);

    a.insert(42);
    a.insert(21);
    a.insert(420);
    a.insert(69);
    a.insert(19);

    assert(a.size() == 5);

    unsigned long num;
    a.get(3, num);
    assert(num == 69);
    a.get(4, num);
    assert(num == 420);

    Sequence b;
    b.insert(0, 0);
    b.insert(1, 10);

    b.get(1, num);
    assert(num == 10);

    b.insert(1, 5);

    assert(b.size() == 3);
    b.get(1, num);
    assert(num == 5);
    assert(b.insert(15) == 3);

//    a.dump(); // 19, 21, 42, 69, 420
//    b.dump(); // 0, 5, 10, 15

    Sequence c;
    for (int i = 0; i < 159; i++)
    {
        c.insert(i);
    }

    assert(c.insert(-1, 0) == -1);
    c.insert(5, 0); // 0 in 5th position
//    c.dump(); // in numbered order, aside from 0

    assert(c.insert(0, 42) == -1);
    assert(c.insert(42) == -1);

    c.swap(b);
//    b.dump(); // in numbered order, aside from 0
//    c.dump(); // 0, 5, 10, 15
    assert(c.insert(42) != -1);
    assert(b.insert(42) == -1);

    c.erase(3);
    assert(c.erase(-1) == 0);
    assert(c.erase(160) == 0);

//    c.dump(); // 0, 5, 10, 42

    Sequence d;
    for (int i = 0; i < 10; i++)
    {
        d.insert(42);
    }

//    d.dump(); // 42 x 10
    d.insert(10, 0);
    assert(d.find(42) == 0);
    d.set(0, 0);
    d.set(1, 1);
//    d.dump(); // 0, 1, 42 x 8, 0
    assert(d.find(42) == 2);
    assert(d.remove(42) == 8);
//    d.dump(); // 0, 1, 0

    d.swap(a);
//    a.dump(); // 0, 1, 0
//    d.dump(); // 19, 21, 42, 69, 420

    cout << "All tests passed!" << endl;
}

