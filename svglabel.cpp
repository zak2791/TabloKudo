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
    setLanguage();
}

void SvgLabel::setLanguage(){
    QSettings settings("settings.ini", QSettings::IniFormat);
    settings.beginGroup("languages");
    QString language = settings.value("language", "ru").toString();
    settings.endGroup();
    if(language == "ru")
        w.load(pathRus);
    else
        w.load(pathEng);
    w.renderer()->setAspectRatioMode(Qt::KeepAspectRatio);
}
