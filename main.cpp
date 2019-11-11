#include <iostream>
#include "Grid.h"
#include <string>

using namespace std;

int main()
{
    Grid * grid = new Grid();
    // grid->drawGrid();
    grid->addShip(5, {1,3}, "down");
    grid->addShip(4, {5,5}, "down");
    grid->addShip(3, {7,4}, "right");
    grid->addShip(2, {10,10}, "up");
    grid->attack({6,4},true);
    grid->drawGrid();
}
