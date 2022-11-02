#ifndef HANSOKU_H
#define HANSOKU_H

#include <QLabel>
#include "ui_hans.h"

class Hansoku : public QLabel{
    Q_OBJECT
public:
    Hansoku(QWidget *parent = 0);

private:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void resizeEvent(QResizeEvent *);

    Ui::Dialog ui;
    QDialog* hansoku;

    QFont font;

};

#endif // HANSOKU_H
