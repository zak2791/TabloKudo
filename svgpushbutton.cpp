#include "svgpushbutton.h"
#include "qboxlayout.h"
#include "qsettings.h"
#include "qsvgrenderer.h"

SVGPushButton::SVGPushButton(QString _pathRus, QString _pathEng) : QPushButton() {
    pathRus = _pathRus;
    pathEng = _pathEng;
    setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QHBoxLayout* box = new QHBoxLayout(this);
    box->setContentsMargins(0,0,0,0);
    setLayout(box);
    layout()->addWidget(&w);
    setLanguage();
}

void SVGPushButton::setLanguage(){
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
