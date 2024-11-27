#include "pcscreen.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QProcess>
//#include "qthread.h"
#include "qmenubar.h"
#include "ui_code.h"
#include <QSettings>
#include "QAction"

PcScreen::PcScreen(MainWindow* mw, QWidget *parent) : QWidget(parent){

    mainwin = mw;

    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("code");
    QString codeBios(settings.value("codeBios", "").toString());
    QString codeMacAddr(settings.value("codeMacAddr", "").toString());
    settings.endGroup();

    QProcess process(0);

    process.start ("cmd"); // Запуск потока cmd
    process.waitForStarted (); // Ожидание завершения процесса запуска и блокировка контакта по истечении 30 секунд
    process.write("getmac\n");
    process.closeWriteChannel();
    process.waitForFinished (); // Ожидание завершения процесса запуска, тайм-аут 30 с, затем блокировка контакта
    QRegularExpression re("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})|([0-9a-fA-F]{4}\\.[0-9a-fA-F]{4}\\.[0-9a-fA-F]{4})$");
    serialNumberMac = "";
    while(1){
        char buf[1024];
        qint64 lineLength = process.readLine(buf, sizeof(buf));
        if (lineLength == -1) {
            break;
        }
        QString s = QString::fromUtf8(buf);
        QList<QString> list = s.split(QRegExp("\\s+"));
        foreach(auto each, list){
            QRegularExpressionMatch match = re.match(each);
            if (match.hasMatch()) {
                serialNumberMac = each;
                break;
            }
        }
    }

    process.start ("cmd"); // Запуск потока cmd
    process.waitForStarted ();
    process.write("wmic bios get serialnumber\n");
    process.closeWriteChannel();
    process.waitForFinished (); // Ожидание завершения процесса запуска, тайм-аут 30 с, затем блокировка контакта
    QString s;
    int i = 0;
    while(1){
        s = QString::fromLocal8Bit(process.readLine());
        i++;
        if(s.contains("SerialNumber"))
            break;
    }
    serialNumberBios = QString::fromLocal8Bit(process.readLine()).simplified();

    QString readCode = "";
    QString serialNumber = "";
    if(codeBios != ""){
        readCode = codeBios;
        serialNumber = serialNumberBios;
    }
    else if(codeMacAddr != ""){
        readCode = codeMacAddr;
        serialNumber = serialNumberMac;
    }

    // int lenString = serialNumber.length();
    // int myListStart[lenString];
    // int myListEnd[lenString];
    // for(int i=0; i < lenString; i++)
    //         myListStart[i] = serialNumber.at(i).toLatin1();

    // QString code = "";
    // for(int i=0; i < lenString; i++){
    //     if(i < lenString - 1){
    //         myListEnd[i] = myListStart[i] + myListStart[i + 1];
    //     }else{
    //         myListEnd[i] = myListStart[i] + myListStart[0];
    //     }
    //     code = code + QString::number(rec(myListEnd[i]));
    // }

    QDialog* frmCode = new QDialog;
    Ui::dlgCode ui_code;
    ui_code.setupUi(frmCode);
    ui_code.leID->setText(serialNumberBios);
    frmCode->setModal(true);
    leId = ui_code.leID;
    connect(ui_code.rbBios, SIGNAL(toggled(bool)), this, SLOT(slotChangeId(bool)));

    // QFile file("key.txt");
    // if(!file.exists()){
    //     file.open(QIODevice::WriteOnly);
    //     file.close();
    // }

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

    settings.beginGroup("settigs_time");
    QString timeFight = settings.value("timeFight", "3:00").toString();
    QString timeParter = settings.value("timeParter", "0:30").toString();
    settings.endGroup();

    mainTimer = new LCDTimer(this);
    if(timeFight == "3:00")
        mainTimer->setTime(180);
    else if(timeFight == "2:00")
        mainTimer->setTime(120);
    else if(timeFight == "1:30")
        mainTimer->setTime(90);
    else
        mainTimer->setTime(60);

    cukamiTimer = new LCDTimer(this, "0:10", QColor(0, 0, 255), QColor(0, 0, 255));
    cukamiTimer->setVisible(false);

    parterTimer = new LCDTimer(this, "0:30", QColor(255, 0, 0), QColor(255, 0, 0));
    parterTimer->setVisible(false);
    if(timeParter == "0:30")
        parterTimer->setTime(30);
    else
        parterTimer->setTime(20);

    stopwatch = new LCDStopwatch(this, "3:00", QColor(255, 255, 0), QColor(255, 255, 0), true);
    stopwatch->setVisible(false);

    //QLabel* lbl = new QLabel(this);

    // lblBallBlue = new QLabel("POINTS", this);
    // lblBallBlue->setStyleSheet("color: white;");
    // lblBallBlue->setAlignment(Qt::AlignCenter);
    // lblBallRed = new QLabel("POINTS", this);
    // lblBallRed->setStyleSheet("color: blue");
    // lblBallRed->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    lblVazBlue =  new QLabel("ВАЗАРИ", this);//("WAZA-ARI", this);
    lblVazBlue->setStyleSheet("color: white;");
    lblVazBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblUkoBlue =  new QLabel("ЮКО", this);//("YUKO", this);
    lblUkoBlue->setStyleSheet("color: white;");
    lblUkoBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblKokBlue =  new QLabel("КОКА", this);//("KOKA", this);
    lblKokBlue->setStyleSheet("color: white;");
    lblKokBlue->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    lblHanBlue =  new QLabel("ХАНСОКУ", this);//("HANSOKU", this);
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

    lblKoeff =  new QLabel("КОЭФФИЦИЕНТ", this);//("PI (PHYSICAL INDEX)", this);
    lblKoeff->setStyleSheet("color: white;");
    lblKoeff->setAlignment(Qt::AlignCenter);

    lblKoeffValue =  new QLabel("", this);
    lblKoeffValue->setStyleSheet("color: white;");
    lblKoeffValue->setAlignment(Qt::AlignCenter);

    lblAge =  new QLabel("ВОЗРАСТ", this);
    lblAge->setStyleSheet("color: white;");
    lblAge->setAlignment(Qt::AlignCenter);

    lblAgeValue =  new QLabel("", this);
    lblAgeValue->setStyleSheet("color: white;");
    lblAgeValue->setAlignment(Qt::AlignCenter);

    lblFight =  new QLabel(tr("БОЙ №"), this);
    lblFight->setStyleSheet("color: blue;");
    lblFight->setAlignment(Qt::AlignCenter);

    lblFightValue =  new QLabel("1", this);
    lblFightValue->setStyleSheet("color: blue;");
    lblFightValue->setAlignment(Qt::AlignCenter);

    btnTime = new QPushButton("ВРЕМЯ", this);
    btnTime->setStyleSheet("color: green");
    btnCukami = new QPushButton("ЦУКАМИ", this);//("TSUKAMI", this);
    btnCukami->setStyleSheet("color: blue");
    btnParter = new QPushButton("ПАРТЕР", this);//("GROUND", this);
    btnParter->setStyleSheet("color: red");
    btnSettings = new QPushButton("СПОРТСМЕНЫ", this);
    //btnSettings->setStyleSheet("color: red");
    btnTimer = new QPushButton("ТАЙМЕР", this);
    btnTimer->setStyleSheet("color: yellow");

    btnResetTime = new QPushButton(tr("Сброс времени"), this);
    connect(btnResetTime, SIGNAL(clicked(bool)), this, SLOT(resetTime()));
    //btnResetTime->setStyleSheet("color: black");

    connect(btnTime, SIGNAL(clicked()), this, SLOT(manageTime()));
    connect(btnParter, SIGNAL(clicked()), this, SLOT(manageParter()));
    connect(btnCukami, SIGNAL(clicked()), this, SLOT(manageCukami()));
    connect(btnTimer, SIGNAL(clicked()), this, SLOT(manageTimer()));
    //connect(btnSettings, SIGNAL(clicked()), this, SLOT(settings()));
    //connect(btnSettings, SIGNAL(clicked()), this, SLOT(showMaximized()));
    connect(btnSettings, SIGNAL(clicked()), this, SLOT(showListSportsmens()));

    QGridLayout* grid = new QGridLayout(this);
    //spacing = 6;
    //margin = 6;
    //сетка 56х31
    grid->setSpacing(5);
    grid->setMargin(5);

    //grid->SetNoConstraint;

    NameBlue = new NameAndTeam("white", "", 63,"",this);
    //NameBlue ->setObjectName("NameBlue");
    TeamBlue = new NameAndTeam("white", "", 10, "Lucida Console");
    //TeamBlue->setObjectName("TeamBlue");

    NameWhite = new NameAndTeam("white", "", 63,"",this);
    //NameWhite->setObjectName("NameWhite");
    TeamWhite = new NameAndTeam("white", "", 10, "Lucida Console");
    //TeamWhite->setObjectName("TeamWhite");

    NameNextBlue = new NameAndTeam("white", "", 63,"",this);
    //NameBlue ->setObjectName("NameBlue");
    NameNextWhite = new NameAndTeam("white", "", 63,"",this);
    //TeamBlue->setObjectName("TeamBlue");

    //connect(mainwin, SIGNAL(triggered()), this, SLOT(closeTablo()));

    lblEndTimer = new EndTime(this);
    lblEndTimer->setObjectName("lblEndTimer");

    connect(mainwin->closeProg, SIGNAL(triggered()), this, SLOT(closeTablo()));

    //сетка 55x35
    grid->addWidget(NameBlue,    0,  0, 2,  27);
    grid->addWidget(NameWhite,   0, 28, 2,  27);

    grid->addWidget(TeamBlue,    2,  0, 2,  27);
    grid->addWidget(TeamWhite,   2, 28, 2,  27);

    grid->addWidget(vaz_blue,    4,  0, 8,  6);
    grid->addWidget(lblVazBlue,  12,  0, 2,  6);
    grid->addWidget(uko_blue,    4,  7, 8,  6);
    grid->addWidget(lblUkoBlue,  12,  7, 2,  6);
    grid->addWidget(kok_blue,    4, 14, 8,  6);
    grid->addWidget(lblKokBlue,  12, 14, 2,  6);
    grid->addWidget(han_blue,    4, 21, 8,  6);
    grid->addWidget(lblHanBlue,  12, 21, 2,  6);

    grid->addWidget(lblKoeff,       14, 0, 2,  12);
    grid->addWidget(lblKoeffValue,  16, 0, 4,  12);

    grid->addWidget(lblAge,       14, 12, 2,  12);
    grid->addWidget(lblAgeValue,  16, 12, 4,  12);

    grid->addWidget(vaz_white,   4, 28, 8,  6);
    grid->addWidget(lblVazWhite, 12, 28, 2,  6);
    grid->addWidget(uko_white,   4, 35, 8,  6);
    grid->addWidget(lblUkoWhite, 12, 35, 2,  6);
    grid->addWidget(kok_white,   4, 42, 8,  6);
    grid->addWidget(lblKokWhite, 12, 42, 2,  6);
    grid->addWidget(han_white,   4, 49, 8,  6);
    grid->addWidget(lblHanWhite, 12, 49, 2,  6);

    grid->addWidget(lblFight,       14, 28, 2,  27);
    grid->addWidget(lblFightValue,  16, 28, 4,  27);

    grid->addWidget(rate_blue,  20,  0, 12, 16);
    grid->addWidget(rate_white, 20, 39, 12, 16);

    grid->addWidget(btnSettings,  14, 24, 3, 7);
    grid->addWidget(btnTimer,     17, 24, 3, 7);
    grid->addWidget(btnResetTime, 17, 32, 3, 6);

    grid->addWidget(mainTimer,   20, 17, 12, 21);
    grid->addWidget(cukamiTimer, 20, 17, 12, 21);
    grid->addWidget(parterTimer, 20, 17, 12, 21);
    grid->addWidget(stopwatch,   20, 17, 12, 21);

    //grid->addWidget(lblBallBlue, 32, 0,  3, 16);
    //grid->addWidget(lblBallRed,  32, 39, 3, 16);

    grid->addWidget(btnCukami,   32,  17, 3, 6);
    grid->addWidget(btnTime,     32,  24, 3, 7);
    grid->addWidget(btnParter,   32,  32, 3, 6);

    grid->addWidget(NameNextBlue,     35,  0, 2, 27);
    grid->addWidget(NameNextWhite,   35,  28, 2, 27);

    // frmSettings = new QWidget;
    // frmSettings->setWindowModality(Qt::ApplicationModal);
    // ui.setupUi(frmSettings);
    // connect(ui.lwKoef, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(choiceKoef(QListWidgetItem*)));
    // connect(ui.rb300, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(ui.rb200, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(ui.rb130, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(ui.rb100, SIGNAL(toggled(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(ui.rb020, SIGNAL(toggled(bool)), this, SLOT(choiceParterTime(bool)));
    // connect(ui.rb030, SIGNAL(toggled(bool)), this, SLOT(choiceParterTime(bool)));

    // connect(mainwin->act100, SIGNAL(triggered(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(mainwin->act130, SIGNAL(triggered(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(mainwin->act200, SIGNAL(triggered(bool)), this, SLOT(choiceMainTime(bool)));
    // connect(mainwin->act300, SIGNAL(triggered(bool)), this, SLOT(choiceMainTime(bool)));

    connect(mainwin, SIGNAL(sigTimeParter(bool)), this, SLOT(choiceParterTime(bool)));
    connect(mainwin, SIGNAL(sigTime(int)),        this, SLOT(choiceMainTime(int)));

    // if(QGuiApplication::screens().count() == 2){
    //     showFullScreen();
    // }else{
    //     show();
    //     setGeometry(QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2,
    //                 QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2);
    // }

    //if (desk->numScreens() == 1) {
    if(QGuiApplication::screens().count() == 1){
        if(mainwin->actLang->isChecked()){
            QMessageBox::information(this, "ATTENTION!",
                                     "Connect the display to the laptop in the \"extended desktop\" mode",
                                     QMessageBox::Ok);
        }
        else{
            QMessageBox::information(this, "ВНИМАНИЕ!",
                                     "Подключите к ноутбуку телевизор в режиме \"расширенный рабочий стол\"",
                                     QMessageBox::Ok);
        }
    }
    //MainWindow* mainW = new MainWindow;
    //mainW = static_cast<MainWindow*>(parent);
    tvScreen = new TVScreen(mainwin);

    if(QGuiApplication::screens().count() == 1)
        tvScreen->setGeometry(0, 0, QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2);
    else{
        //tvScreen->setGeometry(width(), 0, 100, height());
        tvScreen->setGeometry(QApplication::desktop()->availableGeometry(this).right() + 100, 0, 100, height());
        // tvScreen->setGeometry(QApplication::desktop()->availableGeometry(this).right(),
        //                       0, QApplication::desktop()->availableGeometry(tvScreen).width(),
        //                       QApplication::desktop()->availableGeometry(tvScreen).height());
        tvScreen->showFullScreen();
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

    connect(mainTimer,   SIGNAL(sigStarted(bool)),          this ,                 SLOT(endTime(bool)));

    tvScreen->show();

    connect(NameBlue,      SIGNAL(sigText(QString)), tvScreen->NameBlue,      SLOT(Text(QString)));
    connect(NameWhite,     SIGNAL(sigText(QString)), tvScreen->NameWhite,     SLOT(Text(QString)));
    connect(TeamBlue,      SIGNAL(sigText(QString)), tvScreen->TeamBlue,      SLOT(Text(QString)));
    connect(TeamWhite,     SIGNAL(sigText(QString)), tvScreen->TeamWhite,     SLOT(Text(QString)));
    connect(NameNextBlue,  SIGNAL(sigText(QString)), tvScreen->NameNextBlue,  SLOT(Text(QString)));
    connect(NameNextWhite, SIGNAL(sigText(QString)), tvScreen->NameNextWhite, SLOT(Text(QString)));

    connect(mainwin, SIGNAL(reset()), this, SLOT(resetTablo()));

    QString code = calculateCode(serialNumber);
    if(code != readCode || code == ""){
        while(1){
            int ret = frmCode->exec();
            if(ret == 1){
                if(ui_code.rbBios->isChecked())
                    code = calculateCode(serialNumberBios);
                else
                    code = calculateCode(serialNumberMac);

                if(ui_code.leCode->text() == code){

                    settings.beginGroup("code");
                    if(ui_code.rbBios->isChecked()) {
                        settings.setValue("codeBios", code);
                        settings.setValue("codeMacAddr", "");
                    }
                    else {
                        settings.setValue("codeBios", "");
                        settings.setValue("codeMacAddr", code);
                    }
                    settings.endGroup();
                    tvScreen->removeLogo();
                    break;
                }else{
                    ui_code.leCode->setText("");
                    //break;
                }
            }else{
                //delete frmCode;
                //tvScreen->removeLogo();
                break;
            }
        }
    }
    else{
        tvScreen->removeLogo();
    }

    initListNames();

    QTimer* tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(drawTvScreenshot()));
    tmr->start(100);

    connect(mainwin, SIGNAL(sigParter()), this, SLOT(slotParter()));
    slotParter();

    connect(mainTimer, SIGNAL(sigEndTime()), tvScreen->lblEndTimer,     SLOT(startProcess()));
    connect(mainTimer, SIGNAL(sigEndTime()), lblEndTimer,               SLOT(startProcess()));
}

