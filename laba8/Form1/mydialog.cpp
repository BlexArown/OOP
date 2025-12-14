#include "mydialog.h"
#include "./ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::on_pushButton_clicked()
{
    ui->label->setText("Привет, студент!!!");
}


void MyDialog::on_pushButton_2_clicked()
{
    double x;
    QString str=ui->lineEdit->text();
    x=str.toDouble();
    x=x*3;
    ui->label_2->setText("Утроенное значение X="+str.number(x));
}

