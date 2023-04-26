//
//  Game.h
//  BadBunny
//
//  Created by Jenna Wang on 4/5/23.
//

#ifndef game_h
#define game_h

#include <string>
class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif // game_h