PcScreen::~PcScreen()
{
}

void PcScreen::endTime(bool b){
    //qDebug()<<"endTime = "<<b;
    if(!b){
        if(parterTimer->isVisible()){
            parterTimer->StartStop();
            parterTimer->Reset();
            parterTimer->setVisible(false);
        }else if(cukamiTimer->isVisible()){
            cukamiTimer->StartStop();
            cukamiTimer->Reset();
            cukamiTimer->setVisible(false);
        }
        mainwin->menu->setEnabled(true);
    }
    else{
        mainwin->menu->setEnabled(false);
    }
}

void PcScreen::slotChangeId(bool b)
{
    if(b)
        leId->setText(serialNumberBios);
    else
        leId->setText(serialNumberMac);
}

void PcScreen::resetTime()
{
    if(mainTimer->getStatus() == 1 || stopwatch->isVisible())
        return;
    //qDebug()<<"mainwin->actLang->isChecked() = "<<mainwin->actLang->isChecked();
    if(mainwin->actLang->isChecked()){
        if(QMessageBox::question(0, "Reset", u8"Are you sure?") == QMessageBox::No)
            return;
    }
    else{
        if(QMessageBox::question(0, "Сброс", u8"Вы уверены?") == QMessageBox::No)
            return;
    }

    mainTimer->Reset();
    cukamiTimer->Reset();
    parterTimer->Reset();
}

