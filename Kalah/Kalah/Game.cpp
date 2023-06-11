//
//  Game.cpp
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Side.h"
#include <iostream>
#include <string>

using namespace std;

// Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north)
    : m_board(b), m_southPlayer(south), m_northPlayer(north), m_activePlayer(m_southPlayer), m_activeSide(SOUTH)
{
    
}

// Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
void Game::display() const
{
    int nameMiddle = static_cast<int>(m_northPlayer->name().length() / 2);
    int totalSpace = (m_board.holes() * 3) + 4;
    int spaceMiddle = totalSpace / 2;
    int start = spaceMiddle - nameMiddle > 0 ? spaceMiddle - nameMiddle : 0;
    
    // north player's name
    for(int i = 0; i < start; i++)
    {
        cout << " ";
    }
    
    cout << m_northPlayer->name() << endl;
    
    // north holes
    cout << "   ";
    int countSpaces = 1;
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << m_board.beans(NORTH, i) << "  ";
        countSpaces += 3;
    }
    cout << endl;
    
    // north pot
    cout << " " << m_board.beans(NORTH, 0);
    
    // south pot
    for(int k = 0; k < countSpaces - 1; k++)
    {
        cout << " ";
    }
    
    cout << m_board.beans(SOUTH, 0) << endl;
    
    // south holes
    cout << "   ";
    for (int i = 1; i <= m_board.holes(); i++)
    {
        cout << m_board.beans(SOUTH, i) << "  ";
    }
    
    cout << endl;
    
    // south player's name
    nameMiddle = static_cast<int>(m_southPlayer->name().length() / 2);
    spaceMiddle = totalSpace / 2;
    start = spaceMiddle - nameMiddle > 0 ? spaceMiddle - nameMiddle : 0;
    
    for(int i = 0; i < start; i++)
    {
        cout << " ";
    }
    
    cout << m_southPlayer->name() << endl;
    
    cout << endl;
}

// If the game is over (i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false and do not change anything else. If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    if(m_board.beansInPlay(NORTH) > 0 || m_board.beansInPlay(SOUTH) > 0)
    {
        over = false;
    }
    
    else
    {
        over = true;
        
        if(beans(NORTH, 0) > beans(SOUTH, 0))
        {
            hasWinner = true;
            winner = NORTH;
        }
        
        else if(beans(SOUTH, 0) > beans(NORTH, 0))
        {
            hasWinner = true;
            winner = SOUTH;
        }
        
        else if(beans(NORTH, 0) == beans(SOUTH, 0))
        {
            hasWinner = false;
        }
    }
}

// Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. Whenever the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening. If the move can be completed, return true; if not, because the move is not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false.
bool Game::move(Side s)
{
    // side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that opponent's pot and return false
    if(m_board.beansInPlay(NORTH) == 0)
    {
        cout << "No more beans on " << m_northPlayer->name() << "'s side." << endl;
        cout << "Sweeping the remaining beans on " << m_southPlayer->name() << "'s side." << endl << endl;
        
        for(int i = 1; i <= m_board.holes(); i++)
        {
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
        
        display();
        return false;
    }
        
    if(m_board.beansInPlay(SOUTH) == 0)
    {
        cout << "No more beans on " << m_southPlayer->name() << "'s side." << endl;
        cout << "Sweeping the remaining beans on " << m_northPlayer->name() << "'s side." << endl << endl;
        
        for(int i = 1; i <= m_board.holes(); i++)
        {
            m_board.moveToPot(NORTH, i, NORTH);
        }
        
        display();
        return false;
    }
    
    int hole = 0;
    
    cout << m_activePlayer->name() << "'s turn:" << endl;

    hole = m_activePlayer->chooseMove(m_board, m_activeSide);
    
    if(!m_activePlayer->isInteractive())
    {
        cout << m_activePlayer->name() << " chooses hole " << hole << "." << endl << endl;
    }
    
    int endHole;
    Side endSide;

    // sow the seeds from a hole
    m_board.sow(s, hole, endSide, endHole);
    display();

    // take any additional turns required
//    if((s == NORTH && endSide == NORTH && endHole == 0) || (s == SOUTH && endSide == SOUTH && endHole == 0))
    if(s == m_activeSide && endSide == m_activeSide && endHole == 0)
    {
//        if(!m_activePlayer->isInteractive())
//        {
//            cout << "Press enter to continue." << endl;
//            cin.ignore(10000, '\n');
//        }
        
        return move(s);
    }
    
    // or complete a capture
    // if the last bean was placed in one of the player's own holes that was empty just a moment before, and if the opponent's hole directly opposite from that hole is not empty, then that last bean and all beans in the opponent's hole directly opposite from that hole are put into the player's pot, and the turn ends
    if(s == NORTH && m_board.beans(s, endHole) == 1 && m_board.beans(SOUTH, endHole) != 0 && endSide == s)
    {
        int capturedBeans = m_board.beans(NORTH, endHole) + m_board.beans(SOUTH, endHole);
        m_board.moveToPot(NORTH, endHole, NORTH);
        m_board.moveToPot(SOUTH, endHole, NORTH);
        cout << m_northPlayer->name() << " captured " << capturedBeans << " beans." << endl << endl;
        display();
    }
    
    if(s == SOUTH && m_board.beans(s, endHole) == 1 && m_board.beans(NORTH, endHole) != 0 && endSide == s)
    {
        int capturedBeans = m_board.beans(NORTH, endHole) + m_board.beans(SOUTH, endHole);
        m_board.moveToPot(NORTH, endHole, SOUTH);
        m_board.moveToPot(SOUTH, endHole, SOUTH);
        cout << m_southPlayer->name() << " captured " << capturedBeans << " beans." << endl << endl;
        display();
    }
    
    m_activePlayer = m_activePlayer == m_northPlayer ? m_southPlayer : m_northPlayer;
    m_activeSide = m_activeSide == NORTH ? SOUTH : NORTH;
    
    return true;
}

// Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
void Game::play()
{
    cout << "Start:" << endl << endl;
    display();
    
    bool canMove = true, over, hasWinner;
    Side winner;

    while(canMove)
    {
        if(!m_activePlayer->isInteractive())
        {
            cout << "Press enter to continue." << endl;
            cin.ignore(10000, '\n');
        }
        
        canMove = move(m_activeSide);
    }
    
    status(over, hasWinner, winner);
    
    if(over)
    {
        if(hasWinner)
        {
            if(winner == 0)
            {
                cout << m_northPlayer->name() << " is the winner." << endl;
            }
            
            else
            {
                cout << m_southPlayer->name() << " is the winner." << endl;
            }
        }
        
        else
        {
            cout << "The game ended in a draw." << endl;
        }
    }
}

// Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
