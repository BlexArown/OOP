#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QFont>
#include <algorithm>
#include <cmath>

static int stepTowards(int cur, int target, int step)
{
    if (cur < target) return std::min(cur + step, target);
    if (cur > target) return std::max(cur - step, target);
    return cur;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    setFixedSize(1280, 720);

    setupScene();
    resetScene();

    timer->setInterval(40); // 25 FPS
    connect(timer, &QTimer::timeout, this, &MainWindow::onFrame);
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScene()
{
    // задний фон
    ui->labelBackground->setGeometry(0, 0, width(), height());
    ui->labelBackground->setPixmap(QPixmap("C:/OOP/RGR/images/background.png"));
    ui->labelBackground->setScaledContents(true);

    // дерево
    ui->labelTree->resize(230, 320);
    ui->labelTree->setPixmap(QPixmap("C:/OOP/RGR/images/tree.png"));
    ui->labelTree->setScaledContents(true);

    // гг
    heroWalk      = QPixmap("C:/OOP/RGR/images/hero_walk.png");
    heroIdle      = QPixmap("C:/OOP/RGR/images/hero_idle.png");
    heroSurprised = QPixmap("C:/OOP/RGR/images/hero_surprised.png");
    heroSword     = QPixmap("C:/OOP/RGR/images/hero_sword.png");

    // ходьба влево/вправо
    heroWalkLeft  = QPixmap("C:/OOP/RGR/images/hero_walk_left.png");
    heroWalkRight = QPixmap("C:/OOP/RGR/images/hero_walk_right.png");

    ui->labelHero->resize(160, 160);
    ui->labelHero->setScaledContents(true);
    ui->labelHero->setPixmap(heroWalkRight.isNull() ? heroWalk : heroWalkRight);

    // враг
    enemyLeft  = QPixmap("C:/OOP/RGR/images/enemy_left.png");
    enemyRight = QPixmap("C:/OOP/RGR/images/enemy_right.png");

    ui->labelEnemy->resize(170, 170);
    ui->labelEnemy->setScaledContents(true);
    ui->labelEnemy->setPixmap(enemyLeft);

    // звездочка
    starPix = QPixmap("C:/OOP/RGR/images/star.png");
    ui->labelStar->resize(120, 120);
    ui->labelStar->setScaledContents(true);
    ui->labelStar->setPixmap(starPix);

    // рюкзак
    bagClosed = QPixmap("C:/OOP/RGR/images/backpack_closed.png");
    bagOpen   = QPixmap("C:/OOP/RGR/images/backpack_open.png");

    ui->labelBackpack->resize(95, 95);
    ui->labelBackpack->setScaledContents(true);
    ui->labelBackpack->setPixmap(bagClosed);

    // кулон
    pendantPix = QPixmap("C:/OOP/RGR/images/pendant.png");
    ui->labelPendant->resize(60, 60);
    ui->labelPendant->setScaledContents(true);
    ui->labelPendant->setPixmap(pendantPix);
    ui->labelPendant->hide();

    // текста
    ui->labelText->setWordWrap(true);
    ui->labelText->setAlignment(Qt::AlignCenter);
    ui->labelText->resize(300, 90);
    ui->labelText->setText("");
    ui->labelText->setStyleSheet(
        "QLabel {"
        " background-color: rgba(255, 255, 255, 235);"
        " border: 1px solid rgba(0, 0, 0, 120);"
        " border-radius: 14px;"
        " color: #222222;"
        " padding: 8px 12px;"
        "}"
        );

    QFont font("Comic Sans MC");
    font.setPointSize(13);
    font.setWeight(QFont::Medium);
    ui->labelText->setFont(font);
    ui->labelText->hide();

    // Z-order
    ui->labelBackground->lower();
    ui->labelTree->raise();
    ui->labelStar->raise();
    ui->labelEnemy->raise();
    ui->labelHero->raise();
    ui->labelBackpack->raise();
    ui->labelPendant->raise();
    ui->labelText->raise();
}

void MainWindow::resetScene()
{
    stage = 0;
    step  = 0;

    groundY = 490;

    // дерево ближе к центру и ниже
    treeX = 900;
    treeY = 330;
    ui->labelTree->move(treeX, treeY);

    // рюкзак лежит под деревом
    bagX = treeX + 50;
    bagY = groundY + 78;
    ui->labelBackpack->move(bagX, bagY);
    ui->labelBackpack->setPixmap(bagClosed);

    // гг видно изначально
    heroX = -80;
    heroY = groundY;
    ui->labelHero->move(heroX, heroY);
    ui->labelHero->setPixmap(heroWalkRight.isNull() ? heroWalk : heroWalkRight);

    // злодей за краем справа
    enemyX = width() + 220;
    enemyY = groundY;
    ui->labelEnemy->move(enemyX, enemyY);
    ui->labelEnemy->setPixmap(enemyLeft);

    // звезда стартует выше поля зрения
    starX = width()/2 - 60;
    starY = -100;
    ui->labelStar->move(starX, starY);

    // кулон скрыт
    ui->labelPendant->hide();

    // реплики скрыты
    ui->labelText->hide();
    ui->labelText->setText("");

    // где герой “под деревом”
    heroStopX = treeX - 140;

    // приземление звезды
    starLandY = height() - ui->labelStar->height() - 20;
}

void MainWindow::onFrame()
{
    const int dx = 5;
    const int dy = 5;

    const int TALK_SHORT = 110;
    const int TALK_LONG  = 140;
    const int PAUSE      = 40;

    auto hideSay = [&]() {
        ui->labelText->hide();
        ui->labelText->setText("");
    };

    auto sayFor = [&](QLabel* who, const QString& text, int yOffset = 10)
    {
        if (!who) return;

        QRect r = who->geometry();
        if (r.right() < -80 || r.left() > width() + 80) {
            hideSay();
            return;
        }

        ui->labelText->setText(text);

        int x = r.center().x() - ui->labelText->width()/2;
        int y = r.y() - ui->labelText->height() + yOffset;

        x = std::clamp(x, 10, width() - ui->labelText->width() - 10);
        y = std::clamp(y, 10, height() - ui->labelText->height() - 10);

        ui->labelText->move(x, y);
        ui->labelText->show();
    };

    switch (stage)
    {

    // 0: ГГ идёт к дереву
    case 0:
    {
        hideSay();

        // идёт вправо
        ui->labelHero->setPixmap(heroWalkRight.isNull() ? heroWalk : heroWalkRight);

        heroX += dx;
        ui->labelHero->move(heroX, heroY);

        if (heroX >= heroStopX) {
            ui->labelHero->setPixmap(heroIdle);
            stage = 1;
            step = 0;
        }
        break;
    }

    // 1: ГГ говорит
    case 1:
    {
        sayFor(ui->labelHero, "Фух… под деревом самое то.");
        if (++step > TALK_LONG) { stage = 2; step = 0; }
        break;
    }

    // 2: Открывает рюкзак
    case 2:
    {
        sayFor(ui->labelHero, "Посмотрю, что в рюкзаке…");
        if (step == PAUSE) ui->labelBackpack->setPixmap(bagOpen);

        if (++step > TALK_LONG) { stage = 3; step = 0; }
        break;
    }

    // 3: Кулон вылетает (потом в карман)
    case 3:
    {
        const int PUT_AWAY_AT = 70;
        const int END_AT      = PUT_AWAY_AT + TALK_LONG;

        if (step < PUT_AWAY_AT) {
            sayFor(ui->labelHero, "Ого! Магия?!");
        } else {
            sayFor(ui->labelHero, "Ладно… уберу в карман.");
        }

        if (step == 0) {
            ui->labelHero->setPixmap(heroSurprised);
            pendX = bagX + 20;
            pendY = bagY + 10;
            ui->labelPendant->move(pendX, pendY);
            ui->labelPendant->show();
        }

        // Кулон “вылетает вверх”
        if (step < 40) {
            pendY -= 2;
            ui->labelPendant->move(pendX, pendY);
        }

        // “убрал в карман”
        if (step == PUT_AWAY_AT) {
            ui->labelPendant->hide();
            ui->labelHero->setPixmap(heroIdle);
        }

        if (++step > END_AT) {
            stage = 4; step = 0;
            hideSay();
        }
        break;
    }

    // 4: Злодей подходит и говорит
    case 4:
    {
        ui->labelEnemy->setPixmap(enemyLeft);

        int enemyStopX = heroX + 260;

        if (enemyX > enemyStopX) {
            enemyX -= dx;
            ui->labelEnemy->move(enemyX, enemyY);
        }

        // Говорит, когда вошёл в кадр
        if (ui->labelEnemy->geometry().left() < width() - 250) {
            sayFor(ui->labelEnemy, "Эй… что это у тебя?");
        } else {
            hideSay();
        }

        if (++step > TALK_LONG) { stage = 5; step = 0; hideSay(); }
        break;
    }

    // 5: Герой с мечом, злодей "Оу" и убегает
    case 5:
    {
        if (step == 0) {
            ui->labelHero->setPixmap(heroSword);
        }

        if (step < TALK_SHORT) {
            sayFor(ui->labelHero, "Не подходи!");
        }

        if (step == TALK_SHORT) {
            sayFor(ui->labelEnemy, "Оу… эм… я пошёл!");
        }

        if (step == TALK_SHORT + PAUSE) {
            ui->labelEnemy->setPixmap(enemyRight);
        }

        if (step >= TALK_SHORT + PAUSE) {
            enemyX += dx + 6;
            ui->labelEnemy->move(enemyX, enemyY);
        }

        if (++step > (TALK_SHORT + PAUSE + TALK_LONG)) {
            ui->labelHero->setPixmap(heroIdle);
            stage = 6; step = 0;
            hideSay();
        }
        break;
    }

    // 6: Звезда в небе говорит
    case 6:
    {
        sayFor(ui->labelStar, "Молодец, храбрый воин!", 40);
        if (++step > TALK_LONG) { stage = 7; step = 0; hideSay(); }
        break;
    }

    // 7: Звезда приземляется и говорит
    case 7:
    {
        if (starY < starLandY) {
            starY += dy;
            if (starY > starLandY) starY = starLandY;
            ui->labelStar->move(starX, starY);
            hideSay();
        } else {
            sayFor(ui->labelStar, "Полетели со мной!", 40);
            if (++step > TALK_LONG) { stage = 8; step = 0; hideSay(); }
        }
        break;
    }

    // 8: Герой подходит к звезде шагами и встает
    case 8:
    {
        int heroOnStarX = starX + (ui->labelStar->width() - ui->labelHero->width()) / 2;
        int heroOnStarY = starY - ui->labelHero->height() + 45;

        int prevX = heroX;

        heroX = stepTowards(heroX, heroOnStarX, dx);
        heroY = stepTowards(heroY, heroOnStarY, dy);

        if (heroX != prevX) {
            if (heroX > prevX) {
                ui->labelHero->setPixmap(heroWalkRight.isNull() ? heroWalk : heroWalkRight);
            } else {
                ui->labelHero->setPixmap(heroWalkLeft.isNull() ? heroWalk : heroWalkLeft);
            }
        } else {
            ui->labelHero->setPixmap(heroIdle);
        }

        ui->labelHero->move(heroX, heroY);

        if (step < TALK_SHORT) {
            sayFor(ui->labelHero, "Вперёд!");
        } else {
            hideSay();
        }

        if (heroX == heroOnStarX && heroY == heroOnStarY && step > TALK_SHORT) {
            stage = 9; step = 0;
        } else {
            step++;
        }
        break;
    }

    // 9: Улетели вместе
    case 9:
    {
        hideSay();

        starY -= dy;
        ui->labelStar->move(starX, starY);

        int heroOnStarX = starX + (ui->labelStar->width() - ui->labelHero->width()) / 2;
        int heroOnStarY = starY - ui->labelHero->height() + 45;
        ui->labelHero->move(heroOnStarX, heroOnStarY);

        if (++step > 220) { stage = 10; step = 0; }
        break;
    }

    default:
        timer->stop();
        break;
    }
}
