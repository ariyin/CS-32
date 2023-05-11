//
//  tree.cpp
//  Event
//
//  Created by Jenna Wang on 5/8/23.
//

//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;

// countIncludes, order
// must not use while, for, global variables, static variables, references, pointers (unless it's a parameter representing an array; T x[] = T* x)
// if any of the parameters n, n1, or n2 is negative, act as if it were zero

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then for this value of a2            the function must return
//    "john" "ketanji" "elena"                     1
//    "john" "elena" "samuel"                      2
//    "ketanji" "john" "elena"                     0
//    "sonia" "elena" "samuel"                     3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    if(n2 > n1)
    {
        return 0;
    }
    
    if(n2 <= 0)
    {
        return 1;
    }
    
    if(n1 <= 0)
    {
        return 0;
    }
    
    // if there is a match, check if:
    // the next element in a2 matches the next element in a1
    // the current element in a2 matches the next element in a1
    if(a1[0] == a2[0])
    {
        return countIncludes(a1+1, n1-1, a2+1, n2-1) + countIncludes(a1+1, n1-1, a2, n2);
    }
    
    // if there is no match, check the first string of a2 with the next string in a1
    else
    {
        return countIncludes(a1+1, n1-1, a2, n2);
    }
}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator, int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;

      // It will always be the case that just before evaluating the loop
      // condition:
      //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
      //  Every element earlier than position firstNotLess is < separator
      //  Every element from position firstNotLess to firstUnknown-1 is
      //    == separator
      //  Every element from firstUnknown to firstGreater-1 is not known yet
      //  Every element at position firstGreater or later is > separator

    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if (n <= 1)
    {
        return;
    }

    int firstNotLess, firstGreater;
    // separate the array so that strings <= separator are before the separator
    // and strings > separator are after the separator
    // firstNotLess is the first element that's >= than the separator
    // firstGreater is the first element that's > than the separator
    separate(a, n, a[n-1], firstNotLess, firstGreater);
    // order the first part of the array (from 0 to firstNotLess)
    order(a, firstNotLess);
    // order the second part of the array (from firstGreater to end)
    order(a + firstGreater, n - firstGreater);
}

//void orderTest(string a[], int n)
//{
//    order(a, n);
//
//    for(int i = 0; i < n; i++)
//    {
//        cout << a[i] << ", ";
//    }
//
//    cout << endl;
//}
//
//int main()
//{
//    // return the number of ways that all n2 elements of a2 appear
//    // in the n1 element array a1 in the same order (though not
//    // necessarily consecutively)
//    // int countIncludes(const string a1[], int n1, const string a2[], int n2)
//
//    string s[] = {"john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel"};
//
//    string s2[] = {"john", "ketanji", "elena"};
//    assert(countIncludes(s, 7, s2, 3) == 1);
//
//    string s3[] = {"john", "elena", "samuel"};
//    assert(countIncludes(s, 7, s3, 3) == 2);
//
//    string s4[] = {"ketanji", "john", "elena"};
//    assert(countIncludes(s, 7, s4, 3) == 0);
//
//    string s5[] = {"sonia", "elena", "samuel"};
//    assert(countIncludes(s, 7, s5, 3) == 3);
//
//    string a[] = {"apple", "banana", "banana", "carrot", "date", "eggplant"};
//
//    string a2[] = {"banana", "date", "eggplant"};
//    assert(countIncludes(a, 6, a2, 3) == 2);
//
//    string a3[] = {"banana", "eggplant", "apple"};
//    assert(countIncludes(a, 5, a3, 3) == 0);
//
//    string a4[] = {"date"};
//    assert(countIncludes(a, 5, a4, 1) == 1);
//
//    string a5[] = {"banana"};
//    assert(countIncludes(a, 5, a5, 1) == 2);
//
//    string a6[] = {"kiwi"};
//    assert(countIncludes(a, 5, a6, 1) == 0);
//
//    string b[] = {};
//
//    orderTest(b, 0);
//
//    string b2[] = {"apple"};
//    orderTest(b2, 1);
//    assert(countIncludes(b, 0, b2, 1) == 0);
//
//    // the empty sequence appears in a sequence of length n1 in 1 way, even if n1 is 0.
//
//    string b3[] = {""};
//    assert(countIncludes(b, 0, b3, 0) == 1);
//
//    // rearrange the elements of the array so that a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
//    // if n <= 1, do nothing
//    // void order(string a[], int n)
//
//    string c[] = {"apple", "banana", "cherry", "date"};
//    orderTest(c, 4);
//
//    string d[] = {"date", "cherry", "banana", "apple"};
//    orderTest(d, 4);
//
//    string e[] = {"apple", "banana", "banana", "cherry", "date", "date"};
//    orderTest(e, 6);
//
//    string f[] = {"apple", "date", "banana", "date", "cherry", "banana"};
//    orderTest(f, 6);
//
//    string g[] = {"", "apple", "", "banana", "cherry", "date"};
//    orderTest(g, 6);
//
//    string h[] = {"", "apple", "date", "", "cherry", "banana"};
//    orderTest(h, 6);
//
//    cout << "Passed all tests!" << endl;
//
//    return 0;
//}
