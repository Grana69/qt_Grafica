#ifndef GRAFICA_H
#define GRAFICA_H

#include <QWidget>
#include <QVector>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QFileSystemWatcher>


namespace Ui {
class grafica;
}

class grafica : public QWidget
{
    Q_OBJECT

public:
    explicit grafica(QWidget *parent = 0, const QString archivo = "Res.xml",QString ejeX = "x", QString ejeY = "y");
    ~grafica();

private:
    Ui::grafica *ui;
    QDomDocument *xmlTemporal;
    QFileSystemWatcher * watcher;
private slots:
    void GraficarArchivo(const QString& archivo);
};

#endif // GRAFICA_H
