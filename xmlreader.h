#ifndef XMLREADER_H
#define XMLREADER_H

#pragma once
#include <QtCore>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include "posebodypartpoint.h"

class xmlReader: public QObject
{
    Q_OBJECT

public:
    xmlReader();

    QTimer *xmlTimer = new QTimer(this);
    QString QStrDir = "C:/Users/mar/Desktop/OpenPose_demo_1.0.1/OpenPose_demo_1.0.1/output/";
    QString QStrFirstTestedFile = "000000000000_keypoints.json"; //12 zer
    QString QStrActualTestedFile;
    poseBodyPartPoint neck;

    QFile file();
    bool isFileExists(QString path);
    QString findLatestFile();
    QString fileNrToFileQStr(int64_t fileNr);
    void loadFile(QString QStrFileName);

public slots:
    void searchForNewXmlDoc();

signals:
    void sendPointToMainwindow(poseBodyPartPoint);
};

#endif // XMLREADER_H
