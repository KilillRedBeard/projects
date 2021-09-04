#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QObject>
#include <stdint.h>
#include <QVector>
#include <QDebug>
#include <QRandomGenerator>

class signalData
{
private:
    uint16_t nChan;
    uint32_t status;
    uint16_t dataSize;
    QVector<float> data;
    uint32_t crc;

public:
    signalData();
    QVector<float> generateData();

    void setNChan(uint16_t nChan);
    void setStatus(uint32_t status);
    void setDataSize(uint16_t dataSize);
    void setData(QVector<float> data);
    void setCrc(uint32_t crc);

    uint16_t getNChan();
    uint32_t getStatus();
    uint16_t getDataSize();
    QVector<float> getData();
    uint32_t getCrc();
    uint16_t calculateLen();
};

#endif // SIGNALDATA_H
