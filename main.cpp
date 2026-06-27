#include "pcscreen.h"

#include <QApplication>
#include <QDir>

#include "mainwindow.h"
#include "pcscreen.h"
#include "qlockfile.h"
#include "qmessagebox.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("kudo");
    a.setOrganizationDomain("kudo.ru");
    a.setApplicationName("Tablo Kudo");

    QLockFile lockFile(QDir::temp().absoluteFilePath("lurity.lock"));

    if (!lockFile.tryLock(100))
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Приложение уже запущено.\n"
                       "Разрешено запускать только один экземпляр приложения.");
        msgBox.exec();
        return 1;
    }

    MainWindow* mWin = new MainWindow;

    PcScreen * pwgt = new PcScreen(mWin);

    QObject::connect(mWin, SIGNAL(newFile()), pwgt, SLOT(newListSportsmens()));
    QObject::connect(mWin, SIGNAL(sigHeightTimer(bool)), pwgt, SLOT(slotHeightTimer(bool)));

    mWin->setCentralWidget(pwgt);
    mWin->show();

    return a.exec();
}
