#ifndef PCSCREEN_H
#define PCSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "rate.h"
#include "hansoku.h"
#include "lcdtimer.h"
#include "lcdstopwatch.h"
#include "svglabel.h"
#include "svgpushbutton.h"
#include "ui_formsettings.h"
#include <QKeyEvent>
#include "tvscreen.h"
#include "nameandteam.h"
#include "listfamily.h"
#include "choosingnames.h"
#include "endtime.h"

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

    SvgLabel* lblVazWhite;
    SvgLabel* lblUkoWhite;
    SvgLabel* lblKokWhite;
    SvgLabel* lblHanWhite;
    SvgLabel* lblVazBlue;
    SvgLabel* lblUkoBlue;
    SvgLabel* lblKokBlue;
    SvgLabel* lblHanBlue;

    SvgLabel* lblKoeff;
    QLabel* lblKoeffValue;

    SvgLabel* lblAge;
    QLabel* lblAgeValue;

    SvgLabel* lblFight;
    QLabel* lblFightValue;

    SVGPushButton* btnTime;
    SVGPushButton* btnCukami;
    SVGPushButton* btnParter;
    SVGPushButton* btnSettings;
    SVGPushButton* btnTimer;
    SVGPushButton* btnResetTime;

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

    NameAndTeam* NameBlue;
    NameAndTeam* NameWhite;
    NameAndTeam* TeamBlue;
    NameAndTeam* TeamWhite;
    NameAndTeam* NameNextBlue;
    NameAndTeam* NameNextWhite;

    ListFamily * lf = nullptr;

    ChoosingNames* choosingNames = nullptr;

    //QGridLayout* grid;

    void switchLanguage(void);
    void setTvScreenGeometry(void);

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
    void choiceMainTime(int);

    void endTime(bool);
    void slotChangeId(bool);
    void resetTime(void);

    void closeTablo(void);
    void resetTablo(void);

    void showListSportsmens(void);
    void closeWinName(QString, QString, QString, QString, QString, QString, QString, QString);
    void delListNames(void);
    void drawTvScreenshot(void);

    void slotParter(void);

public slots:
    void initListNames(void);   //инициализация списков спортсменов
    void newListSportsmens(void);
    void choiceParterTime(bool);
    void slotHeightTimer(bool);

protected:
    void changeEvent(QEvent*);

public:
    PcScreen(MainWindow*, QWidget *parent = nullptr);
    MainWindow* mainwin;
    EndTime * lblEndTimer;         //красный фон по окончании времени
    ~PcScreen();
};
#endif // PCSCREEN_H
