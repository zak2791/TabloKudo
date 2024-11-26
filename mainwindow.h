#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_settings_window.h"
#include <QCloseEvent>
#include <QTranslator>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getFileSportsmens(void);
    QAction* closeProg;
    QLabel* lblTV;
    QDialog* dlgSettings;
    QAction* actLang;

    // QAction* actO20;
    // QAction* actO30;
    // QAction* act100;
    // QAction* act130;
    // QAction* act200;
    // QAction* act300;
    QAction* actNoCukami;
    QAction* actNoParter;

    QMenuBar* menu;

private:
    Ui::MainWindow* ui;
    Ui::dlgSettings uiSettings;
    QSettings* settings;

    virtual void closeEvent(QCloseEvent*);

    QString lastDir;            //последняя директория, из которой выбирали файл со спортсменами
    QList<QString> listFiles;   //список последних файлов
    QString fileSportsmens;     //текущий файл со списком спортсменов
    QString fileSettings;
    QMenu* lastFiles;

    // // loads a language by the given language shortcur (e.g. de, en)
    // void loadLanguage(const QString& rLanguage);

    // // creates the language menu dynamically from the content of m_langPath
    // void createLanguageMenu(void);

    // QTranslator m_translator; // contains the translations for this application
    // QTranslator m_translatorQt; // contains the translations for qt
    // QString m_currLang; // contains the currently loaded language
    // QString m_langPath; // Path of language files. This is always fixed to /languages.
    QTranslator translator;

private slots:
    void slotOpenSettings(bool);
    void slotChangeHeightNameTeam(void);
    void openFile(void);
    void choiceFile(void);

    void slotSelectEng(bool);
    void slotSelectRus(bool);

    void selectTime(void);

    void slotTsukami(bool);
    void slotParter(bool);

protected:
    //this event is called, when a new translator is loaded or the system language is changed
    void changeEvent(QEvent*);

// protected slots:
//     // this slot is called by the language menu actions
//     void slotLanguageChanged(QAction* action);

signals:
    /////////////////////////////
    /// \brief changeSizeName ///
    /// 0 - + Name            ///
    /// 1 - - Name            ///
    /// 2 - + Team            ///
    /// 3 - - Team            ///
    /// 4 - + NextName        ///
    /// 5 - - NextName        ///
    /////////////////////////////
    void changeSizeName(int);
    void newFile(void);
    void sigExit(void);
    void reset(void);
    void sigTime(int);          //0-1:00
                                //1-1:30
                                //2-2:00
                                //3-3:00

    void sigTimeParter(bool);   //false-0:30, true-0:20
    void sigParter(void);

    void sigHeightTimer(bool);
};

#endif // MAINWINDOW_H
