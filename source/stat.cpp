#include "stat.h"
#include "game.h"
#include "mainwindow.h"
#include <QFont>
#include <QLabel>
extern Game * game;

Stat::Stat(QLabel *parent) {
    score_kol = 0;
    health_kol = 3;
}

void Stat::increaseB() {
    score_kol = score_kol + 10;
}

int Stat::getscore() {
    return score_kol;
}
void Stat::decrease() {
    health_kol=health_kol-1;
    if (health_kol==0){
        MainWindow::gameo();
    }
}

int Stat::gethealth() {
    return health_kol;
}

void Stat::stat0(){
    health_kol=3;
    score_kol=0;
    MainWindow::RefreshScore();
}

