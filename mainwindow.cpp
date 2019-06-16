#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "move.h"
#include <QKeyEvent>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->sc = new QGraphicsScene(0, 0, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    ui->graphicsView->setScene(sc);

    this->grabKeyboard(); //to acquire the KeyPressEvent

    //to set QPushButton : "go"
    go = ui->go;
    sc->addWidget(go);
    connect(go, SIGNAL(clicked(bool)), this, SLOT(START()));

    //to set QPushButton : "stop"
    stop = ui->stop;
    sc->addWidget(stop);
    connect(stop, SIGNAL(clicked(bool)), this, SLOT(STOP()));

    //to set QPushButton : "cheat"
    cheat = ui->cheat;
    sc->addWidget(cheat);
    connect(cheat, SIGNAL(clicked(bool)), this, SLOT(Gh_Stop_5_Sec_1()));

    map_maze = sc->addPixmap(QPixmap(":/new/prefix1/material/Map.jpeg"));
    wall = sc->addPixmap(QPixmap(":/new/prefix1/material/Wall_Map.png"));

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())); //for movement of ghost

    point = new QGraphicsTextItem();
    sc->addItem(point);
    point->setPos(20,20);
    point->setDefaultTextColor(Qt::white);
    point->setPlainText(QString("%0").arg(score));

    //to initialize Pacman
    pac = new QGraphicsPixmapItem();
    sc->addItem(pac);
    pac->setPos(490, 432);
    pac->setPixmap(QPixmap(":/new/prefix1/material/d_Pacman_op.png").scaled(QSize(40, 40)));

    //to initialize G_Ghost
    G_ = new QGraphicsPixmapItem();
    sc->addItem(G_);
    G_->setPos(452.5, 349.5);
    G_->setPixmap(QPixmap(":/new/prefix1/material/rG_ghost.png").scaled(QSize(40, 40)));

    //to initialize W_Ghost
    W_ = new QGraphicsPixmapItem();
    sc->addItem(W_);
    W_->setPos(535, 349.5);
    W_->setPixmap(QPixmap(":/new/prefix1/material/lW_ghost.png").scaled(QSize(40, 40)));

    //to initialize Y_Ghost randomly
    int i = qrand() % 4;
    Y_ = new QGraphicsPixmapItem();
    sc->addItem(Y_);
    if(i == 0 || i == 1) Y_->setPixmap(QPixmap(":/new/prefix1/material/rY_ghost.png").scaled(QSize(40, 40)));
    if(i == 2 || i == 3) Y_->setPixmap(QPixmap(":/new/prefix1/material/lY_ghost.png").scaled(QSize(40, 40)));
    if(i == 0) Y_->setPos(227.5, 79.5);
    if(i == 1) Y_->setPos(227.5, 612);
    if(i == 2) Y_->setPos(760, 79.5);
    if(i == 3) Y_->setPos(760, 612);

    //to initialize Skeleton
    Sk_ = new QGraphicsPixmapItem();
    sc->addItem(Sk_);
    Sk_->setPos(490, 349.5);
    Sk_->setPixmap(QPixmap(":/new/prefix1/material/skeleton_1.png").scaled(QSize(40, 40)));

    //to initialize Special
    Sp_ = new QGraphicsPixmapItem();
    sc->addItem(Sp_);
    Sp_->setPos(490, 259.5);
    Sp_->setPixmap(QPixmap(":/new/prefix1/material/r_special.png").scaled(QSize(40, 40)));


    p = new Pacman(pac, wall);


    //let Pacman be able to open/close its mouth
    timer_1 = new QTimer(this);
    connect(timer_1, SIGNAL(timeout()), p, SLOT(ChangePixmap()));
    timer_1->start(300);

    //to control the velocity of Pacman with timer_2
    timer_2 = new QTimer(this);
    Direct_ = "down";
    p->setDirect(Direct_);
    connect(timer_2, SIGNAL(timeout()), p, SLOT(moving()));
    connect(timer_2, SIGNAL(timeout()), this, SLOT(GameJudge())); //Judge "Game Over"
    connect(timer_2, SIGNAL(timeout()), this, SLOT(ScoreCount())); //Count the score
    connect(timer_2, SIGNAL(timeout()), this, SLOT(SuperJudge()));
    timer_2->start(T_Move);


    g = new G_Ghost(G_);
    w = new W_Ghost(W_);
    s = new Skeleton(Sk_, p);
    y = new Y_Ghost(Y_, g, w, s, i);
    sp = new Special(Sp_);


    //let Ghost can keep moving
    timer_3 = new QTimer(this);
    Direct_ = "right";

    g->setDirect(Direct_);
    Direct_ = "left";

    w->setDirect(Direct_);

    if(i == 0 || i == 1)
    {
        Direct_ = "right";
        y->setDirect(Direct_);
    }
    if(i == 2 ||i == 3)
    {
        Direct_ = "left";
        y->setDirect(Direct_);
    }

    Direct_ = "left";
    s->setDirect(Direct_);

    Direct_ = "right";
    sp->setDirect(Direct_);

    connect(timer_3, SIGNAL(timeout()), g, SLOT(moving()));
    connect(timer_3, SIGNAL(timeout()), w, SLOT(moving()));
    connect(timer_3, SIGNAL(timeout()), y, SLOT(moving()));
    connect(timer_3, SIGNAL(timeout()), s, SLOT(moving()));
    connect(timer_3, SIGNAL(timeout()), sp, SLOT(moving()));
    timer_3->start(T_Ghost);


    XXX_cor << 227.5 << 272.5 << 317.5 << 362.5 << 407.5 << 452.5 << 490 << 535 << 580 << 625 << 670 << 715 << 760;
    YYY_cor << 79.5 << 132 << 169.5 << 214.5 << 259.5 << 304.5 << 349.5 << 387 << 432 << 477 << 522 << 557 << 612;


    //to initialize "pill"
    pill = new QGraphicsPixmapItem();
    sc->addItem(pill);
    pill->setZValue(50);
    pill->setPos(XXX_cor.at(6) + 7.5, YYY_cor.at(6));
    pill->setPixmap(QPixmap(":/new/prefix1/material/pill.png").scaled(QSize(30, 30)));


    //to initialize "stop_pill"
    stop_pill = new QGraphicsPixmapItem();
    sc->addItem(stop_pill);
    stop_pill->setZValue(50);
    stop_pill->setPixmap(QPixmap(":/new/prefix1/material/stoppill.png").scaled(QSize(30, 30)));
    for(;;)
    {
        stop_pill->setPos(XXX_cor.at(qrand()%13) + 7.5, YYY_cor.at(qrand()%13));
        if(stop_pill->collidesWithItem(wall) == false && stop_pill->collidesWithItem(pill) == false) break;
    }


    //to initialize these dots
    QGraphicsPixmapItem *a;
    for(int j = 0; j < 13; ++j)
    {
        for(int k = 0; k < 13; ++k)
        {
            a = new QGraphicsPixmapItem();
            sc->addItem(a);
            a->setPos(XXX_cor.at(j) + 12.25, YYY_cor.at(k) + 12.25);
            a->setPixmap(QPixmap(":/new/prefix1/material/orange.png").scaled(QSize(12, 12)));

            if(a->collidesWithItem(wall) == false && a->collidesWithItem(pac) == false && a->collidesWithItem(pill) == false) {
                if(a->collidesWithItem(stop_pill) == true) a->setVisible(0);
                a->setZValue(50);
                dots << a;
                DotNum++;

            } else {
                delete a;
            }
        }
    }


    //to setZValue
    map_maze->setZValue(1);
    point->setZValue(300);
    pac->setZValue(200);
    G_->setZValue(100);
    W_->setZValue(100);
    Y_->setZValue(100);
    Sk_->setZValue(100);
    Sp_->setZValue(100);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event) //to control the game
{
    if(event->key() == Qt::Key_G)
    {
        p->setGame_1();
        g->setGame_1();
        w->setGame_1();
        y->setGame_1();
        s->setGame_1();
        sp->setGame_1();
        return;
    }

    if(event->key() == Qt::Key_L)
    {
        if(Lock == 0)
        {
            p->setGame_0();
            g->setGame_0();
            w->setGame_0();
            y->setGame_0();
            s->setGame_0();
            sp->setGame_0();

            Lock = 1;
            return;
        }

        if(Lock == 1)
        {
            p->setGame_1();
            g->setGame_1();
            w->setGame_1();
            y->setGame_1();
            s->setGame_1();
            sp->setGame_1();

            Lock = 0;
            return;
        }
    }

    if(event->key() == Qt::Key_Space) //Space : to stop or start the Pacman
    {
        p->setMobility();
        return;
    }

    if(event->key() == Qt::Key_A) //to accelerate Pacman
    {
        Accelerate();
        return;
    }

    if(event->key() == Qt::Key_S) // to slow down Pacman
    {
        SlowDown();
        return;
    }

    if(event->key() == Qt::Key_Up && p->up_key == 1) //Go Left
    {
        Direct_ = "up";
        p->setDirect(Direct_);
        p->moving();
        return;
    }

    if(event->key() == Qt::Key_Down && p->down_key == 1) //Go Down
    {
        Direct_ = "down";
        p->setDirect(Direct_);
        p->moving();
        return;
    }

    if(event->key() == Qt::Key_Left && p->left_key == 1) //Go Left
    {
        Direct_ = "left";
        p->setDirect(Direct_);
        p->moving();
        return;
    }

    if(event->key() == Qt::Key_Right && p->right_key == 1) //Go Right
    {
        Direct_ = "right";
        p->setDirect(Direct_);
        p->moving();
        return;
    }
}


