#include <iostream>
#include "Grid.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void clearScreen(){
    system("CLS");
}

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

void placeShips(Grid * grid, int maxLength){
    for (int i = maxLength; i > 1; i--){
        clearScreen();
        grid->drawGrid();
        int x;
        int y;
        string inputX;
        string inputY;
        string inputDirection;

        cout << "Please place a ship of length: " << i << endl;
        cout << "The process will reset if an invalid digit or direction is given." << endl;
        cout << "X: ";
        getline(cin, inputX);
        if (is_digits(inputX) && inputX.length() > 0){
            stringstream(inputX) >> x;
            if(x > 10 || x < 1){
                i++;
                continue;
            }
        }
        else{
            i++;
            continue;
        }
        cout << endl;

        cout<<"Y: ";
        getline(cin, inputY);
        if (is_digits(inputY) && inputY.length() > 0){
            stringstream(inputY) >> y;
            if(y > 10 || y < 1){
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

        if(grid->addShip(i, {x,y}, inputDirection)){
            clearScreen();
            grid->drawGrid();
        }
        else{
            clearScreen();
            grid->drawGrid();
            cout << "Invalid ship placement" << endl;
            i++;
        }
    }
}

void TEMPFUNCTIONAUTOPLACESHIPS(Grid * grid){
    grid->addShip(5, {1,3}, "down");
    grid->addShip(4, {4,4}, "up");
    grid->addShip(3, {7,4}, "right");
    grid->addShip(2, {10,10}, "up");
    clearScreen();
    grid->drawGrid();
}

int main()
{

    Grid * grid = new Grid();

    grid->drawGrid();
    placeShips(grid, 5);
    // TEMPFUNCTIONAUTOPLACESHIPS(grid);

    while(true){
        int attackX;
        int attackY;
        bool super;
        cout << "Enter X, then Y, that you wish to attack" << endl;
        cout << "X: ";
        cin >> attackX;
        cout << endl;
        cout << "Y: ";
        cin >> attackY;
        cout << endl;
        cout << "Use super attack? (1 for yes, 0 for no)." << endl;
        cin >> super;
        grid->attack({attackX, attackY}, super);
        clearScreen();
        grid->drawGrid();
    }
    grid->drawGrid();
}
