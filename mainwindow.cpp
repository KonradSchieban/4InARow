#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include<iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),P1(1),P2(2)
{
    ui->setupUi(this);

    G.print();

    turn = 1;

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    scene->setSceneRect(0,0,300,140);
    P1.setScene(scene);
    P2.setScene(scene);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

    QString str = QString::number(position);
    ui->label->setText(str);

}


void MainWindow::on_button1_clicked()
{

    int col = 0;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }


    G.print();

}

void MainWindow::on_button2_clicked()
{
    int col = 1;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }

    G.print();
}

void MainWindow::on_button3_clicked()
{
    int col = 2;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }

    G.print();
}

void MainWindow::on_button4_clicked()
{
    int col = 3;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }

    G.print();
}

void MainWindow::on_button5_clicked()
{
    int col = 4;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }

    G.print();
}

void MainWindow::on_button6_clicked()
{
    int col = 5;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }

    G.print();
}

void MainWindow::on_button7_clicked()
{
    int col = 6;

    if(turn == 1){
        P1.move(col,&G);
        turn = 2;
    }else{
        P2.move(col,&G);
        turn = 1;
    }

    G.print();
}
