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

        // Loop through every ship placement, if any of them already contain a ship, return false.
        for(int i = 0; i < shipSize; i++){
            if(mainGrid[x][y - i] ==  SHIP){
                return false;
            }
        }
        // Finally, loop through every ship placement and place a ship.
        for(int i = 0; i < shipSize; i++){
            mainGrid[x][y - i] = SHIP;
        }
        return true;
    }
    else if(direction == "right"){
        if(x + (shipSize - 1) > 9){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            if(mainGrid[x + i][y] ==  SHIP){
                return false;
            }
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x + i][y] = SHIP;
        }
        return true;
    }
    else if(direction == "down"){
        if(y + (shipSize - 1) > 9){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            if(mainGrid[x][y + i] ==  SHIP){
                return false;
            }
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x][y + i] = SHIP;
        }
        return true;
    }
    else if(direction == "left"){
        if(x - (shipSize - 1)< 0){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            if(mainGrid[x - i][y] ==  SHIP){
                return false;
            }
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x - i][y] = SHIP;
        }
        return true;
    }
    else{
        return false;
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
// Creates two variables x and y, and sets them as coordinates. 1 is subtracted to correct for the difference in the arrays 0-9,
// and the users 1-10 grid understanding.
    int x = coords.first - 1;
    int y = coords.second - 1;

// Checks if super is true to
    if (super){
        for(int l = x - 1; l <= x + 1; l++){
            for (int i = y - 1; i <= y + 1; i++){
                try {
                    if (mainGrid[l][i] == SHIP){
                        mainGrid[l][i] = DEAD;
                    }

                }
                catch(int e){
                    cout<<"DEBUG: Shooting at " << l << ", " << i << " failed."<<endl;
                }
            }
        }
    }
    else{ // If not using a super attack.
        if(mainGrid[x][y] == SHIP){
            mainGrid[x][y] = DEAD;
            return true;
        }
        else{
            return false;
        }
    }
}

