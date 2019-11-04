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

    protected:

    private:
};

#endif // GRID_H
