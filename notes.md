# CS 32 Notes

## Resources
- [BruinLearn](https://bruinlearn.ucla.edu/courses/160766)
- [Main Website](http://web.cs.ucla.edu/classes/spring23/cs32/)

## Table of Contents
- [Review](#review)
- [Lecture 1-2](#lecture-1-2)
- [Lecture 3-4](#lecture-3-4)

## Review
- `double&& x` -> reference variable
- `static_cast<double>(variable)`
- c string: array of characters than end in \0 (null byte)
    - `char name[10] = "hello"`
    - `strcopy(destination, source)`
    - `strlen(s)`
        - Position of the zero byte
        - Analogous to x.size() for C++ string
- Pointers: a variable that holds a memory address as its value
    - Memory address points to another location in memory where an object/variable is stored
    - Uses:
        - Allow functions to modify variables outside of their own scope
        - Dynamic memory allocation
    - Notations:
        - `double*`: pointer to a double
        - `&x`: generate a pointer to x, address of x
        - `*p`: the object that p points to
    - `nullptr`: not pointing to anything
    - Example:
        - `int* ptr`: declare a pointer variable by putting an asterick symbol before the variable name
            - Holds the memory address of an integer value
        - `int x = 5;`
            - `int* ptr = &x`
            - Assign a memory address to a pointer using &
            - Returns memory address of a variable
            - Assigns memory address of x to ptr
        - `int value = *ptr`
            - Access the value stored at the memory address pointed to by a pointer
            - Assigns value of the x-variable to the value variable by dereferencing the ptr varaible
        - `char* buffer = new char[8]`
            - `memset(buffer, 0, 8)`
                - `memset(pointer, value, size it should fill)`
            - `delete[] buffer`
            - Asking for 8 bytes of memory
            - Returns a pointer to the beginning of the block of memory
            - `memset` fills in 8 bytes of memory in `buffer` with the value 0
    - Always initialize pointers to some other variable's address or to a nullptr immediately when you define them
        - If you use * on a null pointer, your program will crash immediately and you'll find the bug ASAP
    - Arrays and pointers
        - While every array has an address, in C++ you don't use the & operator to get an array's address
        - You simply write the array's name (without brackets)
        ```git
        int main()
        {
            int nums[3] = {10, 20, 30};
            cout << nums; // prints 9242 (memory address)
            int *ptr = nums; // ptr points to the start of the nums array
        }
        ```
    - Summary:
        - Putting an asterick (*) after a type = memory address
            - `int* var` or `int *var`
        - Putting an ampersand (&) in front of a variable name = memory address of that variable
        - Putting an asterick (*) in front of a variable name = accessing the data in the variable (dereferencing)
            - `*var`
- References
```git
int a = 5;
int& ref = a;
ref = 2;    // a = 2
```

```git
int main()
{
    int a = 5;
    Increment(&a); // using pointers
    Increment(a);  // using references
}
```

Using pointers:
```git
void Increment(int* value)
{
    (*value)++;
}
```

Using references:
```git
void Increment(int& value)
{
    value++;
}
```
- Structs
    - `struct name { // variables/code };`
    - Everything is implied to be public if you don't specify
    - Simple collection of data
- Classes
    - Everything is implied to be private if you don't specify
    - Const member function: `int position() const`
        - Promises not to modify the object it's called on
- Destructor
    - Cleanup function
    - `~className();`
    - Local objects defined in a function are destructed when they "go out of scope"
    - Variables defined in a function go out of scope when the function exists
    - Dynamically allocated variables (e.g., allocated using the `new` command) have their destructor run ONLY when `delete` is called, before the memory is actually freed by the OS
    - When you define an array of N items, the destructor is called N times when the array goes away
- Constructor
    - If you declare a constructor, the compiler wll not write a constructor for you
    - If you declare no constructors at all, the compiler writes a default constructor for you
        - The default constructor won't initialize your object's primitive member variables
    - Default constructor: a constructor with no parameters
    - Overloading the constructor: giving more than one constructor for a class
    - A constructor is called N times (once for each array element) when you create an array of size N
    - A constructor is called when you use `new` to dynamically allocate a new variable
    - If a variable is declared in a loop, it is newly constructed during every iteration 
    - The constructor is not called when you just define a pointer variable
- Creating and instantiating objects
    - Stack:
        - `Entity entity("Cherno")` is the same thing as `Entity entity = Entity("Cherno)`
        - Object will destroyed after exiting the scope
    - Heap:
        - `Entity* entity = new Entity("Cherno")`
        - Returns location on the heap where the entity has actually been allocated
- `new`
    - Returns a pointer to the memory that you've allocated
    - If you use `new`, you must use `delete` (at one point)
- Arrow operator
```git
Entity* ptr = &e;

// two ways to call methods
(*ptr).Print();
ptr->Print();
```
- Class composition
    - C++ always constructs member variables first, in the order they're defined in the class
    ```git
    class HungryNerd 
    {
        public:
            HungryNerd() // then C++ runs the other class's constructor
            {
                myBelly.eat();
                myBrain.think;
            }
        private:
            Stomach myBelly; // C++ constructs members first, from top to bottom
            Brain myBrain;
    }
    ```
    - C++ always runs the main/outer object's destructor first
        - Its member variables are still valid when the outer destructor runs
        - That way, the outer destructor (~HungryNerd()) has access to completely valid member variables (myBelly and myBrain) while it runs
        - After the outer class's destructor runs (and has its last meal and thinks its last thought, using valid myBelly and myBrain member variables), then C++ runs the destructors of the member variables in the reverse order they were constructed
        - So first ~HungryNerd() will run, then ~myBrain() will run, and finally ~myBelly() will run

## Lecture 1-2

**Recordings:**
- [Lecture 1](https://bruinlearn.ucla.edu/courses/160766/modules/items/5973623)
- [Lecture 2](https://bruinlearn.ucla.edu/courses/160766/pages/2-wednesday-april-5-lecture?module_item_id=5973620)

```git
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

class Circle
{
    public:
        Circle(double x, double y, double r);
        bool scale(double factor);
        void draw() const; // Will it change the Circle?
        double radius() const;
    private:
        // Class invariant:
        // m_r > 0
        double m_x;
        double m_y;
        double m_r;
};

double area(const Circle& x);

Circle::Circle(double x, double y, double r)
    : m_x(x), m_y(y), m_r(r) // "member initialization list"
{
    if (r <= 0)
    {
        cout << "Cannot create a circle with radius " << r << endl;
        exit(1); // part of cstdlib
    }

    m_x = x; // don't need these if you do it the top way
    m_y = y;
    m_r = r;
}

bool Circle::scale(double factor)
{
    if (factor <= 0)
        return false;
    m_r *= factor;
    return true;
}

void Circle::draw() const
{
    ...draw a cricle centered at (m_x, m_y) with radius m_r...
}

double Circle::radius() const
{
    return m_r;
}

double area(const Circle& x)
{
    const double PI = 4 * atan(1.0);
    return PI * x.radius() * x.radius();
}

int main()
{
    Circle c(8, -3, 3.7);
    c.scale(2);
    c.draw();
    cout << area(c);
    double z;
    cin >> z;
    if (!c.scale(z))
        ... error ...
}
```
- Class invariant (think about the constraints for variables):
    - Do you want circles outside of the screen?
    - How should the coordinate system be set up
    - Can't have negative radius
- Zero is not positive nor negative
- Throw in an exception in constructors if it's fed a value that doesn't work
- Don't make data variables public
    - People could change the values in methods
    - Don't want that because we want to control the invariants
    - Mistakes are bound to happen, even if they only want it public to check the values
    - Inhibits ability to change implementation 
- Don't make a copy of objects that are expensive to copy; make a reference
- Putting `const` in front of `Circle& x` promises the program the Circle won't change
- Putting `const` after `double radius()` promises the program that the function won't make a change to the Circle
    - Putting `const` after a function name promises the program the function won't make a change to the object it's called on

```git
class StickFigure
{
    public:
        StickFigure(double bl, double hd, string nm, double hx, double hy);
        ...
    private:
        string m_name;
        Circle m_head;
        double m_bodyLength;
};

StickFigure::StickFigure(double bl, double hd, string nm, double hx, double hy)
    : m_name(nm), m_head(hx, hy, hd/2), m_bodyLength(bl)
    {
        if (bl <= 0 || hd <= 0)
            ... error ...
    }

sf:
    m_name:
    m_head
        m_x:
        m_y:
        m_r:
    m_bodyLength:

StickFigure sf(6, 4, "Fred", -2, 8);
```

- Order of construction:
    1. N/A (Inheritance)
    2. Construct the data members, consulting the member initialization list
        - If a data member is not listed in the member initialization list:
            - If it's of a builtin type, it's left unitialized 
            - If it's of a class type, that class's default constructor is called
        - If it is listed:
            - The order they're constructed is based on the order they're declared in the class
    3. Execute the body of the constructor
- Order of destruction:
    1. Execute the body of the destructor
    2. Destory each data member:
        - If it's of a builtin type, do nothing
        - If it's of a class type, call that class's destructor for that member
    3. N/A (Inheritance)

**Circle.h**
```git
#include <string>

class Circle
{
    public:
        Circle(double x, double y, double r);
        void blah(std::string s);
        ...
    private:
    ...
};

double area(const Circle& x);
```

**Circle.cpp**
```git
#include "Circle.h"
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

Circle::Circle(...)
    : ...
{
    ...
}

void Circle::blah(string s)
{
    ...
}

double area(const Circle& x)
{
    ...
}
```

**myapp.cpp**
```git
#include "Circle.h"
#include <iostream>
using namespace std;

int main()
{
    Circle c(-8, 3, 3.7);
    cout << area(c);
    ...
}
```

- Generally two files in C++ separated by:
    1. Implementation
    2. Declarations
- Can do `using namespace std` in a file if the file isn't being used by other files (?)
    - OK to use for Circle.cpp but not Circle.h
    - Usually bad convention
- `#include`
    - Own files: double quotes
    - Defined by C++ standard / operating system: angle brackets

## Lecture 3-4

**Recordings:**
- [Lecture 3](https://bruinlearn.ucla.edu/courses/160766/pages/3-additional-lecture-to-watch-before-friday-april-7-include-guards-circular-dependencies-resource-management-first-42-30-will-be-useful-for-project-1?module_item_id=5973619)
- [Lecture 4](https://bruinlearn.ucla.edu/courses/160766/pages/4-monday-april-10-lecture-resource-management?module_item_id=5973616)

For each source file (.cpp) in a project, the compiler produces an object file (.o or .obj) containing 
- The machine language translation of the code for each function
- Storage for global objects (e.g., std::cout)
- A list of global names defined (i.e., implemented) by this object file
 - A list of global names used in this file that need a definition somewhere

The linker  brings all these object files together, along with needed object files that are part of the library, to produce an executable file. Rules:
- Nothing can be defined more than once
- Every need must be satisfied by some definition
- There must be (exactly) one main routine

**Point.h**
```git
#ifndef POINT_INCLUDED  // include guard
#define POINT_INCLUDED

class Point
{
    ...
};

#endif // POINT_INCLUDED
```

**Circle.h**
```git
#ifndef CIRCLE_INCLUDED
#define CIRCLE_INCLUDED

#include "Point.h"

class Circle
{
    ...
    private:
    Point m_center;
    double m_radius;
};

#endif // CIRCLE_INCLUDED
```

**myapp.cpp**
```git
#include "Circle.h"
#include "Point.h"

int main()
{
    Circle c(-2, 5, 10);
    Point p(2, 4);
    ...
}
```

Circular Dependencies 

**Student.h**
```git
#ifndef STUDENT_INCLUDED
#define STUDENT_INCLUDED

class Course;

class Student
{
    ...
    void enroll(Course* cp);
    ...
    Course* m_studyList[10]'
};

#endif // STUDENT_INCLUDED
```

**Course.h**
```git
#ifndef COURSE_INCLUDED
#define COURSE_INCLUDED

class Student;

class Course
{
    ...
    int units() const;
    ...
    Student* m_roster[1000];
};

#endif // COURSE_INCLUDED
```

**myapp.cpp**
```git
#include "Student.h"
#include "Course.h"

void f(Student* s, Course* cp)
{
    s->enroll(cp);
}
```

- Include etiquette:
    - Never include a cpp file in another .cpp or .h file
        - You'll get linker errors
        - Only include .h files within a .cpp file
    - Never put a `using namespace` command in a header file
        - "Namespace Pollution"
        - The .h file is forcing cpp files that include it to use its namespace
    - Never assume that a header file will include some other header file for you
- Incomplete type declaration:
    - `class A;`
-  Break the circular dependency by using an incomplete header declaration
    - If you can get away by not including the header file and simply providing an incomplete type specification, do that
    - Don't need much information if you're using pointers (?)
    - Must include headers if you use methods of the class (?)
    - If the compiler only needs to know the name of the type -> incomplete header declaration
    - If the compiler needs to know details of the type -> `#include` header file
- If the file Foo.h defines the class Foo, when does another file require you to say `#include "Foo.h"` and when can you simply provide the incomplete type declaration `class Foo;`
- You have to `#include` the header file defining a class when:
    - You declare a data member of that class type
    - You declare a container (e.g. an array or a vector) of objects of that class type
    - You create an object of that class type
    - You use a member of that class type
    - Summary: 
        - You define a regular variable of that class's type
        - You use the variable in any way
- If you do none of the above, but you:
    - Use the class to define a parameter to a function
    - Use the class as the return type for a function
    - Use the class to define a pointer or reference variable
    - You don't need to include the class's .h file

```git
class Blah
{
    ...
    void g(Foo f, Foo& fr, Foo* fp);    // just need to say class Foo;
    ...
    Foo* m_fp;
    Foo* m_fpa[10];
    vector<Foo*> m_fpv;

    Foo m_f;    // must #include Foo.h
    Foo m_fa[10];
    vector<Foo> m_fv;
}

void Blah::g(Foo f, Foo& fr, Foo* fp)
{
    Foo f2(10, 20); // must #include Foo.h
    f.gleep();
    fr.gleep();
    fp->gleep();
}
```
- Header guards
    - If your header file is called xyz.h, the add the following lines to the very top of the header file:
        - `#ifndef XYZ_H`
        - `#define XYZ_H`
    - And add the following line to the very end of the header file:
        - `#endif // XYZ_H`
- Preprocessor directives
    - `#define`
        - Define new constants (like pi)
            - `#define PI 3.14159`
        - Define a new constant without specifying a value
            - `#define FOOBAR`
    - `#ifdef`, `#ifndef`, and `#endif`
        - Use the `#ifdef` command to check if a constant has been defined already
            - The compiler only compiles the code between the `#ifdef` and the `#endif` if the constant was defined above the `#ifdef`
            - So if the constant wasn't defined, the `#ifdef` essentially turns into a `/*` and the `#endif` turns into a `*/`, commenting out the whole section of code
        - Use `#ifndef` to check if a constant has not been defined already
            - The compiler only compiles the code between the `#ifndef` and the `#endif` if the constant was not defined above
            - So if the constant was defined, the `#ifndef` essentially turns into a `/*` and the `#endif` turns into a `*/`, commenting out the whole section of code
- Default arguments
    - `void poop(string name, int numberOfWipes = 2)`
    - When you call the function, you can leave out the parameter if you just want the default
    - `poop("Jenna")` will automatically default to passing in 2
    - You can have more than one default parameter if you like and C++ will figure out what to do
        - `void fart(int length = 10, int volume = 50)`
        - But you can't do something like `fart(,30);`
    - If the jth parameter has a default value, then all of the following parameters (j+1 to n) must also have default values
        - Basically: every parameter after a default value parameter must also be a default value parameter
        - `bool burp(int length = 5, int loudness, int pitch)` INVALID
        - `bool burp(int length = 5, int loudness = 12, int pitch)` INVALID
        - `bool burp(int length = 5, int loudness, int pitch = 60)` INVALID
        - `bool burp(int length = 5, int loudness = 5, int pitch = 60)` VALID
        - `bool burp(int length, int loudness = 5, int pitch = 60)` VALID

**Resource Management**

**String.h**
```git
#ifndef STRING_INCLUDED
#define STRING_INCLUDED

class String
{
  public:
    String(const char* value = "");
    String(const String& other);    // copy constructor
    ~String();
    String& operator=(const String& rhs);
    void swap(String& other);
    int size() const;
  private:
    char* m_text;
    int m_size;
};

#endif // STRING_INCLUDED
```

**String.cpp**
```git
#include "String.h"
#include <cstring>
using namespace std;

String::String(const char* value)
{
    if (value == nullptr)
        value = "";
    m_size = strlen(value);
    m_text = new char[m_size+1];
    strcpy(m_text, value);
}

String::String(const String& other)
 : m_size(other.m_size)
{
    m_text = new char[m_size+1];
    strcpy(m_text, other.m_text);
}

String::~String()
{
    delete [] m_text;
}

String& String::operator=(const String& rhs)
{
    if (this != &rhs)
    {
        String temp(rhs);
        swap(temp);
    }
    return *this;
}

void String::swap(String& other)
{
    ... // exchange the m_size and other.m_size ints
    ... // exchange the m_text and other.m_text pointers
}

int String::size() const
{
    return m_size;
}
```
- Copy construction is when we create (construct) a new object by copying the value of an existing object
- The parameter to your copy constructor should be const
    - This is a promise that you won't modify the old variable while constructing your new variable - you're just reading its value
- The parameter to your copy constructor must be a reference
- The type of your parameter must be the same type as the class itself
If you don't define your own copy construct, C++ will provide a default one for you
    - It just copies all of the member variables from the old instance to the new instance
    - "Shallow copy"
    - Two pointers may end up pointing at the same thing
    - Any time an object holds one or more pointer member variables and you make a shallow copy of the object, bad things will happen when you destruct either the original variable or its copy(ies), since that will cause the other variable's pointer to point to invalid data
- Define your own copy constructor:
    - Determine how much memory is allocated by the old variable
    - Allocate the same amount of memory in the new variable
    - Copy the contents of the old variable to the new variable
- Copy constructor is called when:
    - String x(s)
    - String x = s
    - Passing a String by value to a function
    - Returning a value from a function (not a pointer or reference)
- A member function of a class can access private members of any other objects of that type, not just the ones that the this pointer points to

**Delete**
```git
Blah* bp = new Blah;
...
delete bp;
```

```git
Foo* fp = new Foo[100]
...
delete [] fp;
```

- If you allocate a single item with new, then you delete it with the single object form of delete, which has no square brakets
- If you allocate an array of items with new, when you delete it you have to use the delete square bracket form
    - Ex: `int* b = new int[50]` and `delete[] b`
- If you dynamically allocated an array, the only pointer related to that array that's legal to pass to delete square brackets is a pointer to element 0 of the array 
    - You can't allocate a 100 element array, get back a pointer to the beginning of that array, and decide you want to get rid of the last 20 elements
- Assignment operator
    - Change an existing variable's value to another existing variable
    - Automatically called when we use = 
    - If you don't write your own assignment operator function, then when you do an assignment like `bar = foo;`, C++ will "shallow copy" all of the data, byte for byte, to the new variable
    - You must always make the parameter the the assignment oeprator a const reference
        - `const Circ &`
    - The return type of the assignment operator must always be a reference to the class's type (e.g., `Circ &`) and the function must always `return *this`
    - The body of the assignment operator copies over the values from the parameter to the target variable 
    - In general, any time a class has a member variable/pointer to some shared system resource, you'll also need an assignment operator
    - Define your own assignment operator: `ben = ann`
        - Free any memory currently held by the target variable (ben)
        - Determine how much memory is used by the source variable (ann)
        - Allocate the same amount of memory in the target variable
        - Copy the contents of the source variable to the target variable
        - Return a reference to the target variable
    - To fix any aliasing that might occur:
        - The assignment operator function must check to see if a variable is being assigned to itself, and if so, do nothing
- The convention is the assignment operator returns a reference to the kind of thing you're assigning to, and the last statement the assignment operator should execute should be a return of *this
- Aliasing: two or more different ways of talking about the same object
    - Example: two pointers pointing to the same object
    - Two pointers or references to the same type -> aliasing might occur

## Lecture 5

**Recording:**
- [Lecture 5](https://bruinlearn.ucla.edu/courses/160766/pages/5-wednesday-april-12-lecture-linked-lists-not-needed-for-homework-1?module_item_id=5973612)

```git
struct Node
{
    int value;
    Node* next;
};

Node* head;
```

```git
for(Node* p = head; p != nullptr; p = p->next)
{
    cout << p->value << endl;
}
```

```git
Node* p;
for(p = head, p != nullptr && p->value != 18; p = p->next)
    ;

// Single linked lists
// Insert a 54 after the 18 in the list, if present:
if(p != nullptr)
{
    Node* newGuy = new Node; // bc newGuy is a local variable,
    newGuy->value = 54;      // it'll delete itself after the curly braces
    newGuy->next = p->next;
    p->next = newGuy;
}

// Delete the number after the 18 in the list, if present:
if(p != nullptr)
{
    Node* toBeDeleted = p->next;
    p->next = p->next->next; // toBeDeleted->next
    delete toBeDeleted;
}
```
Linked Lists
- Reserves a new memory block for each item as it's added, and links blocks together with pointers
- Cheat sheet:
```git
// never access a node's data until validating its pointer
if (ptr != nullptr)

// to advance ptr to the next node/end of the list
if (ptr != nullptr)
    ptr = ptr->next

// to see if ptr points to the last node in a list
if (ptr != nullptr && ptr->next == nullptr)

// to get to the next node's data
if (ptr != nullptr && ptr->next != nullptr)
    cout << ptr->next->value;

// to get the head node's data
if (head != nullptr)
    cout << head->value;

// to check if a list is empty
if (head == nullptr)
    cout << "List is empty"

// to check if a pointer points to the first in a list
if (ptr == head)
```

Tips for linked lists:
- Draw pictures!
- Whenever you write p->..., make sure:
    - p is not uninitialized (it has previously been given a value)
    - p is not a nullptr
- Set new Nodes first to avoid setting pointers in the wrong order
- Check if your code (insert, remove, examine) works correctly for:
    - Middle
    - Front
    - Back
    - Empty
    - One-element list