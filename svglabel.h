#ifndef SVGLABEL_H
#define SVGLABEL_H

#include <QLabel>
#include <QSvgWidget>

class SvgLabel : public QLabel
{
private:
    QSvgWidget w;
    QString pathRus;
    QString pathEng;

public:
    SvgLabel(QString, QString, QWidget* parent = nullptr);

public slots:
    void setLanguage(void);

};

#endif // SVGLABEL_H
