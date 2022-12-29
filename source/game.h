#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <Qwidget>
#include <QGraphicsScene>
#include <QPushButton>
#include <QMediaPlayer>
#include "enemyobject.h"
#include "player.h"
#include "stat.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    Game (QWidget * parent = 0);
    QGraphicsScene * scene;
    static Player * player;
    Stat * stat;
    QList<Enemy*> enemies;
    QMediaPlayer *music;
    QMediaPlayer *gmusic;
    QMediaPlayer *smusic;
    QTimer * timer;
    QTimer * timer2;
    QGraphicsItem * logoover;
public slots:
    void spawn();
    void phase();
};

#endif // GAME_H
