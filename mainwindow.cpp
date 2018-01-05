#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <QMessageBox>

// globalne zmienne
QList <QSerialPortInfo> available_port;     // lista portów pod którymi są urządzenia
const QSerialPortInfo *info;                // obecnie wybrany serial port

QSerialPort port;                           // obecnie otwarty port

// funkcje
MainWindow::MainWindow(xmlReader *pjsonReader, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _pjsonReader = pjsonReader;
    ui->setupUi(this);
    info = NULL;

    searchDevices();

    connect(ui->action_refreshPorts,SIGNAL(triggered()),this,SLOT(refresh()));
    connect(_pjsonReader, SIGNAL(sendPointToMainwindow(poseBodyPartPoint)),
            this, SLOT(checkPoint(poseBodyPartPoint)));
}

MainWindow::~MainWindow()
{
    if(port.isOpen())
        port.close();

    delete ui;
}


// aktualizowanie listy z urządzeniami
void MainWindow::searchDevices()
{
    // dodanie ich do listy
    available_port = QSerialPortInfo::availablePorts();

    int porty = available_port.size();
    QString message = QString::number(porty) + (porty == 1 ? " port is ready to use" : " ports are ready to use");

    // wyświetlamy wiadomość z informacją ile znaleźliwśmy urządzeń gotowych do pracy
    ui->statusBar->showMessage(message,3000);

    // aktualizujemy
    info = NULL;
    ui->port->clear();
    ui->port->addItem("NULL");
    for(int i=0;i<porty;i++)
    {
        ui->port->addItem(available_port.at(i).portName());
    }
}

void MainWindow::on_port_currentIndexChanged(int index)
{
    if(port.isOpen()) port.close();
    QString txt = "NULL";
    if (index > 0){
        info = &available_port.at(index-1);
        txt = info->portName();

        port.setPort(available_port.at(index-1));
        if(!port.open(QIODevice::ReadWrite))
            QMessageBox::warning(this,"Device error","Unable to open port.");
    }
    else
        info = NULL;

    ui->statusBar->showMessage("Selected port: " + txt,2000);
}


void MainWindow::refresh()
{
    searchDevices();
}


void MainWindow::on_commandLine_returnPressed()
{
    // jeżeli nie wybrano żadnego urządzenia nie wysyłamy
    if(info == NULL) {
        ui->statusBar->showMessage("Not port selected",3000);
        return;
    }

    addTextToConsole(ui->commandLine->text(),true);
    ui->commandLine->clear();
}


void MainWindow::on_enterButton_clicked()
{
    on_commandLine_returnPressed();
}


void MainWindow::addTextToConsole(QString msg,bool sender)
{
    if(msg.isEmpty()) return;

    // będziemy obsługiwać tutaj tylko 1 komendę więc dlatego w ten sposób
    if(msg == "/clear") {
        ui->output->clear();
        return;
    }

    // dodawanie tekstu do konsoli
    QString line = (sender ? "<user>: " : "<device>: ");
    line += msg + "\n";
    ui->output->setPlainText(ui->output->toPlainText() + line);

    // auto scroll
    QScrollBar *scroll = ui->output->verticalScrollBar();
    scroll->setValue(scroll->maximum());

    // wysyłanie wiadomości do urządzenia
    if(sender) send(msg+"$");
}


void MainWindow::send(QString msg)
{
    if(port.isOpen()) {
        port.write(msg.toStdString().c_str());
        port.waitForBytesWritten(-1);
    }

    // spodziewamy się odpowiedzi więc odbieramy dane
    receive();
}


void MainWindow::receive()
{
    // czekamy 5 sekund na odpowiedź
    if(port.waitForReadyRead(5000)) {
        QByteArray r_data = port.readAll();


        // sprawdzamy czy nie dojdą żadne nowe dane w 10ms
        while(port.waitForReadyRead(10)) {
            r_data += port.readAll();
        }

        QString str(r_data);
        str.remove("$");

        addTextToConsole(str);
    }
}

void MainWindow::checkPoint(poseBodyPartPoint neckPoint)
{
    int screenH = 1280;
    int screenV = 720;
    poseBodyPartPoint center;
    center.x = 720;
    center.y = 360;
    center.c = 0.75; //[0,1] chyba

    //double h = 1.7; //[m]

    double alpha_center = -12; //[deg]
    double beta_center = +22; //[deg]

    poseBodyPartPoint pixelsFromCenter;
    pixelsFromCenter.x = neckPoint.x - center.x;
    pixelsFromCenter.y = neckPoint.y - center.y;
    //qDebug() << "pixelsFromCenter.x =" << pixelsFromCenter.x << ", pixelsFromCenter.y =" << pixelsFromCenter.y;

    double percentFromCenterX = pixelsFromCenter.x/screenH;
    double percentFromCenterY = pixelsFromCenter.y/screenV;
    //qDebug() << "percentFromCenterX =" << percentFromCenterX << ", percentFromCenterY =" << percentFromCenterY;

    double alphaFromCenter = qAtan2(neckPoint.c, percentFromCenterX) * (180/M_PI);
    double betaFromCenter = qAtan2(neckPoint.c, percentFromCenterY) * (180/M_PI);
    //qDebug() << "alphaFromCenter =" << alphaFromCenter << ", betaFromCenter =" << betaFromCenter;

    double alpha = alpha_center + alphaFromCenter;
    double beta = beta_center + betaFromCenter;
    qDebug() << "alpha =" << alpha << ", beta =" << beta;

    QString QStrAlpha = QString::number(int(alpha));
    if (alpha < 100) QStrAlpha = "0" + QStrAlpha;
    if (alpha < 10) QStrAlpha = "0" + QStrAlpha;
    QString QStrBeta = QString::number(int(beta));
    if (beta < 100) QStrAlpha = "0" + QStrBeta;
    if (beta < 10) QStrAlpha = "0" + QStrBeta;
    qDebug() << "QStrAlpha =" << QStrAlpha << ", QStrBeta =" << QStrBeta;

    if(port.isOpen() && alpha >= 0 && beta >= 0)
        this->send("$(" + QStrAlpha + "," + QStrBeta + ")");
    else qDebug() << "port is closed";
}
