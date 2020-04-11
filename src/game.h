/***********************************************************************************
 * File: game.h
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Definition of the game class.
***********************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <time.h>

#include "ball.h"
#include "paddle.h"

#define MOVE_UP_1   'w' || 'W'
#define MOVE_DOWN_1 's' || 'S'
#define MOVE_UP_2   'i' || 'I'
#define MOVE_DOWN_2 'k' || 'K'

using namespace std;

class Game
{
private:
    int _width;
    int _height;
    int _score_1;
    int _score_2;
    bool _quit;

    Ball *ball;
    Paddle *player_1;
    Paddle *player_2;

public:
    Game(int, int); // constructor
    ~Game(); // destructor

    // set functions
    void setWidth(int);
    void setHeight(int);
    void setScore1(int);
    void setScore2(int);
    void setQuit(bool);

    // get functions 
    int getWidth();
    int getHeight();
    int getScore1();
    int getScore2();
    bool getQuit();

    // scores 
    void scoreUp(Paddle*);

    // drawing function
    void draw();

    // input function
    void input();

    // game logic
    void logic();

    // run game
    void run();
};

#endif // GAME_H