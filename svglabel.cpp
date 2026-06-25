#include "svglabel.h"
#include "qsettings.h"

#include <QSvgRenderer>
#include <QHBoxLayout>

SvgLabel::SvgLabel(QString _pathRus, QString _pathEng, QWidget* parent) : QLabel(parent) {
    pathRus = _pathRus;
    pathEng = _pathEng;

    QHBoxLayout* box = new QHBoxLayout(this);
    box->setContentsMargins(0,0,0,0);
    setLayout(box);
    layout()->addWidget(&w);
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("languages");
    QString language = settings.value("language", "ru").toString();
    settings.endGroup();
    if(language == "ru")
        setLanguage(true);
    else
        setLanguage(false);
}

void SvgLabel::setLanguage(bool b){
    if(b)
        w.load(pathRus);
    else
        w.load(pathEng);
    w.renderer()->setAspectRatioMode(Qt::KeepAspectRatio);
}
