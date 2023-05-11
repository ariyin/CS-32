//
//  maze.cpp
//  Event
//
//  Created by Jenna Wang on 5/8/23.
//

//#include <iostream>
//using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    // if the start location = end location
    if(sr == er && sc == ec)
    {
        return true;
    }

    // mark the start location as visited
    maze[sr][sc] = '!';

    // for each of the four directions, if the location one step in that direction (from the start location) has no wall and is unvisited, call pathExists starting from that location (and ending at the same ending location as in the current call)
    if(maze[sr+1][sc] != 'X' && maze[sr+1][sc] != '!')
    {
        if(pathExists(maze, sr+1, sc, er, ec))
        {
            return true;
        }
    }
    
    if(maze[sr-1][sc] != 'X' && maze[sr-1][sc] != '!')
    {
        if(pathExists(maze, sr-1, sc, er, ec))
        {
            return true;
        }
    }
    
    if(maze[sr][sc+1] != 'X' && maze[sr][sc+1] != '!')
    {
        if(pathExists(maze, sr, sc+1, er, ec))
        {
            return true;
        }
    }
    
    if(maze[sr][sc-1] != 'X' && maze[sr][sc-1] != '!')
    {
        if(pathExists(maze, sr, sc-1, er, ec))
        {
            return true;
        }
    }
    
    return false;
}

//int main()
//{
//    char maze[10][10] = {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','X','.','.','.','.','X' },
//        { 'X','.','.','X','X','.','X','X','.','X' },
//        { 'X','.','X','.','.','.','.','X','X','X' },
//        { 'X','X','X','X','.','X','X','X','.','X' },
//        { 'X','.','.','X','.','.','.','X','.','X' },
//        { 'X','.','.','X','.','X','.','X','.','X' },
//        { 'X','X','.','X','.','X','X','X','X','X' },
//        { 'X','.','.','.','.','.','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
//    };
//
//    if (pathExists(maze, 8,8, 5,8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}
