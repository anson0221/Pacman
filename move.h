#ifndef MOVE_H
#define MOVE_H

#include <QGraphicsPixmapItem>
#include <QList>
#include <QString>
#include <QTimer>
#include <QDebug>

//Base Class
class Move : public QObject
{
    Q_OBJECT

public:
    Move(); //to set orbit
    ~Move() = default; //Fuck you

    void setGame_0();
    void setGame_1();
    void setDirect(QString text);

    float X_cur, Y_cur;
    float X_pre, Y_pre;

public slots:
    virtual void moving() = 0;
    virtual void ChangePixmap() = 0;

protected:
    QGraphicsPixmapItem *role;
    QString direction, pre_direct;
    QGraphicsPixmapItem *obstacle;
    QList<float> x_Orbit, y_Orbit; //orbit for the map
    int Game = 0; //0 -> stop  <->  1 -> start
    float S_Move = 7.5;
};


//Pacman
class Pacman : public Move
{
    Q_OBJECT

public:
    Pacman(QGraphicsPixmapItem *pcm, QGraphicsPixmapItem *obs); //ptr of pacman & obstacle(wall)
    ~Pacman();

    void setMode(QString ability);
    void reset_key();
    void adjustCoord(int k);
    void setMobility();
    QString getMode();


    int up_key = 1, down_key = 1, left_key = 1, right_key = 1;

public slots:
    void moving();
    void ChangePixmap();

private:
    QString Mode = "N"; //"N" normal or "S" super
    int Mobility = 1; //0 -> immobile <-> 1 -> moving
    int pix = 0; //for changing pixmap of Pacman
};


//Ghost_Green
class G_Ghost : public Move
{
    Q_OBJECT

public:
    G_Ghost(QGraphicsPixmapItem *GG);
    G_Ghost(); //defult constructor for implementation of ininheritance
    ~G_Ghost();

    virtual void ChangePixmap();
    QString getDirection();

public slots :
    virtual void moving();
    int ChooseDirect(int k);

protected:
    QString l_OR_r;
    QList<float> corner_X, corner_Y;
    int option[4]; //Which direction that ghost can choose(0 -> up; 1 -> down; 2 -> left; 3 -> right)
};


//Ghost_White
class W_Ghost : public G_Ghost
{
    Q_OBJECT

public:
    W_Ghost(QGraphicsPixmapItem *WW);
    ~W_Ghost();

    void ChangePixmap();

public slots:
    void moving();
};


//Skeleton
class Skeleton : public G_Ghost
{
    Q_OBJECT

public:
    Skeleton(QGraphicsPixmapItem *SS, Pacman *pac);
    ~Skeleton();

    void ChangePixmap();

public slots:
    void moving();

private:
    Pacman *pacman;
};


//Ghost_Yellow
class Y_Ghost : public G_Ghost
{
    Q_OBJECT

public:
    Y_Ghost(QGraphicsPixmapItem *YY, G_Ghost *gre, W_Ghost *whi, Skeleton *ske, int i);
    ~Y_Ghost();

    void ChangePixmap();

public slots:
    void moving();

private:
    G_Ghost *green;
    W_Ghost *white;
    Skeleton *skeleton;
};




#endif // MOVE_H
