#include <iostream>
using namespace std;

typedef int Time;

// class Icon
// {
//     public:
//         Icon()
//         {
//             cout << "I ";
//         }
//         ~Icon()
//         {
//             cout << "~I";
//         }
// };

// class File
// {
//     public:
//         File()
//         {
//             cout << "F ";
//         }
//         ~File()
//         {
//             cout << "~F ";
//         }
//     private:
//         Icon m_icons[2];
// };

// class Rectangle
// {
//     public:
//         Rectangle()
//         {
//             cout << "R ";
//         }
//         ~Rectangle()
//         {
//             cout << "~R ";
//         }
// };

// class Caption
// {
//     public:
//         Caption()
//         {
//             cout << "C ";
//         }
//         ~Caption()
//         {
//             cout << "~C ";
//         }
// };

// class Picture : public File
// {
//     public:
//         Picture()
//         {
//             cout << "P ";
//         }
//         ~Picture()
//         {
//             cout << "~P ";
//         }
//     private:
//         Caption m_caption;
//         Rectangle* m_boundary;
// };

// int main()
// {
//     Picture p;
// }

// class Circle
// {
//     public:
//         Circle(Picture* pp, double x, double y, double r)
//             : m_picture(pp), m_x(x), m_y(y), m_radius(r)
//             {

//             }
//         void setPicture(Picture* pp)
//         {
//             m_picture = pp;
//         }
//         double centerX() const
//         {
//             return m_x;
//         }
//         double centerY() const
//         {
//             return m_y;
//         }
//         double centerR() const
//         {
//             return m_radius;
//         }
//     private:
//         Picture* m_picture;
//         double m_x;
//         double m_y;
//         double m_radius;
// };

// class Picture
// {
//     public:
//         Picture()
//             : m_nCircles(0)
//             {

//             }
//     private:
//         Circle* m_Circles[100];
//         int m_nCircles;
// };

// Picture::~Picture()
// {
//     for(int i = 0; i <m_nCircles; i++)
//     {
//         delete m_Circles[i];
//     }
//     delete [] m_Circles;
// }

// Picture::Picture(const Picture& other)
//     : m_nCircles(other.m_nCircles)
// {
//     Circle* m_Circles[100];
//     for(int i = 0; i < m_nCircles; i++)
//     {
//         m_Circles[i] = new Circle(this, other.m_Circles[i]->centerX(), other.m_Circles[i]->centerY(), other.m_Circles[i]->centerR());
//         m_Circles[i]->setPicture(this);
//     }
// }


class Hillary
{
    public:
        Hillary() { cout << "H "; }
        ~Hillary() { cout << "~H "; }
};

class Bernie
{
    public:
        Bernie(int i) { cout << "B "; m_id = i; }
        virtual ~Bernie() { cout << "~B "; }
        int id() const { return m_id; }
        void marco() const { cout << m_id << " "; }
        virtual void ted() const { cout << (m_id+2) << " "; }
        // virtual void ted() const = 0;
        virtual void incr() { m_id++; }
    private:
        int m_id;
        Hillary m_john[2];
};

class Donald : public Bernie
{
    public:
        Donald(int i) : Bernie(i) { cout << "D "; }
        ~Donald() { cout << "~D "; }
        void marco() const { cout << (id() + 3) << " "; }
        virtual void ted() const { cout << (id() + 4) << " "; }
    private:
        Hillary m_ben;
};

void process(Bernie* bp)
{
    bp->ted();
    bp->marco();
    delete bp;
}

class AlarmClock
{
    public:
        AlarmClock(Time current) {m_time = current;}
        virtual void setAlarm(Time alarm) {m_alarm = alarm;} // change
        void tick() {
            cout << "tick\n";
            if(++m_time == m_alarm) playAlarm();
        }
        virtual void playAlarm() {cout << "Buzz! Buzz!\n";} // change
    private:
        Time m_time;
        Time m_alarm;
};

class CuckooClock : public AlarmClock{
    public:
        CuckooClock(Time t) : AlarmClock(t) {} //change
        virtual ~CuckooClock() {cout << "Squawk!\n";}
        void setAlarm(Time t) {
            AlarmClock::setAlarm(t); // change
            cout << "Chirp!\n";
        }
        void playAlarm() { cout << "Cuckoo! Cuckoo! \n"; }
};

void timePasses(AlarmClock& ac)
{
    ac.setAlarm(503);
    ac.tick();
    ac.tick();
}

class Wallet 
{
    public:
        Wallet(double dollar)
        {
            if(dollar < 0)
            {
                dollar = 0;
            }

            money = dollar;
        }

        bool isEmpty() const { return (money == 0); }
        virtual void deposit(double dollar) 
        {
            if(dollar > 0)
            {
                money += dollar;
            }
        }
        virtual double value() const { return money; }
    private:
        double money;
};

class UKWallet : public Wallet 
{
    public:
        UKWallet(double conversion)
            : Wallet(0)
        {
            if(conversion < 0)
            {
                conversion = 1.65;
            }

            m_conversion = conversion;
        }

        virtual void deposit(double pounds)
        {
            if(pounds < 0)
            {
                pounds = 0;
            }

            double dollar = pounds * m_conversion;
            Wallet::deposit(dollar);
        }

        virtual double value() const 
        {
            return (Wallet::value() * m_conversion);
        }
    
    private:
        double m_conversion;
};

bool equals(Node* p1, Node* p2)
{
    if(p1 == nullptr && p2 == nullptr)
        return true;
    if(p1 == nullptr || p2 == nullptr)
        return false;
    if(p1->value != p2->value)
        return false;
    return equals(p1->next, p2->next)
}

int main()
{
    
}