void MainWindow::Accelerate()
{
    int backup = T_Move;
    T_Move = T_Move - 10;

    if(T_Move < 50) //set upper bound of speed
    {
        T_Move = backup;
        return;
    }
    timer_2->stop();
    timer_2->start(T_Move);
}


void MainWindow::SlowDown()
{
    int backup = T_Move;
    T_Move = T_Move + 10;

    if(T_Move > 110) //set lower bound of speed
    {
        T_Move = backup;
        return;
    }
    timer_2->stop();
    timer_2->start(T_Move);
}


void MainWindow::SuperTimer()
{
    connect(timerMODE, SIGNAL(timeout()), this, SLOT(TurnNormal()));
    timerMODE->start(6000);
    map_maze->setPixmap(QPixmap(":/new/prefix1/material/Map_2.jpeg"));
}


void MainWindow::ResetGame()
{
    //initialize MODE
    MODE = "N";
    p->setMode(MODE);

    //let them be static
    p->setGame_0();
    g->setGame_0();
    w->setGame_0();
    y->setGame_0();
    s->setGame_0();
    sp->setGame_0();

    pac->setPos(490, 432); //to initialize position & pixmap of Pacman
    pac->setPixmap(QPixmap(":/new/prefix1/material/d_Pacman_op.png").scaled(QSize(40, 40)));

    G_->setPos(452.5, 349.5); //to initialize position & pixmap of G_Ghost
    G_->setPixmap(QPixmap(":/new/prefix1/material/rG_ghost.png").scaled(QSize(40, 40)));

    W_->setPos(535, 349.5); //to initialize position & pixmap of W_Ghost
    W_->setPixmap(QPixmap(":/new/prefix1/material/lW_ghost.png").scaled(QSize(40, 40)));

    int i = qrand() % 4; //to initialize position & pixmap of Y_Ghost
    if(i == 0 || i == 1) Y_->setPixmap(QPixmap(":/new/prefix1/material/rY_ghost.png").scaled(QSize(40, 40)));
    if(i == 2 || i == 3) Y_->setPixmap(QPixmap(":/new/prefix1/material/lY_ghost.png").scaled(QSize(40, 40)));
    if(i == 0) Y_->setPos(227.5, 79.5);
    if(i == 1) Y_->setPos(227.5, 612);
    if(i == 2) Y_->setPos(760, 79.5);
    if(i == 3) Y_->setPos(760, 612);

    Sk_->setPos(490, 349.5); //to initialize position & pixmap of Skeleton
    Sk_->setPixmap(QPixmap(":/new/prefix1/material/skeleton_1.png").scaled(QSize(40, 40)));

    Sp_->setPos(490, 259.5); //to initialize position & pixmap of Special
    Sp_->setPixmap(QPixmap(":/new/prefix1/material/r_special.png").scaled(QSize(40, 40)));


    //initialize the direction of every roles
    Direct_ = "down";
    p->setDirect(Direct_);

    timer_2->stop();
    T_Move = 80;
    timer_2->start(T_Move);

    Direct_ = "right";
    g->setDirect(Direct_);

    Direct_ = "left";
    w->setDirect(Direct_);

    if(i == 0 || i == 1)
    {
        Direct_ = "right";
        y->setDirect(Direct_);
    }
    if(i == 2 ||i == 3)
    {
        Direct_ = "left";
        y->setDirect(Direct_);
    }

    Direct_ = "left";
    s->setDirect(Direct_);

    Direct_ = "right";
    sp->setDirect(Direct_);


    //initialize the timer for all Ghosts
    T_Ghost = 80;
    Gh_Stop_5_Sec_2();


    //let "pill" show again
    pill->setVisible(1);


    //let "stop_pill" show again
    stop_pill->setVisible(1);
    for(;;)
    {
        stop_pill->setPos(XXX_cor.at(qrand()%13) + 7.5, YYY_cor.at(qrand()%13));
        if(stop_pill->collidesWithItem(wall) == false && stop_pill->collidesWithItem(pill) == false) break;
    }


    //let the dots show again
    for(int i = 0; i < DotNum; ++i)
    {
        if(dots.at(i)->collidesWithItem(stop_pill) == false)
        {
            dots.at(i)->setVisible(1);
            //++backup;
        } else {
            dots.at(i)->setVisible(0);
        }
    }


    //initialize the game's score
    score = 0;
    point->setPlainText(QString("%0").arg(score));
}

