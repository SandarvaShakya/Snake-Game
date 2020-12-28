//SNAKE GAME//

#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>


void gameOver(int);
void gameStart();
int menu();

int main()
{
    int check;

    printf("WELCOME TO OUR SNAKE GAME!!\n\n");
    check = menu();

    //TO START GAME//////IF ELSE PART IN CONSOLE//
    if(check == 1)
    {
        gameStart();
    }
    else
    {
        printf("THANK YOU!!!");
    }

    getch();
    closegraph();


    return 0;
}

//ACTUAL GAME//
void gameStart()
{
    int endcheck;

    initwindow(1000,800,"Snake");


    //TO GET MAXIMUM COORDINATES//
    int maxX = getmaxx();
    int maxY = getmaxy();

    //TO GET MIDPOINT COORDINATES//
    int midX = maxX/2;
    int midY = maxY/2;

    //SNAKES COORDINATES//
    int x[500],y[500];
    int length = 10;

    x[0] = midX;
    y[0] = midY;

    //MOVEMENT COORDINATES//
    int constantDirection = 2;

    int xCoordinateOfFood = midX - 100;
    int yCoordinateOfFood = midY - 100;

    int direction;

    //SCORE//
    int score = 0;
    int check;


    while(1)
    {
        //BORDERS//
        setfillstyle(SOLID_FILL,GREEN);
        bar(0,0,maxX,10);
        bar(0,0,10,maxY);
        bar(0,maxY,maxX,maxY-10);
        bar(maxX,maxY,maxX-10,0);

        //FOOD
        srand(time(NULL));

        if(x[0] == xCoordinateOfFood && y[0] == yCoordinateOfFood)
        {
            length += 1;
            score += 10;
            setfillstyle(1,BLACK);
            bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10);
            do
            {
                xCoordinateOfFood = 1 + rand() % 1000;
                yCoordinateOfFood = 1 + rand() % 800;
            }while(getpixel(xCoordinateOfFood,yCoordinateOfFood) !=0 && xCoordinateOfFood > 10 && yCoordinateOfFood > 10);

            xCoordinateOfFood = xCoordinateOfFood/10 - 1;
            xCoordinateOfFood = xCoordinateOfFood*10 - 1;
            yCoordinateOfFood = yCoordinateOfFood/10 - 1;
            yCoordinateOfFood = yCoordinateOfFood*10 - 1;
        }
        setfillstyle(1,CYAN);
        bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10);
        setfillstyle(1,GREEN);


        //MOVEMENT//
        if(GetAsyncKeyState(VK_RIGHT))
        {
            direction = 1;
        }else if(GetAsyncKeyState(VK_LEFT))
        {
            direction = 2;
        }else if(GetAsyncKeyState(VK_UP))
        {
            direction = 3;
        }else if(GetAsyncKeyState(VK_DOWN))
        {
            direction = 4;
        }else
        {
            direction = 0;
        }

        switch(direction)
        {
        case 0 :
            if(constantDirection == 1)
            {
                x[0] += 10;
            }else if(constantDirection == 2)
            {
                x[0] -= 10;
            }else if(constantDirection == 3)
            {
                y[0] -= 10;
            }else if(constantDirection == 4)
            {
                y[0] += 10;
            }else
            {
                direction = 0;
            }
            break;
        case 1 :
            x[0] += 10;
            constantDirection = 1;
            break;
        case 2 :
            x[0] -=10;
            constantDirection = 2;
            break;
        case 3 :
            y[0] -= 10;
            constantDirection = 3;
            break;
        case 4 :
            y[0] += 10;
            constantDirection = 4;
            break;
        }

        //SNAKE//
        for(int i = 0; i < length; i++)
        {
            bar(x[i],y[i],x[i]+10,y[i]+10);
        }

        for(int i = 499; i > 0; i--)
        {
            x[i] = x[i-1];
            y[i] = y[i-1];
        }

        delay(100);
        cleardevice();
        printf("%d   %d   %d   %d  %d  \n",x[0],y[0],xCoordinateOfFood,yCoordinateOfFood,length);

        if(x[0] >= 1000 || x[0] <= 0 || y[0] >= 800 || y[0] <= 0)
        {
            gameOver(score);
            break;
        }

    }

    getch();
    closegraph();

}

//CONSOLE//
int menu()
{
    char yesno;

    printf("Press 'Y' for yes and 'N' for no\n");
    printf("Start game!!\n\n");
    scanf(" %c",&yesno);

    switch(yesno)
    {
    case 'Y':
    case 'y':
        return 1;

    case 'N':
    case 'n':
        return 0;
    }
}

void gameOver(int score)
{
    int maxX = getmaxx();
    int maxY = getmaxy();

    int midX = maxX/2;
    int midY = maxY/2;

    char a[200];

    delay(100);
    cleardevice();

    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,8);
    int width = textwidth("GAME OVER!!!");
    int height = textheight("GAME OVER!!!");
    int width1 = textwidth("YOUR SCORE IS: ");
    int height1 = textheight("YOUR SCORE IS: ");

    setcolor(CYAN);
    outtextxy(midX-width/2,midY-height/2,"GAME OVER!!!");
    delay(300);

    setcolor(RED);
    outtextxy(midX-width/2,(midY-100)-height/2,"GAME OVER!!!");

    sprintf(a,"YOUR SCORE IS: %d",score);
    outtextxy(midX-width1/2,(midY+100)-height1/2,a);

    int width2 = textwidth("PLAY AGAIN!!!");
    int height2 = textheight("PLAY AGAIN!!!");

    setcolor(WHITE);
    rectangle(midX-width2/2,(midY+200)-height2/2,(midX-width2/2)+500,(midY+200-height2/2)+100);
    setfillstyle(1,BLACK);
    floodfill(1+midX-width2/2,1+(midY+200)-height2/2,WHITE);

    setcolor(CYAN);
    outtextxy(35+midX-width2/2,10+(midY+200)-height2/2,"PLAY AGAIN!!!");

    system("cls");

    printf("THANK YOU!!");

    //PLAY AGAIN//
    int cursorX,cursorY;

    POINT cursorPosition;

    while(1)
    {
        GetCursorPos(&cursorPosition);
        cursorX = cursorPosition.x;
        cursorY = cursorPosition.y;

        if(cursorX >= midX-width2/2 && cursorX <= (midX-width2/2)+500 && cursorY >= (midY+200)-height2/2 && cursorY <= (midY+200-height2/2)+100)
        {
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                gameStart();
                break;
            }
        }
    }
}





