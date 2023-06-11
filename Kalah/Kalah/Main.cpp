//
//  Main.cpp
//  Kalah
//
//  Created by Jenna Wang on 5/22/23.
//

#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"

using namespace std;

int main()
{
    // NORTH = 0, SOUTH = 1
    HumanPlayer bp1("Human");
    SmartPlayer bp2("Smart Bot");
    Board b(6, 4); // 6, 4

//    b.setBeans(NORTH, 0, 5);
//    b.setBeans(NORTH, 1, 1);
//    b.setBeans(NORTH, 2, 0);
//    b.setBeans(NORTH, 3, 4);
//    b.setBeans(SOUTH, 0, 5);
//    b.setBeans(SOUTH, 1, 2);
//    b.setBeans(SOUTH, 2, 1);
//    b.setBeans(SOUTH, 3, 0);
//
//    b.setBeans(NORTH, 0, 22);
//    b.setBeans(NORTH, 1, 0);
//    b.setBeans(NORTH, 2, 1);
//    b.setBeans(NORTH, 3, 0);
//    b.setBeans(NORTH, 4, 0);
//    b.setBeans(NORTH, 5, 2);
//    b.setBeans(NORTH, 6, 0);
//    b.setBeans(SOUTH, 0, 20);
//    b.setBeans(SOUTH, 1, 0);
//    b.setBeans(SOUTH, 2, 0);
//    b.setBeans(SOUTH, 3, 2);
//    b.setBeans(SOUTH, 4, 0);
//    b.setBeans(SOUTH, 5, 1);
//    b.setBeans(SOUTH, 6, 0);

    Game g(b, &bp2, &bp1);
    g.play();
}
