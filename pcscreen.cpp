#include "pcscreen.h"
#include <QPainter>
#include <QGridLayout>
#include "lcdtimer.h"

PcScreen::PcScreen(QWidget *parent) : QWidget(parent){

    vaz_blue = new Rate(this);
    vaz_blue->setFrameShape(QFrame::Box);
    vaz_blue->setObjectName("vaz_blue");
    connect(vaz_blue, SIGNAL(sigPlusMinus(bool)), this, SLOT(setBallBlue(bool)));

    uko_blue = new Rate(this);
    uko_blue->setFrameShape(QFrame::Box);
    uko_blue->setObjectName("uko_blue");
    connect(uko_blue, SIGNAL(sigPlusMinus(bool)), this, SLOT(setBallBlue(bool)));

    kok_blue = new Rate(this);
    kok_blue->setFrameShape(QFrame::Box);
    kok_blue->setObjectName("kok_blue");
    connect(kok_blue, SIGNAL(sigPlusMinus(bool)), this, SLOT(setBallBlue(bool)));

    han_blue = new Hansoku(this);
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
    connect(vaz_white, SIGNAL(sigPlusMinus(bool)), this, SLOT(setBallWhite(bool)));


    uko_white = new Rate(this);
    uko_white->setFrameShape(QFrame::Box);
    uko_white->setObjectName("uko_white");
    uko_white->setStyleSheet("QLabel{border-radius: 30px; "
                             "border-width: 2px; "
                             "border-style: solid; "
                             "border-color:blue; "
                             "background-color: black; "
                             "color: white;}");
    connect(uko_white, SIGNAL(sigPlusMinus(bool)), this, SLOT(setBallWhite(bool)));

    kok_white = new Rate(this);
    kok_white->setFrameShape(QFrame::Box);
    kok_white->setObjectName("kok_white");
    kok_white->setStyleSheet("QLabel{border-radius: 30px; "
                             "border-width: 2px; "
                             "border-style: solid; "
                             "border-color:blue; "
                             "background-color: black; "
                             "color: white;}");
    connect(kok_white, SIGNAL(sigPlusMinus(bool)), this, SLOT(setBallWhite(bool)));

    han_white = new Hansoku(this);
    han_white->setFrameShape(QFrame::Box);
    han_white->setStyleSheet("QLabel{border-radius: 30px; "
                             "border-width: 2px; "
                             "border-style: solid; "
                             "border-color:blue; "
                             "background-color: black; "
                             "color: white;}");

    rate_blue = new Rate(this);
    rate_blue->setFrameShape(QFrame::Box);

    rate_white = new Rate(this);
    rate_white->setFrameShape(QFrame::Box);

    LCDTimer* mainTimer = new LCDTimer(this);

    //QLabel* lbl = new QLabel(this);

    lblBallBlue = new QLabel("БАЛЛЫ", this);
    lblBallBlue->setStyleSheet("color: white;");
    lblBallBlue->setAlignment(Qt::AlignCenter);
    lblBallRed = new QLabel("БАЛЛЫ", this);
    lblBallRed->setStyleSheet("color: blue");
    lblBallRed->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    lblVazBlue =  new QLabel("ВАЗАРИ", this);
    lblVazBlue->setStyleSheet("color: white;");
    lblVazBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblUkoBlue =  new QLabel("ЮКО", this);
    lblUkoBlue->setStyleSheet("color: white;");
    lblUkoBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblKokBlue =  new QLabel("КОКА", this);
    lblKokBlue->setStyleSheet("color: white;");
    lblKokBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblHanBlue =  new QLabel("ХАНСОКУ", this);
    lblHanBlue->setStyleSheet("color: white;");
    lblHanBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblVazWhite =  new QLabel("ВАЗАРИ", this);
    lblVazWhite->setStyleSheet("color: blue;");
    lblVazWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblUkoWhite =  new QLabel("ЮКО", this);
    lblUkoWhite->setStyleSheet("color: blue;");
    lblUkoWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblKokWhite =  new QLabel("КОКА", this);
    lblKokWhite->setStyleSheet("color: blue;");
    lblKokWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblHanWhite =  new QLabel("ХАНСОКУ", this);
    lblHanWhite->setStyleSheet("color: blue;");
    lblHanWhite->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    lblKoeff =  new QLabel("КОЭФФИЦИЕНТ", this);
    lblKoeff->setStyleSheet("color: white;");
    lblKoeff->setAlignment(Qt::AlignCenter);

    lblKoeffValue =  new QLabel("230", this);
    lblKoeffValue->setStyleSheet("color: white;");
    lblKoeffValue->setAlignment(Qt::AlignCenter);

    lblFight =  new QLabel("БОЙ №", this);
    lblFight->setStyleSheet("color: blue;");
    lblFight->setAlignment(Qt::AlignCenter);

    lblFightValue =  new QLabel("1", this);
    lblFightValue->setStyleSheet("color: blue;");
    lblFightValue->setAlignment(Qt::AlignCenter);

    btnTime = new QPushButton("ВРЕМЯ", this);
    btnTime->setStyleSheet("color: green");
    btnCucami = new QPushButton("ЦУКАМИ", this);
    btnCucami->setStyleSheet("color: blue");
    btnParter = new QPushButton("ПАРТЕР", this);
    btnParter->setStyleSheet("color: red");
    btnSettings = new QPushButton("НАСТРОЙКИ", this);
    //btnSettings->setStyleSheet("color: red");
    btnTimer = new QPushButton("ТАЙМЕР", this);
    btnTimer->setStyleSheet("color: yellow");

    QGridLayout* grid = new QGridLayout(this);
    //spacing = 6;
    //margin = 6;
    //сетка 56х31
    grid->setSpacing(0);
    grid->setMargin(5);

    //grid->SetNoConstraint;

    grid->addWidget(vaz_blue,    0,  0, 8,  6);
    grid->addWidget(lblVazBlue,  8,  0, 2,  6);
    grid->addWidget(uko_blue,    0,  7, 8,  6);
    grid->addWidget(lblUkoBlue,  8,  7, 2,  6);
    grid->addWidget(kok_blue,    0, 14, 8,  6);
    grid->addWidget(lblKokBlue,  8, 14, 2,  6);
    grid->addWidget(han_blue,    0, 21, 8,  6);
    grid->addWidget(lblHanBlue,  8, 21, 2,  6);

    grid->addWidget(lblKoeff,       10, 0, 2,  27);
    grid->addWidget(lblKoeffValue,  12, 0, 4,  27);

    grid->addWidget(vaz_white,   0, 28, 8,  6);
    grid->addWidget(lblVazWhite, 8, 28, 2,  6);
    grid->addWidget(uko_white,   0, 35, 8,  6);
    grid->addWidget(lblUkoWhite, 8, 35, 2,  6);
    grid->addWidget(kok_white,   0, 42, 8,  6);
    grid->addWidget(lblKokWhite, 8, 42, 2,  6);
    grid->addWidget(han_white,   0, 49, 8,  6);
    grid->addWidget(lblHanWhite, 8, 49, 2,  6);

    grid->addWidget(lblFight,       10, 28, 2,  27);
    grid->addWidget(lblFightValue,  12, 28, 4,  27);

    grid->addWidget(rate_blue,  16,  0, 12, 16);
    grid->addWidget(rate_white, 16, 39, 12, 16);

    grid->addWidget(btnSettings, 10, 24, 3, 7);
    grid->addWidget(btnTimer,    13, 24, 3, 7);

    grid->addWidget(mainTimer,   16, 17, 12, 21);

    grid->addWidget(lblBallBlue, 28, 0,  3, 16);
    grid->addWidget(lblBallRed,  28, 39, 3, 16);

    grid->addWidget(btnCucami,   28,  17, 3, 6);
    grid->addWidget(btnTime,     28,  24, 3, 7);
    grid->addWidget(btnParter,   28,  32, 3, 6);


}

