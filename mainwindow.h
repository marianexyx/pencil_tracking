#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#pragma once
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCore>
#include <qdebug.h>
#include "posebodypartpoint.h"
#include "xmlreader.h"
#include <QtMath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(xmlReader* pjsonReader, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_port_currentIndexChanged(int index);
    void refresh();

    void on_commandLine_returnPressed();

    void on_enterButton_clicked();

private:
    xmlReader* _pjsonReader;

    Ui::MainWindow *ui;

    void searchDevices();
    void addTextToConsole(QString text, bool sender=false);

    void send(QString msg);
    void receive();

public slots:
    void checkPoint(poseBodyPartPoint neckPoint);
};

#endif // MAINWINDOW_H
