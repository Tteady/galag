#include "player.h"
#include "bullet.h"
#include "game.h"
#include "stat.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QtMultimedia/QSound>

extern Game * game;
Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    setPixmap(QPixmap(":/images/spaceship.png"));
    setScale(0.3);

}

void Player::keyPressEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Left){
        if(pos().x() > 0) {
            setPos(x()-15,y());
        }
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800){
            setPos(x()+15,y());
        }
    }
    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 0) {
            setPos(x(),y()-15);
        }
    }
    else if (event->key() == Qt::Key_Down) {
        if (pos().y() + 100 < 1019){
            setPos(x(),y()+15);
        }
    }
    else if (event->key() == Qt::Key_Space){
        if(event->isAutoRepeat()==false) {
            event->ignore();
            Bullet * bullet = new Bullet();
            bullet->setPos(x(),y());
            scene()->addItem(bullet);
            QSound::play(":/sounds/lz.wav");
        }

    }
}










