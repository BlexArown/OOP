#include "mydialog.h"
#include "ui_mydialog.h"
#include "cmath"
#include "QMessageBox"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMainWindow>

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
    double start,end,step;
    double x,y;
    QString s1,s2,s3;
    QString str("");
    s1=ui->lineEdit->text();
    start=s1.toDouble();
    s2=ui->lineEdit_2->text();
    end=s2.toDouble();
    s3=ui->lineEdit_3->text();
    step=s3.toDouble();
    series = new QLineSeries();
    for(x=start;x<=end;x=x+step)
    {
        y=cos(x);
        series->append(x,y);
        str=str+"x="+s1.number(x)+"\ty="+s1.number(y)+"\n";
    }
    QMessageBox::information(this,"Результат",str);
}


void MyDialog::on_graph_clicked()
{
    double A_start = ui->lineEdit->text().toDouble();
    double A_end   = ui->lineEdit_2->text().toDouble();
    double A_step  = ui->lineEdit_3->text().toDouble();

    double B = 2.5;

    QLineSeries *series = new QLineSeries();
    series->setName("T = e^{|A+B|} - 3^A");

    for (double A = A_start; A <= A_end; A += A_step)
    {
        double T = exp(fabs(A + B)) - pow(3.0, A);
        series->append(A, T);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("График функции T(A)");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

    QMainWindow *window = new QMainWindow();
    window->setCentralWidget(chartView);
    window->show();
}
