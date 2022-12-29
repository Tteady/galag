#ifndef STAT_H
#define STAT_H

#include <QGraphicsTextItem>
#include <QLabel>

class Stat: public QLabel{
    Q_OBJECT
public:
    Stat(QLabel * parent=0);
    void increaseB();
    int getscore();
    void decrease();
    int gethealth();
    void stat0();
    int score_kol;
    int health_kol;
};

#endif // STAT_H
