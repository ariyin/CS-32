////
////  hw.cpp
////  STL
////
////  Created by Jenna Wang on 5/22/23.
////
//
//// 1e
//// Explain in a sentence or two what happens during the execution of test case 3 that eventually leads to test case 3 failing.
//
//#include <iostream>
//#include <vector>
//#include <list>
//using namespace std;
//
////const int MAGIC = 11223344;
////
////void test()
////{
////    bool allValid = true;
////
////    vector<int> v1(5, MAGIC);
////    int k = 0;
////    for ( ; k != v1.size(); k++)
////    {
////        if (v1[k] != MAGIC)
////        {
////            cout << "v1[" << k << "] is " << v1[k] << ", not " << MAGIC <<"!" << endl;
////            allValid = false;
////        }
////        if (k == 2)
////        {
////            for (int i = 0; i < 5; i++)
////                v1.push_back(MAGIC);
////        }
////    }
////    if (allValid  &&  k == 10)
////        cout << "Passed test 1" << endl;
////    else
////        cout << "Failed test 1" << endl;
////
////    allValid = true;
////    list<int> l1(5, MAGIC);
////    k = 0;
////    for (list<int>::iterator p = l1.begin(); p != l1.end(); p++, k++)
////    {
////        if (*p != MAGIC)
////        {
////            cout << "Item# " << k << " is " << *p << ", not " << MAGIC <<"!" << endl;
////            allValid = false;
////        }
////        if (k == 2)
////        {
////            for (int i = 0; i < 5; i++)
////                l1.push_back(MAGIC);
////        }
////    }
////    if (allValid  &&  k == 10)
////        cout << "Passed test 2" << endl;
////    else
////        cout << "Failed test 2" << endl;
////
////    // const int MAGIC = 11223344;
////
////    // The given test fails because the loop condition k == 10 is not satisfied. The loop runs until k reaches 10, but in this case, k never reaches 10 because it gets incremented within the loop only when *p != MAGIC.
////
////    // In the given code, the loop condition k == 10 is meant to check if the loop iterated 10 times, but due to the additional elements being added to the vector v2 inside the loop when k == 2, the loop runs for more than 10 iterations.
////
////    // As a result, the condition allValid && k == 10 evaluates to false, and the code prints "Failed test 3".
////
////    // The code prints out those messages because the loop is iterating beyond the original size of the vector and accessing uninitialized elements.
////
////    // Inside the loop, when k == 2, v2.push_back(MAGIC) is called 5 times, which adds 5 more elements to the end of the vector. This causes the vector to resize and allocate new memory to accommodate the additional elements. Since the vector is initially created with 5 elements, the indices 0 to 4 are valid. However, when k becomes 3 and beyond, it goes beyond the original size of the vector, and the elements accessed at those indices are uninitialized.
////
////    // As a result, the values at indices 3 to 19 are uninitialized (they hold garbage values), and when comparing them with MAGIC, they do not match, leading to the output you see.
////
////    allValid = true;
////    vector<int> v2(5, MAGIC); // 11223344, 11223344, 11223344, 11223344, 11223344
////    k = 0;
////    for (vector<int>::iterator p = v2.begin(); p != v2.end(); p++, k++)
////    {
////        if (k >= 20)  // prevent infinite loop
////            break;
////        if (*p != MAGIC)
////        {
////            cout << "Item# " << k << " is " << *p << ", not " << MAGIC <<"!" << endl;
////            allValid = false;
////        }
////        if (k == 2)
////        {
////            for (int i = 0; i < 5; i++)
////                v2.push_back(MAGIC); // add 5 MAGIC elements to the end of the vector
////        }
////    }
////    if (allValid  &&  k == 10) // FAILED
////        cout << "Passed test 3" << endl;
////    else
////        cout << "Failed test 3" << endl;
////}
////
////int main()
////{
////    test();
////}
//
////// 3
////// Explain in a sentence or two why the call to the one-argument form of Sequence<Coord>::insert causes at least one compilation error. (Notice that the call to the one-argument form of Sequence<int>::insert is fine, as is the call to the two-argument form of Sequence<Coord>::insert.) Don't just transcribe a compiler error message; your answer must indicate you understand the ultimate root cause of the problem and why that is connected to the call to Sequence<Coord>::insert.
////
////#include "Sequence.h"  // class template from problem 2
////
////class Coord
////{
////  public:
////    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
////    Coord() : m_r(0), m_c(0) {}
////    double r() const { return m_r; }
////    double c() const { return m_c; }
////  private:
////    double m_r;
////    double m_c;
////};
////
////int main()
////{
////    Sequence<int> si;
////    si.insert(50);               // OK
////    Sequence<Coord> sc;
////    sc.insert(0, Coord(50,20));  // OK
////    sc.insert(Coord(40,10));     // error!
////
////    // invalid operands to binary expression ('const Coord' and 'Coord')
////    // The Sequence class is a template class, which means it can accept different types as its template argument. However, for the insert function to work correctly, the ItemType type should support comparison operators (> in this case) to determine the correct position for insertion.
////
////    // If Coord does not provide the necessary comparison operators, such as operator>, you will encounter a compilation error. To resolve this, you can either provide the necessary comparison operators for the Coord class or use a different type that already supports these operators as the template argument when instantiating the Sequence class.
////
////
////}
//
//// 5
//// a
//// In conducting its investigation of contacts between people involved in international criminal trafficking, an investigatory agency maintains, for N people numbered 0 through N-1, a two-dimensional array of bool hasCommunicatedWith that records which people have been in direct communication with others: hasCommunicatedWith[i][j] is true if and only if person i and person j have been in direct communication. If person i has directly communicated with person k, and person k has directly communicated with person j, we call person k a direct intermediary between person i and person j.
//
//// The agency has an algorithm that, for every pair of people i and j, determines how many direct intermediaries they have between them. Here's the code:
//
//const int N = some value;
//bool hasCommunicatedWith[N][N];
//...
//int numIntermediaries[N][N];
//for (int i = 0; i < N; i++)
//{
//    numIntermediaries[i][i] = -1;  // the concept of intermediary
//                                   // makes no sense in this case
//    for (int j = 0; j < N; j++)
//    {
//        if (i == j)
//            continue;
//        numIntermediaries[i][j] = 0;
//        for (int k = 0; k < N; k++)
//        {
//            if (k == i  ||  k == j)
//                continue;
//            if (hasCommunicatedWith[i][k]  &&  hasCommunicatedWith[k][j])
//                numIntermediaries[i][j]++;
//        }
//    }
//}
//
//// What is the time complexity of this algorithm, in terms of the number of basic operations (e.g., additions, assignments, comparisons) performed: Is it O(N), O(N log N), or what? Why? (Note: In this homework, whenever we ask for the time complexity, we care only about the high order term, so don't give us answers like O(N3+4N2).)
//
//// The time complexity of the given algorithm is O(N^3), where N is the number of people.
//
//// The algorithm consists of three nested loops. The outermost loop iterates N times, the middle loop iterates N times, and the innermost loop iterates N times. This results in a total of N * N * N iterations.
//
//// Within the innermost loop, there are constant-time operations such as assignments, comparisons, and logical operations. Therefore, the number of basic operations performed in each iteration of the innermost loop is considered constant.
//
//// Since the algorithm performs N^3 iterations, and the number of basic operations performed in each iteration is constant, the overall time complexity is O(N^3).
//
//// It's important to note that when determining time complexity, we focus on the dominant term, so lower-order terms and constant factors are ignored. In this case, the cubic term N^3 is the dominant term, hence the time complexity is expressed as O(N^3).
//
//// b
//// The algorithm in part a doesn't take advantage of the symmetry of communication: for every pair of persons i and j, hasCommunicatedWith[i][j] == hasCommunicatedWith[j][i]. One can skip a lot of operations and compute the number of direct intermediaries more quickly with this algorithm:
//
//const int N = some value;
//bool hasCommunicatedWith[N][N];
//...
//int numIntermediaries[N][N];
//for (int i = 0; i < N; i++)
//{
//    numIntermediaries[i][i] = -1;  // the concept of intermediary
//                                   // makes no sense in this case
//    for (int j = 0; j < i; j++)  // loop limit is now i, not N; only loop changed
//    {
//        numIntermediaries[i][j] = 0;
//        for (int k = 0; k < N; k++)
//        {
//            if (k == i  ||  k == j)
//                continue;
//            if (hasCommunicatedWith[i][k]  &&  hasCommunicatedWith[k][j])
//                numIntermediaries[i][j]++;
//        }
//        numIntermediaries[j][i] = numIntermediaries[i][j];
//    }
//}
//
//// What is the time complexity of this algorithm? Why?
//
//// 5a. The time complexity is O(N3) because there are three for loops nested within each other that each run N times.
//
//// 5b. The time complexity is still O(N3) because the maximum value j can have is i which is N, which is the same as the last problem. There are still 3 nested for loops each with maximum value N.
//
//// 6
//// Here again is the non-member concatReverse function for Sequences from Sequence.cpp:
//
//void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
//{
//    Sequence res;
//
//    for (int k = seq1.size() - 1; k >= 0; k--)
//    {
//        ItemType v;
//        seq1.get(k, v);
//        res.insert(res.size(), v);
//    }
//
//    for (int k = seq2.size() - 1; k >= 0; k--)
//    {
//        ItemType v;
//        seq2.get(k, v);
//        res.insert(res.size(), v);
//    }
//
//    result.swap(res);
//}
//
//// Assume that seq1, seq2, and the old value of result each have N elements. In terms of the number of linked list nodes visited during the execution of this function, what is its time complexity? Why?
//
//// Here is an implementation of a related member function. The call s3.concatReverse(s1,s2); sets s3 to the result of concatenating the reverses of s1 and s2. The implementation is
//
//void Sequence::concatReverse(const Sequence& seq1, const Sequence& seq2)
//{
//    Sequence res;
//
//    for (Node* p = seq1.m_head->m_prev; p != seq1.m_head; p = p->m_prev)
//        res.insertBefore(res.m_head, p->m_value);
//    for (Node* p = seq2.m_head->m_prev; p != seq2.m_head; p = p->m_prev)
//        res.insertBefore(res.m_head, p->m_value);
//
//      // Swap *this with res
//    swap(res);
//      // Old value of *this (now in res) is destroyed when function returns.
//}
//
//// Assume that seq1, seq2, and the old value of *this each have about N elements. In terms of the number of linked list nodes visited during the execution of this function, what is its time complexity? Why? Is it the same, better, or worse, than the implementation in part a?
//
//
//// 6a. Interleave calls the function get which calls the helper function nodeAtPos. Call nmin = N because the sequences are the same size, so nmin is just the number of elements in each sequence. nodeatPos runs through it N/2 = N times, so get runs through the list N times. This is then ran through the for loop N times, so the total is O(N2). The second for loop is disregarded because the sequences both have N elements, so O(N2) dominates.
//
//// 6b. The first for loop is O(N). The second for is O(N) but because both sequences have about N elements this N is smaller than the first for loop’s O(N). So the overall time complexity is O(N), which means this is a better implementation than part a because it has a faster time complexity.
//
