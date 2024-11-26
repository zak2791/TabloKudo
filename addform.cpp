#include "addform.h"
#include "ui_addform.h"

#include <QDebug>
#include "listview.h"
#include <QMessageBox>

ListView::ListView(QWidget * parent) : QListView(parent) {

}

ListView::~ListView()
{
}

void ListView::mouseReleaseEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
        emit mouse_button(0);
    else if (e->button() == Qt::RightButton)
        emit mouse_button(1);
}

addForm::addForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addForm)
{
    ui->setupUi(this);

#ifdef APP_LAUNCH_FROM_IDE
    settings = new QSettings("settings.ini", QSettings::IniFormat);
#else
    settings = new QSettings("bin/settings.ini", QSettings::IniFormat);
#endif

    settings->beginGroup("addedSportsmens");
    sportsmens = settings->value("sportsmens", "").toString();
    settings->endGroup();

    QList<QString> lSportsmens;
    if(sportsmens != "")
        lSportsmens = sportsmens.split(";");

    leName = ui->leName;
    leTeam = ui->leTeam;

    listView = ui->list;

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(addSportsman()));

    ui->hBox->setStretchFactor(ui->vbName, 5);
    ui->hBox->setStretchFactor(ui->vbTeam, 4);

    model = new QStandardItemModel;
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    foreach(QString str, lSportsmens)
        model->appendRow(new QStandardItem(str));

    listView->setModel(model);

    connect(listView, SIGNAL(mouse_button(int)), this, SLOT(mouse()));
    connect(listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(sel(QItemSelection, QItemSelection)));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(clearList()));
}

addForm::~addForm()
{
    delete ui;
}

void addForm::addSportsman(){
    if(leName->text() == "" || leTeam->text() == "")
        return;

    model->appendRow(new QStandardItem(leName->text() + "," + leTeam->text()));
    listView->setModel(model);

    if(sportsmens == "")
        sportsmens = leName->text() + "," + leTeam->text();
    else
        sportsmens = sportsmens + ";" + leName->text() + "," + leTeam->text();

    settings->beginGroup("addedSportsmens");
    settings->setValue("sportsmens", sportsmens);
    settings->endGroup();

}

void addForm::mouse(){
    emit selSportsman(selectedSportsmen);
}

void addForm::sel(QItemSelection s, QItemSelection){
    QList<QString> lS = s.indexes()[0].data().toString().split(",");
    selectedSportsmen = lS.at(0) + ";" + lS.at(1);
}

void addForm::clearList(){
    int ret = QMessageBox::warning(this, tr("Очистка списка"),
                                   tr("Вы уверены?"),
                                   QMessageBox::Ok | QMessageBox::Cancel);

    if(ret == QMessageBox::Cancel)
        return;

    model->clear();
    //model->appendRow(new QStandardItem("-"));

    sportsmens = "";

    settings->beginGroup("addedSportsmens");
    settings->setValue("sportsmens", sportsmens);
    settings->endGroup();

    listView->setModel(model);

}

void addForm::changeEvent(QEvent* event)
{
    if(0 != event) {
        switch(event->type()) {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
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
