/***********************************************************************************
 * File: ball.cpp
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Definition of the ball class functions.
***********************************************************************************/
#include <iostream>

#include "ball.h"

using namespace std;

Ball::Ball(int x, int y) // constructor
{
    setXOriginal(x);
    setYOriginal(y);

    setX(x);
    setY(y);

    setDirection(STOP);
}

Ball::~Ball() // destructor 
{
    // cout << "Ball destructor!" << endl;
}

// set functions
void Ball::setX(int x)
{
    _x = x;
}

void Ball::setY(int y)
{
    _y = y;
}

void Ball::setXOriginal(int x)
{
    _x_original = x;
}

void Ball::setYOriginal(int y)
{
    _y_original = y;
}

void Ball::setDirection(Direction d) // change the direction
{
    _direction = d;
}
// ---

// get functions
int Ball::getX()
{
    return _x;
}

int Ball::getY()
{
    return _y;
}

int Ball::getXOriginal()
{
    return _x_original;
}

int Ball::getYOriginal()
{
    return _y_original;
}

Direction Ball::getDirection()
{
    return _direction;
}
// ---
        
// reset the ball position and direction
void Ball::reset() 
{
    setX(getXOriginal()); // set x as the x original
    setY(getYOriginal()); // initi ball in the middle
 
    setDirection(STOP); // ball initializa stopped
}

void Ball::randomDirection() // random direction
{
    setDirection((Direction)(rand() % 6 + 1)); // random numbers from 1 to 6
}

// move the ball
void Ball::move()
{
    switch (getDirection())
    {
    case STOP:
        break;
    case LEFT:
        setX(getX() - 1);
        break;
    case RIGHT:
        setX(getX() + 1);
        break;
    case UPLEFT:
        setX(getX() - 1);
        setY(getY() - 1);
        break;
    case DOWNLEFT:
        setX(getX() - 1);
        setY(getY() + 1);
        break;
    case UPRIGHT:
        setX(getX() + 1);
        setY(getY() - 1);
        break;
    case DOWNRIGHT:
        setX(getX() + 1);
        setY(getY() + 1);
    default:
        break;
    }
}

//  ostream & operator << (ostream & o, Ball ball)
//     {
//         o << "Ball [" << ball.getX() << "," << ball.getY() << "][" << ball.getDirection() << "]";
//         return o;
//     }