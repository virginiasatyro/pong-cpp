/***********************************************************************************
 * File: paddle.cpp
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Definition of the paddle class functions.
***********************************************************************************/

#include "paddle.h"

using namespace std;

// constructor
Paddle::Paddle()
{
    setX(0);
    setY(0);
    setXOriginal(0);
    setYOriginal(0);
}

// constructor 
Paddle::Paddle(int x, int y) : Paddle()
{
    setX(x);
    setY(y);
    setXOriginal(x);
    setYOriginal(y);
}

// destructor 
Paddle::~Paddle()
{
    // destructor
}

// set functions 
void Paddle::setX(int x)
{
    _x = x;
}

void Paddle::setY(int y)
{
    _y = y;
}

void Paddle::setXOriginal(int x)
{
    _x_original = x;
}

void Paddle::setYOriginal(int y)
{
    _y_original = y;
}
// ---

// get functions 
int Paddle::getX()
{
    return _x;
}

int Paddle::getY()
{
    return _y;
}

int Paddle::getXOriginal()
{
    return _x_original;
}

int Paddle::getYOriginal()
{
    return _y_original;
}
// ---

// reset the paddle position to the original
void Paddle::reset() 
{
    setX(getXOriginal());
    setY(getYOriginal());
}

// move paddle
void Paddle::moveUp()
{
    setY(getY() - 1);
}

void Paddle::moveDown()
{
    setY(getY() + 1);
}