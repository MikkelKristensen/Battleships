#include "Grid.h"
#include <iostream>
#include <string>

using namespace std;

char mainGrid[10][10];

Grid::Grid()
{
    // Initialize every index in our mainGrid to be an O, which represents no ship. This acts as a canvas.
    for(int x = 0; x < 10; x++)
    {
        for(int y = 0; y < 10; y++)
        {
            mainGrid[x][y] = 'O';
        }
    }
}

bool Grid::addShip(int shipSize, pair<int, int> startPoint, string direction){

    // The user input treats the top left corner as (1,1), but the program treats it as (0,0), so the user input is parsed into this format.
    int x = startPoint.first - 1;
    int y = startPoint.second - 1;

    // If the user input is outside of the grid, return false.
    if(x > 9 || x < 0){
        return false;
    }
    else if(y > 9 || y < 0){
        return false;
    }

    if(direction == "up"){
        // Check if the ship would go out of the grid, by seeing if its maximum is over 9, or its minimum is under 0.
        // Since shipSize includes the starting position of the ship, it extrudes this position by (shipSize - 1)
        if(y - (shipSize - 1) < 0){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x][y - i] = 'X';
        }
    }
    else if(direction == "right"){
        if(x + (shipSize - 1) > 9){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x + i][y] = 'X';
        }
    }
    else if(direction == "down"){
        if(y + (shipSize - 1) > 9){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x][y + i] = 'X';
        }
    }
    else if(direction == "left"){
        if(x - (shipSize - 1)< 0){
            return false;
        }

        for(int i = 0; i < shipSize; i++){
            mainGrid[x - i][y] = 'X';
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
