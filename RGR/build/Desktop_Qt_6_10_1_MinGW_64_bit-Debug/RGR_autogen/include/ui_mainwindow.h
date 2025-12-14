/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelBackground;
    QLabel *labelHero;
    QLabel *labelEnemy;
    QLabel *labelStar;
    QLabel *labelTree;
    QLabel *labelBackpack;
    QLabel *labelPendant;
    QLabel *labelSword;
    QLabel *labelText;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1294, 744);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        labelBackground = new QLabel(centralwidget);
        labelBackground->setObjectName("labelBackground");
        labelBackground->setGeometry(QRect(0, 0, 1280, 720));
        labelBackground->setScaledContents(true);
        labelHero = new QLabel(centralwidget);
        labelHero->setObjectName("labelHero");
        labelHero->setGeometry(QRect(0, 500, 150, 150));
        labelHero->setScaledContents(true);
        labelEnemy = new QLabel(centralwidget);
        labelEnemy->setObjectName("labelEnemy");
        labelEnemy->setGeometry(QRect(160, 490, 150, 150));
        labelEnemy->setScaledContents(true);
        labelStar = new QLabel(centralwidget);
        labelStar->setObjectName("labelStar");
        labelStar->setGeometry(QRect(170, 210, 100, 100));
        labelStar->setScaledContents(true);
        labelTree = new QLabel(centralwidget);
        labelTree->setObjectName("labelTree");
        labelTree->setGeometry(QRect(140, 420, 260, 360));
        labelTree->setScaledContents(true);
        labelBackpack = new QLabel(centralwidget);
        labelBackpack->setObjectName("labelBackpack");
        labelBackpack->setGeometry(QRect(210, 420, 90, 90));
        labelBackpack->setScaledContents(true);
        labelPendant = new QLabel(centralwidget);
        labelPendant->setObjectName("labelPendant");
        labelPendant->setGeometry(QRect(270, 420, 60, 60));
        labelPendant->setScaledContents(true);
        labelSword = new QLabel(centralwidget);
        labelSword->setObjectName("labelSword");
        labelSword->setGeometry(QRect(190, 480, 120, 120));
        labelSword->setScaledContents(true);
        labelText = new QLabel(centralwidget);
        labelText->setObjectName("labelText");
        labelText->setGeometry(QRect(90, 130, 420, 140));
        QFont font;
        font.setFamilies({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(13);
        labelText->setFont(font);
        labelText->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelText->setWordWrap(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1294, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelBackground->setText(QString());
        labelHero->setText(QString());
        labelEnemy->setText(QString());
        labelStar->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelTree->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelBackpack->setText(QString());
        labelPendant->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        labelSword->setText(QString());
        labelText->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
