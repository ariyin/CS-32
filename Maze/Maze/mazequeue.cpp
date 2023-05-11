//
//  mazequeue.cpp
//  Maze
//
//  Created by Jenna Wang on 5/1/23.
//

#include <queue>
#include <iostream>
using namespace std;

class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec) through the maze; return false otherwise
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue <Coord> coords;
    Coord start(sr, sc);
    
    // Push the starting coordinate (sr,sc) onto the coordinate stack and update maze[sr][sc] to indicate that the algorithm has encountered it (i.e., set maze[sr][sc] to have a value other than '.').
    coords.push(start);
    maze[sr][sc] = '!';
    
    // While the stack is not empty,
    while(!coords.empty())
    {
        Coord current = coords.front();
        int r = current.r();
        int c = current.c();
        
        // Pop the top coordinate off the stack. This gives you the current (r,c) location that your algorithm is exploring.
//        cout << "(" << r << ", " << c << ")" << endl;
        coords.pop();
        
        // If the current (r,c) coordinate is equal to the ending coordinate, then we've solved the maze so return true!
        if(r == er && c == ec)
        {
            return true;
        }
        
        // If you can move SOUTH and haven't encountered that cell yet, then push the coordinate (r+1,c) onto the stack and update maze[r+1][c] to indicate the algorithm has encountered it.
        if(maze[r+1][c] == '.')
        {
            Coord s(r+1, c);
            coords.push(s);
            maze[r+1][c] = '!';
        }
        
        // If you can move EAST and haven't encountered that cell yet, then push the coordinate (r,c+1) onto the stack and update maze[r][c+1] to indicate the algorithm has encountered it.
        if(maze[r][c+1] == '.')
        {
            Coord e(r, c+1);
            coords.push(e);
            maze[r][c+1] = '!';
        }
        
        // If you can move NORTH and haven't encountered that cell yet, then push the coordinate (r-1,c) onto the stack and update maze[r-1][c] to indicate the algorithm has encountered it.
        if(maze[r-1][c] == '.')
        {
            Coord n(r-1, c);
            coords.push(n);
            maze[r-1][c] = '!';
        }
        
        // If you can move WEST and haven't encountered that cell yet, then push the coordinate (r,c-1) onto the stack and update maze[r][c-1] to indicate the algorithm has encountered it.
        if(maze[r][c-1] == '.')
        {
            Coord w(r, c-1);
            coords.push(w);
            maze[r][c-1] = '!';
        }
    }
    
    // There was no solution, so return false
    return false;
}

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3,4, 8,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

