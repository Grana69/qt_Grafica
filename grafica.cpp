#include "grafica.h"
#include "ui_grafica.h"
#include <algorithm>

grafica::grafica(QWidget *parent,const QString archivo,QString ejeX, QString ejeY ) :
    QWidget(parent),
    ui(new Ui::grafica)
{
    ui->setupUi(this);
    ui->widget->addGraph();
    ui->widget->xAxis->setLabel(ejeX);
    ui->widget->yAxis->setLabel(ejeY);
    GraficarArchivo(archivo);
    watcher = new QFileSystemWatcher(this);
    watcher->addPath(archivo);
    connect(watcher,SIGNAL(fileChanged(QString)),this,SLOT(GraficarArchivo(QString)));
}

void grafica::GraficarArchivo(const QString& archivo){
    qDebug() << "Llego aqui" << endl;
    QVector<double> vVoltaje;
    QVector<double> vTiempo;

    QFile xml(archivo);
    xml.open(QIODevice::ReadOnly);
    xmlTemporal = new QDomDocument();
    xmlTemporal->setContent(&xml);
    xml.close();

    QDomElement root = xmlTemporal->documentElement();
    QDomElement Mediciones = root.firstChild().toElement();
    while(!Mediciones.isNull()){
        if(Mediciones.tagName() == "Medicion"){
            QDomElement medicion = Mediciones.firstChild().toElement();
            while(!medicion.isNull()){
                    vVoltaje.append(medicion.attribute("Voltaje","ErrorVoltaje").toFloat());
                    vTiempo.append(medicion.attribute("Tiempo","ErrorTiempo").toFloat());
                    medicion = medicion.nextSibling().toElement();
            }
        }
        Mediciones = Mediciones.nextSibling().toElement();
    }

    double min_Tiempo = *std::min_element(vTiempo.constBegin(),vTiempo.constEnd());
    double max_Tiempo = *std::max_element(vTiempo.constBegin(),vTiempo.constEnd());
    double min_Voltaje = *std::min_element(vVoltaje.constBegin(),vVoltaje.constEnd());
    double max_Voltaje = *std::max_element(vVoltaje.constBegin(),vVoltaje.constEnd());

    ui->widget->graph(0)->setData(vTiempo, vVoltaje);
    ui->widget->xAxis->setRange(min_Tiempo, max_Tiempo);
    ui->widget->yAxis->setRange(min_Voltaje, max_Voltaje);
    ui->widget->replot();
}

grafica::~grafica()
{
    delete ui;
}
