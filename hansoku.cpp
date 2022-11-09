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

    style = stileString.arg(col, "black");
    styleKei =  stileString.arg(col, "yellow");
    styleHan1 = stileString.arg(col, "yellow");
    styleHan2 = stileString.arg(col, "yellow");
    styleHan3 = stileString.arg(col, "red");

    setStyleSheet(style);
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    connect(ui.cbKeikoku, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku1 , SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku2, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
    connect(ui.cbHansoku3, SIGNAL(stateChanged(int)), this, SLOT(choiceHansoku(int)));
}

void Hansoku::choiceHansoku(int state){
    if(sender()->objectName() == "cbHansoku1"){
        if(state){
            emit sigHansoku(1);
        }else{
            emit sigHansoku(-1);
        }
    }else if(sender()->objectName() == "cbHansoku2"){
        if(state){
            emit sigHansoku(2);
        }else{
            emit sigHansoku(-2);
        }
    }else if(sender()->objectName() == "cbHansoku3"){
        if(state){
            emit sigHansoku(4);
        }else{
            emit sigHansoku(-4);
        }
    }
    if(ui.cbHansoku3->isChecked()){
        setStyleAndText(4);
    }else if(ui.cbHansoku2->isChecked()){
        setStyleAndText(3);
    }else if(ui.cbHansoku1->isChecked()){
        setStyleAndText(2);
    }else if(ui.cbKeikoku->isChecked()){
        setStyleAndText(1);
    }else{
        setStyleAndText(0);
    }
}

void Hansoku::setStyleAndText(int st){
    if(st == 4){
        setText("3");
        setStyleSheet(styleHan3);
        emit sigStyle(4);
    }else if(st == 3){
        setText("2");
        setStyleSheet(styleHan2);
        emit sigStyle(3);
    }else if(st == 2){
        setText("1");
        setStyleSheet(styleHan1);
        emit sigStyle(2);
    }else if(st == 1){
        setStyleSheet(styleKei);
        setText("");
        emit sigStyle(1);
    }else{
        setStyleSheet(style);
        setText("");
        emit sigStyle(0);
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

void Hansoku::sbros(){
    ui.cbKeikoku->setChecked(false);
    ui.cbHansoku1->setChecked(false);
    ui.cbHansoku2->setChecked(false);
    ui.cbHansoku3->setChecked(false);

    //setStyleSheet(style);
    //setText("");
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
