#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamWriter>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include "grafica.h"
#include <QVector>
#include <QFileSystemWatcher>



namespace Ui {
class MainWindow;
}

class QUdpSocket;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


signals:
    //
private slots:
    QString getAdmin(QString dato);
    void on_bnEnviar_clicked();

    void on_bnGraficar_clicked();

    void on_bnBuscarVoltaje_clicked();
    void ShowFilesQLine(QString nombre);

private:
    Ui::MainWindow *ui;
    QDomDocument *xmlTemporal;
    QUdpSocket *mSocket;
    grafica *wGrafica;
    QFileSystemWatcher *watcher;


};

#endif // MAINWINDOW_H
