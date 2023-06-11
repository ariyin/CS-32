// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <functional>
#include <algorithm>
using namespace std;

void removeNonLetters(string& s);

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets) : m_hashTable(maxBuckets) {}
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    vector<list<string>> m_hashTable;
    int hashFunction(string& word) const;
};

// takes an input and produces a fixed-size numerical value called a hash value
int DictionaryImpl::hashFunction(string& word) const
{
    sort(word.begin(), word.end());
    return static_cast<int>(std::hash<string>{}(word));
}

// adds a word to the dictionary
void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);

    if(!word.empty())
    {
        string wordCopy = word;
        int bucketIndex = hashFunction(wordCopy) % m_hashTable.size();
        m_hashTable[bucketIndex].push_back(word);
    }
}

// takes a string and a callback function, and for every word in the dictionary that is an anagram of the letters in the string, it calls the callback function with that word as an argument
void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if(callback == nullptr)
    {
        return;
    }

    removeNonLetters(letters);
    
    if(letters.empty())
    {
        return;
    }
    
    // hashFunction sorts letters
    int bucketIndex = hashFunction(letters) % m_hashTable.size();
    
    // get the linked list at the bucket index
    const list<string>& bucket = m_hashTable[bucketIndex];

    for(const string& word : bucket)
    {
        string sortedWord = word;
        sort(sortedWord.begin(), sortedWord.end());
        
        // if sorted words are the same
        if(letters == sortedWord)
        {
            callback(word);
        }
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}

// oceanography --> 0.0001 ms and 0.0013 ms
// i got 0.004 on xcode, 0.02 on g32, 0.0007 on g32 fast
