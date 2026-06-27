#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dlgSettings = new QDialog;
    dlgSettings->setModal(true);
    uiSettings.setupUi(dlgSettings);
    actLang = ui->actEnglish;
    menu = ui->menubar;

    connect(ui->actSettings,        SIGNAL(triggered()), dlgSettings, SLOT(show()));
    connect(uiSettings.btnNameUp,   SIGNAL(clicked()),   this,        SLOT(slotChangeHeightNameTeam()));
    connect(uiSettings.btnNameDown, SIGNAL(clicked()),   this,        SLOT(slotChangeHeightNameTeam()));
    connect(uiSettings.btnTeamUp,   SIGNAL(clicked()),   this,        SLOT(slotChangeHeightNameTeam()));
    connect(uiSettings.btnTeamDown, SIGNAL(clicked()),   this,        SLOT(slotChangeHeightNameTeam()));
    connect(uiSettings.btnNameNextUp,   SIGNAL(clicked()),   this,    SLOT(slotChangeHeightNameTeam()));
    connect(uiSettings.btnNameNextDown, SIGNAL(clicked()),   this,    SLOT(slotChangeHeightNameTeam()));

    fileSettings = "settings.ini";
    fileSportsmens = "";

    QAction* openFile = ui->openFile;
    connect(openFile, SIGNAL(triggered()), this, SLOT(openFile()));

    settings = new QSettings(fileSettings, QSettings::IniFormat, this);

    settings->beginGroup("languages");
    QString language = settings->value("language", "ru").toString();
    settings->endGroup();

    settings->beginGroup("files");
    lastDir = settings->value("lastDir", "").toString();
    QString lFiles = settings->value("listFiles", "").toString();


    lastFiles = ui->mFile->addMenu(tr("Последние файлы"));
    closeProg = ui->mFile->addAction(tr("Выход"));
    if(lFiles == "")
        lastFiles->setEnabled(false);
    else{
        listFiles = lFiles.split(";");
        foreach(QString str, listFiles){
            if(QFile::exists(str)){
                QAction* act = lastFiles->addAction(str);
                act->setCheckable(true);
                if(str == listFiles.at(0)){
                    act->setChecked(true);
                    fileSportsmens = str;
                }
                connect(act, SIGNAL(triggered()), SLOT(choiceFile()));
            }
            else{
                listFiles.removeOne(str);
            }
        }
        settings->setValue("listFiles", listFiles.join(";"));
    }
    settings->endGroup();

    lblTV = uiSettings.lblTvscreen;

    if(language == "ru"){
        ui->actRus->setChecked(true);
        ui->actEnglish->setChecked(false);
    }
    else{
        ui->actRus->setChecked(false);
        ui->actEnglish->setChecked(true);
        if(translator.load((QApplication::applicationDirPath() + "/languages/language_en"))){
            qApp->installTranslator(&translator);
            ui->retranslateUi(this);
            uiSettings.retranslateUi(dlgSettings);
            //emit sigEnglish();
        }
    }


    connect(ui->actEnglish, SIGNAL(triggered(bool)), this, SLOT(slotSelectEng(bool)));
    connect(ui->actRus, SIGNAL(triggered(bool)), this, SLOT(slotSelectRus(bool)));

    connect(ui->actReset, SIGNAL(triggered()), this, SIGNAL(reset()));

    ui->act100->setObjectName("act100");
    ui->act130->setObjectName("act130");
    ui->act200->setObjectName("act200");
    ui->act300->setObjectName("act300");

    ui->act020->setObjectName("act020");
    ui->act030->setObjectName("act030");

    connect(ui->act100, SIGNAL(triggered()), this, SLOT(selectTime()));
    connect(ui->act130, SIGNAL(triggered()), this, SLOT(selectTime()));
    connect(ui->act200, SIGNAL(triggered()), this, SLOT(selectTime()));
    connect(ui->act300, SIGNAL(triggered()), this, SLOT(selectTime()));

    connect(ui->act030, SIGNAL(triggered()), this, SLOT(selectTime()));
    connect(ui->act020, SIGNAL(triggered()), this, SLOT(selectTime()));

    settings->beginGroup("settigs_time");
    QString timeFight = settings->value("timeFight", "3:00").toString();
    QString timeParter = settings->value("timeParter", "0:30").toString();
    settings->endGroup();
    if(timeFight == "3:00")
        ui->act300->setChecked(true);
    else if(timeFight == "2:00")
        ui->act200->setChecked(true);
    else if(timeFight == "1:30")
        ui->act130->setChecked(true);
    else
        ui->act100->setChecked(true);

    if(timeParter == "0:30")
        ui->act030->setChecked(true);
    else
        ui->act020->setChecked(true);

    settings->beginGroup("settigs_parter");
    bool parter = settings->value("no_parter", false).toBool();
    bool tsukami = settings->value("no_tsukami", false).toBool();
    settings->endGroup();

    actNoCukami = ui->actNoCukami;
    if(tsukami) actNoCukami->setChecked(true);

    actNoParter = ui->actNoParter;
    if(parter){
        actNoParter->setChecked(true);
        actNoCukami->setEnabled(true);
    }

    connect(actNoCukami, SIGNAL(triggered(bool)), this, SLOT(slotTsukami(bool)));
    connect(actNoParter, SIGNAL(triggered(bool)), this, SLOT(slotParter(bool)));

    settings->beginGroup("heightTimers");
    bool heightTimer = settings->value("heightTimer", true).toBool();
    settings->endGroup();
    if(!heightTimer)
        uiSettings.rbSmall->setChecked(true);

    connect(uiSettings.rbBig, &QRadioButton::toggled, this, [=](bool check)
            {
                settings->beginGroup("heightTimers");
                settings->setValue("heightTimer", check);
                emit sigHeightTimer(check);
                settings->endGroup();
            });

    connect(ui->about, &QAction::triggered, this, [=](){
        if(actLang->isChecked())
            QMessageBox::information(this, "About programm", "Version 2.1, 27.06.2026");
        else
            QMessageBox::information(this, "О программе", "Версия 2.1, 27.06.2026");
    });

    connect(ui->winHelp, &QAction::triggered, this, [=](){
        QProcess proc(this);
        if(actLang->isChecked())
            proc.startDetached("notepad", {"manual_en.txt"});
        else
            proc.startDetached("notepad", {"manual_ru.txt"});
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenSettings(bool b)
{
    qDebug()<<b;
}

void MainWindow::slotChangeHeightNameTeam()
{
    if(sender()->objectName() == "btnNameUp"){
        emit changeSizeName(0);
    }
    else if(sender()->objectName() == "btnNameDown"){
        emit changeSizeName(1);
    }
    else if(sender()->objectName() == "btnTeamUp"){
        emit changeSizeName(2);
    }
    else if(sender()->objectName() == "btnTeamDown"){
        emit changeSizeName(3);
    }
    else if(sender()->objectName() == "btnNameNextUp"){
        emit changeSizeName(4);
    }
    else if(sender()->objectName() == "btnNameNextDown"){
        emit changeSizeName(5);
    }
}

void MainWindow::closeEvent(QCloseEvent* e){
    int ret = QMessageBox::question(this, tr("Выход"),
                                    tr("Вы уверены?"),
                                    QMessageBox::Yes | QMessageBox::No
                                    );
    if(ret == QMessageBox::Yes){
        emit sigExit();
        qApp->exit(0);
    }
    else
        e->ignore();
}

void MainWindow::openFile(){
    QString file = QFileDialog::getOpenFileName(this, tr("Выберите файл"),  lastDir, "*.xlsx *.xls");
    if(file == "")
        return;
    fileSportsmens = file;

    listFiles.removeOne(fileSportsmens);
    listFiles.prepend(fileSportsmens);

    foreach(QAction* a, lastFiles->findChildren<QAction*>())
        lastFiles->removeAction(a);

    foreach(QString str, listFiles){
        QAction* act = lastFiles->addAction(str);
        act->setCheckable(true);
        if(str == listFiles.at(0))
            act->setChecked(true);
        connect(act, SIGNAL(triggered()), SLOT(choiceFile()));
    }

    lastFiles->setEnabled(true);
    lastDir = file.remove(file.lastIndexOf('/'), 100);

    QSettings settings(fileSettings, QSettings::IniFormat);
    settings.beginGroup("files");
    settings.setValue("lastDir", lastDir);
    settings.setValue("listFiles", listFiles.join(";"));
    settings.endGroup();
    settings.sync();

    emit newFile();
}

void MainWindow::choiceFile(){
    QAction* action = static_cast<QAction*>(sender());
    qDebug()<<action->text();
    action->setChecked(true);
    fileSportsmens = action->text();

    listFiles.removeOne(fileSportsmens);
    listFiles.prepend(fileSportsmens);

    foreach(QAction* a, lastFiles->findChildren<QAction*>())
        lastFiles->removeAction(a);

    foreach(QString str, listFiles){
        QAction* act = lastFiles->addAction(str);
        act->setCheckable(true);
        if(str == listFiles.at(0))
            act->setChecked(true);
        connect(act, SIGNAL(triggered()), SLOT(choiceFile()));
    }

    QSettings settings(fileSettings, QSettings::IniFormat);
    settings.beginGroup("files");
    settings.setValue("listFiles", listFiles.join(";"));
    settings.endGroup();
    settings.sync();

    emit newFile();

}

QString MainWindow::getFileSportsmens(void){
    return fileSportsmens;
}

void MainWindow::changeEvent(QEvent* event) {
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            //ui->retranslateUi(this);
            if(actLang->isChecked()){
                lastFiles->setTitle("Latest files");
                closeProg->setText("Exit");
            }
            else{
                lastFiles->setTitle("Последние файлы");
                closeProg->setText("Выход");
            }
            break;

            // this event is send, if the system, language changes
        // case QEvent::LocaleChange:
        //     break;
        default:
            break;
        }
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::slotSelectEng(bool)
{
    if(!ui->actEnglish->isChecked()){
        ui->actEnglish->toggle();
        return;
    }
    settings->beginGroup("languages");
    settings->setValue("language", "en");
    settings->endGroup();

    ui->actRus->setChecked(false);

    if(translator.load((QApplication::applicationDirPath() + "/languages/language_en"))){
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        uiSettings.retranslateUi(dlgSettings);
    }

    emit sigLanguage(false);

}

void MainWindow::slotSelectRus(bool)
{
    if(!ui->actRus->isChecked()){
        ui->actRus->toggle();
        qDebug()<<"rus checked";
        return;
    }

    settings->beginGroup("languages");
    settings->setValue("language", "ru");
    settings->endGroup();

    ui->actEnglish->setChecked(false);

    if(translator.load((QApplication::applicationDirPath() + "/languages/language_en"))){
        qApp->removeTranslator(&translator);
        ui->retranslateUi(this);
        uiSettings.retranslateUi(dlgSettings);
    }

    emit sigLanguage(true);

}

void MainWindow::selectTime(){
    settings->beginGroup("settigs_time");

    //QString timeParter = settings->value("timeParter", "0:30").toString();

    if(sender()->objectName() == "act100"){
        ui->act100->setChecked(true);
        ui->act130->setChecked(false);
        ui->act200->setChecked(false);
        ui->act300->setChecked(false);
        settings->setValue("timeFight", "1:00");
        emit sigTime(0);
    }
    else if(sender()->objectName() == "act130"){
        ui->act100->setChecked(false);
        ui->act130->setChecked(true);
        ui->act200->setChecked(false);
        ui->act300->setChecked(false);
        settings->setValue("timeFight", "1:30");
        emit sigTime(1);
    }
    else if(sender()->objectName() == "act200"){
        ui->act100->setChecked(false);
        ui->act130->setChecked(false);
        ui->act200->setChecked(true);
        ui->act300->setChecked(false);
        settings->setValue("timeFight", "2:00");
        emit sigTime(2);
    }
    else if(sender()->objectName() == "act300"){
        ui->act100->setChecked(false);
        ui->act130->setChecked(false);
        ui->act200->setChecked(false);
        ui->act300->setChecked(true);
        settings->setValue("timeFight", "3:00");
        emit sigTime(3);
    }
    else if(sender()->objectName() == "act030"){
        ui->act030->setChecked(true);
        ui->act020->setChecked(false);
        settings->setValue("timeParter", "0:30");
        emit sigTimeParter(true);
    }
    else if(sender()->objectName() == "act020"){
        ui->act030->setChecked(false);
        ui->act020->setChecked(true);
        settings->setValue("timeParter", "0:20");
        emit sigTimeParter(false);
    }
    settings->endGroup();
}

void MainWindow::slotTsukami(bool b)
{
    settings->beginGroup("settigs_parter");
    if(b)
        settings->setValue("no_tsukami", true);
    else
        settings->setValue("no_tsukami", false);
    settings->endGroup();
    emit sigParter();
}

void MainWindow::slotParter(bool b)
{
    settings->beginGroup("settigs_parter");
    if(b){
        actNoCukami->setEnabled(true);
        settings->setValue("no_parter", true);
    }
    else{
        actNoCukami->setEnabled(false);
        actNoCukami->setChecked(false);
        settings->setValue("no_parter", false);
        settings->setValue("no_tsukami", false);
    }
    settings->endGroup();
    emit sigParter();
}
