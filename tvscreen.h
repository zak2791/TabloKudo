#pragma once
#include <QWidget>
#include "lcdtimer.h"

#include <QLabel>
#include "hansoku.h"
#include "rate.h"

#include "lcdstopwatch.h"

class TVScreen : public QWidget {
	Q_OBJECT
public:
    explicit TVScreen(QWidget *parent = 0);

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



private:

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
	
	virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);



};
