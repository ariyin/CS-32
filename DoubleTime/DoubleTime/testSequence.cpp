//
//  testSequence.cpp
//  DoubleTime
//
//  Created by Jenna Wang on 4/24/23.
//

#include "Sequence.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    // testing cases:
    // middle
    // front
    // back
    // empty
    // one-element list

    // constructor
    Sequence a;

    assert(a.empty() == 1); // empty = true
    assert(a.size() == 0); // size = 0

    // copy constructor
    cerr << "COPY CONSTRUCTOR" << endl;
    Sequence a2 = a; // copying empty list
    a2.dump(); // [empty]

    // insert(value)
    cerr << endl << "INSERT(VALUE)" << endl;
    a.insert("i"); // insert into empty sequence
    a.insert("love"); // insert at back, one-element list
    a.insert("cats"); // insert at front
    a.insert("so"); // insert at back
    assert(a.insert("much") == 3); // insert in middle

    a.dump(); // cats i love much so
    assert(a.empty() == 0); // empty = false
    assert(a.size() == 5); // size = 5

    // copy constructor pt.2
    cerr << endl << "COPY CONSTRUCTOR PT.2" << endl;
    Sequence a3 = a;
    a3.dump(); // cats i love much so

    // get
    string str;
    a.get(3, str);
    assert(str == "much");
    a.get(4, str);
    assert(str == "so");

    // insert(pos, value)
    cerr << endl << "INSERT(POS, VALUE)" << endl;
    Sequence b;
    b.insert(0, "are"); // insert into empty sequence
    b.insert(1, "than"); // insert at back, one-element list

    b.get(1, str);
    assert(str == "than");

    b.insert(1, "better"); // insert middle

    assert(b.size() == 3);
    b.get(1, str);
    assert(str == "better");
    assert(b.insert(3, "dogs") == 3); // insert at back
    assert(b.insert(0, "cats") == 0); // insert at front
    assert(b.insert(-1, "meow") == -1); // out of bounds
    assert(b.insert(6, "meow") == -1); // out of bounds

    b.dump(); // cats are better than dogs

    // find
    assert(b.find("better") == 2); // middle
    assert(b.find("cats") == 0); // beginning
    assert(b.find("dogs") == 4); // end

    // assignment operator
    cerr << endl << "ASSIGNMENT OPERATOR" << endl;
    Sequence b2;
    b2.operator=(b);
    b2.dump(); // cats are better than dogs
    b2.set(4, "everything");
    b.dump(); // cats are better than dogs
    b2.dump(); // cats are better than everything

    Sequence c;
    c.insert("meow");
    c.insert("meow");
    c.insert("meow");

    // find pt.2
    assert(c.find("meow") == 0); // multiple instances of the same word
    assert(c.find("woof") == -1); // nonexistent

    // swap
    cerr << endl << "SWAP" << endl;
    c.swap(b);
    b.dump(); // meow meow meow
    c.dump(); // cats are better than dogs

    // erase
    cerr << endl << "ERASE" << endl;
    assert(c.erase(-1) == 0); // out of bounds
    c.erase(0); // erase at front
    c.dump(); // are better than dogs
    c.erase(3); // erase at back
    c.dump(); // are better than
    c.erase(1); // erase middle
    c.dump(); // are than
    c.erase(0);
    c.dump(); // than
    c.erase(0); // erase single item
    c.dump(); // [empty]
    assert(c.erase(0) == 0); // empty list

    // remove
    cerr << endl << "REMOVE" << endl;
    b.insert(2, "woof"); // removing with a word in between
    b.dump(); // meow meow woof meow
    assert(b.remove("meow") == 3);
    b.dump(); // woof
    b.remove("woof");

    b.insert("meow"); // removing a single word
    assert(b.remove("meow") == 1);
    b.dump(); // [empty]

    assert(b.remove("meow") == 0);  // removing an empty list
    b.dump(); // [empty]

    // swap pt.2
    cerr << endl << "SWAP PT.2" << endl;

    // swapping empty sequences
    b.swap(c);
    b.dump(); // [empty]
    c.dump(); // [empty]

    // swapping one non-empty sequence with an empty sequence
    b.insert("meow");
    b.swap(c);
    b.dump(); // [empty]
    c.dump(); // meow

    assert(b.find("meow") == -1); // finding in an empty sequence

    cerr << endl << "SET" << endl;

    Sequence d;
    d.insert(0, "cats");
    d.insert(1, "could");
    d.insert(2, "rule");
    d.insert(3, "the");
    d.insert(4, "world");

    d.dump(); // cats could rule the world

    // set
    assert(d.set(5, "meow") == 0); // out of bounds
    assert(d.set(-1, "meow") == 0); // out of bounds
    assert(d.set(0, "bow") == 1); // within bounds
    d.dump(); // bow could rule the world
    assert(d.set(1, "before") == 1);
    d.dump(); // bow before rule the world
    assert(d.set(2, "the") == 1);
    d.dump(); // bow before the the world
    assert(d.set(3, "cats") == 1);
    d.dump(); // bow before the cats world
    assert(d.set(4, "now") == 1);
    d.dump(); // bow before the cats now

    d.insert(2, "bow");
    d.insert(3, "before");
    d.dump(); // bow before bow before the cats now

    // subsequence
    cerr << endl << "SUBSEQUENCE" << endl;

    Sequence e;
    e.insert(0, "bow");
    e.insert(1, "before");
    e.dump(); // bow before

    assert(subsequence(d, d) == 0); // same sequence
    assert(subsequence(d, e) == 0);
    e.insert(2, "the");
    assert(subsequence(d, e) == 2);

    e.insert(3, "felines");
    assert(subsequence(d, e) == -1);

    Sequence f; // empty sequence
    assert(subsequence(d, f) == -1); // empty subsequence
    assert(subsequence(e, d) == -1); // longer subsequence

    // concatReverse
    cerr << endl << "CONCATREVERSE" << endl;
    Sequence h; // empty sequence
    Sequence g; // result sequence 1
    Sequence i; // result sequence 2

    e.dump(); // bow before the felines
    concatReverse(f, e, g); // seq1 is empty
    g.dump(); // felines the before bow

    concatReverse(e, f, i); // seq2 is empty
    i.dump(); // felines the before bow

    concatReverse(f, h, g); // both sequences are empty, result is empty
    g.dump(); // [empty]

    concatReverse(i, h, g); // i = "felines before the bow", h = empty, g = "felines the before bow"
    g.dump(); // bow before the felines

    concatReverse(f, h, g); // both sequences are empty, result is not empty
    g.dump(); // [empty]

    concatReverse(e, e, e); // same sequence for all three
    e.dump(); // felines the before bow felines the before bow

    concatReverse(e, i, e); // seq1 and result are the same sequence
    e.dump(); // bow before the felines bow before the felines bow before the felines

    cout << endl << "ALL TESTS PASSED" << endl;
}
