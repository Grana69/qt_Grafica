#include "mainwindow.h"
#include "grafica.h"
#include "ui_mainwindow.h"
#include <QUdpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mSocket = new QUdpSocket(this);
    ui->setupUi(this);
    QFile xml("miXml.xml");
    xml.open(QIODevice::WriteOnly);
    QXmlStreamWriter escritorXml(&xml);
    escritorXml.setAutoFormatting(true);
    escritorXml.writeStartDocument();
    escritorXml.writeStartElement("Mediciones");

    QStringList listaVoltaje;
    listaVoltaje.append("2.3");
    listaVoltaje.append("2.5");
    listaVoltaje.append("2.1");
    listaVoltaje.append("2.5");
    listaVoltaje.append("2.7");
    listaVoltaje.append("2.1");
    listaVoltaje.append("2.4");
    listaVoltaje.append("2.3");
    listaVoltaje.append("2.2");
    listaVoltaje.append("2");
    for(int i = 0; i< listaVoltaje.size(); ++i){
        QString Voltaje = listaVoltaje.at(i);
        QString Tiempo = QString::number(i+1);
    escritorXml.writeStartElement("Medicion");
    escritorXml.writeStartElement("Datos");
    escritorXml.writeAttribute("Voltaje",Voltaje);
    escritorXml.writeAttribute("Tiempo",Tiempo);
    escritorXml.writeEndElement();
    escritorXml.writeEndElement();
 }

    escritorXml.writeEndElement();

    escritorXml.writeEndDocument();

    xml.close();
    MiHilo hilo1;
    hilo1.correr("miXml.xml");

}
void MiHilo::correr(QString nombre){
    QFile salida(nombre);
    salida.open(QIODevice::ReadOnly);
    QTextStream leer(&salida);
    ui->plainTextEdit->setPlainText(leer.readAll());
    salida.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::getAdmin(QString dato){

    QFile xml("miXml.xml");
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
                    QString vVoltaje = medicion.attribute("Voltaje","ErrorTiempo");
                    if (medicion.attribute("Tiempo","ErrorTiempo") == dato) return vVoltaje;
                    medicion = medicion.nextSibling().toElement();
            }
        }
        Mediciones = Mediciones.nextSibling().toElement();
    }

    return "No encontrado";
}


void MainWindow::on_bnEnviar_clicked()
{
    auto datagrama = ui->plainTextEdit->toPlainText().toLatin1();
    mSocket->writeDatagram(datagrama,QHostAddress::LocalHost,ui->puerto->value());

}

void MainWindow::on_bnGraficar_clicked()
{
    QVector<float> *vVoltaje;
    QVector<float> *vTiempo;

    vVoltaje = new QVector<float>();
    vTiempo = new QVector<float>();

    QFile xml("miXml.xml");
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
                    vVoltaje->append(medicion.attribute("Voltaje","ErrorVoltaje").toFloat());
                    vTiempo->append(medicion.attribute("Tiempo","ErrorTiempo").toFloat());
                    medicion = medicion.nextSibling().toElement();
            }
        }
        Mediciones = Mediciones.nextSibling().toElement();
    }

    wGrafica = new grafica(NULL,"Tiempo","Voltaje",vVoltaje,vTiempo);
    wGrafica->show();
}

void MainWindow::on_bnBuscarVoltaje_clicked()
{
    ui->tbResultado->setText(getAdmin(ui->tbBuscador->text()));
}
