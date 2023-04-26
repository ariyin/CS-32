//
//  Sequence.cpp
//  DoubleTime
//
//  Created by Jenna Wang on 4/19/23.
//

#include "Sequence.h"
#include <iostream>

Sequence::Sequence()
    : head(nullptr), tail(nullptr), length(0)
{
    
}

// When a Sequence is destroyed, the nodes in the linked list must be deallocated.
Sequence::~Sequence()
{
    // start at the head
    Node *current = head;
    
    // keep going until the pointer points to a nullptr
    while(current != nullptr)
    {
        // create a pointer to the current node
        Node *temp = current;
        
        // current node moves to the next node
        current = current->next;
        
        // delete the temp (previously current) node
        delete temp;
    }
    
    // reset variables
    head = nullptr;
    tail = nullptr;
    length = 0;
}

// When a brand new Sequence is created as a copy of an existing Sequence, enough new nodes must be allocated to hold a duplicate of the original list.
Sequence::Sequence(const Sequence& other)
{
    // initialize member variables
    head = nullptr;
    tail = nullptr;
    length = 0;
    
    // iterate through the original list
    Node* current = other.head;
    while (current != nullptr)
    {
        // create a new node for each node in the original list
        Node* newNode = new Node;
        
        // if first node
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
            
            // set previous and next pointers to nullptr
            newNode->prev = nullptr;
            newNode->next = nullptr;
        }
        
        else
        {
            // update previous and next pointers of the new node
            newNode->prev = tail;
            newNode->next = nullptr;
            
            // set previous node's next to this node
            tail->next = newNode;
            
            // update tail to the new node
            tail = newNode;
        }
        
        // copy data from the original node to the new node
        newNode->value = current->value;
              
        // move to the next node in the original list
        current = current->next;
        
        // increase length
        length++;
   }
}

