#include <QPainter>
#include <QGridLayout>
#include <QDebug>
#include <QPalette>

#include "tvscreen.h"

#include <QScreen>

TVScreen::TVScreen(QWidget * parent) : QWidget(parent) {
    vaz_blue = new Rate(this);
    vaz_blue->setFrameShape(QFrame::Box);
    vaz_blue->setObjectName("vaz_blue");

    uko_blue = new Rate(this);
    uko_blue->setFrameShape(QFrame::Box);
    uko_blue->setObjectName("uko_blue");

    kok_blue = new Rate(this);
    kok_blue->setFrameShape(QFrame::Box);
    kok_blue->setObjectName("kok_blue");

    han_blue = new Hansoku("white", this);
    han_blue->setFrameShape(QFrame::Box);

    vaz_white = new Rate(this);
    vaz_white->setFrameShape(QFrame::Box);
    vaz_white->setObjectName("vaz_white");
    vaz_white->setStyleSheet("QLabel{border-radius: 30px; "
                             "border-width: 2px; "
                             "border-style: solid; "
                             "border-color:blue; "
                             "background-color: black; "
                             "color: white;}");

    uko_white = new Rate(this);
    uko_white->setFrameShape(QFrame::Box);
    uko_white->setObjectName("uko_white");
    uko_white->setStyleSheet("QLabel{border-radius: 30px; "
                             "border-width: 2px; "
                             "border-style: solid; "
                             "border-color:blue; "
                             "background-color: black; "
                             "color: white;}");

    kok_white = new Rate(this);
    kok_white->setFrameShape(QFrame::Box);
    kok_white->setObjectName("kok_white");
    kok_white->setStyleSheet("QLabel{border-radius: 30px; "
                             "border-width: 2px; "
                             "border-style: solid; "
                             "border-color:blue; "
                             "background-color: black; "
                             "color: white;}");

    han_white = new Hansoku("blue", this);
    han_white->setFrameShape(QFrame::Box);

    rate_blue = new Rate(this);
    rate_blue->setFrameShape(QFrame::Box);

    rate_white = new Rate(this);
    rate_white->setFrameShape(QFrame::Box);

    mainTimer = new LCDTimer(this);
    cukamiTimer = new LCDTimer(this, "0:10", QColor(0, 0, 255), QColor(0, 0, 255));
    cukamiTimer->setVisible(false);
    parterTimer = new LCDTimer(this, "0:30", QColor(255, 0, 0), QColor(255, 0, 0));
    parterTimer->setVisible(false);

    stopwatch = new LCDStopwatch(this, "3:00", QColor(255, 255, 0), QColor(255, 255, 0), true);
    stopwatch->setVisible(false);

    //QLabel* lbl = new QLabel(this);

    lblBallBlue = new QLabel("POINTS", this);
    lblBallBlue->setStyleSheet("color: white;");
    lblBallBlue->setAlignment(Qt::AlignCenter);
    lblBallRed = new QLabel("POINTS", this);
    lblBallRed->setStyleSheet("color: blue");
    lblBallRed->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    lblVazBlue =  new QLabel("WAZA-ARI", this);
    lblVazBlue->setStyleSheet("color: white;");
    lblVazBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblUkoBlue =  new QLabel("YUKO", this);
    lblUkoBlue->setStyleSheet("color: white;");
    lblUkoBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblKokBlue =  new QLabel("KOKA", this);
    lblKokBlue->setStyleSheet("color: white;");
    lblKokBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblHanBlue =  new QLabel("HANSOKU", this);
    lblHanBlue->setStyleSheet("color: white;");
    lblHanBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblVazWhite =  new QLabel("WAZA-ARI", this);
    lblVazWhite->setStyleSheet("color: blue;");
    lblVazWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblUkoWhite =  new QLabel("YUKO", this);
    lblUkoWhite->setStyleSheet("color: blue;");
    lblUkoWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblKokWhite =  new QLabel("KOKA", this);
    lblKokWhite->setStyleSheet("color: blue;");
    lblKokWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblHanWhite =  new QLabel("HANSOKU", this);
    lblHanWhite->setStyleSheet("color: blue;");
    lblHanWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    lblKoeff =  new QLabel("PI (PHYSICAL INDEX)", this);
    lblKoeff->setStyleSheet("color: white;");
    lblKoeff->setAlignment(Qt::AlignCenter);

    lblKoeffValue =  new QLabel("230", this);
    lblKoeffValue->setStyleSheet("color: white;");
    lblKoeffValue->setAlignment(Qt::AlignCenter);

    lblFight =  new QLabel("FIGHT №", this);
    lblFight->setStyleSheet("color: blue;");
    lblFight->setAlignment(Qt::AlignCenter);

    lblFightValue =  new QLabel("1", this);
    lblFightValue->setStyleSheet("color: blue;");
    lblFightValue->setAlignment(Qt::AlignCenter);



    QGridLayout* grid = new QGridLayout(this);
    //spacing = 6;
    //margin = 6;
    //сетка 56х31
    grid->setSpacing(0);
    grid->setMargin(5);

    //grid->SetNoConstraint;

    grid->addWidget(vaz_blue,    0,  28, 8,  6);
    grid->addWidget(lblVazBlue,  8,  28, 2,  6);
    grid->addWidget(uko_blue,    0,  35, 8,  6);
    grid->addWidget(lblUkoBlue,  8,  35, 2,  6);
    grid->addWidget(kok_blue,    0, 42, 8,  6);
    grid->addWidget(lblKokBlue,  8, 42, 2,  6);
    grid->addWidget(han_blue,    0, 49, 8,  6);
    grid->addWidget(lblHanBlue,  8, 49, 2,  6);

    grid->addWidget(lblKoeff,       10, 28, 2,  27);
    grid->addWidget(lblKoeffValue,  12, 28, 4,  27);

    grid->addWidget(vaz_white,   0, 0, 8,  6);
    grid->addWidget(lblVazWhite, 8, 0, 2,  6);
    grid->addWidget(uko_white,   0, 7, 8,  6);
    grid->addWidget(lblUkoWhite, 8, 7, 2,  6);
    grid->addWidget(kok_white,   0, 14, 8,  6);
    grid->addWidget(lblKokWhite, 8, 14, 2,  6);
    grid->addWidget(han_white,   0, 21, 8,  6);
    grid->addWidget(lblHanWhite, 8, 21, 2,  6);

    grid->addWidget(lblFight,       10, 0, 2,  27);
    grid->addWidget(lblFightValue,  12, 0, 4,  27);

    grid->addWidget(rate_blue,  16,  39, 12, 16);
    grid->addWidget(rate_white, 16, 0, 12, 16);



    grid->addWidget(mainTimer,   16, 17, 12, 21);
    grid->addWidget(cukamiTimer, 16, 17, 12, 21);
    grid->addWidget(parterTimer, 16, 17, 12, 21);
    grid->addWidget(stopwatch,   16, 17, 12, 21);

    grid->addWidget(lblBallBlue, 28, 39,  3, 16);
    grid->addWidget(lblBallRed,  28, 0, 3, 16);





}

