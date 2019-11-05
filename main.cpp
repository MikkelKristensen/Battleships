#include <iostream>
#include <stdlib.h>
#include "Grid.h"
#include <string>

using namespace std;

int main()
{
    int x;
    int y;
    int length;
    string direction;
    Grid * grid = new Grid();

    /*grid->addShip(5, {1,3}, "down");
    grid->addShip(4, {4,4}, "up");
    grid->addShip(3, {7,4}, "right");
    grid->addShip(2, {10,10}, "up");
    grid->drawGrid();*/

    // Midlertidigt loop hvor vi bare kan adde skibe og se det opdatere.
    while(true){
        system("CLS");
        grid->drawGrid();
        cout << endl;
        cout << "X: ";
        cin >> x;

        cout << endl;
        cout << "Y: ";
        cin >> y;

        cout << endl;
        cout << "Length: ";
        cin >> length;

        cout << endl;
        cout << "direction: ";
        cin >> direction;
        grid->addShip(length, {x,y}, direction);
    }
}
