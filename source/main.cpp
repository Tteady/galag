#include <QApplication>
#include "mainwindow.h"
#include "game.h"
Game * game;
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow c;
    c.show();

    return a.exec();
}
