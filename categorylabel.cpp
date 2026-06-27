#include "categorylabel.h"

CategoryLabel::CategoryLabel() {
    QFont font;
    font.setPixelSize(20);
    setFont(font);
}

void CategoryLabel::setWeight(QString w){
    weight = w;
    setText(age + " " + weight);
}

void CategoryLabel::setAge(QString a){
    age = a;
    setText(age + " " + weight);
}
