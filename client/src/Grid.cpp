#include "Grid.h"
#include <iostream>
#include <string>

using namespace std;

// Grid size.
char mainGrid[10][10];

// Definitions
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

    // Creates two variables x and y, and sets them as coordinates.
    int x = startPoint.first;
    int y = startPoint.second;

    // If either x or y is out of bounds, return false. This check if already done before calling this function, but you can never be too safe.
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
    // Creates two variables x and y, and sets them as coordinates.
    int x = coords.first;
    int y = coords.second;

    // hit is false by default, but is set to true if a ship is hit.
    bool hit = false;

    // If super is true, initiate a 3x3 attack.
    if (super){
        for(int l = x - 1; l <= x + 1; l++){
            for (int i = y - 1; i <= y + 1; i++){
                try {
                    if (mainGrid[l][i] == SHIP){
                        mainGrid[l][i] = DEAD;
                        hit = true;
                    }
                }
                catch(int e){
                    cout<<"DEBUG: Shooting at " << l << ", " << i << " failed."<<endl;
                }
            }
        }
    }
    else{ // If not using a super attack, simply attack a 1x1 area at (x,y).
        if(mainGrid[x][y] == SHIP){
            mainGrid[x][y] = DEAD;
            hit = true;
        }
    }

    return hit;
}

bool Grid::hasLost(){

    // Look through the entire map for a ship. If a ship is found, return false as the user has not lost.
    // If no ship is found and the for-loop concludes, return true as the user has lost.
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            if(mainGrid[x][y] == SHIP){ return false; }
        }
    }
    return true;
}

