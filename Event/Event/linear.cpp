//
//  linear.cpp
//  Event
//
//  Created by Jenna Wang on 5/8/23.
//

//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;
//
//// must not use while, for, global variables, static variables, references, pointers (unless it's a parameter representing an array; T x[] = T* x)
//// if any of the parameters n, n1, or n2 is negative, act as if it were zero
//
//// first three functions must use this
//// predicate s is empty
//bool somePredicate(string s)
//{
//    return s.empty();
//}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    if(n <= 0)
    {
        return true;
    }
    
    if(!somePredicate(a[0]))
    {
        return false;
    }
    
    return(allTrue(a+1, n-1));
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const string a[], int n)
{
    if(n <= 0)
    {
        return 0;
    }
    
    else
    {
        // the count from the next array index to the end of the array
        int count = countTrue(a+1, n-1);
        
        // the count for this array index
        if(somePredicate(a[0]))
        {
            count++;
        }
        
        return count;
    }
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    if(n <= 0)
    {
        return -1;
    }
    
    if(somePredicate(a[0]))
    {
        return 0;
    }
    
    else
    {
        int index = firstTrue(a+1, n-1);
        
        // if index == -1 (you reach the end and there's no element), return -1
        // else return 1 + index ()
        return index == -1 ? -1 : 1 + index;
    }
}

// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1). If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if(n <= 0)
    {
        return -1;
    }
    
    if(n == 1)
    {
        return 0;
    }
    
    else
    {
        int maxIndex = positionOfMax(a+1, n-1) + 1;
        
        // if current element is >= all elements in subarray a[1..n-1], return its index 0
        // else return max index in subarray
        return a[0] >= a[maxIndex] ? 0 : maxIndex;
    }
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    if(n2 > n1)
    {
        return false;
    }
    
    if(n2 <= 0)
    {
        return true;
    }
    
    if(n1 <= 0)
    {
        return false;
    }
    
    // if there is a match, check if the next strings in a2 can also find a match from the next strings in a2
    if(a1[0] == a2[0])
    {
        return contains(a1+1, n1-1, a2+1, n2-1);
    }
    
    // if there is no match, check the first string of a2 with the next string in a1
    else
    {
        return contains(a1+1, n1-1, a2, n2);
    }
}

