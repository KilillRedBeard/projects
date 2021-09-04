#include "message.h"

message::message() {
    generateHeader();
    generateData();
    head.setLen(head.calculateLen() + data.calculateLen());
}

void message::generateHeader() {
    head.setSrc(uint32_t(QRandomGenerator::global()->bounded(0, 9999999)));
    head.setDst(uint32_t(QRandomGenerator::global()->bounded(0, 9999999)));
    head.setType(uint16_t(QRandomGenerator::global()->bounded(0, 9999999)));
    head.setLen(uint16_t(QRandomGenerator::global()->bounded(0, 9999999)));
    head.setCrc(uint16_t(QRandomGenerator::global()->bounded(0, 9999999)));
}

void message::generateData() {
    data.setNChan(uint16_t(QRandomGenerator::global()->bounded(0, 9999999)));
    data.setStatus(uint32_t(QRandomGenerator::global()->bounded(0, 9999999)));
    data.setData(data.generateData());
    data.setCrc(uint32_t(QRandomGenerator::global()->bounded(0, 9999999)));
    data.setDataSize(uint16_t(sizeof(this)));
}

void message::setData(signalData data) {this->data = data;}

void message::setHeader(header head) {this->head = head;}

header message::getHeader() {return head;}

signalData message::getData() {return data;}
