/********************************************************************************
** Form generated from reading UI file 'mydialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYDIALOG_H
#define UI_MYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MyDialog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLabel *label_2;

    void setupUi(QDialog *MyDialog)
    {
        if (MyDialog->objectName().isEmpty())
            MyDialog->setObjectName("MyDialog");
        MyDialog->resize(800, 600);
        label = new QLabel(MyDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 220, 121, 20));
        pushButton = new QPushButton(MyDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(70, 220, 75, 24));
        pushButton_2 = new QPushButton(MyDialog);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(70, 270, 75, 24));
        lineEdit = new QLineEdit(MyDialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(160, 270, 113, 22));
        label_2 = new QLabel(MyDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 310, 171, 20));

        retranslateUi(MyDialog);

        QMetaObject::connectSlotsByName(MyDialog);
    } // setupUi

    void retranslateUi(QDialog *MyDialog)
    {
        MyDialog->setWindowTitle(QCoreApplication::translate("MyDialog", "\320\237\320\265\321\200\320\262\320\260\321\217 \321\204\320\276\321\200\320\274\320\260", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("MyDialog", "\320\222\321\213\320\262\320\276\320\264", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyDialog", "\320\240\320\260\321\201\321\207\320\265\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("MyDialog", "\320\234\320\265\321\201\321\202\320\276 \320\264\320\273\321\217 \320\262\321\213\320\262\320\276\320\264\320\260 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyDialog: public Ui_MyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYDIALOG_H