// int main()
// {
//     // bool somePredicate(string s)
//     // {
//     //     return s.empty();
//     // }
//
//     // return true if all elements are empty
//     // bool allTrue(const string a[], int n)
//
//     // return how many empty elements there are
//     // int countTrue(const string a[], int n)
//
//     // return the subscript of the first element in the array that's empty
//     // if it doesn't exist, return -1
//     // int firstTrue(const string a[], int n)
//
//     // if all n2 elements of a2 appear in the n1 element array a1, in
//     // the same order (though not necessarily consecutively), then return true
//     // otherwise, return false.
//     // bool contains(const string a1[], int n1, const string a2[], int n2)
//
//     // return the subscript of the first string in the array that is >= all strings in the array
//     // if <= 0 strings, return -1
//     // int positionOfMax(const string a[], int n)
//
//     string a[] = {};
//     assert(allTrue(a, 0) == true);
//     assert(countTrue(a, 0) == 0);
//     assert(firstTrue(a, 3) == 0);
//     assert(positionOfMax(a, 0) == -1);
//
//     string b[] = {"", "", ""};
//     assert(allTrue(b, 3) == true);
//     assert(countTrue(b, 3) == 3);
//     assert(firstTrue(b, 3) == 0);
//     assert(positionOfMax(b, 3) == 0);
//
//     string c[] = {"not empty", "", "not empty"};
//     assert(allTrue(c, 3) == false);
//     assert(countTrue(c, 3) == 1);
//     assert(firstTrue(c, 3) == 1);
//     assert(positionOfMax(c, 3) == 0);
//
//     string d[] = {"not empty", "not empty", "not empty"};
//     assert(allTrue(d, 3) == false);
//     assert(countTrue(d, 3) == 0);
//     assert(firstTrue(d, 3) == -1);
//     assert(positionOfMax(d, 3) == 0);
//
//     string e[] = {"not empty", "not empty", ""};
//     assert(allTrue(e, 3) == false);
//     assert(countTrue(e, 3) == 1);
//     assert(firstTrue(e, 3) == 2);
//     assert(positionOfMax(e, 3) == 0);
//
//     string f[] = {"hello", "world", "foo"};
//     assert(allTrue(f, 3) == false);
//     assert(countTrue(f, 3) == 0);
//     assert(firstTrue(f, 3) == -1);
//     assert(positionOfMax(f, 3) == 1);
//
//     string g[] = {"hello", "", "foo", ""};
//     assert(allTrue(g, 4) == false);
//     assert(countTrue(g, 4) == 2);
//     assert(firstTrue(g, 4) == 1);
//     assert(positionOfMax(g, 4) == 0);
//
//     string h[] = {"hello"};
//     assert(allTrue(h, 1) == false);
//     assert(countTrue(h, 1) == 0);
//     assert(firstTrue(h, 1) == -1);
//     assert(positionOfMax(h, 1) == 0);
//
//     string i[] = {"", "abc", "def"};
//     assert(allTrue(i, 3) == false);
//     assert(countTrue(i, 3) == 1);
//     assert(firstTrue(i, 3) == 0);
//     assert(positionOfMax(i, 3) == 2);
//
//     string j[] = {"abc", "def", "ghi"};
//     assert(allTrue(j, 3) == false);
//     assert(countTrue(j, 3) == 0);
//     assert(firstTrue(j, 3) == -1);
//     assert(positionOfMax(j, 3) == 2);
//
//     string k[] = {"", "abc", "def", "ghi", "jkl"};
//     assert(allTrue(k, 5) == false);
//     assert(countTrue(k, 5) == 1);
//     assert(firstTrue(k, 5) == 0);
//     assert(positionOfMax(k, 5) == 4);
//
//     string l[] = {"abc", "def", "ghi", "jkl", "mno"};
//     assert(allTrue(l, 5) == false);
//     assert(countTrue(l, 5) == 0);
//     assert(firstTrue(l, 5) == -1);
//     assert(positionOfMax(l, 5) == 4);
//
//     string m[] = {"abc", "def", "", "ghi", "jkl"};
//     assert(allTrue(m, 5) == false);
//     assert(countTrue(m, 5) == 1);
//     assert(firstTrue(m, 5) == 2);
//     assert(positionOfMax(m, 5) == 4);
//
//     string o[] = {"abc", "def", "ghi", "jkl", ""};
//     assert(allTrue(o, 5) == false);
//     assert(countTrue(o, 5) == 1);
//     assert(firstTrue(o, 5) == 4);
//     assert(positionOfMax(o, 5) == 3);
//
//     string p[] = {"apple", "banana", "carrot", "date", "eggplant"};
//     assert(allTrue(p, 5) == false);
//     assert(countTrue(p, 5) == 0);
//     assert(firstTrue(p, 5) == -1);
//     assert(positionOfMax(p, 5) == 4);
//
//     string q[] = {"watermelon", "tomato", "strawberry", "orange", "banana"};
//     assert(allTrue(q, 5) == false);
//     assert(countTrue(q, 5) == 0);
//     assert(firstTrue(q, 5) == -1);
//     assert(positionOfMax(q, 5) == 0);
//
//     string r[] = {"apple", "apple", "zebra", "carrot", "date"};
//     assert(allTrue(r, 5) == false);
//     assert(countTrue(r, 5) == 0);
//     assert(firstTrue(r, 5) == -1);
//     assert(positionOfMax(r, 5) == 2);
//
//     string s[] = {"john", "sonia", "elena", "ketanji", "sonia", "elena", "samuel"};
//
//     string s2[] = {"sonia", "ketanji", "samuel"};
//     assert(contains(s, 7, s2, 3) == true);
//
//     string s3[] = {"sonia", "elena", "elena"};
//     assert(contains(s, 7, s3, 3) == true);
//
//     string s4[] = {"sonia", "samuel", "ketanji"};
//     assert(contains(s, 7, s4, 3) == false);
//
//     string s5[] = {"john", "ketanji", "ketanji"};
//     assert(contains(s, 7, s4, 3) == false);
//
//     string t1[] = {"apple", "banana", "cherry", "date", "elderberry"};
//     string t2[] = {};
//     assert(contains(t1, 5, t2, 0) == true);
//
//     string u1[] = {"apple", "banana", "cherry", "date", "elderberry"};
//     string u2[] = {"banana", "cherry", "date", "elderberry", "fig"};
//     assert(contains(u1, 5, u2, 5) == false);
//
//     string v1[] = {"apple", "banana", "cherry", "date", "elderberry"};
//     string v2[] = {"banana", "cherry", "date"};
//     assert(contains(v1, 5, v2, 3) == true);
//
//     string w1[] = {"apple", "banana", "cherry", "date", "elderberry"};
//     string w2[] = {"apple", "cherry", "elderberry"};
//     assert(contains(w1, 5, w2, 3) == true);
//
//     string x1[] = {"apple", "banana", "cherry", "date", "elderberry", "cherry", "fig", "banana"};
//     string x2[] = {"banana", "cherry", "date", "cherry"};
//     assert(contains(x1, 8, x2, 4) == true);
//
//     cout << "Passed all tests!" << endl;
//
//     return 0;
//}
