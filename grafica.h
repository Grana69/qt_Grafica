#ifndef GRAFICA_H
#define GRAFICA_H

#include <QWidget>
#include <QVector>


namespace Ui {
class grafica;
}

class grafica : public QWidget
{
    Q_OBJECT

public:
    explicit grafica(QWidget *parent = 0,QString ejeX = "x",QString ejeY="y",QVector<float> *vectorVoltaje = NULL, QVector<float> *vectorTiempo= NULL);
    ~grafica();

private:
    Ui::grafica *ui;
};

#endif // GRAFICA_H
