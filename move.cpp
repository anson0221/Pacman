#include "move.h"
#include <QTime>


Move::Move()
{
    x_Orbit << 227.5 << 272.5 << 317.5 << 362.5 << 407.5 << 452.5 << 490 << 535 << 580 << 625 << 670 << 715 << 760;
    y_Orbit << 79.5 << 132 << 169.5 << 214.5 << 259.5 << 304.5 << 349.5 << 387 << 432 << 477 << 522 << 557 << 612;
}


void Move::setGame_0()
{
    Game = 0;
}


void Move::setGame_1()
{
    Game = 1;
}


void Move::setDirect(QString text)
{
    pre_direct = direction;
    direction = text;
}






Pacman::Pacman(QGraphicsPixmapItem *pcm, QGraphicsPixmapItem *obs)
{
    role = pcm;
    obstacle = obs;
    direction = "down";
    X_pre = 490;
    Y_pre = 432;
}


Pacman::~Pacman() {}


void Pacman::setMode(QString ability)
{
    if(Game == 0) return;

    Mode = ability;
}


void Pacman::reset_key()
{
    if(Game == 0) return;

    up_key = 1;
    down_key = 1;
    left_key = 1;
    right_key = 1;
}


void Pacman::adjustCoord(int k) // k == 1 -> to change X coordinate <-> k == 2 -> to change Y coordinate
{
    if(Game == 0) return;

    float x = role->x();
    float y = role->y();

    if(k == 1)
    {
        for(int i = 0; i < 13; ++i)
        {
            if(qAbs(x - x_Orbit.at(i)) < 25)
            {
                role->setX(x_Orbit.at(i));
                break;
            }
        }
    }

    if(k == 2)
    {
        for (int i = 0; i < 13; ++i)
        {
            if(qAbs(y - y_Orbit.at(i)) < 25)
            {
                role->setY(y_Orbit.at(i));
                break;
            }
        }
    }
}


void Pacman::setMobility()
{
    if(Game == 0) return;

    if(Mobility == 0)
    {
        Mobility = 1;
        return;
    }

    if(Mobility == 1)
    {
        Mobility = 0;
        return;
    }
}


QString Pacman::getMode()
{
    if(Game == 1) return Mode;
}


void Pacman::ChangePixmap()
{
    if(Game == 0) return;

    if(Mobility == 0) return;

    if(pix == 0)
    {
        pix = 1;

        if(direction == "up")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/u_Pacman_cl.png").scaled(QSize(40, 40)));
            return;
        }

        if(direction == "down")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/d_Pacman_cl.png").scaled(QSize(40, 40)));
            return;
        }

        if(direction == "left")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/l_Pacman_cl.png").scaled(QSize(40, 40)));
            return;
        }

        if(direction == "right")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/r_Pacman_cl.png").scaled(QSize(40, 40)));
            return;
        }

    } else { //pix == 1

        pix = 0;

        if(direction == "up")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/u_Pacman_op.png").scaled(QSize(40, 40)));
            return;
        }

        if(direction == "down")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/d_Pacman_op.png").scaled(QSize(40, 40)));
            return;
        }

        if(direction == "left")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/l_Pacman_op.png").scaled(QSize(40, 40)));
            return;
        }

        if(direction == "right")
        {
            role->setPixmap(QPixmap(":/new/prefix1/material/r_Pacman_op.png").scaled(QSize(40, 40)));
            return;
        }
    }
}


void Pacman::moving()
{
    if(Game == 0) return;

    if(Mobility == 0) return;

    X_cur = role->x();
    Y_cur = role->y();

    if(direction != pre_direct && role->collidesWithItem(obstacle) == false)
    {
        reset_key();

        if(direction == "up" && up_key == 1)
        {
            role->setY(Y_cur - S_Move);
            adjustCoord(1);
        }

        if(direction == "down" && down_key == 1)
        {
            role->setY(Y_cur + S_Move);
            adjustCoord(1);
        }

        if(direction == "left" && left_key == 1)
        {
            role->setX(X_cur - S_Move);
            adjustCoord(2);
        }

        if(direction == "right" && right_key == 1)
        {
            role->setX(X_cur + S_Move);
            adjustCoord(2);
        }

        X_pre = X_cur;
        Y_pre = Y_cur;
        pre_direct = direction;
        return;
    }

    if(role->collidesWithItem(obstacle) == true) //Collision
    {
        role->setPos(X_pre, Y_pre);

        if(direction == "up")
        {
            up_key = 0;
            return;
        }
        if(direction == "down")
        {
            down_key = 0;
            return;
        }
        if(direction == "left")
        {
            left_key = 0;
            return;
        }
        if(direction == "right")
        {
            right_key = 0;
            return;
        }
    }

    if(role->collidesWithItem(obstacle) == false)//no Collision
    {
        X_pre = X_cur;
        Y_pre = Y_cur;

        pre_direct = direction;

        if(direction == "up" && up_key == 1)
        {
            role->setY(Y_cur - S_Move);
            //qDebug() << "(" << role->x() << ", " << role->y() << ")";
            adjustCoord(1);
            return;
        }

        if(direction == "down" && down_key == 1)
        {
            role->setY(Y_cur + S_Move);
            //qDebug() << "(" << role->x() << ", " << role->y() << ")";
            adjustCoord(1);
            return;
        }

        if(direction == "left" && left_key == 1)
        {
            role->setX(X_cur - S_Move);
            //qDebug() << "(" << role->x() << ", " << role->y() << ")";
            adjustCoord(2);
            return;
        }

        if(direction == "right" && right_key == 1)
        {
            role->setX(X_cur + S_Move);
            //qDebug() << "(" << role->x() << ", " << role->y() << ")";
            adjustCoord(2);
            return;
        }
    }
}






