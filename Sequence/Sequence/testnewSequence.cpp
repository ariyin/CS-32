//
//  testnewSequence.cpp
//  Sequence
//
//  Created by Jenna Wang on 4/16/23.
//

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a(1000); // a can hold at most 1000 items

    assert(a.empty() == 1);
    assert(a.size() == 0);

    a.insert(42);
    a.insert(21);
    a.insert(420);
    a.insert(69);
    a.insert(19);

    Sequence a2 = Sequence(a);
//    a.dump(); // 19 21 42 69 420
//    a2.dump(); // 19 21 42 69 420

    assert(a.size() == 5);

    unsigned long num;
    a.get(3, num);
    assert(num == 69);
    a.get(4, num);
    assert(num == 420);

    for (int i = 0; i < 995; i++)
    {
        a.insert(i);
    }

//    a.dump();
    assert(a.insert(42) == -1);
    assert(a.insert(0, 42) == -1);

    Sequence b(5); // b can hold at most 5 items
    b.insert(0, 0);
    b.insert(1, 10);

    b.get(1, num);
    assert(num == 10);

    b.insert(1, 5);

    assert(b.size() == 3);
    b.get(1, num);
    assert(num == 5);

    b.insert(15);
    assert(b.insert(20) == 4);
    assert(b.insert(25) == -1);
    assert(b.erase(5) == 0);
    b.erase(4);

//    b.dump(); // 0, 5, 10, 15

    Sequence b2;
    b2.operator=(b);
//    b2.dump(); // 0, 5, 10, 15
    b2.set(3, 20);
//    b.dump(); // 0, 5, 10, 15
//    b2.dump(); // 0, 5, 10, 20

    Sequence c; // c can hold at most DEFAULT_MAX_ITEMS items
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

    c.erase(5);
    assert(c.erase(-1) == 0);
    assert(c.erase(160) == 0);

//    c.dump(); // in numbered order

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
