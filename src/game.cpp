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

int _kbhit(void); // auxiliar function - conio.h function in windows
// had to be made to work on linux

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
  
    // reset the ball and paddles positions to its default
    ball->reset();     
    player_1->reset(); 
    player_2->reset(); 
}


// drawing function
void Game::draw()
{
    system("clear"); // clear prompt

    // draw bottom wall 
    for(int i = 0; i < getWidth() + 2; i++)
        cout << WALL_BOTTOM;
    cout << endl;

    for(int i = 0; i < getHeight(); i++)
    {
        for(int j = 0; j < getWidth(); j++)
        {
            // auxiliar variables 
            int ball_x = ball->getX();
            int ball_y = ball->getY();
            int player1_x = player_1->getX();
            int player1_y = player_1->getY();
            int player2_x = player_2->getX();
            int player2_y = player_2->getY();
            // ---

            // left column 
            if(j == 0)
                cout << WALL_LEFT;

            if(ball_x == j && ball_y == i)
                cout << BALL;

            // player 1 - left 
            else if(player1_x == j && player1_y == i)
                cout << PADDLE_LEFT;
            else if(player1_x == j && player1_y + 1 == i)
                cout << PADDLE_LEFT;
            else if(player1_x == j && player1_y + 2 == i)
                cout << PADDLE_LEFT;
            else if(player1_x == j && player1_y + 3 == i)
                cout << PADDLE_LEFT;
            // ---  

            // player 2 - right 
            else if(player2_x == j && player2_y == i)
                cout << PADDLE_RIGHT;
            else if(player2_x == j && player2_y + 1 == i)
                cout << PADDLE_RIGHT;
            else if(player2_x == j && player2_y + 2 == i)
                cout << PADDLE_RIGHT;
            else if(player2_x == j && player2_y + 3 == i)
                cout << PADDLE_RIGHT;
            // ---  

            // blank spaces
            else 
                cout << " ";


            if(j == getWidth() - 1)
                cout << WALL_RIGHT;
        }
        cout << endl;
    }

    for(int i = 0; i < getWidth() + 2; i++)
        cout << WALL_TOP;
    cout << endl;

    // scores 
    cout << "\nPLAYER 1: " << getScore1() << "\t\tPLAYER 2: " << getScore2();
}

// input function
void Game::input()
{
    ball->move();

    // auxiliar variables to store y position of the paddles
    int player1_y = player_1->getY();
    int player2_y = player_2->getY();

    if(_kbhit())
    {
        char current_key = getchar();
        current_key = toupper(current_key); // key compared is upper

        // move paddle 1
        //if(!strcmp(current_key, MOVE_UP_1))
        if(current_key == MOVE_UP_1)
            if(player1_y > 0)
                player_1->moveUp();
        if(current_key == MOVE_DOWN_1)
            if(player1_y + 4 < getHeight())
                player_1->moveDown();

        // move paddle 2
        if(current_key == MOVE_UP_2)
            if(player2_y > 0)
                player_2->moveUp();
        if(current_key == MOVE_DOWN_2)
            if(player2_y + 4 < getHeight())
                player_2->moveDown();

        if(ball->getDirection() == STOP)
            ball->randomDirection();

        if(current_key == getQuit())
            setQuit(true);
    }
}

// game logic
void Game::logic()
{
    // auxiliar variables 
    int ball_x = ball->getX();
    int ball_y = ball->getY();
    int player1_x = player_1->getX();
    int player1_y = player_1->getY();
    int player2_x = player_2->getX();
    int player2_y = player_2->getY();
    // ---

    // player 1 - left paddle 
    for(int i = 0; i < PADDLE_LENGHT; i++)
        if(ball_x == player1_x + 1) // x coordinate 
            if(ball_y == player1_y + i) // y coordinate 
                ball->setDirection((Direction)(rand() % 3 + 4)); // RIGHT, UPRIGHT or DOWNRIGHT
    
    // player 2 - right paddle 
    for(int i = 0; i < PADDLE_LENGHT; i++)
        if(ball_x == player2_x - 1)
            if(ball_y == player2_y + i)
                ball->setDirection((Direction)(rand() % 3 + 1)); // LEFT, UPLEFT or DOWNLEFT

    // bottom wall - ball hit wall 
    if(ball_y == getHeight() - 1)
        ball->setDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT); // set ball direction based on previous direction 

    // top wall - ball hit wall 
    if(ball_y == 0)
        ball->setDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT); // set ball direction based on previous direction 

    // left wall - ball hit left wall
    if(ball_x == 0)
        scoreUp(player_2); // 2 win - 1 lose 
    
    // right wall - ball hit right wall 
    if(ball_x == getWidth() - 1)
        scoreUp(player_1); // 1 win - 2 lose
}

// run game
void Game::run()
{
    while (!getQuit())
    {
        draw();
        input();
        logic();
        usleep(30000);
    }
}


int _kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
    ungetc(ch, stdin);
    return 1;
    }

    return 0;
}