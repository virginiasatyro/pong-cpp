#include <iostream>
#include <time.h>
// #include <conio.h>

using namespace std;

enum Direction {STOP = 0, 
                LEFT = 1, 
                UPLEFT = 2, 
                DOWNLEFT = 3,
                RIGHT = 4,
                UPRIGHT = 5,
                DOWNRIGHT = 6};

class Ball
{
private:
    int _x;
    int _y;
    int _x_original;
    int _y_original;

    Direction direction;

public: 
    Ball(int x_pos, int y_pos)
    {
        _x_original = x_pos;
        _y_original = y_pos;

        // original position of the ball - reset later 
        _x = x_pos;
        _y = y_pos;
        direction = STOP;
    }
    void reset()
    {
        _x = _x_original;
        _y = _y_original;
        direction = STOP;
    }

    void changeDirection(Direction d)
    {
        direction = d;
    }

    void randomDirection()
    {
        direction = (Direction)(rand() % 6 + 1); // random numbers from 1 to 6
    }

    inline int getX()
    {
        return _x;
    }

    inline int getY()
    {
        return _y;
    }

    inline Direction getDirection()
    {
        return direction;
    }

    void move()
    {
        switch (direction)
        {
            case STOP:
                break;
            case LEFT:
                _x--;
                break;
            case RIGHT:
                _x++;
                break;
            case UPLEFT:
                _x--;
                _y--;
                break;
            case DOWNLEFT:
                _x--;
                _y++;
                break;
            case UPRIGHT:
                _x++;
                _y--;
                break;
            case DOWNRIGHT:
                _x++;
                _y++;
                break;
            default:
                break;
        }
    }
    // friend to output 
    friend ostream & operator << (ostream & o, Ball ball) // ????????
    {
        o << "Ball [" << ball._x << "," << ball._y << "][" << ball.direction << "]";
        return o;
    }

};

class Paddle
{
private:
    int _x; // position
    int _y; 
    int _x_original; // so we can reset
    int _y_original;

public:
    Paddle()
    {
        _x = _y = 0;
    }

    Paddle(int x_pos, int y_pos) : Paddle()
    {
        _x_original = x_pos;
        _y_original = y_pos;
        _x = x_pos;
        _y = y_pos;
    }
    
    inline void reset()
    {
        _x = _x_original;
        _y = _y_original;
    }

    inline int getX()
    {
        return _x;
    }

    inline int getY()
    {
        return _y;
    }

    inline void moveUp()
    {
        _y--;
    }

    inline void moveDown()
    {
        _y++;
    }

    friend ostream & operator << (ostream & o, Paddle paddle)
    {
        o << "Paddle [" << paddle._x << "," << paddle._y << "]";
        return o; 
    }
};

class GameManager
{
private:
    int _width;
    int _height;
    int _score1;
    int _score2;
    char move_up1, move_down1;
    char move_up2, move_down2;
    bool quit;

    Ball *ball; // define pointer - initialize the ball - create the ball object
    Paddle *player1;
    Paddle *player2;

public:
    GameManager(int w, int h)
    {
        srand(time(NULL));
        quit = false;
        move_up1 = 'w';
        move_down1 = 's';
        move_up2 = 'i';
        move_down2 = 'k';
        _score1 = _score2 = 0;
        _width = w;
        _height = h;
        ball = new Ball(w / 2, h / 2); // place ball at the middle 
        player1 = new Paddle(1, h / 2 - 3);
        player2 = new Paddle(w - 2, h / 2 - 3);
    }

    ~GameManager()
    {
        delete ball;
        delete player1;
        delete player2;
    }

    void scoreUp(Paddle *player)
    {
        if(player == player2)
            _score1++;
        else if(player == player2)
            _score2++;

        ball->reset();
        player1->reset();
        player2->reset();
    }

    void draw()
    {
        system("clear"); // cls (windows)

        for(int i = 0; i < _width + 2; i++)
            cout << "#";
        cout << endl;

        for(int i = 0; i < _height; i++)
        {
            for(int j = 0; j < _width; j++)
            {
                int ballX = ball->getX();
                int ballY = ball->getY();
                int player1X = player1->getX();
                int player1Y = player1->getY();
                int player2X = player2->getX();
                int player2Y = player2->getY();

                if(j == 0) // first column
                    cout << "#";

                if(ballX == j && ballY == i)
                    cout << "o";
                else if(player1X == j && player1Y == i)
                    cout << "#"; // player 1 
                else if(player2X == j && player2Y == i)
                    cout << "#"; // player 2
                else
                    cout << " ";
                

                if(j == _width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for(int i = 0; i < _width + 2; i++)
            cout << "#";
        cout << endl;
    }
};

int main()
{
    GameManager game(40, 20);
    game.draw();

    return 0;
}