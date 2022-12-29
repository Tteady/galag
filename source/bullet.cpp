#include "bullet.h"
#include "enemyobject.h"
#include "game.h"
#include "mainwindow.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include <QtMultimedia/QSound>
extern Game*game;
Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {

    setPixmap(QPixmap(":/images/bullet.png"));
    setScale(0.06);

    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move() {
    QList<QGraphicsItem *> col_items=collidingItems();
    for (int i=0,n=col_items.size();i<n;i++){
        if (typeid(*(col_items[i]))==typeid(Enemy)) {
            int collidedItem = Enemy::detectCollision(col_items[i]->x(), col_items[i]->y(), game->enemies);
            game->enemies[collidedItem]->hp--;
            if (game->enemies[collidedItem]->hp==0){
                scene()->removeItem(col_items[i]);
                QSound::play(":/sounds/vz.wav");
                game->stat->score_kol+=game->enemies[collidedItem]->reward;
                MainWindow::RefreshScore();
                delete game->enemies[collidedItem];
                game->enemies.removeAt(collidedItem);     
            }
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
    setPos(x(),y()-10);
    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
    if(game->stat->gethealth()==0){
        game->scene->removeItem(this);
        delete this;
    }
}



