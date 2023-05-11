#include <iostream>
using namespace std;

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

class Circle
{
    public:
        Circle(Picture* pp, double x, double y, double r)
            : m_picture(pp), m_x(x), m_y(y), m_radius(r)
            {

            }
        void setPicture(Picture* pp)
        {
            m_picture = pp;
        }
        double centerX() const
        {
            return m_x;
        }
        double centerY() const
        {
            return m_y;
        }
        double centerR() const
        {
            return m_radius;
        }
    private:
        Picture* m_picture;
        double m_x;
        double m_y;
        double m_radius;
};

class Picture
{
    public:
        Picture()
            : m_nCircles(0)
            {

            }
    private:
        Circle* m_Circles[100];
        int m_nCircles;
};

Picture::~Picture()
{
    for(int i = 0; i <m_nCircles; i++)
    {
        delete m_Circles[i];
    }
    delete [] m_Circles;
}

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

int main()
{
    Picture pic;
}