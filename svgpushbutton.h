#ifndef SVGPUSHBUTTON_H
#define SVGPUSHBUTTON_H

#include "qsvgwidget.h"
#include <QPushButton>

class SVGPushButton : public QPushButton
{
private:
    QSvgWidget w;
    QString pathRus;
    QString pathEng;

public:
    SVGPushButton(QString, QString);

public slots:
    void setLanguage(void);

};

#endif // SVGPUSHBUTTON_H
