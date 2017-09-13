#include "grafica.h"
#include "ui_grafica.h"
#include <algorithm>

grafica::grafica(QWidget *parent, QString ejeX, QString ejeY, QVector<float> *vectorVoltaje, QVector<float> *vectorTiempo) :
    QWidget(parent),
    ui(new Ui::grafica)
{
    ui->setupUi(this);

    QVector<double> vTiempo;
    QVector<double> vVoltaje;
    for(int i = 0; i<vectorVoltaje->size();i++)
        vVoltaje.append(vectorVoltaje->at(i));
    for(int i = 0; i<vectorTiempo->size();i++)
        vTiempo.append(vectorTiempo->at(i));


    // create graph and assign data to it:
    double min_Tiempo = *std::min_element(vTiempo.constBegin(),vTiempo.constEnd());
    double max_Tiempo = *std::max_element(vTiempo.constBegin(),vTiempo.constEnd());

    double min_Voltaje = *std::min_element(vVoltaje.constBegin(),vVoltaje.constEnd());
    double max_Voltaje = *std::max_element(vVoltaje.constBegin(),vVoltaje.constEnd());

    ui->widget->addGraph();
    ui->widget->graph(0)->setData(vTiempo, vVoltaje);
    ui->widget->xAxis->setLabel(ejeX);
    ui->widget->yAxis->setLabel(ejeY);
    ui->widget->xAxis->setRange(min_Tiempo, max_Tiempo);
    ui->widget->yAxis->setRange(min_Voltaje, max_Voltaje);
    ui->widget->replot();
}

grafica::~grafica()
{
    delete ui;
}
