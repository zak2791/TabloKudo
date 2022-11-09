#include "pcscreen.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>

PcScreen::PcScreen(QWidget *parent) : QWidget(parent){

    numFight = 1;

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

    han_blue = new Hansoku("white", this);
    han_blue->setFrameShape(QFrame::Box);
    connect(han_blue, SIGNAL(sigHansoku(int)), this, SLOT(changeBallWhite(int)));

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

    han_white = new Hansoku("blue", this);
    han_white->setFrameShape(QFrame::Box);
    //han_white->setSizePolicy(Policy::Ignored);
    connect(han_white, SIGNAL(sigHansoku(int)), this, SLOT(changeBallBlue(int)));

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
    btnCukami = new QPushButton("ЦУКАМИ", this);
    btnCukami->setStyleSheet("color: blue");
    btnParter = new QPushButton("ПАРТЕР", this);
    btnParter->setStyleSheet("color: red");
    btnSettings = new QPushButton("НАСТРОЙКИ", this);
    //btnSettings->setStyleSheet("color: red");
    btnTimer = new QPushButton("ТАЙМЕР", this);
    btnTimer->setStyleSheet("color: yellow");

    connect(btnTime, SIGNAL(clicked()), this, SLOT(manageTime()));
    connect(btnParter, SIGNAL(clicked()), this, SLOT(manageParter()));
    connect(btnCukami, SIGNAL(clicked()), this, SLOT(manageCukami()));
    connect(btnTimer, SIGNAL(clicked()), this, SLOT(manageTimer()));
    connect(btnSettings, SIGNAL(clicked()), this, SLOT(settings()));

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
    grid->addWidget(cukamiTimer, 16, 17, 12, 21);
    grid->addWidget(parterTimer, 16, 17, 12, 21);
    grid->addWidget(stopwatch,   16, 17, 12, 21);

    grid->addWidget(lblBallBlue, 28, 0,  3, 16);
    grid->addWidget(lblBallRed,  28, 39, 3, 16);

    grid->addWidget(btnCukami,   28,  17, 3, 6);
    grid->addWidget(btnTime,     28,  24, 3, 7);
    grid->addWidget(btnParter,   28,  32, 3, 6);

    frmSettings = new QWidget;
    frmSettings->setWindowModality(Qt::ApplicationModal);
    ui.setupUi(frmSettings);
    connect(ui.lwKoef, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(choiceKoef(QListWidgetItem*)));
    connect(ui.rb300, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    connect(ui.rb200, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    connect(ui.rb130, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    connect(ui.rb100, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));

    if(QGuiApplication::screens().count() == 2){
        showFullScreen();
    }else{
        show();
        setGeometry(QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2,
                    QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2);
    }

    //if (desk->numScreens() == 1) {
    if(QGuiApplication::screens().count() == 1){
        QMessageBox::information(this, "ВНИМАНИЕ!",
        "Подключите к компьютеру дисплей в режиме \"Расширенный рабочий стол!\"",
        QMessageBox::Ok);
    }
    tvScreen = new TVScreen();

    if(QGuiApplication::screens().count() == 1)
        tvScreen->setGeometry(0, 0, QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2);
    else{
        tvScreen->setGeometry(width(), 0, 100, height());
        tvScreen->setGeometry(QApplication::desktop()->availableGeometry(this).right(),
                        0, QApplication::desktop()->availableGeometry(tvScreen).width(),
                        QApplication::desktop()->availableGeometry(tvScreen).height());
    }

    connect(vaz_blue,	SIGNAL(sigRate(int)),		tvScreen->vaz_blue,	  SLOT(setRate(int)));
    connect(uko_blue,	SIGNAL(sigRate(int)),		tvScreen->uko_blue,   SLOT(setRate(int)));
    connect(kok_blue,   SIGNAL(sigRate(int)),		tvScreen->kok_blue,	  SLOT(setRate(int)));
    connect(rate_blue,	SIGNAL(sigRate(int)),		tvScreen->rate_blue,  SLOT(setRate(int)));

    connect(vaz_white,	SIGNAL(sigRate(int)),		tvScreen->vaz_white,  SLOT(setRate(int)));
    connect(uko_white,	SIGNAL(sigRate(int)),		tvScreen->uko_white,  SLOT(setRate(int)));
    connect(kok_white,  SIGNAL(sigRate(int)),		tvScreen->kok_white,  SLOT(setRate(int)));
    connect(rate_white,	SIGNAL(sigRate(int)),		tvScreen->rate_white, SLOT(setRate(int)));

    connect(mainTimer,   SIGNAL(sigTime(QString,QPalette)), tvScreen->mainTimer ,  SLOT(showTime(QString,QPalette)));
    connect(cukamiTimer, SIGNAL(sigVisible(bool)),          tvScreen->cukamiTimer, SLOT(setVisible(bool)));
    connect(cukamiTimer, SIGNAL(sigTime(QString,QPalette)), tvScreen->cukamiTimer, SLOT(showTime(QString,QPalette)));
    connect(parterTimer, SIGNAL(sigVisible(bool)),          tvScreen->parterTimer, SLOT(setVisible(bool)));
    connect(parterTimer, SIGNAL(sigTime(QString,QPalette)), tvScreen->parterTimer, SLOT(showTime(QString,QPalette)));
    connect(stopwatch,   SIGNAL(sigVisible(bool)),          tvScreen->stopwatch,   SLOT(setVisible(bool)));
    connect(stopwatch,   SIGNAL(sigTime(QString,QPalette)), tvScreen->stopwatch,   SLOT(showTime(QString,QPalette)));

    connect(han_blue,    SIGNAL(sigStyle(int)),             tvScreen->han_blue,    SLOT(setStyleAndText(int)));
    connect(han_white,   SIGNAL(sigStyle(int)),             tvScreen->han_white,   SLOT(setStyleAndText(int)));

    tvScreen->show();

}

PcScreen::~PcScreen()
{
}

void PcScreen::closeEvent(QCloseEvent*){
    QApplication::exit();
}

void PcScreen::choiceMainTime(bool checked){
    if(checked){
        if(sender() == ui.rb300)
            mainTimer->setTime(180);
        else if(sender() == ui.rb200)
            mainTimer->setTime(120);
        else if(sender() == ui.rb130)
            mainTimer->setTime(90);
        else if(sender() == ui.rb100)
            mainTimer->setTime(60);
    }
}

void PcScreen::choiceKoef(QListWidgetItem* item){
    lblKoeffValue->setText(item->text());
}

void PcScreen::settings(){
    if(!(cukamiTimer->isVisible()) && mainTimer->getStatus() == 0){
        frmSettings->show();
    }
}

void PcScreen::manageTime(){
    if(stopwatch->isVisible() == true)
        return;
    mainTimer->StartStop();
    if(parterTimer->isVisible()){
        parterTimer->StartStop();
        parterTimer->Reset();
        parterTimer->setVisible(false);
    }else if(cukamiTimer->isVisible()){
        cukamiTimer->StartStop();
        cukamiTimer->Reset();
        cukamiTimer->setVisible(false);
    }
}

void PcScreen::manageTimer(){
    if(mainTimer->isVisible() && (mainTimer->getStatus() != 1)){
        if(!stopwatch->isVisible()){
            stopwatch->setVisible(true);
            stopwatch->StartStop();
        }else{
            if(stopwatch->getStatus() == 1){
                stopwatch->StartStop();
            }else{
                stopwatch->Reset();
                stopwatch->hide();
            }
        }
    }
}


void PcScreen::manageParter(){
    if(mainTimer->getStatus() == 1){
        if(parterTimer->isVisible()){
            parterTimer->StartStop();
            parterTimer->Reset();
            parterTimer->setVisible(false);
        }else{
            parterTimer->setVisible(true);
            parterTimer->StartStop();
            if(cukamiTimer->isVisible()){
                cukamiTimer->StartStop();
                cukamiTimer->Reset();
                cukamiTimer->setVisible(false);
            }
        }
    }
}

void PcScreen::manageCukami(){
    if(mainTimer->getStatus() == 1 && !(parterTimer->isVisible())){
        if(cukamiTimer->isVisible()){
            cukamiTimer->StartStop();
            cukamiTimer->Reset();
            cukamiTimer->setVisible(false);
        }else{
            cukamiTimer->setVisible(true);
            cukamiTimer->StartStop();
        }
    }
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
    font.setPixelSize(h * 0.8);
    lblKoeff->setFont(font);
    lblFight->setFont(font);
    h = lblKoeffValue->height();
    font.setPixelSize(h * 0.8);
    lblKoeffValue->setFont(font);
    lblFightValue->setFont(font);

    int minHeight = height() * 2 / 31;
    btnTime->setMinimumHeight(minHeight);
    btnCukami->setMinimumHeight(minHeight);
    btnParter->setMinimumHeight(minHeight);
    btnSettings->setMinimumHeight(minHeight);
    btnTimer->setMinimumHeight(minHeight);

    h = btnTime->height();
    font.setPixelSize(h * 0.4);
    btnTime->setFont(font);
    btnCukami->setFont(font);
    btnParter->setFont(font);
    btnSettings->setFont(font);
    btnTimer->setFont(font);

}

void PcScreen::changeBallWhite(int b){
    int r = rate_white->getRate() + b;
    if(r > 0)
        rate_white->setRate(r);
    else
        rate_white->setRate(0);
}

void PcScreen::changeBallBlue(int b){
    int r = rate_blue->getRate() + b;
    if(r > 0)
        rate_blue->setRate(r);
    else
        rate_blue->setRate(0);
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

void PcScreen::keyPressEvent(QKeyEvent * e){
    if(e->key() == Qt::Key_Backspace){
        qDebug()<<e->modifiers();
        if(e->modifiers() != Qt::AltModifier)
            Reset();
        else
            Fight(-1);
    }
    else if(e->key() == Qt::Key_Escape){
        if(QMessageBox::question(0, "Выход", u8"Вы уверены?") == QMessageBox::No)
            return;
        else
            QApplication::exit();
    }else if(e->key() == Qt::Key_0)
        Fight(0);
    else if(e->key() == Qt::Key_1)
        Fight(1);
    else if(e->key() == Qt::Key_2)
        Fight(2);
    else if(e->key() == Qt::Key_3)
        Fight(3);
    else if(e->key() == Qt::Key_4)
        Fight(4);
    else if(e->key() == Qt::Key_5)
        Fight(5);
    else if(e->key() == Qt::Key_6)
        Fight(6);
    else if(e->key() == Qt::Key_7)
        Fight(7);
    else if(e->key() == Qt::Key_8)
        Fight(8);
    else if(e->key() == Qt::Key_9)
        Fight(9);
}

void PcScreen::Fight(int f){
    if(f != -1){
        if(numFight == 0){
            numFight = f;
            lblFightValue->setText(QString::number(numFight));
        }else if(numFight < 100){
            numFight = numFight * 10 + f;
            lblFightValue->setText(QString::number(numFight));
        }
    }else{
        if(numFight > 10){
            numFight = numFight / 10;
            lblFightValue->setText(QString::number(numFight));
        }else{
            numFight = 0;
            lblFightValue->setText("");
        }
    }
}

void PcScreen::Reset(){
    if(mainTimer->getStatus() == 1 || stopwatch->isVisible())
        return;
    if(QMessageBox::question(0, "Сброс", u8"Вы уверены?") == QMessageBox::No)
        return;
    vaz_blue->sbros();
    uko_blue->sbros();
    kok_blue->sbros();
    han_blue->sbros();
    vaz_white->sbros();
    uko_white->sbros();
    kok_white->sbros();
    han_white->sbros();

    rate_blue->sbros();
    rate_white->sbros();

    mainTimer->Reset();
    cukamiTimer->Reset();
    parterTimer->Reset();
}
