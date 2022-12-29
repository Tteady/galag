#include <QGraphicsScene>
#include <QApplication>
#include <QtAlgorithms>
#include "player.h"
#include "enemyobject.h"
#include "bullet.h"
#include "game.h"
#include "stat.h"
#include "mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QtMultimedia/QSound>
Player *Game::player;
Game::Game(QWidget *parent):QGraphicsView(parent){
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,789,1019);
    scene->setBackgroundBrush(QBrush(QImage(":/images/space2.png")));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(789,1019);

    stat = new Stat();

    player = new Player();

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(spawn()));

    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(phase()));

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/HeatleyBros.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(15);

    gmusic = new QMediaPlayer();
    gmusic->setMedia(QUrl("qrc:/sounds/gameover.mp3"));
    gmusic->setVolume(15);

    smusic = new QMediaPlayer();
    smusic->setMedia(QUrl("qrc:/sounds/startmusic.mp3"));
    smusic->setVolume(15);
    smusic->play();
    logoover = scene->addPixmap(QPixmap(":/images/gameover.png"));
    logoover->setPos(90, 250);
}

void Game::spawn(){
    if(Enemy::phase % 10 == 0 && Enemy::phase <= 20){
         for(int i = 0; i < 5; i++){
             enemies.push_back(new Enemy(3, 10, 15, 20+i*100, EnemyType::meteor));
             scene->addItem(enemies.last());
         }
     }
    if(Enemy::phase == 50){
        for(int i = 0; i < 5; i++){
            enemies.push_back(new Enemy(1, 10, 5, 210+i*100, EnemyType::rogue));
            scene->addItem(enemies.last());
        }
     }
    if(Enemy::phase == 60){
        for(int i = 0; i < 3; i++){
            enemies.push_back(new Enemy(5,10,25,215+i*200, EnemyType::armorship));
            scene->addItem(enemies.last());
        }
    }
}

void Game::phase(){
    Enemy::phase++;
}
