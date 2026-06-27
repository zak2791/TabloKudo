#ifndef CATEGORYLABEL_H
#define CATEGORYLABEL_H

#include <QLabel>

class CategoryLabel : public QLabel
{
public:
    CategoryLabel();

public slots:
    void setWeight(QString);
    void setAge(QString);

private:
    QString age;
    QString weight;
    //QString age_and_weight;

};

#endif // CATEGORYLABEL_H
