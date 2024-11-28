#include <QPainter>
#include <QGridLayout>
#include <QDebug>
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

    lblKoeffValue =  new QLabel("", this);
    lblKoeffValue->setStyleSheet("color: white;");
    lblKoeffValue->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    lblAgeValue =  new QLabel("", this);
    lblAgeValue->setStyleSheet("color: white;");
    lblAgeValue->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);


    lblFight =  new QLabel("БОЙ №", this);
    lblFight->setStyleSheet("color: blue;");
    lblFight->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    lblFightValue =  new QLabel("1", this);
    lblFightValue->setStyleSheet("color: blue;");
    lblFightValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);


    NameBlue = new FirstLastName("white", "", 63,"",this);
    //NameBlue ->setObjectName("NameBlue");
    TeamBlue = new NameAndTeam("white", "", 10, "Lucida Console");
    //TeamBlue->setObjectName("TeamBlue");

    NameWhite = new FirstLastName("white", "", 63,"",this);
    //NameWhite->setObjectName("NameWhite");
    TeamWhite = new NameAndTeam("white", "", 10, "Lucida Console");
    //TeamWhite->setObjectName("TeamWhite");

    NameNextBlue = new NameAndTeam("white", "", 63,"",this);
    //NameBlue ->setObjectName("NameBlue");

    NameNextWhite = new NameAndTeam("white", "", 63,"",this);
    //NameWhite->setObjectName("NameWhite");

    logo = new QLabel("Not\nactivated");
    logo->setStyleSheet("color: red;");
    logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


    grid = new QGridLayout(this);
    //spacing = 6;
    //margin = 6;
    //сетка 56х44
    grid->setSpacing(5);
    grid->setMargin(5);

    //grid->SetNoConstraint;
    grid->addWidget(NameBlue,    0,  0, 8,  27);
    grid->addWidget(NameWhite,   0, 28, 8,  27);

    grid->addWidget(TeamBlue,    8,  0, 4,  27);
    grid->addWidget(TeamWhite,   8, 28, 4,  27);

    grid->addWidget(vaz_blue,    12,  28, 8,  6);
    grid->addWidget(lblVazBlue,  20,  28, 2,  6);
    grid->addWidget(uko_blue,    12,  35, 8,  6);
    grid->addWidget(lblUkoBlue,  20,  35, 2,  6);
    grid->addWidget(kok_blue,    12, 42, 8,  6);
    grid->addWidget(lblKokBlue,  20, 42, 2,  6);
    grid->addWidget(han_blue,    12, 49, 8,  6);
    grid->addWidget(lblHanBlue,  20, 49, 2,  6);

    //grid->addWidget(lblKoeff,       24, 28, 2,  7);
    grid->addWidget(lblKoeffValue,  24, 28, 4,  10);

    //grid->addWidget(lblAge,       22, 28, 2,  27);
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

    //grid->addWidget(lblBallBlue, 40, 39,  3, 16);
    //grid->addWidget(lblBallRed,  40, 0, 3, 16);

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
    //int h = lblBallBlue->height();
    QFont font;
    //font.setPixelSize(h * 0.8);
    font.setBold(true);
    //lblBallBlue->setFont(font);
    //lblBallRed->setFont(font);
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
    h = lblFight->height();
    font.setPixelSize(h * 0.45);
    //lblKoeff->setFont(font);
    //lblAge->setFont(font);
    lblFight->setFont(font);
    h = lblKoeffValue->height();
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

    //HEIGHT_TEAM = settings->value("HEIGHT_TEAM", -1).toInt();
    // = settings->value("HEIGHT_NEXT_FAMILY", -1).toInt();

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
        qDebug()<<sz - 1;
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
        qDebug()<<sz + 1;
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
        qDebug()<<sz - 1;
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
        qDebug()<<sz + 1;
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
        qDebug()<<sz - 1;
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
        qDebug()<<sz + 1<<i;
    }
    settings->endGroup();
}

void TVScreen::changeEvent(QEvent* event)
{
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            qDebug()<<"retranslate tv";
            //switchLanguage();
            if(main->actLang->isChecked()){
                lblVazBlue->setText("WAZA-ARI");
                lblUkoBlue->setText("YUKO");
                lblKokBlue->setText("KOKA");
                lblHanBlue->setText("HANSOKU");
                lblVazWhite->setText("WAZA-ARI");
                lblUkoWhite->setText("YUKO");
                lblKokWhite->setText("КОКА");
                lblHanWhite->setText("HANSOKU");
                //lblKoeff->setText("PI (PHYSICAL INDEX)");
                //lblAge->setText("AGE");
                lblFight->setText("FIGHT №");
                if(logo != nullptr)
                    logo->setText("Not\nactivated");
            }
            else{
                lblVazBlue->setText("ВАЗАРИ");
                lblUkoBlue->setText("ЮКО");
                lblKokBlue->setText("KOKA");
                lblHanBlue->setText("ХАНСОКУ");
                lblVazWhite->setText("ВАЗАРИ");
                lblUkoWhite->setText("ЮКО");
                lblKokWhite->setText("KOKA");
                lblHanWhite->setText("ХАНСОКУ");
                //lblKoeff->setText("КОЭФФИЦИЕНТ");
                //lblAge->setText("ВОЗРАСТ");
                lblFight->setText("БОЙ №");
                if(logo != nullptr)
                    logo->setText("Не\nактивировано");
            }

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

