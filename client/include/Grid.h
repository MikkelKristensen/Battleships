#ifndef GRID_H
#define GRID_H
#include <string>
#include <iostream>

using namespace std;


class Grid
{
    public:
        Grid();
        void drawGrid();
        bool addShip(int, pair<int, int>, string);
        bool attack(pair<int,int>,bool);
        bool hasLost();

    protected:

    private:
};

#endif // GRID_H
