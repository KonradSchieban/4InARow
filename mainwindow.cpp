#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include<QScrollBar>
#include<QPoint>
#include<QPalette>
#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    G.print();

    //disable game mode since no players are chose yet
    enabled = false;

    ui->statusField->setText("Player 1's turn");

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    /*  Initialize Scene
     *
     */

    QRect graphicsGeometry = ui->graphicsView->geometry();
    graphicsWidth = graphicsGeometry.width()*0.9;
    graphicsHeight = graphicsGeometry.height()*0.9;
    graphicsLeftBorder = graphicsGeometry.width()*0.05;
    graphicsRightBorder = graphicsGeometry.width()*0.95;

    scene->setSceneRect(0,0,graphicsWidth,graphicsHeight);

    QPen blackPen(Qt::black);

    for(int i = 0; i <= 7; i++){
        scene->addLine(i*graphicsWidth/7.0,0,i*graphicsWidth/7.0,graphicsHeight,blackPen);
        scene->addLine(0,i*graphicsHeight/7.0,graphicsWidth,i*graphicsHeight/7.0,blackPen);
    }

    //hide scrollbars in graphicsView
    ui->graphicsView->horizontalScrollBar()->hide();
    ui->graphicsView->verticalScrollBar()->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::moveUI(int col)
{

    int winner = 0;
    int moveResult;

    if(turn == 1){

        moveResult = P1->move(&G,col);

        if(moveResult == 0){ //check if move was invalid because column full
            winner = 0;
            return winner;
        }else if(moveResult == 2){
            winner = 1;
        }

        turn = 2;

    }else{

        moveResult = P2->move(&G,col);

        if(moveResult == 0){ //check if move was invalid because column full
            winner = 0;
            return winner;
        }else if(moveResult == 2){
            winner = 2;
        }

        turn = 1;

    }

    if(moveResult==3){
        winner = 3;
    }

    G.print();

    statusOutput(winner);

    return winner;

}


void MainWindow::statusOutput(int winner)
{
    switch(winner){
    case 0:
        if(turn == 1)
            ui->statusField->setText("Player 1's turn");
        else
            ui->statusField->setText("Player 2's turn");
        break;
    case 1:
        ui->statusField->setText("Player 1 won");
        ui->statusField->setStyleSheet("QTextEdit {background-color:red}");
        break;
    case 2:
        ui->statusField->setText("Player 2 won");
        ui->statusField->setStyleSheet("QTextEdit {background-color:blue}");
        break;
    case 3:
        ui->statusField->setText("The game is tied!");
        ui->statusField->setStyleSheet("QTextEdit {background-color:green}");
        break;
    }

    //check if game is over and in case, make start button a "Play Again" button
    if(winner > 0){
        enabled = false;
        ui->startButton->setText("Play again?");
        ui->startButton->setEnabled(true);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *ev){

    if(enabled)
    {
        int sizeX = G.getSizeX();

        QPoint P = ev->pos();
        QPoint Q = ui->graphicsView->pos();

        //get cursor position on game board
        int posInFrame = P.x()-Q.x()-graphicsLeftBorder;

        //check if curor was on game board
        if(posInFrame < 0 || posInFrame > graphicsWidth)
            return;

        int col = (1.0*posInFrame)/graphicsWidth*sizeX;

        if(col >= 0 && col < 7)
            cout<<"Winner:"<<moveUI(col)<<endl;
    }

}


void MainWindow::on_startButton_clicked()
{

    //create first player dependant on which radio button has been checked
    if(ui->radioButtonH1->isChecked())
        P1 = new humanPlayer(1);
    else if(ui->radioButtonC1->isChecked())
        P1 = new computerPlayer(1);
    else
        return;

    //create second player dependant on which radio button has been checked
    if(ui->radioButtonH2->isChecked())
        P2 = new humanPlayer(2);
    else if(ui->radioButtonC2->isChecked())
        P2 = new computerPlayer(2);
    else
        return;

    //initialize players with scene object and frame metrics
    P1->setScene(scene,graphicsWidth,graphicsHeight);
    P2->setScene(scene,graphicsWidth,graphicsHeight);

    //Clear board and paint grid again
    scene->clear();
    ui->graphicsView->viewport()->update();

    QPen blackPen(Qt::black);

    for(int i = 0; i <= 7; i++){
        scene->addLine(i*graphicsWidth/7.0,0,i*graphicsWidth/7.0,graphicsHeight,blackPen);
        scene->addLine(0,i*graphicsHeight/7.0,graphicsWidth,i*graphicsHeight/7.0,blackPen);
    }

    //clear gameBoard
    G.clear();

    //enable game mode
    enabled = true;

    //Player 1 is starting the game
    turn = 1;

    //reset status field and disable start button
    ui->startButton->setEnabled(false);
    ui->statusField->setText("Player 1's turn");
    ui->statusField->setStyleSheet("QTextEdit {background-color:white}");


}

void MainWindow::on_CloseButton_clicked()
{
    this->close();
}
