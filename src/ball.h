/***********************************************************************************
 * File: ball.h
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Definition of the ball class.
***********************************************************************************/

#ifndef BALL_H
#define BALL_H

#include <iostream> 

using namespace std;

enum Direction {STOP      = 0, 
                LEFT      = 1, 
                UPLEFT    = 2, 
                DOWNLEFT  = 3,
                RIGHT     = 4,
                UPRIGHT   = 5,
                DOWNRIGHT = 6};


class Ball
{
private:
    int _x;
    int _y;
    int _x_original;
    int _y_original;

    Direction _direction;

public: 
    Ball(int, int); // constructor
    ~Ball(); // destructor 

    // set functions
    void setX(int);
    void setY(int);
    void setXOriginal(int);
    void setYOriginal(int);
    void setDirection(Direction); // change the direction

    // get functions
    int getX();
    int getY();
    int getXOriginal();
    int getYOriginal();
    Direction getDirection();

    void reset(); // reset 
    void randomDirection(); // random direction
    void move(); // move the ball

    friend ostream & operator << (ostream & o, Ball ball)
    {
        o << "Ball [" << ball.getX() << "," << ball.getY() << "][" << ball.getDirection() << "]";
        return o;
    }
};

#endif // BALL_H