#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyDialog;
}
QT_END_NAMESPACE

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent = nullptr);
    ~MyDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MyDialog *ui;
};
#endif // MYDIALOG_H
