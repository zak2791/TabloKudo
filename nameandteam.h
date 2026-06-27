#ifndef NAMEANDTEAM_H
#define NAMEANDTEAM_H

#include <QLabel>

class NameAndTeam : public QLabel {
    Q_OBJECT
    //Q_PROPERTY(QString text WRITE Text)

public:
    NameAndTeam(QString _cl = "white",
                QString _tx = "text",
                int _wt = 10,
                QString fn = "",
                QWidget *parent = 0);
    ~NameAndTeam();

    int align = 0;

public slots:
    void Text(QString);
    void setViewStyle(int);
    QString getText(void);
    //private slots:
    //

    //public:


private:
    virtual void paintEvent(QPaintEvent *);


protected:
    int wt;
    //QString fn;
    QString tx;
    QFont fm;


signals:
    void sigText(QString);
};

class FirstLastName : public NameAndTeam
{

public:
    FirstLastName(QString _cl = "yellow",
                  QString _tx = "text",
                  int _wt = 10,
                  QString fn = "",
                  QWidget *parent = 0);

private:
    virtual void paintEvent(QPaintEvent *);

};
#endif // NAMEANDTEAM_H
