/***********************************************************************************
 * File: paddle.h
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Definition of the paddle class.
***********************************************************************************/

#ifndef PADDLE_H
#define PADDLE_H

#include <iostream> 

using namespace std;

class Paddle
{
private:
    int _x; // position
    int _y;
    int _x_original; // so we can reset to the center
    int _y_original;

public:
    Paddle(); // constructor
    Paddle(int, int);
    ~Paddle(); // destructor 

    // set functions 
    void setX(int);
    void setY(int);
    void setXOriginal(int);
    void setYOriginal(int);

    // get functions 
    int getX();
    int getY();
    int getXOriginal();
    int getYOriginal();

    void reset(); // reset to the original position

    // move 
    void moveUp();
    void moveDown();

    friend ostream & operator << (ostream & o, Paddle paddle)
    {
        o << "Paddle [" << paddle.getX() << "," << paddle.getY() << "]";
        return o; 
    }
};

#endif // PADDLE_H