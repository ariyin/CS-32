//
//  Game.h
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#ifndef Game_h
#define Game_h

#include "Board.h"
#include "Side.h"
#include "Player.h"

class Game
{
  public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move(Side s);
    void play();
    int beans(Side s, int hole) const;
  private:
    Board m_board;
    Player* m_southPlayer;
    Player* m_northPlayer;
    Player* m_activePlayer;
    Side m_activeSide;
};

#endif /* Game_h */
