#include "pcscreen.h"

#include <QApplication>

#include "mainwindow.h"
#include "pcscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("kudo");
    a.setOrganizationDomain("kudo.ru");
    a.setApplicationName("Tablo Kudo");

    //QSettings settings;

    MainWindow* mWin = new MainWindow;

    PcScreen * pwgt = new PcScreen(mWin);

    QObject::connect(mWin, SIGNAL(newFile()), pwgt, SLOT(newListSportsmens()));
    QObject::connect(mWin, SIGNAL(sigHeightTimer(bool)), pwgt, SLOT(slotHeightTimer(bool)));

    //QGuiApplication::setAttribute(Qt::AA_UseOpenGLES);

    mWin->setCentralWidget(pwgt);
    mWin->show();

    return a.exec();
}
