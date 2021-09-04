#include "signaldata.h"

QVector<float> signalData::generateData() {
    QVector<float> generatedData;
    int num = QRandomGenerator::global()->bounded(1, 1000);

    data.clear();

    for(int i = 0; i < num; ++i) {
        generatedData.push_back(static_cast<float>(sin(i)));
    }

    return generatedData;
}

signalData::signalData() {}

void signalData::setNChan(uint16_t nChan) {this->nChan = nChan;}

void signalData::setStatus(uint32_t status) {this->status = status;}

void signalData::setDataSize(uint16_t dataSize) {this->dataSize = dataSize;}

void signalData::setData(QVector<float> data) {this->data = data;}

void signalData::setCrc(uint32_t crc) {this->crc = crc;}

uint16_t signalData::getNChan() {return nChan;}

uint32_t signalData::getStatus() {return status;}

uint16_t signalData::getDataSize() {return dataSize;}

QVector<float> signalData::getData() {return data;}

uint32_t signalData::getCrc() {return crc;}

uint16_t signalData::calculateLen() {
    uint16_t res = 0;

    for(int i = 0; i < data.size(); ++i) {
        res += sizeof (data.at(i));
    }

    res += sizeof(nChan) + sizeof(status) + sizeof(dataSize) + sizeof(data) + sizeof(crc);

    return res;
}
