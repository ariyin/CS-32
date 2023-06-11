//
//  Board.h
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#ifndef Board_h
#define Board_h

#include "Side.h"
#include <vector>

class Board
{
  public:
    Board(int nHoles, int nInitialBeansPerHole);
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
//    void display() const;
  private:
    int m_totalHoles;
    int m_sideHoles;
    int m_totalBeans;
    int m_northPot;
    int m_southPot;
    std::vector<int> m_north;
    std::vector<int> m_south;
};

#endif /* Board_h */