void MainWindow::START()
{
    p->setGame_1();
    g->setGame_1();
    w->setGame_1();
    y->setGame_1();
    s->setGame_1();
    sp->setGame_1();
    return;
}

void MainWindow::STOP()
{
    p->setGame_0();
    g->setGame_0();
    w->setGame_0();
    y->setGame_0();
    s->setGame_0();
    sp->setGame_0();
    return;
}


void MainWindow::Gh_Stop_5_Sec_1() //for QPushButton "stop"
{
    timer_3->stop();
    connect(timerSTOP, SIGNAL(timeout()), this, SLOT(Gh_Stop_5_Sec_2()));
    timerSTOP->start(5000);
}


void MainWindow::Gh_Stop_5_Sec_2() //for "Gh_Stop_5_Sec_1()"
{
    disconnect(timerSTOP, SIGNAL(timeout()), this, SLOT(Gh_Stop_5_Sec_2()));
    timerSTOP->stop();
    timer_3->start(T_Ghost);
}


void MainWindow::GameJudge()
{
    int k = 1;
    for(int i = 0; i < DotNum; ++i)
    {
        if(dots.at(i)->isVisible() == 1) k = 0;
    }
    if(k == 1)
    {
        ResetGame();
        return;
    }


    if(pac->collidesWithItem(G_) == true && G_->isVisible() == 1 && p->getMode() == "N")
    {
        ResetGame();
        return;
    }

    if(pac->collidesWithItem(W_) == true && W_->isVisible() == 1 && p->getMode() == "N")
    {
        ResetGame();
        return;
    }

    if(pac->collidesWithItem(Y_) == true && Y_->isVisible() == 1 && p->getMode() == "N")
    {
        ResetGame();
        return;
    }

    if(pac->collidesWithItem(Sk_) == true && Sk_->isVisible() == 1 && p->getMode() == "N")
    {
        ResetGame();
        return;
    }

    if(pac->collidesWithItem(Sp_) == true && Sp_->isVisible() == 1 && p->getMode() == "N")
    {
        ResetGame();
        return;
    }




    if(pac->collidesWithItem(G_) == true && G_->isVisible() == 1 && p->getMode() == "S")
    {
        G_->setVisible(0);
        G_->setPos(452.5, 349.5);
        g->setGame_0();
        return;
    }

    if(pac->collidesWithItem(W_) == true && W_->isVisible() == 1 && p->getMode() == "S")
    {
        W_->setVisible(0);
        W_->setPos(535, 349.5);
        w->setGame_0();
        return;
    }

    if(pac->collidesWithItem(Y_) == true && Y_->isVisible() == 1 && p->getMode() == "S")
    {
        Y_->setVisible(0);
        Y_->setPos(490, 432);
        y->setGame_0();
        return;
    }

    if(pac->collidesWithItem(Sk_) == true && Sk_->isVisible() == 1 && p->getMode() == "S")
    {
        Sk_->setVisible(0);
        Sk_->setPos(490, 349.5);
        s->setGame_0();
        return;
    }

    if(pac->collidesWithItem(Sp_) == true && Sp_->isVisible() == 1 && p->getMode() == "S")
    {
        Sp_->setVisible(0);
        Sp_->setPos(490, 349.5);
        sp->setGame_0();
        return;
    }

    return;
}


