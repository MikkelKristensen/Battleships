#include <iostream>
#include "Ship.h"

using namespace std;

int size = 1;
pair<int, int> coordinates[4];

Ship::Ship()
{
}

Ship::~Ship()
{
    //dtor
}

void Ship::setSize(int newSize)
{
    if(newSize > 0 && newSize < 5){
        size = newSize;
    }
    else{
        cout << "Invalid ship size attempt" << endl;
    }
}