TVScreen::~TVScreen()
{
}

void TVScreen::paintEvent(QPaintEvent * ) {
    QPainter pn;
    pn.begin(this);

    pn.setBrush(Qt::white);
    pn.drawRect(0, 0, width() / 2, height());
    pn.setBrush(Qt::blue);
    pn.drawRect(width() / 2, 0, width() / 2, height());

    pn.end();
}



void TVScreen::resizeEvent(QResizeEvent *){
    int h = lblBallBlue->height();
    QFont font;
    font.setPixelSize(h * 0.8);
    font.setBold(true);
    lblBallBlue->setFont(font);
    lblBallRed->setFont(font);
    h = lblVazBlue->height();
    font.setPixelSize(h * 0.55);
    lblVazBlue->setFont(font);
    lblUkoBlue->setFont(font);
    lblKokBlue->setFont(font);
    lblHanBlue->setFont(font);
    lblVazWhite->setFont(font);
    lblUkoWhite->setFont(font);
    lblKokWhite->setFont(font);
    lblHanWhite->setFont(font);
    h = lblKoeff->height();
    font.setPixelSize(h * 0.8);
    lblKoeff->setFont(font);
    lblFight->setFont(font);
    h = lblKoeffValue->height();
    font.setPixelSize(h * 0.8);
    lblKoeffValue->setFont(font);
    lblFightValue->setFont(font);
}



