#ifndef HEADER_H
#define HEADER_H

#include <stdint.h>

class header
{
private:
    uint32_t src;
    uint32_t dst;
    uint16_t type;
    uint16_t len;
    uint32_t crc;

public:
    header(/* args */);
    ~header();

    void setSrc(uint32_t src);
    void setDst(uint32_t dst);
    void setType(uint16_t type);
    void setLen(uint16_t len);
    void setCrc(uint32_t crc);

    uint32_t getSrc();
    uint32_t getDst();
    uint16_t getType();
    uint16_t getLen();
    uint32_t getCrc();
    uint16_t calculateLen();
};

#endif // HEADER_H
