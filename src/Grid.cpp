#include "Grid.h"
#include <iostream>
#include <string>

using namespace std;

char mainGrid[10][10];
char SHIP = 'O';
char DEAD = 'X';
char WATER = '-';


Grid::Grid()
{
    // Initialize every index in our mainGrid to be an O, which represents no ship. This acts as a canvas.
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            mainGrid[x][y] = WATER;
        }
    }
}

bool Grid::addShip(int shipSize, pair<int, int> startPoint, string direction){

    // The user input treats the top left corner as (1,1), but the program treats it as (0,0), so the user input is parsed into this format.
    int x = startPoint.first - 1;
    int y = startPoint.second - 1;

    if(x > 9 || x < 0){
        return false;
    }
    else if(y > 9 || y < 0){
        return false;
    }

    if(direction == "up"){
        // Since shipSize includes the starting position of the ship, it extrudes this position by (shipSize - 1)
        if(y - (shipSize - 1) < 0){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x][y - i] = SHIP;
        }
    }
    else if(direction == "right"){
        if(x + (shipSize - 1) > 9){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x + i][y] = SHIP;
        }
    }
    else if(direction == "down"){
        if(y + (shipSize - 1) > 9){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x][y + i] = SHIP;
        }
    }
    else if(direction == "left"){
        if(x - (shipSize - 1)< 0){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x - i][y] = SHIP;
        }
    }
    else{
        cout << "Invalid ship direction" << endl;
    }
}

void Grid::drawGrid()
{
    // For every coordinate combination (x,y), draw the character connected to this index in our mainGrid.
    for(int y = 0; y < 10; y++)
    {
        for(int x = 0; x < 10; x++)
        {
            cout << mainGrid[x][y] << " ";
        }
        cout << endl;
    }
}

bool Grid::attack(pair<int,int> coords,bool super){

    int x = coords.first-1;
    int y = coords.second-1;


    if (super==true){
        for(int l= x-1; l<=x+1; l++){
            for (int i = y-1;i<=y+1; i++){
                try {
                    if (mainGrid[l][i]==SHIP){

                        mainGrid[l][i]=DEAD;
                        cout<<'x, y'<<endl;
                    }

                }
                catch(int e){
                cout<<"shit"<<endl;
                }
            }
        }
    }
    else{
         if (mainGrid[x][y]==SHIP){
        mainGrid[x][y]=DEAD;
        return true;
    }
    else{
        return false;
    }
    }
}
