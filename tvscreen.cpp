#include <QPainter>
#include <QGridLayout>
#include <QPalette>
#include "tvscreen.h"
#include <QScreen>
#include <QAction>

TVScreen::TVScreen(MainWindow* mWin, QWidget * parent) : QWidget(parent) {
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

    lblVazBlue =  new SvgLabel(":/images/vazaari_white_rus.svg", ":/images/vazaari_white_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblVazBlue, &SvgLabel::setLanguage);

    lblUkoBlue =  new SvgLabel(":/images/yuko_white_rus.svg", ":/images/yuko_white_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblUkoBlue, &SvgLabel::setLanguage);

    lblKokBlue =  new SvgLabel(":/images/koka_white_rus.svg", ":/images/koka_white_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblKokBlue, &SvgLabel::setLanguage);

    lblHanBlue =  new SvgLabel(":/images/hansoku_white_rus.svg", ":/images/hansoku_white_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblHanBlue, &SvgLabel::setLanguage);

    lblVazWhite =  new SvgLabel(":/images/vazaari_blue_rus.svg", ":/images/vazaari_blue_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblVazWhite, &SvgLabel::setLanguage);

    lblUkoWhite =  new SvgLabel(":/images/yuko_blue_rus.svg", ":/images/yuko_blue_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblUkoWhite, &SvgLabel::setLanguage);

    lblKokWhite =  new SvgLabel(":/images/koka_blue_rus.svg", ":/images/koka_blue_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblKokWhite, &SvgLabel::setLanguage);

    lblHanWhite =  new SvgLabel(":/images/hansoku_blue_rus.svg", ":/images/hansoku_blue_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblHanWhite, &SvgLabel::setLanguage);

    lblKoeffValue =  new QLabel("", this);
    lblKoeffValue->setStyleSheet("color: white;");
    lblKoeffValue->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    lblAgeValue =  new QLabel("", this);
    lblAgeValue->setStyleSheet("color: white;");
    lblAgeValue->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    lblFight =  new SvgLabel(":/images/fight_tv_rus.svg", ":/images/fight_tv_eng.svg");
    connect(mWin, &MainWindow::sigLanguage, lblFight, &SvgLabel::setLanguage);

    lblFightValue =  new QLabel("1", this);
    lblFightValue->setStyleSheet("color: blue;");
    lblFightValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    NameBlue = new FirstLastName("white", "", 63,"",this);

    TeamBlue = new NameAndTeam("white", "", 10, "Lucida Console");

    NameWhite = new FirstLastName("white", "", 63,"",this);

    TeamWhite = new NameAndTeam("white", "", 10, "Lucida Console");

    NameNextBlue = new NameAndTeam("white", "", 63,"",this);

    NameNextWhite = new NameAndTeam("white", "", 63,"",this);

    logo = new QLabel("Not\nactivated");
    logo->setStyleSheet("color: red;");
    logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid = new QGridLayout(this);
    grid->setSpacing(5);
    grid->addWidget(NameWhite,    0,  0, 8,  27);
    grid->addWidget(NameBlue,   0, 28, 8,  27);
    grid->addWidget(TeamWhite,    8,  0, 4,  27);
    grid->addWidget(TeamBlue,   8, 28, 4,  27);
    grid->addWidget(vaz_blue,    12,  28, 8,  6);
    grid->addWidget(lblVazBlue,  20,  28, 2,  6);
    grid->addWidget(uko_blue,    12,  35, 8,  6);
    grid->addWidget(lblUkoBlue,  20,  35, 2,  6);
    grid->addWidget(kok_blue,    12, 42, 8,  6);
    grid->addWidget(lblKokBlue,  20, 42, 2,  6);
    grid->addWidget(han_blue,    12, 49, 8,  6);
    grid->addWidget(lblHanBlue,  20, 49, 2,  6);
    grid->addWidget(lblKoeffValue,  24, 28, 4,  10);
    grid->addWidget(lblAgeValue,  24, 40, 4,  10);
    grid->addWidget(vaz_white,   12, 0, 8,  6);
    grid->addWidget(lblVazWhite, 20, 0, 2,  6);
    grid->addWidget(uko_white,   12, 7, 8,  6);
    grid->addWidget(lblUkoWhite, 20, 7, 2,  6);
    grid->addWidget(kok_white,   12, 14, 8,  6);
    grid->addWidget(lblKokWhite, 20, 14, 2,  6);
    grid->addWidget(han_white,   12, 21, 8,  6);
    grid->addWidget(lblHanWhite, 20, 21, 2,  6);
    grid->addWidget(lblFight,       24, 0, 4,  13);
    grid->addWidget(lblFightValue,  24, 13, 4, 13);
    grid->addWidget(rate_blue,  28,  39, 12, 16);
    grid->addWidget(rate_white, 28, 0, 12, 16);

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    settings->beginGroup("heightTimers");
    bool heightTimer = settings->value("heightTimer", true).toBool();
    settings->endGroup();

    if(heightTimer){
        grid->addWidget(mainTimer,   28, 17, 12, 21);
        grid->addWidget(cukamiTimer, 28, 17, 12, 21);
        grid->addWidget(parterTimer, 28, 17, 12, 21);
        grid->addWidget(stopwatch,   28, 17, 12, 21);
    }
    else{
        grid->addWidget(mainTimer,   29, 17, 10, 21);
        grid->addWidget(cukamiTimer, 29, 17, 10, 21);
        grid->addWidget(parterTimer, 29, 17, 10, 21);
        grid->addWidget(stopwatch,   29, 17, 10, 21);
    }

    grid->addWidget(NameNextBlue, 40, 28,  4, 27);
    grid->addWidget(NameNextWhite,  40, 0, 4, 27);
    grid->addWidget(logo,  0, 0, 44, 55);

    connect(mWin, SIGNAL(changeSizeName(int)),this, SLOT(slotChangeSize(int)));

    settings->beginGroup("height");
    HEIGHT_FAMILY = settings->value("HEIGHT_FAMILY", -1).toInt();
    HEIGHT_TEAM = settings->value("HEIGHT_TEAM", -1).toInt();
    HEIGHT_NEXT_FAMILY = settings->value("HEIGHT_NEXT_FAMILY", -1).toInt();
    settings->endGroup();

    grid->setRowMinimumHeight(0, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(1, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(2, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(3, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(4, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(5, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(6, HEIGHT_FAMILY);
    grid->setRowMinimumHeight(7, HEIGHT_FAMILY);

    grid->setRowMinimumHeight(8, HEIGHT_TEAM);
    grid->setRowMinimumHeight(9, HEIGHT_TEAM);
    grid->setRowMinimumHeight(10, HEIGHT_TEAM);
    grid->setRowMinimumHeight(11, HEIGHT_TEAM);

    grid->setRowMinimumHeight(40, HEIGHT_NEXT_FAMILY);
    grid->setRowMinimumHeight(41, HEIGHT_NEXT_FAMILY);
    grid->setRowMinimumHeight(42, HEIGHT_NEXT_FAMILY);
    grid->setRowMinimumHeight(43, HEIGHT_NEXT_FAMILY);

    main = mWin;

    lblEndTimer = new EndTime(this);

    QEvent ev(QEvent::LanguageChange);
    changeEvent(&ev);
}

TVScreen::~TVScreen()
{
    delete logo;
}

void TVScreen::removeLogo()
{
    grid->removeWidget(logo);
    delete logo;
    logo = nullptr;
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
    QFont font;
    font.setBold(true);
    int h = lblKoeffValue->height();
    font.setPixelSize(h * 0.7 );
    lblKoeffValue->setFont(font);
    lblFightValue->setFont(font);
    lblAgeValue->setFont(font);
    font.setPixelSize(height() / 5);
    if(logo != nullptr)
        logo->setFont(font);

    lblEndTimer->setGeometry(0, 0, width(), height());
}

void TVScreen::slotChangeSize(int i)
{
    settings->beginGroup("height");
    if(i == 1){
        int sz = grid->rowMinimumHeight(0);
        if(sz == 1)
            HEIGHT_FAMILY -= 2;
        else
            HEIGHT_FAMILY -= 1;
        grid->setRowMinimumHeight(0, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(1, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(2, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(3, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(4, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(5, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(6, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(7, HEIGHT_FAMILY);
        settings->setValue("HEIGHT_FAMILY", HEIGHT_FAMILY);
    }else if(i == 0){
        int sz = grid->rowMinimumHeight(0);
        if(sz == -1)
            HEIGHT_FAMILY += 2;
        else
            HEIGHT_FAMILY += 1;
        grid->setRowMinimumHeight(0, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(1, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(2, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(3, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(4, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(5, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(6, HEIGHT_FAMILY);
        grid->setRowMinimumHeight(7, HEIGHT_FAMILY);
        settings->setValue("HEIGHT_FAMILY", HEIGHT_FAMILY);
    }
    else if(i == 3){
        int sz = grid->rowMinimumHeight(8);
        if(sz == 1)
            HEIGHT_TEAM -= 2;
        else
            HEIGHT_TEAM -= 1;
        grid->setRowMinimumHeight( 8, HEIGHT_TEAM);
        grid->setRowMinimumHeight( 9, HEIGHT_TEAM);
        grid->setRowMinimumHeight(10, HEIGHT_TEAM);
        grid->setRowMinimumHeight(11, HEIGHT_TEAM);
        settings->setValue("HEIGHT_TEAM", HEIGHT_TEAM);
    }else if(i == 2){
        int sz = grid->rowMinimumHeight(8);
        if(sz == -1)
            HEIGHT_TEAM += 2;
        else
            HEIGHT_TEAM += 1;
        grid->setRowMinimumHeight( 8, HEIGHT_TEAM);
        grid->setRowMinimumHeight( 9, HEIGHT_TEAM);
        grid->setRowMinimumHeight(10, HEIGHT_TEAM);
        grid->setRowMinimumHeight(11, HEIGHT_TEAM);
        settings->setValue("HEIGHT_TEAM", HEIGHT_TEAM);
    }else if(i == 5){
        int sz = grid->rowMinimumHeight(40);
        if(sz == 1)
            HEIGHT_NEXT_FAMILY -= 2;
        else
            HEIGHT_NEXT_FAMILY -= 1;
        grid->setRowMinimumHeight(40, HEIGHT_NEXT_FAMILY);
        grid->setRowMinimumHeight(41, HEIGHT_NEXT_FAMILY);
        grid->setRowMinimumHeight(42, HEIGHT_NEXT_FAMILY);
        grid->setRowMinimumHeight(43, HEIGHT_NEXT_FAMILY);
        settings->setValue("HEIGHT_NEXT_FAMILY", HEIGHT_NEXT_FAMILY);
    }else if(i == 4){
        int sz = grid->rowMinimumHeight(40);
        if(sz == -1)
            HEIGHT_NEXT_FAMILY += 2;
        else
            HEIGHT_NEXT_FAMILY += 1;
        grid->setRowMinimumHeight(40, HEIGHT_NEXT_FAMILY);
        grid->setRowMinimumHeight(41, HEIGHT_NEXT_FAMILY);
        grid->setRowMinimumHeight(42, HEIGHT_NEXT_FAMILY);
        grid->setRowMinimumHeight(43, HEIGHT_NEXT_FAMILY);
        settings->setValue("HEIGHT_NEXT_FAMILY", HEIGHT_NEXT_FAMILY);
    }
    settings->endGroup();
}

void TVScreen::changeEvent(QEvent* event)
{
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            if(main->actLang->isChecked()){
                if(logo != nullptr)
                    logo->setText("Not\nactivated");
            }
            else{
                if(logo != nullptr)
                    logo->setText("Не\nактивировано");
            }
            break;
        default:
            break;
        }
    }
}

void TVScreen::mouseDoubleClickEvent(QMouseEvent*)
{
    if(windowState() == Qt::WindowFullScreen){
        QRect r = geometry();
        showNormal();
        setGeometry(r.x() + 100, r.y() + 100, r.width() / 2, r.height() / 2);
    }
    else{
        showFullScreen();
    }
}