void MainWindow::SuperJudge()
{
    if(pill->collidesWithItem(pac) == true && pill->isVisible() == 1)
    {
        MODE = "S";
        p->setMode(MODE);
        pill->setVisible(0);
        SuperTimer();
        return;
    }

    if(stop_pill->collidesWithItem(pac) == true && stop_pill->isVisible() == 1)
    {
        stop_pill->setVisible(0);
        Gh_Stop_5_Sec_1();
        return;
    }
}


void MainWindow::TurnNormal()
{
    timerMODE->stop();
    disconnect(timerMODE, SIGNAL(timeout()), this, SLOT(TurnNormal()));

    map_maze->setPixmap(QPixmap(":/new/prefix1/material/Map.jpeg"));

    if(G_->isVisible() == 0)
    {
        G_->setVisible(1);
        Direct_ = "right";
        g->setDirect(Direct_);
        g->setGame_1();
    }

    if(W_->isVisible() == 0)
    {
        W_->setVisible(1);
        Direct_ = "left";
        w->setDirect(Direct_);
        w->setGame_1();
    }

    if(Y_->isVisible() == 0)
    {
        Y_->setVisible(1);
        Direct_ = "down";
        y->setDirect(Direct_);
        y->setGame_1();
    }

    if(Sk_->isVisible() == 0)
    {
        Sk_->setVisible(1);
        Direct_ = "left";
        s->setDirect(Direct_);
        s->setGame_1();
    }
    
    if(Sp_->isVisible() == 0)
    {
        Sp_->setVisible(1);
        Direct_ = "right";
        sp->setDirect(Direct_);
        sp->setGame_1();
    }



    MODE = "N";
    p->setMode(MODE);
}


void MainWindow::ScoreCount()
{
    for(int i = 0; i < DotNum; ++i)
    {
        if(pac->collidesWithItem(dots.at(i)) == true && dots.at(i)->isVisible() == true)
        {
            score++;
            dots.at(i)->setVisible(0);
            point->setPlainText(QString("%0").arg(score));
        }

        if(Sp_->collidesWithItem(dots.at(i)) == true && dots.at(i)->isVisible() == true)
        {
            dots.at(i) ->setVisible(0);
        }
    }

}