G_Ghost::G_Ghost(QGraphicsPixmapItem *GG) //corner : 49 in total
{
    role = GG;
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

G_Ghost::G_Ghost() {}

G_Ghost::~G_Ghost() {}

void G_Ghost::moving()
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

void G_Ghost::ChangePixmap()
{
    if(Game == 0) return;

    if(l_OR_r == "l")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/lG_ghost.png").scaled(QSize(40, 40)));
        return;
    }

    if(l_OR_r == "r")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/rG_ghost.png").scaled(QSize(40, 40)));
        return;
    }
}

QString G_Ghost::getDirection()
{
    return direction;
}

int G_Ghost::ChooseDirect(int k) //(return 0 -> not yet) <-> (return 1 -> has already been decided)
{
    if(Game == 0) return 2;

    if(k == 0)
    {
        if(direction == "up") direction = "right";
        if(direction == "left") direction = "down";
        return 1;
    }

    if(k == 1)
    {
        if(direction == "left")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "right")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 2)
    {
        if(direction == "right") direction = "down";
        if(direction == "up") direction = "left";
        return 1;
    }

    if(k == 3)
    {
        if(direction == "left") direction = "down";
        if(direction == "up") direction = "right";
        return 1;
    }

    if(k == 4)
    {
        if(direction == "left")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "right")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 5)
    {
        if(direction == "right") direction = "down";
        if(direction == "up") direction = "left";
        return 1;
    }

    if(k == 6)
    {
        if(direction == "left") direction = "up";
        if(direction == "down") direction = "right";
        return 1;
    }

    if(k == 7)
    {
        if(direction == "up") direction = "left";
        if(direction == "right") direction = "down";
        return 1;
    }

    if(k == 8)
    {
        if(direction == "up") direction = "right";
        if(direction == "left") direction = "down";
        return 1;
    }

    if(k == 9)
    {
        if(direction == "right") direction = "up";
        if(direction == "down") direction = "left";
        return 1;
    }

    if(k == 10)
    {
        if(direction == "down") direction = "right";
        if(direction == "left") direction = "up";
        return 1;
    }

    if(k == 11)
    {
        if(direction == "up") direction = "left";
        if(direction == "right") direction = "down";
        return 1;
    }

    if(k == 12)
    {
        if(direction == "up") direction = "right";
        if(direction == "left") direction = "down";
        return 1;
    }

    if(k == 13)
    {
        if(direction == "down") direction = "left";
        if(direction == "right") direction = "up";
        return 1;
    }

    if(k == 14)
    {
        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 15)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 16)
    {
        if(direction == "right")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 17)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 18)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 19)
    {
        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 20)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 21)
    {
        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 22)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 23)
    {
        if(direction == "left") direction = "right";
        return 1;
    }

    if(k == 24) //center of the map
    {
        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }

        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 25)
    {
        if(direction == "right") direction = "left";
        return 1;
    }

    if(k == 26)
    {
        if(direction == "up") direction = "right";
        if(direction == "left") direction = "down";
        return 1;
    }

    if(k == 27)
    {
        if(direction == "right") direction = "up";
        if(direction == "down") direction = "left";
        return 1;
    }

    if(k == 28)
    {
        if(direction == "down") direction = "right";
        if(direction == "left") direction = "up";
        return 1;
    }

    if(k == 29)
    {
        if(direction == "up") direction = "left";
        if(direction == "right") direction = "down";
        return 1;
    }

    if(k == 30)
    {
        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 31)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 32)
    {
        if(direction == "up") direction = "down";
        return 1;
    }
    if(k == 33)
    {
        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 34)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }
    }

    if(k == 35)
    {
        if(direction == "up") direction = "right";
        if(direction == "left") direction = "down";
        return 1;
    }

    if(k == 36)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 37)
    {
        if(direction == "right") direction = "down";
        if(direction == "up") direction = "left";
        return 1;
    }

    if(k == 38)
    {
        if(direction == "down") direction = "right";
        if(direction == "left") direction = "up";
        return 1;
    }

    if(k == 39)
    {
        if(direction == "right")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 40)
    {
        if(direction == "right") direction = "up";
        if(direction == "down") direction = "left";
        return 1;
    }

    if(k == 41)
    {
        if(direction == "down") direction = "right";
        if(direction == "left") direction = "up";
        return 1;
    }

    if(k == 42)
    {
        if(direction == "right")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 0;
            option[1] = 1;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "up")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 43)
    {
        if(direction == "right") direction = "up";
        if(direction == "down") direction = "left";
        return 1;
    }

    if(k == 44)
    {
        if(direction == "left") direction = "up";
        if(direction == "down") direction = "right";
        return 1;
    }

    if(k == 45)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 46)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 47)
    {
        if(direction == "right")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 0;
            option[3] = 1;
            return 0;
        }

        if(direction == "left")
        {
            option[0] = 1;
            option[1] = 0;
            option[2] = 1;
            option[3] = 0;
            return 0;
        }

        if(direction == "down")
        {
            option[0] = 0;
            option[1] = 0;
            option[2] = 1;
            option[3] = 1;
            return 0;
        }
    }

    if(k == 48)
    {
        if(direction == "right") direction = "up";
        if(direction == "down") direction = "left";
        return 1;
    }

}






