#include "bulletenemy.h"
#include "bullet.h"
#include "game.h"
#include "mainwindow.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
extern Game * game;
Bulletenemy::Bulletenemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/images/EBullet.png"));
    setScale(0.1);
    setTransformOriginPoint(40,50);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bulletenemy::move() {
    QList<QGraphicsItem *> col_items=collidingItems();
    for (int i=0,n=col_items.size();i<n;i++){
        if (typeid(*(col_items[i]))==typeid(Player)) {
            game->stat->decrease();
            scene()->removeItem(this);
            delete this;
            return;
        }
        else if (typeid(*(col_items[i]))==typeid(Bullet)) {
            game->stat->increaseB();
            MainWindow::RefreshScore();
            scene()->removeItem(col_items[i]);
            scene()->removeItem(this);
            delete col_items[i];
            delete this;
            return;
        }
    }
    if(game->stat->gethealth()>0){
        setPos(x(),y()+15);
        if (pos().y() > 1019){
            scene()->removeItem(this);
            delete this;
        }
    }
    if(game->stat->gethealth()==0){
        game->scene->removeItem(this);
        delete this;
    }
}
