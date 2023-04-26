//
//  History.h
//  BadBunny
//
//  Created by Jenna Wang on 4/6/23.
//

#ifndef history_h
#define history_h

#include "globals.h"

class History
{
  public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
  private:
    int m_rows;
    int m_cols;
    char m_grid[MAXROWS][MAXCOLS];
};

#endif // history_h
