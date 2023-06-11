# CS 32 Notes

## Resources
- [BruinLearn](https://bruinlearn.ucla.edu/courses/160766)
- [Main Website](http://web.cs.ucla.edu/classes/spring23/cs32/)

## Table of Contents
- [Review](#review)
- [Lecture 1-2](#lecture-1-2)
- [Lecture 3-4](#lecture-3-4)
- [Lecture 5](#lecture-5)
- [Lecture 6](#lecture-6)
- [Lecture 7-8](#lecture-7-8)
- [Lecture 9-11](#lecture-9-11)
- [Lecture 12-15](#lecture-12-15)
- [Lecture 16-17](#lecture-16-17)
- [Lecture 18](#lecture-18)
- [Final Review](#final-review)

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

## Lecture 6

**Recording:**
- [Lecture 6](https://bruinlearn.ucla.edu/courses/160766/pages/6-monday-april-17-lecture-stacks-and-queues?module_item_id=5973609)

**Stack**
- Cafeteria tray analogy
- Use if the only time you're adding/removing from the end
- Limits possibilities, easier to read the program
- In an array, top is the space after the last valid input
- In a linked list, top is the head (do operations at the front)
- Operations:
    - Required:
        - Create an empty stack
        - Push an item onto the stack (insert)
        - Pop an item from the stack (remove)
        - Look at the top item on the stack
    - Optional:
        - Look at any item in the stack
        - How many items are in the stack
- Examples:
    - Solving calculator equations:
        - Push operand onto the stack
        - Pop top two operands off the stack
        - Apply operator
        - Push the result onto the stack
    - Convert infix to postfix:
        - (if) If the current item is an operand, append it to the result sequence
        - (else if) If the current item is (, push it onto the stack
        - (else if) If the current item is ), pop operators off the stack, appending them to the result sequence, until you pop an (, which you do not append to the sequence
        - (else) If the current item is an operator:
            - (if) If the operator stack is empty, push the current operator onto the stack
            - (else if) If the top of the stack is (, push the current operator onto the stack
            - (else if) If the current operator has precendence greater than that of the operator at the top of the stack, push the current operator onto the stack
            - (else) Pop the top operator from the stack and append it to the result sequence
                - Check again
        - At the end of the input sequence, pop each operator off the stack and append it to the result sequence 

```git
#include <stack>
using namespace std;

stack<int> s;
s.push(10); 
s.push(20); // 10 20
cout << s.top() << endl; // 20
s.pop();
if(s.empty())
    cout << "Stack is empty!" << endl;
else
    cout << s.top() << endl; // writes 10
 out << s.size() << endl; // writes 1
```

**Queue**
- Line analogy
- Inserted at one end, removed from the other end
- Head/tail or front/back
- For an array, treat it like a "ring buffer" or "circular array"
    - If head = tail, queue is either empty or full
    - Need a size variable
- Operations:
    - Required:
        - Create an empty queue
        - Enqueue an item (insert)
        - Dequeue an item (remove)
        - Look at the front item in the queue
        - Is the queue empty
    - Optional:
        - Look at the back item in the queue
        - Look at any item in the queue
        - How many items are in the queue

```git
#include <queue>
using namespace std;

queue<int> q;
q.push(10);
q.push(20); // 10 20
cout << q.front() << endl; // 10
q.pop();
if(q.empty())
    cout << "Queue is empty! << endl;
else
    cout << q.front() << endl; // writes 20
cout << q.size() << endl; // writes 1 
cout << q.back() << endl;  // writes 20
```

## Lecture 7-8

**Recording:**
- [Lecture 7](https://bruinlearn.ucla.edu/courses/160766/pages/7-wednesday-april-19-lecture-inheritance?module_item_id=5973606)
- [Lecture 8](https://bruinlearn.ucla.edu/courses/160766/pages/8-monday-april-24-inheritance-and-polymorphism?module_item_id=5973603)

**Inheritance**
- The derived class inherits all the properties of the base class
- Static binding: at compile time; default
- Dynamic binding: at run time; `virtual`
- Never attempt to override a non-virtual function
    - If you want to override or specialize existing functions from the base class in your derived class, you should always insert the `virtual` keyword in front of both the original and replacement functions
    - If you define your member functions outside your class, you must only use the `virtual` keyword within your class definition
        - Ex: `void Student::WhatDoISay()` (no virtual in front even though in the class it would be `virtual void WhatDoISay();`)
- If the base class version is
    - Likely to be overwritten in at least one derived class, then make it virtual
    - Never going to be overwritten in any derived class, you have the option of making it virtual, but you don't have to make it virtual
- If you would like your derived class to be able to reuse one or more private member functions of the base class but you don't want the rest of your program (outside your class) to use them, then make them protected instead of private in the base class
    - This lets your derived class (and its derived classes) reuse the member functions from the base class but still prevents the rest of your program from seeing/using them
- But never make your member variables protected or public
    - If you expose member variables to a derived class, you violate encapsulation
- Your derived class will by default always use the most derived version that it knows of a specialized method
    - Ex: If Student and NerdyStudent both have a cheer() function, and NerdyStudent's getExcitedAboutCS() calls Student::cheer(), the cheer() that gets called is NerdyStudent's cheer
    - If you want to call the base class's version of a method that's been redefined in the derived class, you can do so by using `baseclass::method()` or `Student::cheer()`
- If a superclass requires parameters for construction, then you must add an initializer to the subclass constructor
    - The first item in your initializer list must be the name of the base class, along with parameters in parentheses
    - Ex: Duck() : Animal(2) { m_feathers = 99; }
- What happens if I assign one instance of a derived class to another?
    - It works fine; C++ first copies the base data from y to x, and then copies the derived data from y to x
    - However, if your base and derived classes have dynamically allocated member variables (or would otherwise need a special copy constructor/assignment operator), then you must define assignment operators and copy constructors for the base class and also the special versions of these functions for the derived class
- Shape is an abstract base class (ABC)
    - Cannot create something that is just a shape and nothing more
- If a class has at least one pure virtual function, it's an abstract class
    - An abstract class cannot be instantiated, you cannot create an object that is of just that type
- If you define an abstract base class, its derived class
    - Must either provide code for all pure virtual functions
    - Or the derived class becomes an abstract base class
- If a class is designed to be a base class, declare a destructor for it, and make it virtual
- First step of a constructor: construct the base part
- Last step of a destructor: destroy the base part

**Polymorphism**
- Once you define a function that accepts a reference or pointer to a Person, not only can you pass Person variables to that class, but you can also pass any variable that was derived from a Person
- Any time you use a base pointer or a base reference to access a derived object, that is called polymorphism 
- Only works when you use a reference or a pointer to pass an object
    - Otherwise "chopping happens"
    - C++ will chop off all the data/methods of the derived class and only send the base parts of the variable to the function
- If you pass in a reference/pointer to a method with the base class, the method thinks that every variable you pass in is jus the base class
    - This means that it only knows about the functions found in the base class
    - Functions specific to derived classes are totally invisible to it
- When should you use the virtual keyword?
    - Use the virtual keyword in your base class any time you expect to redefine a function in a derived class
    - Use the virtual keyword in your derived classes any time you redefine a function (for clarity, not required)
    - Always use the virtual keyword for the destructor in your base class (and in your derived classes for clarity)
    - You can't have a virtual constructor, so don't try
        - The constructor is always called at class creation, and there you always know what type the class is, so virtual doesn't make any sense
        - Constructors are class local, so you can't override the constructor of the parent class
- In general, you may point a superclass pointer at a subclassed variable
    - But you may never point a subclass pointer at a superclass variable
    - Like a square is a rectangle but a rectangle is not a square
        - Shape *ptr;
        - ptr = &sq;
        - ptr->getArea();
- You should always make sure that you use virtual destructors when you use inheritance/polymorphism
    - You don't need to make the derived class destructor virtual so long as the destructor in your base class is virtual
    - The derived class's virtual destructor will automatically become virtual if the base destructor is
    - If you forget a virtual destructor, it only causes problems when you use polymorphism
- Cheat sheet
    - You can't access private members of the base class from the derived class
    - Always make sure to add a virtual destructor to your base class
    - Don't forget to use virtual to define methods in your base class, if you expect to redefine them in your derived class(es)
    - To call a base class method that has been redefined in a derived class, use the base:: prefix
    - So long as you define your base version of a function with virtual, all derived versions of the function will automatically be virtual too (even without the virtual keyword)
    - When you use a base pointer to access a derived object
        - And you call a virtual function defined in both the base and the derived classes, your code will call the derived version of the function
        - And you call a non-virtual function defined in both the base and the derived classes, your code will call the base version of the function
        - All function calls to virtual functions will be directed to the derived object's version, even if the function calling the virtual function is not virtual itself

```git
class Shape // base class
{
  public:
    Shape(double x, double y);
    void move(double xnew, double ynew);
    virtual void draw() const = 0; // "pure virtual function"; no general method
    virtual ~Shape();
    double x() const;
    double y() const;
    ...
  private:
    double m_x;
    double m_y;
};

class Circle : public Shape // derived class; a circle is a kind of shape
{
  public:
    Circle(double r, double x, double y);
    virtual void draw() const;
    ...
  private:
    double m_r;
};

class Rectangle : public Shape
{
  public:
    Rectangle(double x, double y, double dx, double dy);
    virtual void draw() const;
    virtual double diag() const;
    ...
  private:
    double m_dx;
    double m_dy;
};

Shape::Shape(double x, double y)
 : m_x(x), m_y(y)
{}

void Shape::move(double xnew, double ynew)
{
    m_x = xnew;
    m_y = ynew;
}

Shape::~Shape()
{}

double Shape::x() const
{
    return m_x;
}

double Shape::y() const
{
    return m_y;
}

Circle::Circle(double r, double x, double y)
 : Shape(x, y), m_r(r) // if not listed, will call default constructor for shape -> if doesn't exist, error
{
    if (r < 0)
        ... error: radius must be non-negative ...
}

void Circle::draw() const
{
  ... draw a circle of radius m_r centered at (x(), y()) ...
}

Rectangle::Rectangle(double x, double y, double dx, double dy)
 : Shape(x, y), m_dx(dx), m_dy(dy)
{}

void Rectangle::draw() const
{
  ... draw a line from (x(), y()) to (x()+m_dx, y()) ...
  ... draw a line from (x()+m_dx, y()) to (x()+m_dx, y()+m_dy) ...
  ... draw a line from (x()+m_dx, y()+m_dy) to (x(), y()+m_dy) ...
  ... draw a line from (x(), y()+m_dy) to (x(), y()) ...
}

double Rectangle::diag() const
{
    return std::sqrt(m_dx*m_dx + m_dy*m_dy);
}
```

```git
class Shape
{
    virtual ~Shape();
    virtual void draw() const = 0;
    ...
};

Shape::~Shape()
{}

class Polygon : public Shape
{
    virtual ~Polygon();
    Node* head;
};
```

## Lecture 9-11
**Recording:**
- [Lecture 9](https://bruinlearn.ucla.edu/courses/160766/pages/9-wednesday-april-26-recursion?module_item_id=5973600)
- [Lecture 10](https://bruinlearn.ucla.edu/courses/160766/pages/10-monday-may-1-recursion-templates-up-to-54-35-is-what-you-need-for-homework-3?module_item_id=5973597)
- [Lecture 11](https://bruinlearn.ucla.edu/courses/160766/pages/11-wednesday-may-3-templates-stl?module_item_id=5973594)

**Recursion**
- Sort a pile of n items:
    - if (n >= 2)
    - Split the pile into two unsorted piles of about n/2 items
    - Sort the left subpile
    - Sort the right subpile
    - Merge the two sorted subpiles into one sorted pile
- Recursive function
    - Base case(s): path(s) through the function that do not make a recursive call
    - Recursive case(s): path(s) through the function that make a recursive call
- Every recursive call is to solve a strictly "smaller" problem ("closer" to base case)
- Recursive functions should never use global, static, or member variables; they should only use local variables and parameters
- Writing recursive functions
    - Write the function header
    - Define your magic function
    - Add your base case code
    - Solve the problem with the magic function
    - Remove the magic
    - Validate your function
- When writing recursive functions with linked lists:
    - Your recursive function should generally only access the current node/array cell passed into it
    - Your recursive function should rarely/never access the value(s) in the node(s)/cell(s) below it

```git
void sort(int a[], int b, int e)
{
    if (e - b >= 2)
    {
        int mid = (b + e) / 2;
        sort(a, b, mid);
        sort(a, mid, e);
        merge(a, b, mid, e);
    }
}
```

```git
bool has(int a[], int n, int target)
{
    if (n <= 0)
        return false;
    if (a[0] == target)
        return true;
    return has(a+1, n-1, target);
}
```

```git
bool solve(start, end)
{
    if (start == end)
        return true;
    mark start as visited
    for each direction
    {
        if (moving in that direction is possible, and that sport has not been visited)
            if (solve(position reached by moving that step, end))
                return true
    }
    return false
}
```

**Templates**

```git
int minimum(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}

double minimum(double a, double b)
{
    if(a < b)
        return a;
    else
        return b;
}

int main()
{
    int k;
    cin >> k;
    cout << minimum(k, 10) / 2;
    double x;
    ...
    double y = 3 * minimum(x*x, x+10);
    ...
    int z = minimum(0, 3*k - k + 4);
    ...
}
```

```git
template<typename T>
T minimum(const T& a, const T& b) // pass by reference for things expensive to copy
{
    if(a < b)
        return a;
    else
        return b;
}
```

- For a successful call to the template function (template argument deduction):
    - The call must match some template
    - The instantiated template must compile
    - The instantiated template must do what you want
- For matching, the only conversions considered for any type A are
    - A -> A&
    - A -> const A
    - Array of A -> A*

```git
template<typename T>
T sum(const T a[], int n)
{
    T total = T(); // double() or string()
    for(int k = 0; k < n; k++>)
        total += a[k];
    return total;
}
```

```git
template<typename T>
class Stack
{
    public:
        Stack();
        void push(const T& x);
        void pop();
        T top() const;
        int size() const;
    private:
        int m_data[100];
        int m_top;
};

template<typename T>
Stack<T>::Stack()
    : m_top(0)
{}

template<typename T>
void Stack<T>::push(const T& x)
{
    m_data[m_top] = ; // undefined if full
    m_top++;
}

template<typename T>
void Stack<T>::pop()
{
    m_top--;
}

template<typename T>
T Stack<T>::top() const
{
    return m_data[m_top-1];
}

template<typename T>
int Stack<T>::size() const
{
    return m_top;
}
```

- Always place your templated functions in a header file
    - You must put the entire template function body in the header file, not just the prototype, or you'll get an error
- Each time you use a template function with a different type of variable, the compiler generates a new version of the function in your program to handle that type of variable
- You must use the template data type to define the type of at least one formal parameter, or you'll get an error
- If a function has two or more "templated parameters," with the same type you must pass in the same type of variable/value for both
- If your templated function uses a comparison operator on templated variables then C++ expects that all variables passed in will have that operator defined
- To make an entire class generic, you must use the prefix `template <typename xxx>` before the class definition itself
    - Then update the appropriate types in your class
    - Ex: void setVal(Item a), Item m_a
- In classes with externally-defined member functions:
    - You add the prefix `template <typename xxx>` before the class definition itself and before each function definition outside the class
    - Update the types to use your templated type
    - Place the postfix `<xxx>` between the clsas name and the :: in all function definitions 
    - Ex: template <typename Item>
    - void Foo<Item>::setVal(Item a)


**STL**
- A collection of pre-written, tested classes provided by the authors of C++
- All built using templates, meaning they can be used with many different data types
- Vector
    - #include <vector>
    - vector<string> strs;
- Lists
    - push_back (add back)
    - pop_back (remove back)
    - push_front (add front)
    - pop_front (remove front)
    - front
    - back
    - size
    - empty
- Vectors vs Lists
    - Since vectors are based on dynamic arrays, they allow fast access to any element (via brackets) but adding new items is often slower
    - The STL list is based on a linked list, so it offers fast insertion/deletion, but slow access to middle elements
- Map
- Set

**Iterators**
- Last half of Lecture 11
- To enumerate the contents of a container, you typically use an iterator variable
- An iterator variable is just like a pointer variable, but it's used just with STL containers
- Typically, you start by pointing an iterator to some item in your container (e.g., the first item)
- Just like a pointer, you can incremenet and decrement an iterator to move it up/down through a container's items
- You can also use the iterator to read/write each value it points to
- To define an iterator variable, write the container type followed by two colons, followed by the word iterator and then a variable name
    - Ex: vector<string>::iterator it;
- To point your iterator at the first item, simply use the container's begin() method
    - it = myVec.begin();
- Once the iterator points at a value, you can use the * operator with it to access the value
    - Operator overloading
    - cout << (*it);
- You can move your iterator down one item by using the ++ operator
    - Same logic for --
- Each container has an end() method, but it doesn't point to the last item; it points just past the last item in the container
    - So if you want to get the last item, you've got to first point it at end() and then decremenet it
- it->beNerdy();
- Sometimes you'll pass a container as a const reference parameter
    - void tickleNerds(const list<string> &nerds)
    - To iterate through such a container, you can't use the regular iterator
    - Use a const iterator: list<string>::const_iterator it;

## Lecture 12-15
**Recordings:**
- [Lecture 12](https://bruinlearn.ucla.edu/courses/160766/pages/12-monday-may-8-stl-algorithm-analysis?module_item_id=5973591)
- [Lecture 13](https://bruinlearn.ucla.edu/courses/160766/pages/13-wednesday-may-10-sorting?module_item_id=5973590)
- [Lecture 14](https://bruinlearn.ucla.edu/courses/160766/pages/14-monday-may-15-sorting-trees?module_item_id=5973587)
- [Lecture 15](https://bruinlearn.ucla.edu/courses/160766/pages/15-wednesday-may-17-trees?module_item_id=5973584)

**Algorithm Analysis**
- The Big-O approach measures an algorithm by the gross number of steps that it requires to process an input of size N in the worst case scenario
- Ignore the coefficients and lower-order terms of the expression
- If a loop doesn't run for a fixed number of iterations, turn them into loops with a fixed number of iterations using their maximum possible iteration count
- A function f(N) is O(g(N)) if there exist N_0 and k such that for all N >= N_0, |f(N)| <= k*g(N)
- f(N) is "order g(N)"
- 2(N^2) + 1000(N) + 1000 is O(N^2)

```git
for(int i = 0; i < N; i++) // N * O(1) -> O(N) 
    c[i] = a[i] * b[i]; // O(1)

for(int i = 0; i < N; i++) // N*O(N) -> O(N^2)
{ // O(1) + O(N) -> O(1+N) -> O(N)
    a[i] *= 2; // O(1)
    for(int j = 0; j < N; j++) // O(N)
        d[i][j] = a[i] * c[j]; // O(1)
}

for(int i = 0; i < N; i++) // N*O(1) -> O(N)
{ // O(1)
    a[i] *= 2; // O(1)
    for(int j = 0; j < 100; j++) // 100*O(1) -> O(100) -> O(1)
        d[i][j] = a[i] * c[j]; // O(1)
}

for(int i = 0; i < N; i++) //  O(0+1+2+3+...+(N-1)) -> O(N^2)
{ // O(i)
    a[i] *= 2; // O(1)
    for(int j = 0; j < i; j++) // i*O(1) = O(i)
        d[i][j] = a[i] * c[j]; // O(1)
}

0+1+2+3+...+(N-1)*N/2 = (.5N^2 - .5N) = O(N^2)

for(int i = 0; i < N; i++) // O(N^2)
{ // O(N)
    if(find(a, a+N, 10*i) != a+N) // O(N)
        count++; // O(1)
}

for(int i = 0; i < N; i++) // O(N^2 log N)
{ // O(N log N)
    a[i] *= 2; // O(1)
    for(int j = 0; j < N; j++) // O(N log N)
        d[i][j] = f(a, N); // O(log N)
}

Suppose f(a, N) takes O(log N) time

for(int i = 0; i < R; i++) // O(RC log C)
{ // O(C log C)
    a[i] *= 2; // O(1)
    for(int j = 0; j < C; j++) / O(C log C)
        ...g(... C ...)...; // O(log C)
}

Suppose g(... X ...) takes O(log X) time
```

**Sorting**
- Selection Sort
    - Look at all N books, select the shortest book
    - Swap this with the first book
    - Look at the remaining N-1 books, and select the shortest
    - Swap this book with the second book
    - Look at the remaining N-2 books, and select the shortest
    - Swap this book with the third book and so on...
    - O(N^2)
    - Takes just as many steps either way
- An "unstable" sorting algorithm re-orders the items without taking into account the initial ordering
- A "stable" sorting algorithm does take into account the initial ordering when sorting, maintaining the order of similar-valued items
- Insertion Sort
    - Focus on the first two books
    - If the last book in this set is in the wrong order
        - Remove it from the shelf
        - Shift the book before it to the right
        - Insert our book into the proper slot
    - Focus on the first three books
    - If the last book in this set is in the wrong order
        - Remove it from the shelf
        - Shift the books before it to the right, as necessary
        - Insert our book into the proper slot
    - Etc
    - O(N^2)
    - If all books are in the proper order, it just takes roughly ~N steps to sort the array O(N)
- Bubble Sort
    - Start at the top element of your array
    - Compare the first two elements: A[0] and A[1]
        - If they're out of order, then swap them
    - Then advance one element in your array
    - Compare these two elements: A[1] and A[2]
        - If they're out of order, swap them
    - Repeat until you hit the end of the array
    - When you hit the end of the array, if you made at least one swap on your way down, then start back at the top and repeat the whole process again
    - O(N^2)
- Quicksort and mergesort are efficient "divide and conquer" sorting algorithms
    - Divide the elements to be sorted into two gropus of roughly equal size
    - Sort each of these smaller groups of elements using recursion
    - Combine the two sorted groups into one large sorted group
    - Usually require O(N*log2(N)) steps
- Quicksort
    - If the array contains only 0 or 1 element, return
    - Select an arbitrary element P from the array (typically the first element in the array)
    - Move all elements that are less than or equal to P to the left of the array and all elements greater than it to the right (partitioning)
    - Recursively repeat this process on the left sub-array and then the right sub-array
    - If the array is already sorted or mostly sorted or in reverse order, quicksort becomes very slow
- Mergesort
    - The basic merge algorithm takes two presorted arrays as inputs and outputs a combined, third sorted array
    - If array has one element, then return
    - Split up the array into two equal sections
    - Recursively call mergesort function on the left half
    - Recursively call mergesort function on the right half
    - Merge the two halves using our merge function
    - Works equally well regardless of the ordering of the data

**Trees**
- Trees are made of nodes
- Every tree has a "root" pointer
- The top node of a tree is called its "root" node
- Every node may have zero or more "children" nodes
- A node with 0 children is called a "leaf" node
- A tree with no nodes is called an "empty tree"
- Binary trees
    - In a binary tree every node has at most two children nodes: a left child and a right child
```git
struct BTNODE
{
    string value;
    BTNODE *pLeft, *pRight;
}
```
- When we iterate through all the nodes in a tree, it's called a traversal
- Any time we traverse through a tree, we always start with the root node
- Each technique differs in the order that each node is visited during the traversal:
    - Pre-order traversal
        - Process the current node
        - Recursively call PreOrder on the left sub-tree
        - Recursively call PreOrder on the right sub-tree
    - In-order traversal
        - Recursively process nodes in the left sub-tree
        - Process the current node
        - Recursively process nodes in the right sub-tree
    - Post-order traversal
        - Recursively process nodes in the left sub-tree
        - Recursively process nodes in the right sub-tree
        - Process the current node
    - Level-order traversal
        - Visit each level's nodes, from left to right, before visiting nodes in the next level
        - Use a temp pointer variable and a queue of node pointers
        - Insert the root node pointer into the queue
        - While the queue is not empty:
            - Dequeue the top node pointer and put it in temp
            - Process the node
            - Add the node's children to queue if they are not null

## Lecture 16-17
**Recording:**
- [Lecture 16](https://bruinlearn.ucla.edu/courses/160766/pages/16-monday-may-22-hash-tables?module_item_id=5973581)
- [Lecture 17](https://bruinlearn.ucla.edu/courses/160766/pages/17-wednesday-may-24-hash-tables?module_item_id=5973578)

**Hash Tables**
- Load factor = # of items / # of buckets
- Always expect collisions
    - A collision is a condition where two or more values both map into the same bucket in the array
    - This causes ambiguity because we can't tell what value was actually stored in the array
- Hash function takes a key and produces an integer for you
- O(N)

```git
#include <functional>
using namespace std;

string s = "hello";
unsigned int x = std::hash<string>()(s) % numberOfBuckets;
```

```git
#include <map>

map<string, double> ious;

string name;
double amt;
while(cin >> name >> amt)
    ious[name] += amt;
for(map<string, double>::iterator p = ious.begin(); p != ious.end(); p++)
    cout << p->first << " owes me $" << p->second << endl; 
```
- % Rule: When you divide by a given value N, all of your remainders are guaranteed to be between 0 and N-1
- How can we write a mapFunc that converts a large ID# into a bucket # that falls within our 100,000 element array?
```git
int mapFunc(int idNum)
{
    const int ARRAY_SIZE = 100000;

    int bucket = idNum % ARRAY_SIZE;
    return bucket;
}
```
- Closed hash table with linear probing
    - If the target bucket is empty, we can store our value there
    - However, instead of storing true in the bucket, we store our full original value
    - If the bucket is occupied, we scan down from that bucket until we hit the first empty bucket and put the new value there
    - If you run into a collision on the last bucket, wrap back around the top to slot zero
    - To search the hash table, compute a target bucket number with our mapping function
        - We then look in that bucket for our value
        - If we don't find our value, probe linearly down the array until we either find our value or hit an empty bucket
        - If while probing you run into an empty bucket, it means your value isn't in the array
        - If you go past the end of the array, wrap around back to slot zero and continue searching
    - Only use this method when you don't intend to delete items from your hash table (dictionary)
- Open hash table
    - Instead of storing our values directly in the array, each array bucket points to a linked list of values
    - To search for an item:
        - Compute a bucket # with your mapping function: `bucket = mapFunc(idNum);`
        - Search the linked list at array[bucket] for your item
        - If we reach the end of the list without finding our item, it's not in the table
    - Good if you plan to repeatedly insert and delete values into the hash table
- Open hash tables are almost always more efficient than closed hash tables
- Choosing a hash function:
    - The hash function must always give us the same output value for a given input value
    - The hash function should disperse items throughout the hash array as randomly as possible
    - When coming up with a new hash function, always measure how well it disperses items

```git
struct BUCKET
{
    int idNum;
    bool used;
} 
```

## Lecture 18
**Recording:**
- [Lecture 18](https://bruinlearn.ucla.edu/courses/160766/pages/18-wednesday-may-31-heaps?module_item_id=5973575)

**Heaps**
- A complete binary tree is a binary tree that is completely filled at every level, except possibly the deepest level, which is filled from left to right
- A (max) heap is a complete binary tree in which the value at every node is greater than the values of all the nodes in its subtrees
- A min heap is a complete binary tree in which the value at every node is less than the values of all the nodes in its subtrees
- Insert into a heap:
    - Add the item as the bottom rightmost one, producing a complete binary tree
    - Bubble up the item to its proper place
- Remove from a heap:
    - The root value is the item removed
    - Promote the bottom rightmost item to be the root, producing a complete binary tree
    - Trickle that value down to its proper place
- Inserting and extracting from a heap is O(log2(n))
- In an array:
    - Node is heap[i]
    - Parent is heap[(i-1)/2]
- Heapsort:
    - Given an array of N numbers that we want to sort:
    - Convert our input array into a maxheap
        - Create a tree
        - Start at the last node (bottom-most, right-most node), move to the root node
            - Swap the "root" value down with it's larger child until it's bigger than both of its children (or it hits a leaf) 
    - While there are numbers left in the heap:
        - Remove the biggest value from the heap
        - Place it in the last open slot of the array
    - Time complexity: O(NlogN)

## Final Review
- Converting infix to postfix: (nice doing output horizontally, stack vertically)
    1. Create an empty stack and an empty output string.
    2. Start scanning the infix expression from left to right.
    3. If the scanned character is an operand, append it to the output string.
    4. If the scanned character is an operator, then:
        - If the stack is empty, push the operator onto the stack.
        - If the operator has higher precedence than the top of the stack, push the operator onto the stack.
        - If the operator has equal precedence with the top of the stack, pop the top of the stack and append it to the output string. Then push the incoming operator onto the stack.
        - If the operator has lower precedence than the top of the stack, pop the top of the stack and append it to the output string. Then repeat step 4 with the incoming operator.
    5. If the scanned character is an opening parenthesis '(', push it onto the stack.
    6. If the scanned character is a closing parenthesis ')', then:
        - Pop operators from the stack and append them to the output string until an opening parenthesis '(' is encountered.
        - Pop and discard the opening parenthesis '('.
    7. Repeat steps 3 to 6 until all characters are scanned.
    8. Pop any remaining operators from the stack and append them to the output string.
    9. The output string is the postfix expression.
- Converting postfix to infix: (nice working vertically)
    1. Start reading the postfix expression from left to right.
    2. Initialize an empty stack to store the intermediate results.
    3. For each character in the postfix expression:
        - If the character is an operand (a number or variable), push it onto the stack.
        - If the character is an operator (+, -, *, /, etc.), pop the top two operands from the stack.
        - Construct an infix expression by placing the operator between the two operands in the order of "operand1 operator operand2".
        - Push the newly constructed infix expression back onto the stack.
    4. Repeat steps 3 for all characters in the postfix expression until you reach the end.
    5. At the end, the stack will contain the final infix expression.
- Converting infix to prefix:
    1. Start reading the infix expression from right to left.
    2. Same steps as converting infix to postfix.
    3. Finally, reverse the output to obtain the prefix expression.
- Converting prefix to infix: 
    1. Scan the prefix expression from right to left.
    2. Same steps as converting postfix to infix
- Evaluate a prefix expression:
    1. Start scanning the expression from right to left.
    2. If the current token is an operand (a number), push it onto the stack.
    3. If the current token is an operator (+, -, *, /), pop the top two operands from the stack.
    4. Apply the operator to the two operands.
    5. Push the result of the operation back onto the stack.
    6. Repeat steps 2-5 until all tokens in the expression are processed.
    7. The final result will be the value left on the stack.  
- Tree traversals:
    - Preorder: root, left, right
    - Postorder: left, right, root
    - Inorder: left, root, right
- To find the pivots in a quicksort algorithm, see if at a certain index the other items to the left and right are in the right place (less than or greater than); order does not matter as long as the items are on the right side
- Sort using heapsort:
    - Create a tree 
    - Delete the largest item (at the root of the tree)
        - Follow the deletion rules (swap with the bottom rightmost item, trickle down)
    - Move the item to the back of the array
    - Promote the next largest item to be the root
    - Reconfigure the tree (make sure it's still a max heap)
    - Repeat
- Binary tree balancing: 
```git
bool isLeaf(Node* node)
{
    return (node->left == nullptr && node->right == nullptr);
}

int calculateWeight(Node* root)
{
    if (root == nullptr)
        return 0;

    if (isLeaf(root))
        return root->weight;

    return calculateWeight(root->left) + calculateWeight(root->right);
}

bool isInBalance(Node* root)
{
    if (root == nullptr)
        return true;

    int leftWeight = calculateWeight(root->left);
    int rightWeight = calculateWeight(root->right);

    return (leftWeight == rightWeight) && isInBalance(root->left) && isInBalance(root->right);
}
```
- Hash table reallocation:
```git
void HashTable::setNumberOfBuckets(unsigned int newNumberOfBuckets)
{
    list<string>* newBuckets = new list<string>[newNumberOfBuckets];

    for (unsigned int i = 0; i < m_numberOfBuckets; i++) {
        for (const string& str : m_buckets[i]) {
            size_t newBucketIndex = hashFunction(str) % newNumberOfBuckets;
            newBuckets[newBucketIndex].push_back(str);
        }
    }

    delete[] m_buckets;

    m_numberOfBuckets = newNumberOfBuckets;
    m_buckets = newBuckets;
}
```
- In general, hash_map has better time efficiency, but if you need something to be sorted, BST_map is better
- e1: B, e2: E, e3: A
- When deleting a node in BST, and the node's children has multiple children (granchildren), choose either the rightmost node of the left branch of the leftmost node of the right branch
- Time complexity practice:
    - Note: A pair<T1, T2> is a simple struct with two data members, one of type T1 and one of type T2. A set<K> and a map<K, V> are organized as approximately balanced binary search trees; an unordered_set<K> and an unordered_map<K, V> are organized as hash tables that never allow the load factor to exceed some constant, and a loop that visits every item in a hash table of N items is O(N). For the keys to be hashed, the hash function used produces uniformly distributed results.
    - Suppose UCLA has C courses each of which has on average S students enrolled. For this problem, courses are represented by strings (e.g. "CS 32"), and students by their int UIDs. We will consider a variety of data structures, and for each determine the big-O time complexity of the appropriate way to use that data structure to determine whether a particular student s is enrolled in course c. For example, if the data structure were vector<pair<string, vector<int>>>, where each pair in the outer vector represents a course and all the students in that course, with those students being sorted in order, then if the pairs are in no particular order in the outer vector, the answer would be O(C + log S). (The reason is that we'd have to do a linear search through the outer vector to find the course, which is O(C), and then after that we could do a binary search of the S students in the sorted vector for that course, which is O(log S).) In these problems, we're just looking for the answer; you don't need to write the reason.
    - vector<pair<string, list<int>>>, where each pair in the outer vector represents a course and all the students in that class, with those students being sorted in order. The pairs are in no particular order in the outer vector. What is the big-O complexity to determine whether a particular student s is enrolled in course c?
        - O(C + S). We'd have to do a linear search through the outer vector to find the course, which is O(C), and then after that do a linear search of the S students in the list, which is O(S). We can't do a binary search in a linked list in logarithmic time, because it takes linear time just to get to the middle item of a list, sorted or not.
    - map<string, list<int>>, where the students in each list are in no particular order. What is the big-O complexity to determine whether a particular student s is enrolled in course c?
        - O((log C) + S). A BST-based map finds the course in O(log C) time, and after that we do a linear search of the S students in the list.
    - map<string, set<int>>. What is the big-O complexity to determine whether a particular student s is enrolled in course c?
        - O(log C + log S). A BST-based map finds the course in O(log C) time, and a BST-based set finds the student in O(log S) time. Notice that a mathematically equivalent way to write this is O(log CS), but that form makes it harder to understand why it's right.
    - unordered_map<string, set<int>>. What is the big-O complexity to determine whether a particular student s is enrolled in course c?
        - O(log S). A hash-based map finds the course in O(1) time, and a BST-based set finds the student in O(log S) time. Notice that a constant like 1 is dominated by a function that grows with S, so we write O(log S) instead of O(1 + log S).
    - unordered_map<string, unordered_set<int>>. What is the big-O complexity to determine whether a particular student s is enrolled in course c?
        - O(1). A hash-based map finds the course in O(1) time, and a hash-based set finds the student in O(1) time.
    - Suppose we have the data structure map<string, set<int>> and we wish for a particular course c to write the id numbers of all the students in that course in sorted order. What is the big-O complexity?
        - O((log C) + S). A BST-based map finds the course in O(log C) time, and we can visit all S items in order in a BST-based set in O(S) time.
    - Suppose we have the data structure unordered_map<string, unordered_set<int>> and we wish for a particular course c to write the id numbers of all the students in that course in sorted order (perhaps using an additional container to help with that). What is the big-O complexity?
        - O(S log S). A hash-based map finds the course in O(1) time, and although we can visit all S items in a hash-based set in O(S) time, they'd be in whatever order the hash function caused them to be scattered across the buckets. We have to sort them. It takes O(S) steps to get them into and out of an auxiliary vector, say, and O(S log S) to sort them.
    - Suppose we have the data structure unordered_map<string, set<int>> and we wish for a particular student s to write all the courses that student is enrolled in, in no particular order. What is the big-O complexity?
        - O(C log S). The hash-based map is keyed on the course, not the student, so it's not organized to look up students efficiently. Our only choice is to check every course and see in O(log S) time whether the student is in its set of students. Since we have to do the O(log S) operation for each of the C courses, it's O(C log S).
