#include <iostream>
#include <time.h>
//#include <curses.h>
// #include <conio.h>

using namespace std;

// #include <stdio.h>
// #include <sys/select.h>
// #include <termios.h>
// #include <stropts.h>

// int _kbhit() {
//     static const int STDIN = 0;
//     static bool initialized = false;

//     if (! initialized) {
//         // Use termios to turn off line buffering
//         termios term;
//         tcgetattr(STDIN, &term);
//         term.c_lflag &= ~ICANON;
//         tcsetattr(STDIN, TCSANOW, &term);
//         setbuf(stdin, NULL);
//         initialized = true;
//     }

//     int bytesWaiting;
//     ioctl(STDIN, FIONREAD, &bytesWaiting);
//     return bytesWaiting;
// }

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
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
        if(player == player1)
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
            cout << "▄";
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
                   cout << "▋";

                if(ballX == j && ballY == i)
                    cout << "●";
                // player 1 ---------------------------
                else if(player1X == j && player1Y == i)
                    cout << "▋";
                else if(player1X == j && player1Y + 1 == i)
                    cout << "▋"; // player 1 
                else if(player1X == j && player1Y + 2 == i)
                    cout << "▋"; // player 1 
                else if(player1X == j && player1Y + 3 == i)
                    cout << "▋"; // player 1 
                // --

                // player 2 ---------------------------
                else if(player2X == j && player2Y == i)
                    cout << "▐"; // player 2
                else if(player2X == j && player2Y + 1 == i)
                    cout << "▐"; // player 2
                else if(player2X == j && player2Y + 2 == i)
                    cout << "▐"; // player 2
                else if(player2X == j && player2Y + 3 == i)
                    cout << "▐"; // player 2
                // --

                else
                    cout << " ";
                

                if(j == _width - 1)
                    cout << "▐";
            }
            cout << endl;
        }

        for(int i = 0; i < _width + 2; i++) 
            cout << "▀";
        cout << endl;

        // scores 
        cout << "Score 1 " << _score1 << "\nScore 2 " << _score2 << endl; 
    }

    void input()
    {
        ball->move();
        
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();

        if(_kbhit())
        {
            char current = getchar();
            if(current == move_up1)
                if(player1Y > 0)
                    player1->moveUp();
            if(current == move_up2)
                if(player1Y > 0)
                    player2->moveUp();
            if(current == move_down1)
                if(player1Y + 4 < _height)
                    player1->moveDown();
            if(current == move_down2)
                if(player2Y + 4 < _height)
                    player2->moveDown();

            if(ball->getDirection() == STOP)
                ball->randomDirection();

            if(current == 'q')
                quit = true;
        }
    }

    void logic()
    {
        int ballX = ball->getX();
        int ballY = ball->getY();
        int player1X = player1->getX();
        int player1Y = player1->getY();
        int player2X = player2->getX();
        int player2Y = player2->getY();

        // left paddle
        for(int i = 0; i < 4; i++)
            if(ballX == player1X + 1)
                if(ballY == player1Y + i)
                    ball->changeDirection((Direction)(rand()%3 + 4)); // right, upright or downright

        // right paddle
        for(int i = 0; i < 4; i++)
        if(ballX == player2X - 1)
            if(ballY == player2Y + i)
                ball->changeDirection((Direction)(rand()%3 + 1)); // left, upleft or downleft

        // bottom wall
        if(ballY == _height - 1) // hit the wall - dont get into it
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

        // top wall
        if(ballY == 0) 
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        
        // right wall 
        if(ballX == _width - 1)
            scoreUp(player1);
        
        // left wall
        if(ballX == 0)
            scoreUp(player2); // não está funcionando
    }

    void run()
    {
        while (!quit)
        {
            draw();
            input();
            logic();
            usleep(30000);
        }
        
    }
};

int main()
{
    GameManager game(40, 20);
    game.run();

    return 0;
}