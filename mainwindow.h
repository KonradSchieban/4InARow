#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>

//Own classes
#include "player.h"
#include "gameBoard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    gameBoard G;

    player P1;
    player P2;

    QGraphicsScene *scene;


    int turn;

private slots:
    void on_horizontalSlider_sliderMoved(int position);

    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void on_button5_clicked();

    void on_button6_clicked();

    void on_button7_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
