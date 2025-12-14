#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onFrame();

private:
    Ui::MainWindow *ui;
    QTimer *timer;

    void setupScene();
    void resetScene();

    int stage;
    int step;

    int heroX, heroY;
    int enemyX, enemyY;
    int starX, starY;
    int bagX, bagY;
    int pendX, pendY;
    int treeX, treeY;

    // константы сцен
    int groundY;
    int heroStopX;
    int starLandY;

    // изображения персонажей
    QPixmap heroWalk;
    QPixmap heroWalkLeft;
    QPixmap heroWalkRight;
    QPixmap heroIdle;
    QPixmap heroSurprised;
    QPixmap heroSword;

    QPixmap enemyLeft;
    QPixmap enemyRight;

    QPixmap starPix;
    QPixmap treePix;

    QPixmap bagClosed;
    QPixmap bagOpen;

    QPixmap pendantPix;
    QPixmap swordPix;
};

#endif
