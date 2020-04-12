/***********************************************************************************
 * File: main.cpp
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * The main funciton of the game.
***********************************************************************************/

#include "game.h"

using namespace std;

int main()
{
    Game game(40, 20);
    game.run();

    return 0;
}