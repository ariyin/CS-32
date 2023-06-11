//
//  list.cpp
//  STL
//
//  Created by Jenna Wang on 5/20/23.
//

//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//class MenuItem
//{
//  public:
//    MenuItem(string nm) : m_name(nm) {}
//    virtual ~MenuItem() {}
//    string name() const { return m_name; }
//    virtual bool add(MenuItem* m) = 0;
//    virtual const vector<MenuItem*>* menuItems() const = 0;
//  private:
//    string m_name;
//};
//
//class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
//{
//  public:
//    PlainMenuItem(string nm) : MenuItem(nm) {}
//    virtual bool add(MenuItem* m) { return false; }
//    virtual const vector<MenuItem*>* menuItems() const { return nullptr; }
//};
//
//class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
//{
//  public:
//    CompoundMenuItem(string nm) : MenuItem(nm) {}
//    virtual ~CompoundMenuItem();
//    virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
//    virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
//  private:
//    vector<MenuItem*> m_menuItems;
//};
//
//CompoundMenuItem::~CompoundMenuItem()
//{
//    for (int k = 0; k < m_menuItems.size(); k++)
//        delete m_menuItems[k];
//}

// You must not use any additional container (such as a stack), and the two-parameter overload of listAll must be recursive. You must not use any global variables or variables declared with the keyword static, and you must not modify any of the code we have already written or add new functions. You may use a loop to traverse the vector; you must not use loops to avoid recursion.
// Hint: use + to concatenate strings,  if you choose to traverse an STL container using some kind of iterator, then if the container is const, you must use a const_iterator:

//void f(const list<int>& c)  // c is const
//{
//    for (list<int>::const_iterator it = c.begin(); it != c.end(); it++)
//        cout << *it << endl;
//}

// We introduced the two-parameter overload of listAll. Why could you not solve this problem given the constraints in part a if we had only a one-parameter listAll, and you had to implement it as the recursive function?

void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if(m == nullptr)
    {
        return;
    }

    string prefix;
    
    if (m->name() == "")
    {
        prefix = "";
    }
    
    else
    {
        prefix = "/";
        path += m->name();
        cout << path << endl;
    }
    
    if (m->menuItems() != nullptr)
    {
        for (auto const &item : *(m->menuItems()))
        {
            listAll(item, path + prefix);
        }
    }
}

// Each call to the one-parameter overload of listAll produces a list, one per line, of the complete path to each menu item in the tree rooted at listAll's argument. A path is a sequence of menu item names separated by "/". There is no "/" before the first name in the path.

//void listAll(const MenuItem* m)  // one-parameter overload
//{
//    if (m != nullptr)
//        listAll(m, "");
//}
//
//int main()
//{
//    CompoundMenuItem* cm0 = new CompoundMenuItem("New");
//    cm0->add(new PlainMenuItem("Window"));
//    CompoundMenuItem* cm1 = new CompoundMenuItem("File");
//    cm1->add(cm0);
//    cm1->add(new PlainMenuItem("Open"));
//    cm1->add(new PlainMenuItem("Exit"));
//    CompoundMenuItem* cm2 = new CompoundMenuItem("Help");
//    cm2->add(new PlainMenuItem("Index"));
//    cm2->add(new PlainMenuItem("About"));
//    CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar
//    cm3->add(cm1);
//    cm3->add(new PlainMenuItem("Refresh"));  // no submenu
//    cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
//    cm3->add(cm2);
//    listAll(cm3);
//    delete cm3;
//
////    File
////    File/New
////    File/New/Window
////    File/Open
////    File/Exit
////    Refresh
////    Under Development
////    Help
////    Help/Index
////    Help/About
//}
//
