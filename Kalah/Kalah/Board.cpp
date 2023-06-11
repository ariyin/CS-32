//
//  Board.cpp
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#include "Board.h"
#include "Side.h"
#include <iostream>
using namespace std;

// Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
Board::Board(int nHoles, int nInitialBeansPerHole)
{
    // nHoles: number of holes per side
    if(nHoles < 0)
    {
        nHoles = 1;
    }
    
    m_sideHoles = nHoles;
    m_totalHoles = nHoles * 2;
    
    if(nInitialBeansPerHole < 0)
    {
        nInitialBeansPerHole = 0;
    }
    
    m_totalBeans = m_totalHoles * nInitialBeansPerHole;
    
    for(int i = 0; i < m_sideHoles; i++)
    {
        m_north.push_back(nInitialBeansPerHole);
        m_south.push_back(nInitialBeansPerHole);
    }
    
    m_northPot = 0;
    m_southPot = 0;
}

// Return the number of holes on a side (not counting the pot).
int Board::holes() const
{
    return m_sideHoles;
}

// Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
    int beans = -1;
    
    if(hole >= 0 && hole <= m_sideHoles)
    {
        if(s == NORTH)
        {
            if(hole == 0)
            {
                beans = m_northPot;
            }
            
            else
            {
                beans = m_north.at(hole - 1);
            }
        }
        
        if(s == SOUTH)
        {
            if(hole == 0)
            {
                beans = m_southPot;
            }
            
            else
            {
                beans = m_south.at(hole - 1);
            }
        }
    }
    
    return beans;
}

// Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
    int total = 0;
    
    if(s == NORTH)
    {
        for(int i = 0; i < m_sideHoles; i++)
        {
            total += m_north.at(i);
        }
    }
    
    else if(s == SOUTH)
    {
        for(int i = 0; i < m_sideHoles; i++)
        {
            total += m_south.at(i);
        }
    }
    
    return total;
}

// Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
    return m_totalBeans;
}

// If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    // invalid cases
    if(s == NORTH && (hole <= 0 || hole > m_sideHoles || m_north.at(hole - 1) == 0))
    {
        return false;
    }
    
    if(s == SOUTH && (hole <= 0 || hole > m_sideHoles || m_south.at(hole - 1) == 0))
    {
        return false;
    }
    
    bool inPot = false;
    
    // sow beans
    if(s == NORTH)
    {
        // beans are removed from hole
        int currentBeans = m_north.at(hole - 1);
        m_north.at(hole - 1) = 0;
        
        Side currentSide = NORTH;
        int currentHole = hole - 1;
        
        // sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot
        while(currentBeans != 0)
        {
            // about to go to the south side
            if(currentSide == NORTH && currentHole == 0)
            {
                m_northPot++;
                currentBeans--;
                
                if(currentBeans != 0)
                {
                    currentHole++;
                    currentSide = SOUTH;
                }
                
                else
                {
                    inPot = true;
                }
            }
            
            // about to go to the north side
            else if(currentSide == SOUTH && currentHole == m_sideHoles + 1)
            {
                currentSide = NORTH;
                currentHole--;
            }
            
            // normal cases
            // go to next hole and drop 1 bean
            
            else
            {
                if(currentSide == NORTH)
                {
                    m_north.at(currentHole - 1)++;
                    currentHole--;
                    currentBeans--;
                }
                
                if(currentSide == SOUTH)
                {
                    m_south.at(currentHole - 1)++;
                    currentHole++;
                    currentBeans--;
                }
            }
        
//            display();
        }
        
        // sets endsSide and endHole to the side and hole where the last bean was placed
        endSide = currentSide;
        
        if(inPot)
        {
            endHole = currentHole;
        }
        
        else if(currentSide == NORTH)
        {
            endHole = currentHole + 1;
        }
        
        else if(currentSide == SOUTH)
        {
            endHole = currentHole - 1;
        }
    }
    
    else if(s == SOUTH)
    {
        // beans are removed from hole
        int currentBeans = m_south.at(hole - 1);
        m_south.at(hole - 1) = 0;
        
        Side currentSide = SOUTH;
        int currentHole = hole + 1;
        
        // sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot
        while(currentBeans != 0)
        {
            // about to go to the south side
            if(currentSide == NORTH && currentHole == 0)
            {
                currentSide = SOUTH;
                currentHole++;
            }
            
            // about to go to the north side
            else if(currentSide == SOUTH && currentHole == m_sideHoles + 1)
            {
                m_southPot++;
                currentBeans--;
                
                if(currentBeans != 0)
                {
                    currentHole--;
                    currentSide = NORTH; // CHANGES
                }
                
                else
                {
                    inPot = true;
                }
            }
            
            // normal cases
            // go to next hole and drop 1 bean
            
            else
            {
                if(currentSide == NORTH)
                {
                    m_north.at(currentHole - 1)++;
                    currentHole--;
                    currentBeans--;
                }
                
                if(currentSide == SOUTH)
                {
                    m_south.at(currentHole - 1)++;
                    currentHole++;
                    currentBeans--;
                }
            }
        
//            display();
        }
        
        // sets endsSide and endHole to the side and hole where the last bean was placed
        endSide = currentSide;

        if(inPot)
        {
            endHole = 0;
        }
        
        else if(currentSide == NORTH)
        {
            endHole = currentHole + 1;
        }
        
        else if(currentSide == SOUTH)
        {
            endHole = currentHole - 1;
        }
    }
    
    return true;
}

