#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include "player.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsView * gamescene;
    QTimer * timer;
    QTimer * timer2;
    Stat * stat;
    QVector<QPair<QString, int>> scores;
    static Ui::MainWindow *ui;

    static void RefreshScore();
    static void gameo();

public slots:
        void start();
        void close();
        void leaderboard();
        void back();
        void save();
private:

};

#endif // MAINWINDOW_H
