#ifndef PCSCREEN_H
#define PCSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "rate.h"
#include "hansoku.h"
#include "lcdtimer.h"
#include "lcdstopwatch.h"
#include "ui_formsettings.h"
#include <QKeyEvent>
#include "tvscreen.h"

class PcScreen : public QWidget {
    Q_OBJECT

private:
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void closeEvent(QCloseEvent *);

    void Reset(void);
    void Fight(int);
    int rec(int);

    QLineEdit* leId;
    QString serialNumberBios;
    QString serialNumberMac = "";

    QLabel* lblBallBlue;
    QLabel* lblBallRed;

    QLabel* lblVazWhite;
    QLabel* lblUkoWhite;
    QLabel* lblKokWhite;
    QLabel* lblHanWhite;
    QLabel* lblVazBlue;
    QLabel* lblUkoBlue;
    QLabel* lblKokBlue;
    QLabel* lblHanBlue;

    QLabel* lblKoeff;
    QLabel* lblKoeffValue;

    QLabel* lblFight;
    QLabel* lblFightValue;

    QPushButton* btnTime;
    QPushButton* btnCukami;
    QPushButton* btnParter;
    QPushButton* btnSettings;
    QPushButton* btnTimer;

    Rate* vaz_blue;
    Rate* uko_blue;
    Rate* kok_blue;
    Hansoku* han_blue;
    Rate* vaz_white;
    Rate* uko_white;
    Rate* kok_white;
    Hansoku* han_white;

    Rate* rate_blue;
    Rate* rate_white;

    LCDTimer* mainTimer;
    LCDTimer* cukamiTimer;
    LCDTimer* parterTimer;
    LCDStopwatch * stopwatch;

    Ui::FormSettings ui;
    QWidget* frmSettings;

    int numFight;

    TVScreen* tvScreen;

    QString calculateCode(QString);

private slots:
    void setBallBlue(bool);
    void setBallWhite(bool);
    void changeBallWhite(int);
    void changeBallBlue(int);
    void manageTime(void);
    void manageParter(void);
    void manageCukami(void);
    void manageTimer(void);
    void settings(void);
    void choiceKoef(QListWidgetItem*);
    void choiceMainTime(bool);
    void choiceParterTime(bool);
    void endTime(bool);
    void slotChangeId(bool);

public:
    PcScreen(QWidget *parent = nullptr);
    ~PcScreen();
};
#endif // PCSCREEN_H
