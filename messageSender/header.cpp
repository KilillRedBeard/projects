#include "header.h"

header::header()
{

}

header::~header()
{

}

void header::setSrc(uint32_t src) {this->src = src;}

void header::setDst(uint32_t dst) {this->dst = dst;}

void header::setType(uint16_t type) {this->type = type;}

void header::setLen(uint16_t len) {this->len = len;}

void header::setCrc(uint32_t crc) {this->crc = crc;}

uint32_t header::getSrc() {return src;}

uint32_t header::getDst() {return dst;}

uint16_t header::getType() {return type;}

uint16_t header::getLen() {return len;}

uint32_t header::getCrc() {return crc;}

uint16_t header::calculateLen() {
    return sizeof (src) + sizeof (dst) +sizeof (type) +sizeof (len) +sizeof (crc);
}
