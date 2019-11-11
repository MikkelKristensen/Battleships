#include <iostream>
#include "Grid.h"
#include <string>

using namespace std;

int main()
{

    Grid * grid = new Grid();
    // grid->drawGrid();
    cout<<"You have 4 ships"<<endl;
    for (int i=5; i>1; i--){
        cout<<"Length: "<<i<<" please enter the X coordinate and press enter"<<endl;
        int x;
        cin>>x;
        cout<<"Please enter the Y coordinate and press enter"<<endl;
        int y;
        cin>>y;
        cout<<"Please write the direction of the ship, lowercase."<<endl;
        string direc;
        cin>>direc;
        grid->addShip(i, {x,y}, direc);
        grid->drawGrid();

    }
    /*grid->addShip(5, {1,3}, "down");
    grid->addShip(4, {4,4}, "up");
    grid->addShip(3, {7,4}, "right");
    grid->addShip(2, {10,10}, "up");
    grid->attack({5,5},true);*/
    grid->drawGrid();
}
