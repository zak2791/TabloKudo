#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

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

    connect(uiSettings.rbBig, &QRadioButton::toggled, [=](bool check)
            {
                settings->beginGroup("heightTimers");
                settings->setValue("heightTimer", check);
                emit sigHeightTimer(check);
                settings->endGroup();
            });

    //slotSelectEng(true);

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

// // we create the menu entries dynamically, dependent on the existing translations.
// void MainWindow::createLanguageMenu(void) {
//     QActionGroup* langGroup = new QActionGroup(ui->languages);
//     langGroup->setExclusive(true);

//     connect(langGroup, SIGNAL (triggered(QAction *)), this, SLOT (slotLanguageChanged(QAction *)));

//     // format systems language
//     QString defaultLocale = QLocale::system().name(); // e.g. "de_RU"
//     defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "re"

//     m_langPath = QApplication::applicationDirPath();
//     m_langPath.append("/languages");
//     QDir dir(m_langPath);
//     QStringList fileNames = dir.entryList(QStringList("Translation_*.qm"));

//     for (int i = 0; i < fileNames.size(); ++i) {
//         // get locale extracted by filename
//         QString locale;
//         locale = fileNames[i]; // "Translation_ru.qm"
//         locale.truncate(locale.lastIndexOf('.')); // "Translation_ru"
//         locale.remove(0, locale.lastIndexOf('_') + 1); // "ru"

//         QString lang = QLocale::languageToString(QLocale(locale).language());
//         QIcon ico(QString("%1/%2.png").arg(m_langPath).arg(locale));

//         QAction *action = new QAction(ico, lang, this);
//         action->setCheckable(true);
//         action->setData(locale);

//         ui->languages->addAction(action);
//         langGroup->addAction(action);

//         // set default translators and language checked
//         if (defaultLocale == locale) {
//             action->setChecked(true);
//         }
//     }
// }

// // Called every time, when a menu entry of the language menu is called
// void MainWindow::slotLanguageChanged(QAction* action)
// {
//     if(0 != action) {
//         // load the language dependant on the action content
//         loadLanguage(action->data().toString());
//         setWindowIcon(action->icon());
//     }
// }

// void switchTranslator(QTranslator& translator, const QString& filename) {
//     // remove the old translator
//     qApp->removeTranslator(&translator);

//     // load the new translator
//     QString path = QApplication::applicationDirPath();
//     path.append("/languages/");
//     if(translator.load(path + filename)) //Here Path and Filename has to be entered because the system didn't find the QM Files else
//         qApp->installTranslator(&translator);
// }

// void MainWindow::loadLanguage(const QString& rLanguage) {
//     if(m_currLang != rLanguage) {
//         m_currLang = rLanguage;
//         QLocale locale = QLocale(m_currLang);
//         QLocale::setDefault(locale);
//         QString languageName = QLocale::languageToString(locale.language());
//         switchTranslator(m_translator, QString("Translation_%1.qm").arg(rLanguage));
//         switchTranslator(m_translatorQt, QString("qt_%1.qm").arg(rLanguage));
//         //ui->statusBar->showMessage(tr("Current Language changed to %1").arg(languageName));
//     }
// }

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
        case QEvent::LocaleChange:
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
    QMainWindow::changeEvent(event);
}

void MainWindow::slotSelectEng(bool b)
{
    if(!ui->actEnglish->isChecked()){
        ui->actEnglish->toggle();
        return;
    }
    qDebug()<<"slotSelectEng";
    settings->beginGroup("languages");
    settings->setValue("language", "en");
    settings->endGroup();

    ui->actRus->setChecked(false);

    if(translator.load((QApplication::applicationDirPath() + "/languages/language_en"))){
        qApp->installTranslator(&translator);
        ui->retranslateUi(this);
        //emit sigTranslate(true);
        uiSettings.retranslateUi(dlgSettings);
    }

}

void MainWindow::slotSelectRus(bool b)
{
    if(!ui->actRus->isChecked()){
        ui->actRus->toggle();
        qDebug()<<"rus checked";
        return;
    }
    qDebug()<<"slotSelectRus";
    settings->beginGroup("languages");
    settings->setValue("language", "ru");
    settings->endGroup();

    ui->actEnglish->setChecked(false);

    qApp->removeTranslator(&translator);
    ui->retranslateUi(this);
    uiSettings.retranslateUi(dlgSettings);
    //emit sigTranslate(false);



}

void MainWindow::selectTime(){
    settings->beginGroup("settigs_time");

    QString timeParter = settings->value("timeParter", "0:30").toString();

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
