#pragma once
#include <QWidget>
#include "lcdtimer.h"

#include <QLabel>
#include <QGridLayout>
#include <QSettings>
#include "hansoku.h"
#include "rate.h"

#include "lcdstopwatch.h"
#include "nameandteam.h"
#include "mainwindow.h"
#include "endtime.h"
#include "svglabel.h"

class TVScreen : public QWidget {
	Q_OBJECT
public:
    explicit TVScreen(MainWindow*, QWidget *parent = 0);
    EndTime* lblEndTimer;

    ~TVScreen();

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

    QLabel* lblFightValue;

    QLabel* lblKoeffValue;
    QLabel* lblAgeValue;

    FirstLastName* NameBlue;
    FirstLastName* NameWhite;
    NameAndTeam* NameNextBlue;
    NameAndTeam* NameNextWhite;
    NameAndTeam* TeamBlue;
    NameAndTeam* TeamWhite;

    QGridLayout* grid;

    void removeLogo(void);

private:

    QLabel* lblBallBlue;
    QLabel* lblBallRed;

    SvgLabel* lblVazWhite;
    SvgLabel* lblUkoWhite;
    SvgLabel* lblKokWhite;
    SvgLabel* lblHanWhite;
    SvgLabel* lblVazBlue;
    SvgLabel* lblUkoBlue;
    SvgLabel* lblKokBlue;
    SvgLabel* lblHanBlue;

    QLabel* logo;


    //QLabel* lblKoeff;
    //QLabel* lblAge;

    SvgLabel* lblFight;

    int HEIGHT_FAMILY;
    int HEIGHT_TEAM;
    int HEIGHT_NEXT_FAMILY;

    QSettings* settings;

    MainWindow* main;

	virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);

    void mouseDoubleClickEvent(QMouseEvent *);

protected:
    void changeEvent(QEvent*);

private slots:
    void slotChangeSize(int);

};
