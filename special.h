#ifndef SPECIAL_H
#define SPECIAL_H

#include "move.h"
#include <QGraphicsPixmapItem>
#include <QList>

class Special : public G_Ghost
{
    Q_OBJECT

public:
    Special(QGraphicsPixmapItem *sp);
    ~Special();

    void ChangePixmap();

public slots:
    void moving();
};

#endif // SPECIAL_H
