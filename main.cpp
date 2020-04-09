#include <iostream>

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
    void Reset()
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

int main()
{

    Ball ball(0, 0);

    cout << "Current position status: " << ball << endl; 

    ball.randomDirection(); // direction change 

    cout << "Position after random: " << ball << endl; 

    ball.move();

    cout << "Position after move: " << ball << endl; 

    ball.randomDirection();

    cout << "Position after random: " << ball << endl; 

    ball.move();

    cout << "Position after move: " << ball << endl; 

    Paddle player1(0, 0);
    Paddle player2(10, 0);

    cout << "Player 1: " << player1 << endl;
    cout << "Player 2: " << player2 << endl;

    player1.moveUp();
    player2.moveDown();

    cout << "Player 1: " << player1 << endl;
    cout << "Player 2: " << player2 << endl;

    return 0;
}