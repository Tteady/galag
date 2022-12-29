#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QDebug>
#include <QWidget>
#include <QtMultimedia/QSound>
#include "enemyobject.h"
#include "mainwindow.h"
#include "bulletenemy.h"
#include "game.h"
extern Game* game;

int Enemy::phase = 0;

Enemy::Enemy(int hp, int speed, int reward, int x, EnemyType type, QGraphicsItem *parent) {
    this->hp = hp;
    this->speed = speed;
    this->reward = reward;
    setPos(x,0);

    int random_number=2000+rand()%3000;
    int random_number2=3000+rand()%4000;
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    timer->start(300);

    if(type == EnemyType::meteor){
        setPixmap(QPixmap(":/images/meteor.png"));
        setScale(0.1);

    }
    if(type == EnemyType::armorship){
        setPixmap(QPixmap(":/images/speedship.png"));
        setScale(0.1);
        QTimer * timer2 = new QTimer();
        connect(timer2, SIGNAL(timeout()), this, SLOT(attack()));

        timer2->start(random_number2);

    }
    if(type == EnemyType::rogue){
        setPixmap(QPixmap(":/images/enemy.png"));
        setScale(0.2);

        QTimer * timer3 = new QTimer();
        connect(timer3, SIGNAL(timeout()), this, SLOT(attack()));

        timer3->start(random_number);
    }
}
//конструктор по умолчанию
Enemy::Enemy()
{
    hp=0;
    speed=0;
    reward=0;
}
//конструктор копирования
Enemy::Enemy(const Enemy &enemy)
{
   this->hp=enemy.hp;
   this->speed=enemy.speed;
   this->reward=enemy.reward;
}
void Enemy::move() {
    int phaseStep = 20;
    if(Enemy::phase < phaseStep)
        setPos(x(), y()+speed);
    else if(Enemy::phase < phaseStep*2)
        setPos(x()+speed, y());
    else if(Enemy::phase < phaseStep*3)
        setPos(x(),y()+speed);
    else if(Enemy::phase < phaseStep*4)
        setPos(x()-speed, y());
    else if(Enemy::phase < phaseStep*5)
        Enemy::phase = 0;



    if (pos().y() > 1019){
        game->enemies.removeOne(this);
        game->scene->removeItem(this);
        delete this;
        return;
    }

    if(game->stat->gethealth()==0){
        Enemy::phase = 0;
        game->enemies.removeOne(this);
        game->scene->removeItem(this);
        delete this;
        return;
    }

    QList<QGraphicsItem *> col_items=collidingItems();
    for (int i=0; i <col_items.size(); i++){
        if (typeid(*(col_items[i]))==typeid(Player)) {
            QSound::play(":/sounds/vz.wav");
            game->stat->decrease();
            MainWindow::RefreshScore();
            game->enemies.removeOne(this);
            game->scene->removeItem(this);
            delete this;
            return;
        }
    }
}

int Enemy::detectCollision(int x, int y, QList<Enemy*> enemies) {
    for(int i=0; i<enemies.size(); i++){
        if (enemies[i]->x()==x && enemies[i]->y()==y){
            return i;
        }
    }
}
void Enemy::attack() {
    Bulletenemy * bullete = new Bulletenemy();
    bullete->setPos(x(),y());
    scene()->addItem(bullete);
}


