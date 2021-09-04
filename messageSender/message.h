#ifndef MESSAGE_H
#define MESSAGE_H

#include "header.h"
#include "signaldata.h"
#include <QVector>
#include <QObject>

class message
{
private:
    header head;
    signalData data;

public:
    message();

    void generateHeader();
    void generateData();

    void setData(signalData data);
    void setHeader(header head);

    header getHeader();
    signalData getData();
};

#endif // MESSAGE_H