PcScreen::~PcScreen()
{
}

void PcScreen::resizeEvent(QResizeEvent *){
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
    font.setPixelSize(h * 0.9);
    lblKoeff->setFont(font);
    lblFight->setFont(font);
    h = lblKoeffValue->height();
    font.setPixelSize(h * 0.8);
    lblKoeffValue->setFont(font);
    lblFightValue->setFont(font);

    int minHeight = height() * 2 / 31;
    btnTime->setMinimumHeight(minHeight);
    btnCucami->setMinimumHeight(minHeight);
    btnParter->setMinimumHeight(minHeight);
    btnSettings->setMinimumHeight(minHeight);
    btnTimer->setMinimumHeight(minHeight);

    h = btnTime->height();
    font.setPixelSize(h * 0.4);
    btnTime->setFont(font);
    btnCucami->setFont(font);
    btnParter->setFont(font);
    btnSettings->setFont(font);
    btnTimer->setFont(font);

}

void PcScreen::setBallBlue(bool b){
    if(sender()->objectName() == "vaz_blue"){
        if(b){
            rate_blue->plus();
            rate_blue->plus();
            rate_blue->plus();
            rate_blue->plus();
        }else{
            rate_blue->minus();
            rate_blue->minus();
            rate_blue->minus();
            rate_blue->minus();
        }
    }else if(sender()->objectName() == "uko_blue"){
        if(b){
            rate_blue->plus();
            rate_blue->plus();
        }else{
            rate_blue->minus();
            rate_blue->minus();
        }
    }else if(sender()->objectName() == "kok_blue"){
        if(b)
            rate_blue->plus();
        else
            rate_blue->minus();
    }
}

void PcScreen::setBallWhite(bool b){
    if(sender()->objectName() == "vaz_white"){
        if(b){
            rate_white->plus();
            rate_white->plus();
            rate_white->plus();
            rate_white->plus();
        }else{
            rate_white->minus();
            rate_white->minus();
            rate_white->minus();
            rate_white->minus();
        }
    }else if(sender()->objectName() == "uko_white"){
        if(b){
            rate_white->plus();
            rate_white->plus();
        }else{
            rate_white->minus();
            rate_white->minus();
        }
    }else if(sender()->objectName() == "kok_white"){
        if(b)
            rate_white->plus();
        else
            rate_white->minus();
    }
}

void PcScreen::paintEvent(QPaintEvent * ) {
    QPainter pn;
    pn.begin(this);

    pn.setBrush(Qt::blue);
    pn.drawRect(0, 0, width() / 2, height());
    pn.setBrush(Qt::white);
    pn.drawRect(width() / 2, 0, width() / 2, height());

    pn.end();
}
