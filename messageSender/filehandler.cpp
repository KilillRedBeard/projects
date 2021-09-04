#include "filehandler.h"

bool fileHandler::openFile() {
    if(!QDir(pathToFile).exists()) {
        QDir().mkdir(pathToFile);
    }

    if(file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        return true;
    } else {
        qDebug() << file.errorString();
        return false;
    }
}

bool fileHandler::closeFile() {
    file.close();

    if(file.isOpen()) {
        return false;
    } else {
        return true;
    }
}

fileHandler::fileHandler() {
    file.setFileName(pathToFile + "/" + fileName);
}

void fileHandler::setFileName(QString name) {this->fileName = name;}

void fileHandler::setPathToFile(QString path) {this->pathToFile = path;}

void fileHandler::setMessage(message mess) {
    this->mess.setData(mess.getData());
    this->mess.setHeader(mess.getHeader());
}

void fileHandler::writeToFile(message mess) {
    if(openFile()) {
        file.write("Message\n");
        file.write("\tHeader struct\n");
        file.write(QString("\t\tsrc: " + QString::number(mess.getHeader().getSrc()) + "\n").toUtf8());
        file.write(QString("\t\tdts: " + QString::number(mess.getHeader().getDst()) + "\n").toUtf8());
        file.write(QString("\t\ttype: " + QString::number(mess.getHeader().getType()) + "\n").toUtf8());
        file.write(QString("\t\tlen: " + QString::number(mess.getHeader().getLen()) + "\n").toUtf8());
        file.write(QString("\t\tcrc: " + QString::number(mess.getHeader().getCrc()) + "\n").toUtf8());
        file.write("\tData struct\n");
        file.write(QString("\t\tnChan: " + QString::number(mess.getData().getNChan()) + "\n").toUtf8());
        file.write(QString("\t\tstatus: " + QString::number(mess.getData().getStatus()) + "\n").toUtf8());
        file.write(QString("\t\tdataSize: " + QString::number(mess.getData().getDataSize()) + "\n").toUtf8());

        for(int i = 0; i < mess.getData().getData().size(); ++i) {
            file.write(QString("\t\tdata " + QString::number(i + 1) + ": " + QString::number(mess.getData().getData().at(i), 'g', 6) + "\n").toUtf8());
        }

        file.write(QString("\t\tcrc: " + QString::number(mess.getData().getNChan()) + "\n").toUtf8());
        file.write("EndMessage\n");

        closeFile();
    }
}

void fileHandler::readFromFile() {
    if(file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        message newMes;
        header head;
        signalData data;
        QVector<float> values;
        bool isHeader = false;
        bool isData = false;

        while(!file.atEnd()) {
            QString str = file.readLine();
            str.remove("\t");
            str.remove("\n");
            QStringList lst = str.split(": ");
            qDebug() << lst;

            if(lst.at(0) == "Header struct") {
                isHeader = true;
                isData = false;
            }

            if(lst.at(0) == "Data struct") {
                isHeader = false;
                isData = true;
            }

            if(isHeader) {
                if(lst.at(0) == "src") {
                    head.setSrc(lst.at(1).toInt());
                }
                if(lst.at(0) == "dts") {
                    head.setDst(lst.at(1).toInt());
                }
                if(lst.at(0) == "type") {
                    head.setType(lst.at(1).toInt());
                }
                if(lst.at(0) == "len") {
                    head.setLen(lst.at(1).toInt());
                }
                if(lst.at(0) == "crc") {
                    head.setCrc(lst.at(1).toInt());
                }
            }

            if(isData) {
                if(lst.at(0) == "nChan") {
                    data.setNChan(lst.at(1).toInt());
                }
                if(lst.at(0) == "status") {
                    data.setStatus(lst.at(1).toInt());
                }
                if(lst.at(0) == "dataSize") {
                    data.setDataSize(lst.at(1).toInt());
                }
                if(lst.at(0).contains("data ")) {
                    values.push_back(lst.at(1).toFloat());
                }
                if(lst.at(0) == "crc") {
                    data.setCrc(lst.at(1).toInt());
                }
            }

            if(lst.at(0) == "EndMessage") {
                data.setData(values);
                newMes.setHeader(head);
                newMes.setData(data);
                values.clear();

                emit addMessageToList(newMes);
            }
        }

        closeFile();
    }
}
