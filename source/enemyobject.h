#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPointF>
#include "Stat.h"
enum EnemyType {rogue, meteor, armorship} ;

class Enemy: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(int hp, int speed, int reward, int x, EnemyType type, QGraphicsItem *parent=0);
    Enemy();
    Enemy(const Enemy& enemy);
    Stat * stat;
    int hp;
    int speed;
    int reward;
    static int phase;

    static int detectCollision(int x, int y, QList<Enemy *> enemies);

public slots:
    void move();
    void attack();
};
#endif // ENEMYOBJECT_H
