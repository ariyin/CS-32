//
//  main.cpp
//  Dictionary
//
//  Created by Jenna Wang on 6/4/23.
//

#include "Dictionary.h"
#include <iostream>

using namespace std;

void outputCallback(string anagram);

int main()
{
    Dictionary dict;
    
    dict.insert("act");
    dict.insert("act");
    dict.insert("cat");

    for (;;)
    {
        cout << "Enter a set of letters: ";
        string letters;
        getline(cin,letters);
        if ( ! cin  ||  letters.empty())
            break;

        cout << "Anagrams of " << letters << ":\n";

        dict.lookup(letters, outputCallback);
        
        cout << endl;
    }
}

void outputCallback(string anagram)
{
    cout << "  " << anagram;
}
