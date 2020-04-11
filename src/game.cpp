/***********************************************************************************
 * File: game.cpp
 * C++
 * Author: Virgínia Sátyro
 * License: Free - Open Source
 * Created on April 2020 
 * 
 * Definition of the game class functions. Run game, draw functions, logic, etc.
 ***********************************************************************************/

#include "game.h"

using namespace std;

// constructor
Game::Game(int width, int height)
{
    srand(time(NULL)); // seed rand() function

    setQuit(false);

    // set initial scores
    setScore1(0);
    setScore2(0);

    // set width and height
    setWidth(width);
    setHeight(height);

    // create objects 
    ball = new Ball(width / 2, height / 2); // place ball in the middle
    player_1 = new Paddle(1, height/2 - 3); // place paddle 1 in the left
    player_2 = new Paddle(width - 2, height/2 - 3); // place paddle 2 in the right
    // podemos desenvolver um novo método pra definir esse posicionamento de acordo com o tamanho do jogo
} 

// destructor
Game::~Game()
{
    delete ball;
    delete player_1;
    delete player_2;
} 

// set functions
void Game::setWidth(int width)
{
    _width = width;
}

void Game::setHeight(int height)
{
    _height = height;
}

void Game::setScore1(int score)
{
    _score_1 = score;
}

void Game::setScore2(int score)
{
    _score_2 = score;
}

void Game::setQuit(bool q)
{
    _quit = q;
}
// ---

// get functions 
int Game::getWidth()
{
    return _width;
}

int Game::getHeight()
{
    return _height;
}

int Game::getScore1()
{
    return _score_1;
}

int Game::getScore2()
{
    return _score_2;
}

bool Game::getQuit()
{
    return _quit;
}

// scores up
void Game::scoreUp(Paddle *player)
{
    if(player == player_1)
        setScore1(getScore1() + 1); // score player 1 up
    else if(player == player_2)
        setScore2(getScore2() + 1); // score player 2 up
  
    ball->reset(); // ball return to the middle
    player_1->reset(); // paddle return to the middle
    player_2->reset(); // paddle return to the middle
}

/*
    // drawing function
    void draw();

    // input function
    void input();

    // game logic
    void logic();

    // run game
    void run();
    */