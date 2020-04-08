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

};

int main()
{
    return 0;
}