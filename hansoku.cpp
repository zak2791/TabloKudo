#include "hansoku.h"
#include <QDebug>
#include <QEvent>

Hansoku::Hansoku(QString col, QWidget *parent):
QLabel(parent){
    hansoku = new QDialog;
    hansoku->setModal(true);
    ui.setupUi(hansoku);
    color = col;

    stileString = "QLabel{border-radius: 30px; "
                  "border-width: 2px; "
                  "border-style: solid; "
                  "border-color: %1; "
                  "background-color: %2; "
                  "color: black;}";

    style = stileString.arg(col, "black");
    styleKei =  stileString.arg(col, "yellow");
    styleHan1 = stileString.arg(col, "yellow");
    styleHan2 = stileString.arg(col, "yellow");
    styleHan3 = stileString.arg(col, "red");

    setStyleSheet(style);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    connect(ui.cbKeikoku, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku1 , SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku2, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku3, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
}

void Hansoku::choiceHansoku(int state){
    if(sender()->objectName() == "cbHansoku1"){
        if(state){
            emit sigHansoku(1);
        }else{
            emit sigHansoku(-1);
        }
    }else if(sender()->objectName() == "cbHansoku2"){
        if(state){
            emit sigHansoku(2);
        }else{
            emit sigHansoku(-2);
        }
    }else if(sender()->objectName() == "cbHansoku3"){
        if(state){
            emit sigHansoku(4);
        }else{
            emit sigHansoku(-4);
        }
    }
    if(ui.cbHansoku3->isChecked()){
        setStyleAndText(4);
    }else if(ui.cbHansoku2->isChecked()){
        setStyleAndText(3);
    }else if(ui.cbHansoku1->isChecked()){
        setStyleAndText(2);
    }else if(ui.cbKeikoku->isChecked()){
        setStyleAndText(1);
    }else{
        setStyleAndText(0);
    }
}

void Hansoku::setStyleAndText(int st){
    if(st == 4){
        setText("3");
        setStyleSheet(styleHan3);
        emit sigStyle(4);
    }else if(st == 3){
        setText("2");
        setStyleSheet(styleHan2);
        emit sigStyle(3);
    }else if(st == 2){
        setText("1");
        setStyleSheet(styleHan1);
        emit sigStyle(2);
    }else if(st == 1){
        setStyleSheet(styleKei);
        setText("");
        emit sigStyle(1);
    }else{
        setStyleSheet(style);
        setText("");
        emit sigStyle(0);
    }

}

void Hansoku::mousePressEvent(QMouseEvent *){
    hansoku->show();
    //setText("1");
    //setAutoFillBackground(true);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


    font = QFont();
}

void Hansoku::sbros(){
    ui.cbKeikoku->setChecked(false);
    ui.cbHansoku1->setChecked(false);
    ui.cbHansoku2->setChecked(false);
    ui.cbHansoku3->setChecked(false);

    //setStyleSheet(style);
    //setText("");
}

void Hansoku::resizeEvent(QResizeEvent *){
    font.setWeight(QFont::DemiBold);
    font.setPixelSize(height() * 2);
    QFontMetrics fm = QFontMetrics(font);

    int fontSize = height() * 1.05;
    while (true) {
        font.setPixelSize(fontSize);
        setFont(font);
        fm = QFontMetrics(font);
        if (fm.horizontalAdvance("0") < width() )
            break;
        if (fontSize > 20)
            fontSize -= 20;
        else
            break;
    }

}

void Hansoku::changeEvent(QEvent* event)
{
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            ui.retranslateUi(hansoku);
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
        //case QEvent::MacGLClearDrawable:
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

