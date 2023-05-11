//
//  event.cpp
//  Event
//
//  Created by Jenna Wang on 5/7/23.
//

//#include <iostream>
//#include <string>
//using namespace std;

// if going to be overwritten: virtual
// virtual void draw() const = 0; // "pure virtual function"; no general method -> abstract base class

// data members: private
// member functions: public or private, must be const

// no default constructor
// only constructor must have exactly one parameter of type string
// methods needed: name(), isSport(), need()
class Event
{
  public:
    Event(string name) : m_name(name) {}
    string name() const { return m_name; }
    virtual bool isSport() const { return true; };
    virtual string need() const = 0;
    virtual ~Event() {};
  private:
    string m_name;
};

class BasketballGame : public Event
{
  public:
    BasketballGame(string name) : Event(name) {}
    virtual string need() const { return "hoops"; }
    virtual ~BasketballGame() { cout << "Destroying the " << name() << " basketball game" << endl; }
};

class Concert : public Event
{
  public:
    Concert(string name, string genre) : Event(name), m_genre(genre) {}
    virtual bool isSport() const { return false; }
    virtual string need() const { return "a stage"; }
    virtual ~Concert() { cout << "Destroying the " << name() << " " << m_genre << " concert" << endl; }
  private:
    string m_genre;
};

class HockeyGame : public Event
{
  public:
    HockeyGame(string name) : Event(name) {}
    virtual string need() const { return "ice"; }
    virtual ~HockeyGame() { cout << "Destroying the " << name() << " hockey game" << endl; }
};

//// comment out below when turning in
//void display(const Event* e)
//{
//    cout << e->name() << ": ";
//    if (e->isSport())
//        cout << "(sport) ";
//    cout << "needs " << e->need() << endl;
//}

//int main()
//{
//    Event* events[4];
//    events[0] = new BasketballGame("Lakers vs. Warriors");
//      // Concerts have a name and a genre.
//    events[1] = new Concert("Ricardo Arjona", "Latin pop");
//    events[2] = new Concert("Erykah Badu", "neo soul");
//    events[3] = new HockeyGame("Kings vs. Oilers");
////    events[3] = new Event("Sparks vs. Mercury");
//
//    cout << "Here are the events." << endl;
//    for (int k = 0; k < 4; k++)
//        display(events[k]);
//
//      // Clean up the events before exiting
//    cout << "Cleaning up." << endl;
//    for (int k = 0; k < 4; k++)
//        delete events[k];
//
////    Output:
////    Here are the events.
////    Lakers vs. Warriors: (sport) needs hoops
////    Ricardo Arjona: needs a stage
////    Erykah Badu: needs a stage
////    Kings vs. Oilers: (sport) needs ice
////    Cleaning up.
////    Destroying the Lakers vs. Warriors basketball game
////    Destroying the Ricardo Arjona Latin pop concert
////    Destroying the Erykah Badu neo soul concert
////    Destroying the Kings vs. Oilers hockey game
//}
