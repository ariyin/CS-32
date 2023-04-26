//
//  History.cpp
//  BadBunny
//
//  Created by Jenna Wang on 4/6/23.
//

#include "History.h"
#include <iostream>
#include <cstdlib>
using namespace std;

History::History(int nRows, int nCols)
    : m_rows(nRows), m_cols(nCols)
{
    for (int r = 0; r < m_rows; r++)
    {
        for(int c = 0; c < m_cols; c++)
        {
            m_grid[r][c] = '.';
        }
    }
}

// The record function is to be called to notify the History object that a rabbit has started its turn poisoned but alive at a grid point. The function returns false if row r, column c is not within the bounds specified by the History constructor; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as an Arena (e.g., row 1, column 1 is the upper-left-most position).
bool History::record(int r, int c)
{
    // return false if [r,c] is not within the bounds specified by the History constructor
    if(r < 1 || r > m_rows || c < 1 || c > m_cols)
    {
        return false;
    }
    
    // return true after recording what it needs to
    // . = 0, A = 1, B = 2, ..., Z = 26+
    else
    {
        if(m_grid[r-1][c-1] == '.')
        {
            m_grid[r-1][c-1] = 'A';
        }
        
        else if(m_grid[r-1][c-1] < 'Z')
        {
            m_grid[r-1][c-1]++;
        }
        
        return true;
    
    }
}

// The display function clears the screen and displays the history grid as the posted programs do. This function does clear the screen, display the history grid, and write an empty line after the history grid; it does not print the Press enter to continue. after the display (That should be done somewhere else in the program). (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
void History::display() const
{
    // clear the screen
    clearScreen();
    
    // display the history grid
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    
    // write an empty line after the history grid (NO "press enter to continue")
    cout << endl;
}
