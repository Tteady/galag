#include "mainwindow.h"
#include "game.h"
#include "Player.h"
#include <QVector>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QtMultimedia/QSound>
#include <QFile>
#include <QPair>
#include <QDir>
extern Game*game;

Ui::MainWindow *MainWindow::ui = new Ui::MainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    game = new Game();
    gamescene = new QGraphicsView;
    timer = new QTimer;
    stat = new Stat();
    connect(timer, SIGNAL(timeout()), this, SLOT(spawn()));
    QObject::connect(ui->StartGame,SIGNAL(clicked()),this,SLOT(start()));
    QObject::connect(ui->Quite,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->LeaderBoard,SIGNAL(clicked()),this,SLOT(leaderboard()));
    QObject::connect(ui->Back,SIGNAL(clicked()),this,SLOT(back()));
    QObject::connect(ui->restartGame,SIGNAL(clicked()),this,SLOT(start()));
    QObject::connect(ui->mainmenu,SIGNAL(clicked()),this,SLOT(back()));
    QObject::connect(ui->save,SIGNAL(clicked()),this,SLOT(save()));

    QString filename = ":/text/text.txt";
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    if(!file.isOpen()){
        QMessageBox::information(0, "Ошибка", "Файл не найден!");
        return;
    }
    QString text = "";

    QString name;
    QString score;
    bool bol=false;

    QTextStream st(&file);
    text = st.readAll();

     for (int i=0; i<text.length(); i++){
        if (text[i]==';')
        {
            bol=true;
            continue;
        }

        if (text[i]=='\n')
        {
            bol=false;
            scores.push_back(QPair<QString, int>(name, score.toInt()));
            name="";
            score="";
            continue;
        }

        if(bol==false)
            name+=text[i];
        else
            score+=text[i];

     }

    file.close();
    for(int i=0; i<scores.length();i++){
        for(int j=0; j<scores.length()-1;j++){
            if(scores[j].second<scores[j+1].second){
                QPair<QString, int> temp=scores[j];
                scores[j]=scores[j+1];
                scores[j+1]=temp;
            }
        }
    }
}
void MainWindow::start() {
    ui->stackedWidget->setCurrentIndex(1);
    ui->gamescene->setScene(game->scene);
    ui->restartGame->setVisible(false);
    ui->mainmenu->setVisible(false);
    ui->save->setVisible(false);
    ui->name->setVisible(false);
    ui->text->setVisible(false);

    ui->gamescene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gamescene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    if (game->gmusic->state() == QMediaPlayer::PlayingState){
        game->gmusic->stop();
    }
    if (game->smusic->state() == QMediaPlayer::PlayingState){
        game->smusic->stop();
    }
    game->player->setFlag(QGraphicsItem::ItemIsFocusable);
    game->player->setFocus();
    game->music->play();
    game->stat->stat0();
    game->player->setPos(350,924);
    game->scene->addItem(game->player);
    game->logoover->setVisible(false);
    game->timer->start(300);
    game->timer2->start(300);
}

void MainWindow::close() {
    QApplication::quit();
}

void MainWindow::leaderboard() {
    ui->stackedWidget->setCurrentIndex(2);
    for(int i=0; i<scores.length();i++){
        for(int j=0; j<i-1;j++){
            if(scores[j].second<scores[j+1].second){
                QPair<QString, int> temp=scores[j];
                scores[j]=scores[j+1];
                scores[j+1]=temp;
            }
        }
    }

    for(int i=0; i<scores.length();i++){
        ui->leader->addItem(scores[i].first + '-' + QString::number(scores[i].second));
    }
}
void MainWindow::back(){
    ui->stackedWidget->setCurrentIndex(0);
    if (game->gmusic->state() == QMediaPlayer::PlayingState){
        game->gmusic->stop();
    }
    game->smusic->play();
    ui->leader->clear();
}

void MainWindow::save() {
    QString filename = ":/text/text.txt";
    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);
    if(!file.isOpen()){
        QMessageBox::information(0, "Ошибка", "Файл не найден!");
        return;
    }

    QString text = "";

    QString name;
    QString score;
    bool bol=false;

    QTextStream st(&file);
    text = st.readAll();

    scores.clear();
     for (int i=0; i<text.length(); i++){
        if (text[i]==';')
        {
            bol=true;
            continue;
        }

        if (text[i]=='\n')
        {
            bol=false;
            scores.push_back(QPair<QString, int>(name, score.toInt()));
            name="";
            score="";
            continue;
        }

        if(bol==false)
            name+=text[i];
        else
            score+=text[i];

     }

    file.close();

    scores.push_back(QPair<QString, int>(ui->text->text(), game->stat->score_kol));

    for(int i=0; i<scores.length();i++){
        for(int j=0; j<scores.length()-1;j++){
            if(scores[j].second<scores[j+1].second){
                QPair<QString, int> temp=scores[j];
                scores[j]=scores[j+1];
                scores[j+1]=temp;
            }
        }
    }

    filename = QFileInfo(".").absolutePath()+"/galag/text.txt"; //"C:/Users/Tteady/Documents/galag/text.txt";
    QFile file2(filename);
    file2.open(QFile::WriteOnly | QFile::Text);
    if(!file2.isOpen()){
        QMessageBox::information(0, "Ошибка", "Файл не найден!");
        return;
    }

    QTextStream stw(&file2);
    QString newname;
    for(int i=0; i<scores.length();i++){
        newname+=scores[i].first;
        newname+=';';
        newname+=QString::number(scores[i].second);
        newname+='\n';
    }
    stw<<newname;
    file2.close();

    ui->save->setVisible(false);
    ui->text->setVisible(false);
    ui->name->setVisible(false);
}

void MainWindow::gameo() {
    ui->restartGame->setVisible(true);
    ui->mainmenu->setVisible(true);
    ui->save->setVisible(true);
    ui->name->setVisible(true);
    ui->text->setVisible(true);
    game->logoover->setVisible(true);
    game->music->stop();
    game->scene->removeItem(game->player);
    game->timer->stop();
    game->timer2->stop();
    game->gmusic->play();
    QSound::play(":/sounds/vzp.wav");
}

void MainWindow::RefreshScore(){
    ui->score->setText("Score: "+QString::number(game->stat->score_kol));
    ui->health->setText("Health: "+QString::number(game->stat->health_kol));
}

MainWindow::~MainWindow()
{
    delete ui;
}
