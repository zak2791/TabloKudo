#include "hansoku.h"

Hansoku::Hansoku(QWidget *parent):
QLabel(parent){
    hansoku = new QDialog;
    hansoku->setModal(true);
    ui.setupUi(hansoku);

}

void Hansoku::mousePressEvent(QMouseEvent *){
    hansoku->show();
    setText("1");
    setAutoFillBackground(true);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    font = QFont();
}
void Hansoku::resizeEvent(QResizeEvent *){
    font.setWeight(50);
    font.setPixelSize(height() * 2);
    QFontMetrics fm = QFontMetrics(font);




    int fontSize = height() * 1.05;
    while (true) {
        font.setPixelSize(fontSize);
        setFont(font);
        fm = QFontMetrics(font);
        if (fm.horizontalAdvance("0") < width() )
            break;
        if (fontSize > 20)
            fontSize -= 20;
        else
            break;
    }


}
