#include <iostream>
#include <ConnectToServer.h>
#include "Grid.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11 exclusive function for checking if all of str is digits.
}

void placeShips(Grid * grid, int maxLength){
    // This function runs a for-loop so that the user places ships ranging from maxLength to 2.
    for (int i = maxLength; i > 1; i--){
        // Clear the screen and redraw the grid.
        system("CLS");
        grid->drawGrid();

        // Setup
        int x;
        int y;
        string inputX;
        string inputY;
        string inputDirection;

        cout << "Please place a ship of length: " << i << endl;
        cout << "The process will reset if an invalid digit or direction is given." << endl;
        cout << "X: ";

        // Get a line input, check if its composed of digits, and has a length over 0, as is_digits returns true for empty strings for some reason.
        getline(cin, inputX);
        if (is_digits(inputX) && inputX.length() > 0){

            // Stream the buffer into an integer. Make a check to see if it's within the grid, and if it's not, restart this iteration of the loop.
            stringstream(inputX) >> x;
            x--;
            if(x > 9 || x < 0){
                i++;
                continue;
            }
        }
        else{
            // Restart iteration
            i++;
            continue;
        }
        cout << endl;

        cout<<"Y: ";
        getline(cin, inputY);
        if (is_digits(inputY) && inputY.length() > 0){
            stringstream(inputY) >> y;
            y--;
            if(y > 9|| y < 0){
                i++;
                continue;
            }
        }
        else{
            i++;
            continue;
        }
        cout << endl;


        cout<<"Direction(up/down/left/right): ";
        getline(cin, inputDirection);
        cout << endl;

        // Finally, try to add the ship to the grid. This returns true if it succeeds, and false it it doesn't.
        // Restart the iteration if it fails.
        if(grid->addShip(i, {x,y}, inputDirection)){
            system("CLS");
            grid->drawGrid();
        }
        else{
            system("CLS");
            grid->drawGrid();
            cout << "Invalid ship placement" << endl;
            i++;
        }
    }
}

int main()
{
    // Program initialization
    Grid * grid = new Grid();
    grid->drawGrid();

    // Initialize placeShips phase.
    placeShips(grid, 5);
    system("CLS");
    grid->drawGrid();

    // Finally connect to the server, starting the main game loop.
    ConnectToServer * frac = new ConnectToServer(grid);
    return 0;
}
