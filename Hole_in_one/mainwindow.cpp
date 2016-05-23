#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *mylabel;
    //QPixmap papierknuel("qrc:/Papierkneul.png");
    ui->mylabel->setPixmap(QPixmap("qrc:/Papierkneul.png"));
    ui->mylabel->show();
   // QPixmap pix(200,100);
   // QPainter painter();
   // painter.drawPixmap(20,30,10,10,&pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}


