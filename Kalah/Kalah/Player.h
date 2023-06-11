//
//  Player.h
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#ifndef Player_h
#define Player_h

#include "Board.h"
#include "Side.h"
#include <string>

class JumpyTimer;

class Player
{
  public:
    Player(std::string name);
    std::string name() const;
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player();
  private:
    std::string m_name;
};

class BadPlayer : public Player
{
  public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
};

class HumanPlayer : public Player
{
  public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player
{
  public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
  private:
    void chooseMove(const Board& b, Side s, Side og, int& bestHole, int& value, int depth, double timeLimit, JumpyTimer& timer) const;
    int evaluate(Board& b, Side s, int hole) const;
};

#endif /* Player_h */