// When an existing Sequence (the left-hand side) is assigned the value of another Sequence (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
Sequence& Sequence::operator = (const Sequence &rhs)
{
    // if they're not equal
    if (this != &rhs)
    {
        // create a temp sequence with what you want to copy
        Sequence temp(rhs);
        
        // swap the current sequence with the temp sequence
        swap(temp);
    }
    
    // return the current sequence
    return *this;
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const
{
    return (length == 0);
}

// Return the number of items in the sequence.
int Sequence::size() const
{
    return length;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one greater than they were at before.
// Return pos if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return -1.  Notice that
// if pos is equal to size(), the value is inserted at the end.
int Sequence::insert(int pos, const ItemType& value)
{
    // return -1 if out of bounds
    if (pos < 0 || pos > size())
    {
        return -1;
    }
    
    // create a new node with the passed in value
    Node* newNode = new Node;
    newNode->value = value;
    
    // front
    if (pos == 0)
    {
        // assign next to the current head and prev to a nullptr
        newNode->next = head;
        newNode->prev = nullptr;
        
        // if not an empty list
        if (head != nullptr)
        {
            // assign this node's prev to the new node
            head->prev = newNode;
        }
        
        // assign the head to the new node
        head = newNode;
        
        // if an empty list
        if (tail == nullptr)
        {
            // assign the tail to the new node
            tail = newNode;
        }
    }
    
    // back
    else if (pos == size())
    {
        // assign next to a nullptr and prev to the current tail
        newNode->next = nullptr;
        newNode->prev = tail;
        
        // if not an empty list
        if (tail != nullptr)
        {
            // assign the current tail's next to the new node
            tail->next = newNode;
        }
        
        // assign tail to the new node
        tail = newNode;
        
        // if an empty list
        if (head == nullptr)
        {
            // assign head to the new node
            head = newNode;
        }
    }
    
    // middle
    else
    {
        Node* current = head;
        
        // loop through the list until current is the node at the desired position
        for (int i = 0; i < pos; i++)
        {
            current = current->next;
        }
        
        // don't need to check for nullptrs, because it's in the middle
        // assign all the pointers
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    
    // increase the length
    length++;
    
    return pos;
}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item in position
// p.  The original item in position p and those that follow it end
// up at positions one greater than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).
int Sequence::insert(const ItemType& value)
{
    // create a new node with the passed in value
    Node* newNode = new Node;
    newNode->value = value;
    
    int p = 0;
    Node* current = head;
    
    // iterate until p is found; p = size at end
    // current = pointer at node @ p + 1
    while (current != nullptr && value > current->value)
    {
        p++;
        current = current->next;
    }
    
    // front
    if (p == 0)
    {
        newNode->next = head;
        newNode->prev = nullptr;
        
        // if not an empty list
        if (head != nullptr)
        {
            head->prev = newNode;
        }
        
        head = newNode;
        
        // if an empty list
        if (tail == nullptr)
        {
            tail = newNode;
        }
    }
    
    // back
    else if (p == size())
    {
        newNode->next = nullptr;
        newNode->prev = tail;
        
        // if not an empty list
        if (tail != nullptr)
        {
            tail->next = newNode;
        }
        
        tail = newNode;
        
        // if an empty list
        if (head == nullptr)
        {
            head = newNode;
        }
    }
    
    // middle
    else
    {
        // don't need to check for nullptrs, because it's in the middle
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    
    length++;
    
    return p;
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= size())
    {
        return false;
    }
    
    int i = 0;
    Node* current = head;
    
    // iterate until current is the pointer at pos
    while (current != nullptr && i < pos)
    {
        current = current->next;
        i++;
    }
    
    // remove head
    if (pos == 0)
    {
        // if not a single item
        if (current->next != nullptr)
        {

            head = current->next;
            head->prev = nullptr;
        }
        
        // if a single item
        else
        {
            head = nullptr;
            tail = nullptr;
        }

        delete current;
    }
    
    // remove tail
    else if (pos == size() - 1)
    {
        // if not a single item
        if (current->prev != nullptr)
        {
            tail = current->prev;
            tail->next = nullptr;
        }
        
        // if a single item
        else
        {
            head = nullptr;
            tail = nullptr;
        }
        
        delete current;
    }
    
    // middle
    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        
        delete current;
    }
    
    length--;
    
    return true;
}
 
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value)
{
    int num = 0;
    Node* current = head;
    Node* next = nullptr;

    for (int i = 0; current != nullptr; i++)
    {
        // store the next node before deleting
        next = current->next;
        
        if (current->value == value)
        {
            erase(i);
            num++;
            i--;
        }

        // update current to the next node
        current = next;
    }

    return num;
}

// If 0 <= pos < size(), copy into value the item in position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const
{
    // return false if out of bounds
    if (pos < 0 || pos >= size())
    {
        return false;
    }
    
    Node* current = head;
    
    // iterate through the entire list until current is at pos
    for (int i = 0; i < pos; i++)
    {
        current = current->next;
    }
    
    // set value with current->value
    value = current->value;
    
    return true;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value)
{
    // return false if out of bounds
    if (pos < 0 || pos >= size())
    {
        return false;
    }
    
    Node* current = head;
    
    // iterate through the entire list until current is at pos
    for (int i = 0; i < pos; i++)
    {
        current = current->next;
    }
    
    // set current->value with value
    current->value = value;
    
    return true;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const
{
    int p = 0;
    Node* current = head;
    
    // iterate through entire list
    while (current != nullptr)
    {
        // if values equal
        if (value == current->value)
        {
            // return position
            return p;
        }
        
        p++;
        current = current->next;
    }
    
    return -1;
}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other)
{
    // swap head
    Node* tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    // swap tail
    Node* tempTail = tail;
    tail = other.tail;
    other.tail = tempTail;
    
    // swap length
    int tempLength = length;
    length = other.length;
    other.length = tempLength;
}

void Sequence::dump() const
{
    // display the sequence
    for(Node* p = head; p != nullptr; p = p->next)
    {
        std::cerr << p->value << " ";
    }
    
    std::cerr << std::endl;
}


// Consider all the items in seq2; let's call them seq20, seq21, ..., seq2n. If there exists at least one k such that seq1k == seq20 and seq1k+1 == seq21 and ... and seq1k+n == seq2n, and k+n < seq1.size(), then this function returns the smallest such k. (In other words, if seq2 is a consecutive subsequence of seq1, the function returns the earliest place in seq1 where that subsequence starts.) If no such k exists or if seq2 is empty, the function returns -1. For example, if seq1 were a sequence of ints consisting of 30 21 63 42 17 63 17 29 8 3 and seq2 consists of 63 17 29 then the function returns 5, since the consecutive items 63 17 29 appear in seq1 starting with the 63 at position 5. (The result is not 2, because while there's a 63 at position 2, followed eventually by a 17 and a 29, those items are not consecutive in seq1.) With the same seq1, if seq2 consists of 17 63 29 then the function returns -1.
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // SHOULD BE: seq1 > seq2
    if (seq1.size() < seq2.size() || seq1.empty() || seq2.empty())
    {
        return -1;
    }
    
    int pos;
    ItemType value, seq2Start;
    seq2.get(0, seq2Start);
    
    // loop through seq1
    for (int i = 0; i < seq1.size(); i++)
    {
        seq1.get(i, value);
        
        // if seq1 value = start of seq2, place a marker
        if (value == seq2Start)
        {
            pos = i;
            
            bool isEqual = true;
            
            // loop through length of seq2
            for (int j = 0; j < seq2.size(); j++)
            {
                // check each value are equal
                ItemType seq1Value, seq2Value;
                seq1.get(pos + j, seq1Value);
                seq2.get(j, seq2Value);
                
                if(seq1Value != seq2Value)
                {
                    isEqual = false;
                }
            }
            
            // if each value are equal, return the position marker
            if (isEqual)
            {
                return pos;
            }
            
        }
    }
    
    return -1;
}

