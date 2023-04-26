//
//  newSequence.h
//  Sequence
//
//  Created by Jenna Wang on 4/16/23.
//

#ifndef newSequence_h
#define newSequence_h

//#include <string>
//using ItemType = std::string;
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 160;

class Sequence
{
  public:
    Sequence();
    Sequence(int size);
    ~Sequence();
    Sequence(const Sequence& other); // copy constructor
    Sequence& operator = (const Sequence &src); // assignment operator
    
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
//    void dump() const;
    
  private:
    ItemType* array;
    int itemSize;
    int maxSize;
};

#endif /* newSequence_h */
