//
//  Player.cpp
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#include "Player.h"
#include "Side.h"
#include <string>
#include <iostream>
#include <climits>

using namespace std;

// PLAYER

// Create a Player with the indicated name.
Player::Player(string name)
    : m_name(name)
{
    
}

// Since this class is designed as a base class, it should have a virtual destructor.
Player::~Player()
{
    
}

// Return the name of the player.
string Player::name() const
{
    return m_name;
}
    
// Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
bool Player::isInteractive() const
{
    return false;
}

// BADPLAYER

BadPlayer::BadPlayer(string name)
    : Player(name)
{
    
}

// A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    int hole = 1;
    
    if(s == NORTH)
    {
        while(hole <= b.holes())
        {
            if(b.beans(NORTH, hole) != 0)
            {
                return hole;
            }
            
            hole++;
        }
    }
    
    if(s == SOUTH)
    {
        while(hole <= b.holes())
        {
            if(b.beans(SOUTH, hole) != 0)
            {
                return hole;
            }
            
            hole++;
        }
    }
    
    return -1;
}

// HUMANPLAYER

HumanPlayer::HumanPlayer(string name)
    : Player(name)
{
    
}

bool HumanPlayer::isInteractive() const
{
    return true;
}

// A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(NORTH) == 0 || b.beansInPlay(SOUTH) == 0)
    {
        return -1;
    }
    
    int hole;
    
    cout << "Select a move: ";
    cin >> hole;
    cin.ignore();
    cout << endl;
    
    while(hole <= 0 || hole > b.holes() || b.beans(s, hole) == 0)
    {
        if(hole <= 0 || hole > b.holes())
        {
            cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        }
        
        if(b.beans(s, hole) == 0)
        {
            cout << "There are no beans in that hole." << endl;
        }
        
        cout << "Select a move: ";
        cin >> hole;
        cin.ignore();
    }
    
    return hole;
}

// SMARTPLAYER

SmartPlayer::SmartPlayer(std::string name)
    : Player(name)
{
    
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    int bestHole = -1, value, depth = 1;
    double timeLimit = 4990;  // 4.99 seconds; allow 10 ms for wrapping up
    JumpyTimer timer(1000);
    chooseMove(b, s, s, bestHole, value, depth, timeLimit, timer);
//    cout << timer.actualElapsed() << " ms" << endl;
    return bestHole;
}

// return the best move through bestHole
void SmartPlayer::chooseMove(const Board& b, Side s, Side og, int& bestHole, int& value, int depth, double timeLimit, JumpyTimer& timer) const
{
    Board original = b;
    Board copy = b;

    // if no move for player exists (i.e., game is over),
    if(copy.beansInPlay(s) == 0)
    {
        return;
    }

    // if the criterion says we should not search below this node
    if(timer.actualElapsed() >= timeLimit || depth > 8) // 
    {
        return;
    }

    value = INT_MIN;
    bool uninitialized = true;

    // for every hole h the player can choose
    for(int i = 1; i <= original.holes(); i++)
    {
        if(copy.beans(s, i) != 0)
        {
            int anotherBestHole = 0, thisValue = INT_MIN; // h2, v2
            Side opponent = s == NORTH ? SOUTH : NORTH;

            // evaluate the move hole = i
            thisValue = evaluate(copy, s, i);

            if(s != og)
            {
                thisValue = -thisValue;
            }

            // opponent's move
            chooseMove(copy, opponent, og, anotherBestHole, thisValue, depth + 1, timeLimit, timer);

            copy = original; // "unmake" the move

            if(uninitialized) // very first node
            {
                value = thisValue;
                uninitialized = false;
            }

            // if og moves, inherit the max
            // if opponent moves, inherit the min
            if((s == og && thisValue >= value) || (s != og && thisValue <= value))
            {
                bestHole = i;
                value = thisValue;
            }
        }
    }

    return;
}

// given a position, returns a number that measures how good that position is for the player
int SmartPlayer::evaluate(Board& b, Side s, int hole) const
{
    Side opponent;

    opponent = s == NORTH ? SOUTH : NORTH;
    
    // game is still continuing
    Side endSide;
    int endHole;
    
    b.sow(s, hole, endSide, endHole);
    
    // capture
    if(b.beans(s, endHole) == 1 && b.beans(opponent, endHole) != 0 && endSide == s)
    {
        b.moveToPot(s, endHole, s);
        b.moveToPot(opponent, endHole, s);
    }
        
    // if north side has no more beans, game is ending
    if(b.beansInPlay(NORTH) == 0)
    {
        for(int i = 1; i <= b.holes(); i++)
        {
            b.moveToPot(SOUTH, i, SOUTH);
        }
        
        if(b.beans(s, 0) > b.beans(opponent, 0))
        {
            return INT_MAX;
        }
        
        else if(b.beans(opponent, 0) > b.beans(s, 0))
        {
            return INT_MIN;
        }
        
        else
        {
            return b.beans(s, 0) - b.beans(opponent, 0);
        }
    }
    
    // if south side has no more beans, game is ending
    if(b.beansInPlay(SOUTH) == 0)
    {
        for(int i = 1; i <= b.holes(); i++)
        {
            b.moveToPot(NORTH, i, NORTH);
        }
        
        if(b.beans(s, 0) > b.beans(opponent, 0))
        {
            return INT_MAX;
        }
        
        else if(b.beans(opponent, 0) > b.beans(s, 0))
        {
            return INT_MIN;
        }
        
        else
        {
            return b.beans(s, 0) - b.beans(opponent, 0);
        }
    }
    
    // if it lands in the pot, go again
    if(endSide == s && endHole == 0)
    {
        int bestValue = INT_MIN;
        Board copy = b, bestCopy = b;
        
        for(int i = 1; i <= b.holes(); i++)
        {
            if(b.beans(s, i) != 0)
            {
                int value = evaluate(copy, s, i);
                
                if(value >= bestValue)
                {
                    bestValue = value;
                    bestCopy = copy;
                }
                
                copy = b; // if you get free turns, you should set copy back to the version of the move that grants the best evaluate score
            }
        }
        
        b = bestCopy;
        
        return bestValue;
    }
    
    return b.beans(s, 0) - b.beans(opponent, 0);
}