W_Ghost::W_Ghost(QGraphicsPixmapItem *WW)
{
    role = WW;
    l_OR_r = "l";
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

W_Ghost::~W_Ghost() {}

void W_Ghost::ChangePixmap()
{
    if(Game == 0) return;

    if(l_OR_r == "l")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/lW_ghost.png").scaled(QSize(40, 40)));
        return;
    }

    if(l_OR_r == "r")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/rW_ghost.png").scaled(QSize(40, 40)));
        return;
    }
}

void W_Ghost::moving()
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
                if(option[0] == 1)
                {
                    direction = "up";
                    break;
                }

                if(option[2] == 1)
                {
                    direction = "left";
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






Y_Ghost::Y_Ghost(QGraphicsPixmapItem *YY, G_Ghost *gre, W_Ghost *whi, Skeleton *ske, int i)
{
    role = YY;
    green = gre;
    white = whi;
    skeleton = ske;

    if(i == 0 || i == 1) l_OR_r = "r";
    if(i == 2 || i == 3) l_OR_r = "l";

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

Y_Ghost::~Y_Ghost() {}

void Y_Ghost::ChangePixmap()
{
    if(Game == 0) return;

    if(l_OR_r == "l")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/lY_ghost.png").scaled(QSize(40, 40)));
        return;
    }

    if(l_OR_r == "r")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/rY_ghost.png").scaled(QSize(40, 40)));
        return;
    }
}

void Y_Ghost::moving()
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
                if(Y_cur < white->Y_cur && option[1] == 1)
                {
                    direction = "down";
                    break;
                }

                if(X_cur > skeleton->X_cur && option[2] == 1)
                {
                    direction = "left";
                    break;
                }

                if(X_cur < green->X_cur && option[3] == 1)
                {
                    direction = "right";
                    break;
                }

                if(Y_cur > skeleton->Y_cur && option[0] == 1)
                {
                    direction = "up";
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






Skeleton::Skeleton(QGraphicsPixmapItem *SS, Pacman *pac)
{
    role = SS;
    pacman = pac;
    l_OR_r = "l";

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

Skeleton::~Skeleton() {}

void Skeleton::ChangePixmap()
{
    if(Game == 0) return;

    if(l_OR_r == "l")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/skeleton_1.png").scaled(QSize(40, 40)));
        return;
    }

    if(l_OR_r == "r")
    {
        role->setPixmap(QPixmap(":/new/prefix1/material/skeleton_2.png").scaled(QSize(40, 40)));
        return;
    }
}

void Skeleton::moving()
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
                if(X_cur < pacman->X_cur && option[3] == 1)
                {
                    direction = "right";
                    break;
                }

                if(X_cur > pacman->X_cur && option[2] == 1)
                {
                    direction = "left";
                    break;
                }

                if(Y_cur < pacman->Y_cur && option[1] == 1)
                {
                    direction = "down";
                    break;
                }

                if(Y_cur > pacman->Y_cur && option[0] == 1)
                {
                    direction = "up";
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



