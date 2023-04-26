//
//  Game.cpp
//  BadBunny
//
//  Created by Jenna Wang on 4/5/23.
//

#include "Game.h"
#include "globals.h"
#include "Arena.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
using namespace std;

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a poisoned carrot and
// not move; otherwise, this function sets bestDir to the recommended
// direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // How dangerous is it to stand?
  int standDanger = computeDanger(a, r, c);

    // if it's not safe, see if moving is safer
  if (standDanger > 0)
  {
      int bestMoveDanger = standDanger;
      int bestMoveDir = NORTH;  // arbitrary initialization

        // check the four directions to see if any move is
        // better than standing, and if so, record the best
      for (int dir = 0; dir < NUMDIRS; dir++)
      {
          int rnew = r;
          int cnew = c;
          if (attemptMove(a, dir, rnew, cnew))
          {
              int danger = computeDanger(a, rnew, cnew);
              if (danger < bestMoveDanger)
              {
                  bestMoveDanger = danger;
                  bestMoveDir = dir;
              }
          }
      }

        // if moving is better than standing, recommend move
      if (bestMoveDanger < standDanger)
      {
          bestDir = bestMoveDir;
          return true;
      }
  }
  return false;  // recommend standing
}

bool decodeDirection(char ch, int& dir)
{
  switch (tolower(ch))
  {
    default:  return false;
    case 'n': dir = NORTH; break;
    case 'e': dir = EAST;  break;
    case 's': dir = SOUTH; break;
    case 'w': dir = WEST;  break;
  }
  return true;
}

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
             << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small to hold a player and "
             << nRabbits << " rabbits!" << endl;
        exit(1);
    }

      // Create the arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c/h or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        if (playerMove == "h")
        {
            // tell its Arena's history object to display the history grid
            m_arena->history().display();
            
            // print the Press enter to continue
            cout << "Press enter to continue." << endl;

            // prompt and wait for the user to respond (cin.ignore(10000,'\n'); does that nicely.)
            cin.ignore(10000, '\n');
            
            // typing the h command does not count as the player's turn.
            m_arena->display("");
            continue;
        }
        
        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}