void PcScreen::closeTablo()
{
    QKeyEvent *key_press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);
    QApplication::sendEvent(this, key_press);
}

void PcScreen::resetTablo()
{
    QKeyEvent *key_press = new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
    QApplication::sendEvent(this, key_press);
}

int PcScreen::rec(int num){
    int dig = 0;
    QString str_num = QString::number(num);
    for(int i = 0; i < str_num.length(); i++){
        dig +=  QString(str_num.at(i)).toInt();
    }
    if(dig > 9){
        return rec(dig);
    }else{
        return dig;
    }
}

QString PcScreen::calculateCode(QString serial)
{
    int lenString = serial.length();
    int myListStart[lenString];
    int myListEnd[lenString];
    for(int i=0; i < lenString; i++)
        myListStart[i] = serial.at(i).toLatin1();

    QString code = "";
    for(int i=0; i < lenString; i++){
        if(i < lenString - 1){
            myListEnd[i] = myListStart[i] + myListStart[i + 1];
        }else{
            myListEnd[i] = myListStart[i] + myListStart[0];
        }
        code = code + QString::number(rec(myListEnd[i]));
    }
    return code;
}

void PcScreen::closeEvent(QCloseEvent*){
    QApplication::exit();
}

void PcScreen::choiceParterTime(bool b){
    qDebug()<<"choiceParterTime = "<<b;
    if(b)
        //if(sender() == ui.rb020)
        parterTimer->setTime(30);
    else //if(sender() == ui.rb030)
        parterTimer->setTime(20);

}

