#include "pcscreen.h"
#include <QPainter>
#include <QGridLayout>
#include <QDebug>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QProcess>
#include "ui_code.h"
#include <QSettings>

PcScreen::PcScreen(QWidget *parent) : QWidget(parent){

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

    btnTime = new QPushButton("TIME", this);
    btnTime->setStyleSheet("color: green");
    btnCukami = new QPushButton("TSUKAMI", this);
    btnCukami->setStyleSheet("color: blue");
    btnParter = new QPushButton("GROUND", this);
    btnParter->setStyleSheet("color: red");
    btnSettings = new QPushButton("SETTINGS", this);
    //btnSettings->setStyleSheet("color: red");
    btnTimer = new QPushButton("TIMER", this);
    btnTimer->setStyleSheet("color: yellow");

    btnResetTime = new QPushButton("Reset time", this);
    connect(btnResetTime, SIGNAL(clicked(bool)), this, SLOT(resetTime()));
    //btnResetTime->setStyleSheet("color: black");

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

    grid->addWidget(btnSettings,  10, 24, 3, 7);
    grid->addWidget(btnTimer,     13, 24, 3, 7);
    grid->addWidget(btnResetTime, 13, 32, 3, 6);

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
    connect(ui.rb020, SIGNAL(toggled(bool)), this, SLOT(choiceParterTime(bool)));
    connect(ui.rb030, SIGNAL(toggled(bool)), this, SLOT(choiceParterTime(bool)));

    if(QGuiApplication::screens().count() == 2){
        showFullScreen();
    }else{
        show();
        setGeometry(QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2,
                    QApplication::desktop()->availableGeometry(this).width() / 2, QApplication::desktop()->availableGeometry(this).height() / 2);
    }

    //if (desk->numScreens() == 1) {
    if(QGuiApplication::screens().count() == 1){
        QMessageBox::information(this, "ATTENTION!",
        "Connect the display to the laptop in the \"extended desktop\" mode",
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

    connect(mainTimer,   SIGNAL(sigStarted(bool)),          this ,                 SLOT(endTime(bool)));

    tvScreen->show();

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
                    break;
                }else{
                    ui_code.leCode->setText("");
                    //break;
                }
            }else{
                delete frmCode;
                QApplication::exit();
            }
        }
    }
}

PcScreen::~PcScreen()
{
}

void PcScreen::endTime(bool b){
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
    if(QMessageBox::question(0, "Reset", u8"Are you sure?") == QMessageBox::No)
        return;
    mainTimer->Reset();
    cukamiTimer->Reset();
    parterTimer->Reset();
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

void PcScreen::choiceParterTime(bool checked){
    if(checked){
        if(sender() == ui.rb020)
            parterTimer->setTime(20);
        else if(sender() == ui.rb030)
            parterTimer->setTime(30);
   }
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
    btnResetTime->setMinimumHeight(minHeight);

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
        if(QMessageBox::question(0, "Exit", u8"Are you sure?") == QMessageBox::No)
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
    if(QMessageBox::question(0, "Reset", u8"Are you sure?") == QMessageBox::No)
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
