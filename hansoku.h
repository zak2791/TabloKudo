#ifndef HANSOKU_H
#define HANSOKU_H

#include <QLabel>
#include "ui_hans.h"

class Hansoku : public QLabel{
    Q_OBJECT
public:
    Hansoku(QString, QWidget *parent = 0);
    void sbros(void);
    Ui::Dialog ui;

public slots:
    void setStyleAndText(int);

private:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void resizeEvent(QResizeEvent *);


    QDialog* hansoku;

    QFont font;

    QString color;
    QString stileString;
    QString style;
    QString styleKei;
    QString styleHan1;
    QString styleHan2;
    QString styleHan3;

private slots:
    void choiceHansoku(int);

signals:
    void sigHansoku(int);
    void sigStyle(int);

};

#endif // HANSOKU_H
