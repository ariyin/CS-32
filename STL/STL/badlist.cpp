//
//  badlist.cpp
//  STL
//
//  Created by Jenna Wang on 5/20/23.
//

// Implement the removeBad function; you must use list's erase member function; you must not use lists's remove or remove_if member functions. Each Restaurant in the list must have its number of stars (the value of its m_stars member) examined no more than once.

//#include <list>
//#include <vector>
//#include <algorithm>
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//vector<int> destroyedOnes;
//
//class Restaurant
//{
//  public:
//    Restaurant(int s) : m_stars(s) {}
//    ~Restaurant() { destroyedOnes.push_back(m_stars); }
//    int stars() const { return m_stars; }
//  private:
//    int m_stars;
//};

  // Remove the restaurants in li with 2 or fewer stars and destroy them.
  // It is acceptable if the order of the remaining restaurants is not
  // the same as in the original list.
void removeBad(list<Restaurant*>& li)
{
    list<Restaurant*>::iterator it = li.begin();
    
    while(it != li.end())
    {
        if((*it)->stars() <= 2)
        {
            // erase the current element and move iterator to the next element
            delete *it;
            it = li.erase(it);
        }
        
        else
        {
            it++;
        }
    }
}

//void test()
//{
//    int a[8] = { 4, 3, 2, 4, 1, 1, 5, 2 };
//    list<Restaurant*> x;
//    for (int k = 0; k < 8; k++)
//        x.push_back(new Restaurant(a[k]));
//    assert(x.size() == 8 && x.front()->stars() == 4 && x.back()->stars() == 2);
//    removeBad(x);
//    assert(x.size() == 4 && destroyedOnes.size() == 4);
//    vector<int> v;
//    for (list<Restaurant*>::iterator p = x.begin(); p != x.end(); p++)
//    {
//        Restaurant* rp = *p;
//        v.push_back(rp->stars());
//    }
//      // Aside:  Since C++11, the above loop could be
//      //     for (auto p = x.begin(); p != x.end(); p++)
//      //     {
//      //         Restaurant* rp = *p;
//      //         v.push_back(rp->stars());
//      //     }
//      // or
//      //     for (auto p = x.begin(); p != x.end(); p++)
//      //     {
//      //         auto rp = *p;
//      //         v.push_back(rp->stars());
//      //     }
//      // or
//      //     for (Restaurant* rp : x)
//      //         v.push_back(rp->stars());
//      // or
//      //     for (auto rp : x)
//      //         v.push_back(rp->stars());
//    sort(v.begin(), v.end());
//    int expect[4] = { 3, 4, 4, 5 };
//    for (int k = 0; k < 4; k++)
//        assert(v[k] == expect[k]);
//    sort(destroyedOnes.begin(), destroyedOnes.end());
//    int expectGone[4] = { 1, 1, 2, 2 };
//    for (int k = 0; k < 4; k++)
//        assert(destroyedOnes[k] == expectGone[k]);
//    for (list<Restaurant*>::iterator p = x.begin(); p != x.end(); p++)
//        delete *p;
//}
//
//int main()
//{
//    test();
//    cout << "Passed" << endl;
//}
//