void PcScreen::slotHeightTimer(bool b)
{
    tvScreen->grid->removeWidget(tvScreen->mainTimer);
    tvScreen->grid->removeWidget(tvScreen->cukamiTimer);
    tvScreen->grid->removeWidget(tvScreen->parterTimer);
    tvScreen->grid->removeWidget(tvScreen->stopwatch);
    if(b){
        tvScreen->grid->addWidget(tvScreen->mainTimer,   28, 17, 12, 21);
        tvScreen->grid->addWidget(tvScreen->cukamiTimer, 28, 17, 12, 21);
        tvScreen->grid->addWidget(tvScreen->parterTimer, 28, 17, 12, 21);
        tvScreen->grid->addWidget(tvScreen->stopwatch,   28, 17, 12, 21);
    }
    else{
        tvScreen->grid->addWidget(tvScreen->mainTimer,   29, 17, 10, 21);
        tvScreen->grid->addWidget(tvScreen->cukamiTimer, 29, 17, 10, 21);
        tvScreen->grid->addWidget(tvScreen->parterTimer, 29, 17, 10, 21);
        tvScreen->grid->addWidget(tvScreen->stopwatch,   29, 17, 10, 21);
    }

}

void PcScreen::choiceMainTime(int time){
    // if(!mainTimer->getInitState())
    //     return;
    switch (time) {
    case 0:
        mainTimer->setTime(60);
        break;
    case 1:
        mainTimer->setTime(90);
        break;
    case 2:
        mainTimer->setTime(120);
        break;
    case 3:
        mainTimer->setTime(180);
        break;
    default:
        break;
    }
    // if(t){
    //     if(sender() == mainwin->act300)
    //         mainTimer->setTime(180);
    //     else if(sender() == mainwin->act200)
    //         mainTimer->setTime(120);
    //     else if(sender() == mainwin->act130)
    //         mainTimer->setTime(90);
    //     else if(sender() == mainwin->act100)
    //         mainTimer->setTime(60);
    // }
}