// This function produces as a result a sequence that consists of the items in seq1 in reverse order of their occurrence in seq1 followed by the items in seq2 in reverse order of their occurrence in seq2.
// More formally: Consider the items in seq1; let's call them seq10, seq11, …, seq1m, and let's call the items seq2 contains seq20, seq21, …, seq2n. When this function returns, result must consist of the sequence seq1m, seq1m-1, …, seq11, seq10, seq2n, seq2n-1, …, seq21, seq20, and no other items.
// If seq1 is empty, then when this function returns, result must consist of the sequence seq2n, …, seq20, and no other items. If seq2 is empty, then when this function returns, result must consist of the sequence seq1m, …, seq10, and no other items. If seq1 and seq2 are empty, then when this function returns, result must be empty.
// When this function returns, result must not contain any items that this spec does not require it to contain. (You must not assume result is empty when it is passed in to this function; it might not be.)
// As an example, if seq1 were a sequence of chars consisting of p a r and seq2 consists of r o t then no matter what value it had before, result ends up consisting of: r a p t o r
// Be sure that in the face of aliasing, these functions behave as this spec requires: Does your implementation work correctly if seq1 and result refer to the same Sequence, for example?
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    int resultPos = 0;
    
    Sequence resultCopy = result;
    
    // clear result
    while (!resultCopy.empty())
    {
        resultCopy.erase(0);
    }
    
    // flip seq1
    for (int i = seq1.size() - 1; i >= 0; i--)
    {
        ItemType value;
        seq1.get(i, value);
        
        // add value to result
        resultCopy.insert(resultPos, value);
        resultPos++;
    }
    
    // flip seq2
    for (int j = seq2.size() - 1; j >= 0; j--)
    {
        ItemType value;
        seq2.get(j, value);
        
        // add value to result
        resultCopy.insert(resultPos, value);
        resultPos++;
    }
    
    result = resultCopy;
}
