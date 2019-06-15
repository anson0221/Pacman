#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPushButton>
#include <QString>
#include "move.h"
#include "special.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    void Accelerate(); //for Pacman
    void SlowDown(); //for Pacman
    void SuperTimer();
    void ResetGame();

public slots:
    void START();
    void STOP();
    void Gh_Stop_5_Sec_1();
    void Gh_Stop_5_Sec_2();
    void GameJudge();
    void SuperJudge();
    void TurnNormal();
    void ScoreCount();  

private:
    Ui::MainWindow *ui;
    QGraphicsScene *sc;
    QGraphicsPixmapItem *pac, *G_, *W_, *Y_, *Sk_, *Sp_, *map_maze, *wall;
    QGraphicsTextItem *point;
    QPushButton *go, *stop, *cheat; //to stop all ghosts for 5 second
    QTimer *timer_1 ,*timer_2, *timer_3;
    QTimer *timerSTOP = new QTimer(this);
    QTimer *timerMODE = new QTimer(this);
    QString Direct_, MODE;
    Pacman *p;
    G_Ghost *g;
    G_Ghost *fth_w, *fth_y, *fth_s, *fth_sp; //for Polymorphism
    W_Ghost *w;
    Y_Ghost *y;
    Skeleton *s;
    Special *sp;
    QList <float> XXX_cor, YYY_cor;
    QList<QGraphicsPixmapItem*> dots;
    QGraphicsPixmapItem *pill;
    QGraphicsPixmapItem *stop_pill;

    int Lock = 0; //to stop the game
    int T_Move = 80; //to control the velocity of Pacman with timer_2
    int T_Ghost = 80; //to control the velocity of Ghost with timer_3
    int DotNum = 0;
    int score = 0;
};

#endif // MAINWINDOW_H
