#include "special.h"

Special::Special(QGraphicsPixmapItem *sp)
{
    role = sp;
    l_OR_r = "r";
    corner_X << 227.5 << 317.5 << 407.5 << 580 << 670 << 760 //row1
             << 407.5 << 452.5 << 535 << 580                 //row2
             << 317.5 << 362.5 << 625 << 670                 //row4
             << 362.5 << 452.5 << 490 << 535 << 625          //row5
             << 227.5 << 362.5 << 625 << 760                 //row6
             << 452.5 << 490 << 535                          //row7
             << 317.5 << 362.5 << 625 << 670                 //row8
             << 227.5 << 317.5 << 490 << 670 << 760          //row9
             << 407.5 << 490 << 580                          //row10
             << 317.5 << 362.5 << 407.5 << 580 << 625 << 670 //row11
             << 227.5 << 362.5 << 490 << 625 << 760;         //row13

    corner_Y << 79.5 << 79.5 << 79.5 << 79.5 << 79.5 << 79.5 //row1
             << 132  << 132 << 132 << 132                    //row2
             << 214.5 << 214.5 << 214.5 << 214.5             //row4
             << 259.5 << 259.5 << 259.5 << 259.5 << 259.5    //row5
             << 304.5 << 304.5 << 304.5 << 304.5             //row6
             << 349.5 << 349.5 << 349.5                      //row7
             << 387 << 387 << 387 << 387                     //row8
             << 432 << 432 << 432 << 432 << 432              //row9
             << 477 << 477 << 477                            //row10
             << 522 << 522 << 522 << 522 << 522 << 522       //row11
             << 612 << 612 << 612 << 612 << 612;             //row13
}

Special::~Special() {}

void Special::ChangePixmap()
{
    if(Game == 0) return;

    if(l_OR_r == "l")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/l_special.png").scaled(QSize(40, 40)));
        return;
    }

    if(l_OR_r == "r")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/r_special.png").scaled(QSize(40, 40)));
        return;
    }
}

void Special::moving()
{
    if(Game == 0) return;

    X_cur = role->x();
    Y_cur = role->y();

    int i, j, k;
    for(i = 0; i < 49; ++i) //There are 49 corners
    {
        if(X_cur == corner_X.at(i) && Y_cur == corner_Y.at(i))
        {
            j = ChooseDirect(i);
            if(j == 0)
            {
                if(option[1] == 1)
                {
                    direction = "down";
                    break;
                }

                if(option[3] == 1)
                {
                    direction = "right";
                    break;
                }

                for(;;)
                {
                    k = qrand() % 4;

                    if(option[k] == 1)
                    {
                        if(k == 0)
                        {
                            direction = "up";
                            break;
                        }

                        if(k == 1)
                        {
                            direction = "down";
                            break;
                        }

                        if(k == 2)
                        {
                            direction = "left";
                            break;
                        }

                        if(k == 3)
                        {
                            direction = "right";
                            break;
                        }
                    }
                }
            }

            break;
        }
    }

    if(direction == "up")
    {
        role->setY(Y_cur - 7.5); //S_Move == 7.5
        return;
    }

    if(direction == "down")
    {
        role->setY(Y_cur + 7.5); //S_Move == 7.5
        return;
    }

    if(direction == "left")
    {
        role->setX(X_cur - 7.5); //S_Move == 7.5
        l_OR_r = "l";
        ChangePixmap();
        return;
    }

    if(direction == "right")
    {
        role->setX(X_cur + 7.5); //S_Move == 7.5
        l_OR_r = "r";
        ChangePixmap();
        return;
    }
}