void PcScreen::choiceKoef(QListWidgetItem* item){
    lblKoeffValue->setText(item->text());
    tvScreen->lblKoeffValue->setText(item->text());
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
    //int h = lblBallBlue->height();
    QFont font;
    // font.setPixelSize(h * 0.8);
    font.setBold(true);
    // lblBallBlue->setFont(font);
    // lblBallRed->setFont(font);
    int h = lblVazBlue->height();
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
    lblAge->setFont(font);
    h = lblKoeffValue->height();
    font.setPixelSize(h * 0.8);
    lblKoeffValue->setFont(font);
    lblFightValue->setFont(font);
    lblAgeValue->setFont(font);

    int minHeight = height() * 2 / 31;
    btnTime->setMinimumHeight(minHeight);
    btnCukami->setMinimumHeight(minHeight);
    btnParter->setMinimumHeight(minHeight);
    btnSettings->setMinimumHeight(minHeight);
    btnTimer->setMinimumHeight(minHeight);
    btnResetTime->setMinimumHeight(minHeight);

    h = btnTime->height();
    font.setPixelSize(h * 0.4);
    btnTime->setFont(font);
    btnCukami->setFont(font);
    btnParter->setFont(font);
    btnSettings->setFont(font);
    btnTimer->setFont(font);
    font.setPixelSize(h * 0.3);
    btnResetTime->setFont(font);

    lblEndTimer->setGeometry(0, 0, width(), height());
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
        if(mainwin->actLang->isChecked()){
            if(QMessageBox::question(0, "Exit", u8"Are you sure?") == QMessageBox::No)
                return;
            else
                QApplication::exit();
        }
        else{
            if(QMessageBox::question(0, "Выход", u8"Вы уверены?") == QMessageBox::No)
                return;
            else
                QApplication::exit();
        }
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
            tvScreen->lblFightValue->setText(QString::number(numFight));
        }else if(numFight < 100){
            numFight = numFight * 10 + f;
            lblFightValue->setText(QString::number(numFight));
            tvScreen->lblFightValue->setText(QString::number(numFight));
        }
    }else{
        if(numFight > 10){
            numFight = numFight / 10;
            lblFightValue->setText(QString::number(numFight));
            tvScreen->lblFightValue->setText(QString::number(numFight));
        }else{
            numFight = 0;
            lblFightValue->setText("");
            tvScreen->lblFightValue->setText("");
        }
    }
}