// If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    // invalid cases
    if(hole <= 0 || hole > m_sideHoles)
    {
        return false;
    }

    // move all the beans in hole into the pot belonging to potOwner
    if(s == NORTH)
    {
        if(potOwner == NORTH)
        {
            m_northPot += m_north.at(hole - 1);
        }
        
        if(potOwner == SOUTH)
        {
            m_southPot += m_north.at(hole - 1);
        }
        
        m_north.at(hole - 1) = 0;
    }
    
    if(s == SOUTH)
    {
        if(potOwner == NORTH)
        {
            m_northPot += m_south.at(hole - 1);
        }
        
        if(potOwner == SOUTH)
        {
            m_southPot += m_south.at(hole - 1);
        }
        
        m_south.at(hole - 1) = 0;
    }
    
    return true;
}

// If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
    // invalid cases
    if(hole < 0 || hole > m_sideHoles)
    {
        return false;
    }
    
    if(hole != 0 && s == NORTH && m_north.at(hole - 1) < 0)
    {
        return false;
    }
    
    if(hole != 0 && s == SOUTH && m_south.at(hole - 1) < 0)
    {
        return false;
    }
    
    // valid cases
    // set the number of beans to the value of beans
    if(s == NORTH)
    {
        if(hole == 0)
        {
            m_northPot = beans;
        }
        
        else
        {
            int originalBeans = m_north.at(hole - 1);
            m_north.at(hole - 1) = beans;
            m_totalBeans -= (originalBeans - beans);
        }
    }
    
    if(s == SOUTH)
    {
        if(hole == 0)
        {
            m_southPot = beans;
        }
        
        else
        {
            int originalBeans = m_south.at(hole - 1);
            m_south.at(hole - 1) = beans;
            m_totalBeans -= (originalBeans - beans);
        }
    }
    
    return true;
}

//void Board::display() const
//{
//    // north holes
//    cout << "   ";
//    int countSpaces = 1;
//    for (int i = 0; i < m_sideHoles; i++)
//    {
//        cout << m_north.at(i) << "  ";
//        countSpaces += 3;
//    }
//    cout << endl;
//    
//    // north pot
//    cout << " " << m_northPot;
//    
//    // south pot
//    int k = 0;
//    while (k < countSpaces)
//    {
//        cout << " ";
//        k++;
//    }
//    cout << m_southPot << endl;
//    
//    // south holes
//    cout << "   ";
//    for (int i = 0; i < m_sideHoles; i++)
//    {
//        cout << m_south.at(i) << "  ";
//    }
//    
//    cout << endl;
//    cout << endl;
//}
