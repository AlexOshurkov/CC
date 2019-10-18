#include "stdafx.h"
#pragma hdrstop

using namespace std;

const size_t MW = 50;
const size_t MH = 20;

size_t maze[MW][MH];

const char chBrick = 219;
const char chVisited = '+';
const char chEntry = '>';
const char chExit = 'X';

typedef pair<size_t, size_t> pos_t;

pos_t posEntry(1, MH / 2);
pos_t posExit(MW - 2, MH / 2);

void putMark(pos_t pos, char mark) {
    maze[pos.first][pos.second] = mark;
}

void initMaze() {
    
    ::memset(maze, 0, sizeof(maze));

    for (size_t c = 0; c < MW; ++c)
    {
        maze[c][0] = chBrick;
        maze[c][MH - 1] = maze[c][0];
    }

    for (size_t  r = 0; r < MH; ++r)
    {
        maze[0][r] = chBrick;
        maze[MW - 1][r] = maze[0][r];
    }

    putMark(posEntry, chEntry);
    putMark(posExit, chExit);
}

void printMaze() {

    for (size_t r = 0; r < MH; ++r)
    {
        cout << "\n";
        for (size_t c = 0; c < MW; ++c)
            cout << (char)maze[c][r];
    }
}

int main6() {

    initMaze();
    printMaze();

    return 0;
}