void PcScreen::Reset(){
    if(mainTimer->getStatus() == 1 || stopwatch->isVisible())
        return;
    if(mainwin->actLang->isChecked()){
        if(QMessageBox::question(0, "Reset", u8"Are you sure?") == QMessageBox::No)
            return;
    }
    else{
        if(QMessageBox::question(0, "Сброс", u8"Вы уверены?") == QMessageBox::No)
            return;
    }
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

void PcScreen::newListSportsmens(){
    choosingNames->setNames(lf->getSportsmens());
    choosingNames->setAge(lf->lAge);
    choosingNames->setWeight(lf->lWeight);
}

void PcScreen::showListSportsmens(){
    choosingNames->showMaximized();
}

void PcScreen::initListNames(){
    if(mainwin->actLang->isChecked())
        choosingNames = new ChoosingNames("en");
    else
        choosingNames = new ChoosingNames;
    lf = new ListFamily(this);
    lf->setObjectName("lf");
    choosingNames->setNames(lf->getSportsmens());
    choosingNames->setAge(lf->lAge);
    choosingNames->setWeight(lf->lWeight);

    connect(choosingNames,
            SIGNAL(close(QString, QString, QString, QString, QString, QString, QString, QString)),
            this,
            SLOT(closeWinName(QString, QString, QString, QString, QString, QString, QString, QString)));

    connect(choosingNames, SIGNAL(del()), this, SLOT(delListNames()));;
}

void PcScreen::switchLanguage(){
    if(mainwin->actLang->isChecked()){
        lblVazBlue->setText("WAZA-ARI");// =  new QLabel(tr("ВАЗАРИ"), this);//("WAZA-ARI", this);
        lblUkoBlue->setText("YUKO");//new QLabel(tr("ЮКО"), this);//("YUKO", this);
        lblKokBlue->setText("KOKA");//new QLabel(tr("КОКА"), this);//("KOKA", this);
        lblHanBlue->setText("HANSOKU");//new QLabel(tr("ХАНСОКУ"), this);//("HANSOKU", this);
        lblVazWhite->setText("WAZA-ARI");//new QLabel(tr("ВАЗАРИ"), this);
        lblUkoWhite->setText("YUKO");//new QLabel(tr("ЮКО"), this);
        lblKokWhite->setText("КОКА");//new QLabel(tr("КОКА"), this);
        lblHanWhite->setText("HANSOKU");//new QLabel(tr("ХАНСОКУ"), this);
        lblKoeff->setText("PI (PHYSICAL INDEX)");//("PI (PHYSICAL INDEX)", this);
        lblAge->setText("AGE");
        lblFight->setText("FIGHT №");

        btnTime->setText("TIME");
        btnCukami->setText("TSUKAMI");//("TSUKAMI", this);
        btnParter->setText("GROUND");//("GROUND", this);
        btnSettings->setText("ATHLETES");
        btnTimer->setText("TIMER");
        btnResetTime->setText("RESET TIME");
    }
    else{
        lblVazBlue->setText("ВАЗАРИ");
        lblUkoBlue->setText("ЮКО");//new QLabel(tr("ЮКО"), this);//("YUKO", this);
        lblKokBlue->setText("KOKA");//new QLabel(tr("КОКА"), this);//("KOKA", this);
        lblHanBlue->setText("ХАНСОКУ");//new QLabel(tr("ХАНСОКУ"), this);//("HANSOKU", this);
        lblVazWhite->setText("ВАЗАРИ");//new QLabel(tr("ВАЗАРИ"), this);
        lblUkoWhite->setText("ЮКО");//new QLabel(tr("ЮКО"), this);
        lblKokWhite->setText("KOKA");//new QLabel(tr("КОКА"), this);
        lblHanWhite->setText("ХАНСОКУ");//new QLabel(tr("ХАНСОКУ"), this);
        lblKoeff->setText("КОЭФФИЦИЕНТ");//("PI (PHYSICAL INDEX)", this);
        lblAge->setText("ВОЗРАСТ");
        lblFight->setText("БОЙ №");

        btnTime->setText("ВРЕМЯ");
        btnCukami->setText("ЦУКАМИ");//("TSUKAMI", this);
        btnParter->setText("ПАРТЕР");//("GROUND", this);
        btnSettings->setText("СПОРТСМЕНЫ");
        btnTimer->setText("ТАЙМЕР");
        btnResetTime->setText("СБРОС ВРЕМЕНИ");
    }
    // if(choosingNames != nullptr)
    //     choosingNames->deleteLater();
    // if(lf != nullptr)
    //     lf->deleteLater();

    // initListNames();
}

void PcScreen::changeEvent(QEvent* event)
{
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            switchLanguage();
            break;

        case QEvent::None:
        case QEvent::Timer:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        case QEvent::FocusIn:
        case QEvent::FocusOut:
        case QEvent::FocusAboutToChange:
        case QEvent::Enter:
        case QEvent::Leave:
        case QEvent::Paint:
        case QEvent::Move:
        case QEvent::Resize:
        case QEvent::Create:
        case QEvent::Destroy:
        case QEvent::Show:
        case QEvent::Hide:
        case QEvent::Close:
        case QEvent::Quit:
        case QEvent::ParentChange:
        case QEvent::ParentAboutToChange:
        case QEvent::ThreadChange:
        case QEvent::WindowActivate:
        case QEvent::WindowDeactivate:
        case QEvent::ShowToParent:
        case QEvent::HideToParent:
        case QEvent::Wheel:
        case QEvent::WindowTitleChange:
        case QEvent::WindowIconChange:
        case QEvent::ApplicationWindowIconChange:
        case QEvent::ApplicationFontChange:
        case QEvent::ApplicationLayoutDirectionChange:
        case QEvent::ApplicationPaletteChange:
        case QEvent::PaletteChange:
        case QEvent::Clipboard:
        case QEvent::Speech:
        case QEvent::MetaCall:
        case QEvent::SockAct:
        case QEvent::WinEventAct:
        case QEvent::DeferredDelete:
        case QEvent::DragEnter:
        case QEvent::DragMove:
        case QEvent::DragLeave:
        case QEvent::Drop:
        case QEvent::DragResponse:
        case QEvent::ChildAdded:
        case QEvent::ChildPolished:
        case QEvent::ChildRemoved:
        case QEvent::ShowWindowRequest:
        case QEvent::PolishRequest:
        case QEvent::Polish:
        case QEvent::LayoutRequest:
        case QEvent::UpdateRequest:
        case QEvent::UpdateLater:
        case QEvent::EmbeddingControl:
        case QEvent::ActivateControl:
        case QEvent::DeactivateControl:
        case QEvent::ContextMenu:
        case QEvent::InputMethod:
        case QEvent::TabletMove:
        case QEvent::LocaleChange:
        case QEvent::LayoutDirectionChange:
        case QEvent::Style:
        case QEvent::TabletPress:
        case QEvent::TabletRelease:
        case QEvent::OkRequest:
        case QEvent::HelpRequest:
        case QEvent::IconDrag:
        case QEvent::FontChange:
        case QEvent::EnabledChange:
        case QEvent::ActivationChange:
        case QEvent::StyleChange:
        case QEvent::IconTextChange:
        case QEvent::ModifiedChange:
        case QEvent::MouseTrackingChange:
        case QEvent::WindowBlocked:
        case QEvent::WindowUnblocked:
        case QEvent::WindowStateChange:
        case QEvent::ReadOnlyChange:
        case QEvent::ToolTip:
        case QEvent::WhatsThis:
        case QEvent::StatusTip:
        case QEvent::ActionChanged:
        case QEvent::ActionAdded:
        case QEvent::ActionRemoved:
        case QEvent::FileOpen:
        case QEvent::Shortcut:
        case QEvent::ShortcutOverride:
        case QEvent::WhatsThisClicked:
        case QEvent::ToolBarChange:
        case QEvent::ApplicationActivate:
        case QEvent::ApplicationDeactivate:
        case QEvent::QueryWhatsThis:
        case QEvent::EnterWhatsThisMode:
        case QEvent::LeaveWhatsThisMode:
        case QEvent::ZOrderChange:
        case QEvent::HoverEnter:
        case QEvent::HoverLeave:
        case QEvent::HoverMove:
        case QEvent::AcceptDropsChange:
        case QEvent::ZeroTimerEvent:
        case QEvent::GraphicsSceneMouseMove:
        case QEvent::GraphicsSceneMousePress:
        case QEvent::GraphicsSceneMouseRelease:
        case QEvent::GraphicsSceneMouseDoubleClick:
        case QEvent::GraphicsSceneContextMenu:
        case QEvent::GraphicsSceneHoverEnter:
        case QEvent::GraphicsSceneHoverMove:
        case QEvent::GraphicsSceneHoverLeave:
        case QEvent::GraphicsSceneHelp:
        case QEvent::GraphicsSceneDragEnter:
        case QEvent::GraphicsSceneDragMove:
        case QEvent::GraphicsSceneDragLeave:
        case QEvent::GraphicsSceneDrop:
        case QEvent::GraphicsSceneWheel:
        case QEvent::KeyboardLayoutChange:
        case QEvent::DynamicPropertyChange:
        case QEvent::TabletEnterProximity:
        case QEvent::TabletLeaveProximity:
        case QEvent::NonClientAreaMouseMove:
        case QEvent::NonClientAreaMouseButtonPress:
        case QEvent::NonClientAreaMouseButtonRelease:
        case QEvent::NonClientAreaMouseButtonDblClick:
        case QEvent::MacSizeChange:
        case QEvent::ContentsRectChange:
        case QEvent::MacGLWindowChange:
        case QEvent::FutureCallOut:
        case QEvent::GraphicsSceneResize:
        case QEvent::GraphicsSceneMove:
        case QEvent::CursorChange:
        case QEvent::ToolTipChange:
        case QEvent::NetworkReplyUpdated:
        case QEvent::GrabMouse:
        case QEvent::UngrabMouse:
        case QEvent::GrabKeyboard:
        case QEvent::UngrabKeyboard:
        case QEvent::MacGLClearDrawable:
        case QEvent::StateMachineSignal:
        case QEvent::StateMachineWrapped:
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::NativeGesture:
        case QEvent::RequestSoftwareInputPanel:
        case QEvent::CloseSoftwareInputPanel:
        case QEvent::WinIdChange:
        case QEvent::Gesture:
        case QEvent::GestureOverride:
        case QEvent::ScrollPrepare:
        case QEvent::Scroll:
        case QEvent::Expose:
        case QEvent::InputMethodQuery:
        case QEvent::OrientationChange:
        case QEvent::TouchCancel:
        case QEvent::ThemeChange:
        case QEvent::SockClose:
        case QEvent::PlatformPanel:
        case QEvent::StyleAnimationUpdate:
        case QEvent::ApplicationStateChange:
        case QEvent::WindowChangeInternal:
        case QEvent::ScreenChangeInternal:
        case QEvent::PlatformSurface:
        case QEvent::Pointer:
        case QEvent::TabletTrackingChange:
        case QEvent::User:
        case QEvent::MaxUser:
            break;
        }
    }
}

