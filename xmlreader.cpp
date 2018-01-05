#include "xmlreader.h"

xmlReader::xmlReader()
{
    xmlTimer->setInterval(500);
    xmlTimer->setSingleShot(false);
    connect(xmlTimer, SIGNAL(timeout()),
            this, SLOT(searchForNewXmlDoc()));

    xmlTimer->start();
}

void xmlReader::searchForNewXmlDoc()
{
    if(QDir(QStrDir).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
    {
        qDebug() << "ERROR: Directory is empty!";
        return;
    }
    else
    {
        if(!this->isFileExists(QStrDir + QStrFirstTestedFile))
        {
            qDebug() << "ERROR: dir not empty, but 1st file doesnt exist. file name:"
                     << QStrFirstTestedFile;
            return;
        }
        else
        {
            QStrActualTestedFile = this->findLatestFile();
            this->loadFile(QStrActualTestedFile);
        }
    }
}

bool xmlReader::isFileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    //qDebug() << "is file exists:" << check_file.exists() << ", is file not dir:" << check_file.isFile();
    if (check_file.exists() && check_file.isFile())
        return true;
    else
        return false;
}

QString xmlReader::findLatestFile()
{
    int64_t nLatestFileNr = 0;
    bool isLatestFileHasBeenFound = false;

    do
    {
        if (!isFileExists(QStrDir + fileNrToFileQStr(nLatestFileNr)))
        {
            --nLatestFileNr;
            isLatestFileHasBeenFound = true;
        }
        else
            ++nLatestFileNr;
        if(nLatestFileNr > 10000)
        {
            qDebug() << "WARNING: nLatestFileNr rather too big. break the loop";
            isLatestFileHasBeenFound = true;
        }
    }
    while (!isLatestFileHasBeenFound);

    if(nLatestFileNr < 0) nLatestFileNr = 0;
    return fileNrToFileQStr(nLatestFileNr);
}

QString xmlReader::fileNrToFileQStr(int64_t fileNr)
{
    QString QStrFileName = QString::number(fileNr) + "_keypoints.json";
    int nMissingZeros = QStrFirstTestedFile.length() - QStrFileName.length();
    QString QStrMissingZeros = "";
    if (nMissingZeros > 0)
    {
        for(int i=1; i <= nMissingZeros; ++i)
            QStrMissingZeros += "0";
        QStrFileName = QStrMissingZeros + QStrFileName;
    }

    if(QStrFileName.length() != QStrFirstTestedFile.length())
        qDebug() << "ERROR: wrong QStrFileName.length(). it =" <<
                    QStrFileName.length();


    return QStrFileName;
}

void xmlReader::loadFile(QString QStrFileName)
{
    QFile file(QStrDir + QStrFileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "ERROR: xmlReader::loadFile(QString QStrFileName): failed to load file:" << QStrFileName;
        return;
    }
    else
    {
        qDebug() << "loaded file name:" << QStrFileName;

        QJsonDocument jsonDoc1 = QJsonDocument::fromJson(file.readAll());
        QString strJson(jsonDoc1.toJson(QJsonDocument::Compact));

        strJson = strJson.mid(101);

        QStringList StrListJson = strJson.split(",");
        if (StrListJson.size() > 5)
        {
            QString QStrNeckX = StrListJson.at(3);
            neck.x = QStrNeckX.toDouble();
            QString QStrNeckY = StrListJson.at(4);
            neck.y = QStrNeckY.toDouble();
            QString QStrNeckC = StrListJson.at(5);
            neck.c = QStrNeckC.toDouble();
            neck.showPointInDebug();
        }
        else
            qDebug() << "no person to track";


        file.close();

        emit sendPointToMainwindow(neck);
    }

}

/*void xmlReader::readJson(QString QStrJson)
{

}*/
