#include "nameandteam.h"

#include <QMouseEvent>
#include <QPainter>
#include <QFontMetrics>

NameAndTeam::NameAndTeam(QString _cl,
                         QString _tx,
                         int _wt,
                         QString fn,
                         QWidget *parent) :

    QLabel(parent), tx(QString("")) {

    setStyleSheet("QLabel{background-color: black; color: " + _cl + "; }");
    setAutoFillBackground(true);
    wt = _wt;  //жирность шрифта

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    if (QString::compare(fn, "") == 0)
        fm = QFont();
    else
        fm = QFont(fn);
    align = 0;						//0 - центр
        //1 - левый край
        //2 - правый край
    Text(_tx);
};

NameAndTeam::~NameAndTeam()
{
}

void NameAndTeam::setViewStyle(int s){
    if (s == 0)
        setStyleSheet("QLabel{background-color: black; color: white; }");
    else if(s == 1)
        setStyleSheet("QLabel{background-color: black; color: red; }");
    else
        setStyleSheet("QLabel{background-color: black; color: blue; }");
}

void NameAndTeam::Text(QString t) {
    tx = t;
    repaint();
    emit sigText(t);
}

QString NameAndTeam::getText(){
    return tx;
}

void NameAndTeam::paintEvent(QPaintEvent * ){
    fm.setPixelSize(height() / 0.9);
    fm.setWeight(QFont::DemiBold); //63
    setFont(fm);

    QPainter pn;
    pn.begin(this);

    QFontMetrics p(font()); // .width(tx);

    if(p.horizontalAdvance(tx) >= width())
        pn.drawText(0, height() * 0.9, tx);
    else
        if(align == 0)
            pn.drawText((width() - p.horizontalAdvance(tx)) / 2, height() * 0.9, tx);
        else if(align == 1)
            pn.drawText(0, height() * 0.9, tx);
        else
            pn.drawText(width() - p.horizontalAdvance(tx), height() * 0.9, tx);
    if (align == 0 || align == 1 || p.horizontalAdvance(tx) >= width()) {
        QLinearGradient gr(width() * 0.85, 0, width(), 0);
        gr.setColorAt(0, QColor(0, 0, 0, 0));
        gr.setColorAt(1, QColor(0, 0, 0, 255));
        pn.setBrush(gr);
    }
    pn.setPen(Qt::NoPen);
    pn.drawRect(0, 0, width(), height());

    pn.end();

}

FirstLastName::FirstLastName(QString _cl,
                             QString _tx,
                             int _wt,
                             QString fn,
                             QWidget *parent)  :
    NameAndTeam(_cl, _tx, _wt, fn, parent)
{

}

void FirstLastName::paintEvent(QPaintEvent * ){
    fm.setPixelSize(height() / 1.8);
    fm.setWeight(QFont::DemiBold); //63
    setFont(fm);

    QPainter pn;
    pn.begin(this);

    QFontMetrics p(font()); // .width(tx);

    QList<QString> sList = tx.split(" ");
    QString LastName = sList.at(0);
    QString FirstName;
    if(sList.count() > 1)
        FirstName = sList.at(1);
    else
        FirstName = "";

    if(p.horizontalAdvance(LastName) >= width())
        pn.drawText(0, height() * 0.45, LastName);
    else
        if(align == 0)
            pn.drawText((width() - p.horizontalAdvance(LastName)) / 2, height() * 0.45, LastName);
        else if(align == 1)
            pn.drawText(0, height() * 0.45, LastName);
        else
            pn.drawText(width() - p.horizontalAdvance(LastName), height() * 0.45, LastName);

    if(p.horizontalAdvance(FirstName) >= width())
        pn.drawText(0, height() * 0.9, FirstName);
    else
        if(align == 0)
            pn.drawText((width() - p.horizontalAdvance(FirstName)) / 2, height() * 0.9, FirstName);
        else if(align == 1)
            pn.drawText(0, height() * 0.9, FirstName);
        else
            pn.drawText(width() - p.horizontalAdvance(FirstName), height() * 0.9, FirstName);

    //if (align == 0 || align == 1 || p.width(tx) >= width()) {
    QLinearGradient gr(width() * 0.85, 0, width(), 0);
    gr.setColorAt(0, QColor(0, 0, 0, 0));
    gr.setColorAt(1, QColor(0, 0, 0, 255));
    pn.setBrush(gr);
    //}
    pn.setPen(Qt::NoPen);
    pn.drawRect(0, 0, width(), height());

    pn.end();

}

