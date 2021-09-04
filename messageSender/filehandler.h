#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <message.h>

class fileHandler : public QObject
{
    Q_OBJECT

    QString fileName = "test.txt";
    QString pathToFile = QCoreApplication::applicationDirPath() + "/archive";
    message mess;

    QFile file;

    bool openFile();
    bool closeFile();
public:
    fileHandler();

    void setFileName(QString name);
    void setPathToFile(QString path);
    void setMessage(message mess);

public slots:
    void writeToFile(message mess);
    void readFromFile();

signals:
    void addMessageToList(message mes);
};

#endif // FILEHANDLER_H
