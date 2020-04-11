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

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "ball.h"
#include "paddle.h"

// define keys to move paddle 
#define MOVE_UP_1   'W'
#define MOVE_DOWN_1 'S'
#define MOVE_UP_2   'I'
#define MOVE_DOWN_2 'K'
#define QUIT 'Q'

// define 'bricks'
#define WALL_TOP    '▀'
#define WALL_BOTTOM '▄'
#define WALL_LEFT   '▋'
#define WALL_RIGHT  '▐'

#define BALL '●'

#define PADDLE_LEFT  '▋'
#define PADDLE_RIGHT '▐'

using namespace std;

class Game
{
private:
    int _width;   // game width
    int _height;  // game height
    int _score_1; // score of player 1
    int _score_2; // score of player 2
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