void PcScreen::delListNames()
{
    //QThread::msleep(100);
    if(choosingNames != nullptr)
        choosingNames->deleteLater();
    if(lf != nullptr)
        lf->deleteLater();

    initListNames();

    choosingNames->showMaximized();
}

void PcScreen::closeWinName(QString redName, QString redRegion, QString blueName,
                            QString blueRegion, QString redNameNext, QString blueNameNext,
                            QString Age, QString Weight){
    NameBlue-> Text(redName);
    TeamBlue->Text(redRegion);
    NameWhite->Text(blueName);
    TeamWhite->Text(blueRegion);
    NameNextBlue->Text(redNameNext);
    NameNextWhite->Text(blueNameNext);
    lblAgeValue->setText(Age);
    lblKoeffValue->setText(Weight);
    tvScreen->lblAgeValue->setText(Age);
    tvScreen->lblKoeffValue->setText(Weight);
}

void PcScreen::drawTvScreenshot(){
    if(mainwin->dlgSettings->isVisible()){
        QPixmap pix = tvScreen->grab();
        pix = pix.scaled(mainwin->lblTV->width(), mainwin->lblTV->height());
        mainwin->lblTV->setPixmap(pix);
    }
}

void PcScreen::slotParter()
{
    if(mainwin->actNoParter->isChecked())
        btnParter->setVisible(false);
    else
        btnParter->setVisible(true);

    if(mainwin->actNoCukami->isChecked())
        btnCukami->setVisible(false);
    else
        btnCukami->setVisible(true);

}
