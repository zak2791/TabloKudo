#include "hansoku.h"
#include <QDebug>

Hansoku::Hansoku(QString col, QWidget *parent):
QLabel(parent){
    hansoku = new QDialog;
    hansoku->setModal(true);
    ui.setupUi(hansoku);
    color = col;

    stileString = "QLabel{border-radius: 30px; "
                  "border-width: 2px; "
                  "border-style: solid; "
                  "border-color: %1; "
                  "background-color: %2; "
                  "color: black;}";

    style = stileString.arg(col).arg("black");
    styleKei =  stileString.arg(col).arg("yellow");
    styleHan1 = stileString.arg(col).arg("yellow");
    styleHan2 = stileString.arg(col).arg("yellow");
    styleHan3 = stileString.arg(col).arg("red");

    setStyleSheet(style);
    connect(ui.cbKeikoku, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku1 , SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku2, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku3, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
}

void Hansoku::choiceHansoku(int state){
    if(sender()->objectName() == "cbHansoku1"){
        if(state){
            sigHansoku(1);
        }else{
            sigHansoku(-1);
        }
    }else if(sender()->objectName() == "cbHansoku2"){
        if(state){
            sigHansoku(2);
        }else{
            sigHansoku(-2);
        }
    }else if(sender()->objectName() == "cbHansoku3"){
        if(state){
            sigHansoku(4);
        }else{
            sigHansoku(-4);
        }
    }
    if(ui.cbHansoku3->isChecked()){
        setStyleSheet(styleHan3);
        setText("3");
    }else if(ui.cbHansoku2->isChecked()){
        setStyleSheet(styleHan2);
        setText("2");
    }else if(ui.cbHansoku1->isChecked()){
        setStyleSheet(styleHan1);
        setText("1");
    }else if(ui.cbKeikoku->isChecked()){
        setStyleSheet(styleKei);
        setText("");
    }else{
        setStyleSheet(style);
        setText("");
    }
}

void Hansoku::mousePressEvent(QMouseEvent *){
    hansoku->show();
    //setText("1");
    //setAutoFillBackground(true);
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
