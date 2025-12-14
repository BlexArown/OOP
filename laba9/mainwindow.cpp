#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define dt 15

#define path_forward "C:/OOP/lab9/RIS/2.png"
#define path_back "C:/OOP/lab9/RIS/1.png"
int k = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::onTimeout()
{
    if(ui->label->geometry().x()<1140 && k==0)
    {
        ui->label->setPixmap(QPixmap(path_forward));
        ui->label->setGeometry(ui->label->geometry().x()+dt,250,131,92);
    }
    else
    {
        k=1;
        ui->label->setPixmap(QPixmap(path_back));
        ui->label->setGeometry(ui->label->geometry().x()-dt,250,131,92);
        if(ui->label->geometry().x()<5)k=0;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    timer->start(50);
}



void MainWindow::on_actionStop_triggered()
{
    timer->stop();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

