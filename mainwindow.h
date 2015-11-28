#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QMouseEvent>

//Own classes
#include "player.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
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

    player* P1;
    player* P2;

    QGraphicsScene *scene;

    bool enabled;

    int graphicsWidth;
    int graphicsHeight;
    int graphicsLeftBorder;
    int graphicsRightBorder;
    int turn;

private slots:

    void mousePressEvent(QMouseEvent *ev);

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;

    int moveUI(int col);
    /* Performs a move in a specified column
     * Returns -1 if move was invalid
     *          0 if move was regular and thereis no winner yet
     *          1 if player 1 won
     *          2 if player 2 won
     *          3 if match is tied
     */

    void statusOutput(int winner);
    /* Updates the winner in the Status Field "statusField"
     */
};

#endif // MAINWINDOW_H
