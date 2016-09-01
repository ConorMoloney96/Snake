#include <conio.h> //includes the _kbhit() and _getch() functions
#include <windows.h> //includes the sleep() function
#include <iostream>

using namespace std;

bool gameOver;   //determines if the game is over
int width =30, height=20; //sets the width and height of the game grid
int x, y; //represents the position of the head of the snake on the x axis and y axis of the game grid
int fruitX, fruitY; //position of the fruit on the x axis and the y axis of the grid
enum direction {STOP=0, LEFT, RIGHT, UP, DOWN}; //creates a new variable direction whose values can be set to those listed
direction dir;
int tailX[100], tailY[100]; //tailX array contains the location on the x axis of each segment of the snake's tail, tailY contains the locations on the Y-axis for the corresponding segment
int prevX, prevY, prev2X, prev2Y; //used for storing values while the position of the tale is updated
int score;               //keeps the games score
int tailLength;
bool print;
string message;

void setup()
{
    gameOver=false;
    dir = STOP;
    x = width/2;   //starting position of the head of the snake is halfway across the grid's x axis
    y = height/2;
    fruitX = rand()%width;
    fruitY = rand()%height;
}

void draw()
{

    system("cls"); //clears the screen
    for(int i=0;i<width+1;i++ )
    {
        cout<<"#";
    }
    cout<<"#"<<endl;
    for(int i=0;i<height;i++ )    //iterates through each row of the grid
    {
        for(int j=0;j<width;j++ )   //goes through each column of the grid within each row
        {
            if(j==0)
                cout<<"#";
            if(i==y&&j==x)
                cout<<"O";
            else if(i==fruitY&&j==fruitX) //if the current location is not equivalent to the position of the head of the snake but is equivalent to the fruit
                cout<<"F";

            else
            {
            print = false;
            for(int k=0;k<tailLength;k++)    //prints the tail
            {

                if(i==tailY[k]&&j==tailX[k])   //goes through each tale segment position stored in the arrays to check if they match the current position
                {
                    cout<<"o";
                    print = true;

                }
            }
            if(!print)
                cout<<" ";

            }

            if(j==width-1)       //prints the right wall of the grid
                cout<<"#";

        }
        cout<<" "<<endl;         //moves onto the next row to be printed

    }
    for(int i=0;i<width+2;i++)     //prints the bottom border line of the grid
        cout<<"#";

}

void input()
{
    if(_kbhit()) //if a key on the keyboard was pressed and an input value was stored in the buffer
    {
        switch(_getch() ) //different actions are performed based on what value is retrieved from the buffer by the _getch() function
        {
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'a':
            dir=LEFT;
            break;
        case 'q':           //press q to quit the game
            gameOver=true;
            message = "You have quit the game.";
            break;

        }
    }

}

void logic()
{
    prevX= tailX[0];
    prevY = tailY[0];
    tailX[0]=x;
    //the x axis position of the most advanced segment of the tail is now set to the current x position of the head (same will be applied to the positions on the y axis below).
    //This is done as the most advanced tail segment moves into the current position of the head regardless of what direction the head moves.
    tailY[0]=y;

    for(int i=1;i<tailLength;i++)
    {
         prev2X=prevX; //prevX, which contains the value from the previous index position, is now stored to prev2X to free prevX up.
         prev2Y=prevY;
         prevX=tailX[i]; //prevX is now set to contain the value of the current index position in the tail array. This value will be used in the next iteration.
         prevY=tailY[i];
         tailX[i] =prev2X; //the value stored in prev2X (transferred over earlier from prevX which was set to contain the value from the previous index position of the tail array) is now stored to the current index position of the tail array.
         tailY[i] = prev2Y;
    }

    //the purpose of the above tail section of the logic function is to move the most advanced section of the tail (i.e. the tail segment
    //whose location is stored at tailX[0] on the x-axis and tailY[0] on the y-axis to the current location of the snakes head and for each segment of
    //the snake to move forward one place to the location previously occupied by the segment ahead of it.

    switch(dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case RIGHT:
        x++;
        break;
    case LEFT:
        x--;
        break;
    }

    if(x==width||y==height||x<0||y<0)    //ends the game if the head of the snake goes out of bounds
    {
        gameOver=true;
        message = "You ran out of bounds.";
    }

    for(int i=0;i<tailLength;i++)
    {
        if(x==tailX[i]&&y==tailY[i])
        {
            gameOver=true;
            message="You ran into your tail.";
        }
    }
    if(x==fruitX && y==fruitY)         //if the head of the snake makes contact with the fruit
    {
        tailLength++;
        score+=10;
        fruitX = rand()%width;
        fruitY = rand()% height;

    }

}

int main()
{
    setup();
    while(!gameOver)
    {
        draw();   //draws the game grid with everything updated to it's current position
        input();  //accepts the users input i.e. which direction they want the snake to go
        logic();  //performs the operations indicated by the users input
        Sleep(200);
    }
    cout<<" "<<endl;
    cout<<"Game Over"<<endl;
    cout<<message<<endl;
    cout<<"Score: "<<score;


    return 0;
}
