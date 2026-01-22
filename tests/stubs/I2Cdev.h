#ifndef _I2CDEV_H_
#define _I2CDEV_H_

#include <cstdint>
#include <map>
#include <vector>

// Simulated I2C device register storage
class I2CDevSimulator
{
public:
    static std::map<uint8_t, std::map<uint8_t, uint8_t>> deviceRegisters;

    static void reset()
    {
        deviceRegisters.clear();
    }

    static void setRegister(uint8_t devAddr, uint8_t regAddr, uint8_t value)
    {
        deviceRegisters[devAddr][regAddr] = value;
    }

    static uint8_t getRegister(uint8_t devAddr, uint8_t regAddr)
    {
        return deviceRegisters[devAddr][regAddr];
    }
};

class I2Cdev
{
public:
    static const uint16_t readTimeout;

    static int8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum,
                          uint8_t *data, uint16_t timeout = 1000, void *wireObj = nullptr);

    static int8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart,
                           uint8_t length, uint8_t *data, uint16_t timeout = 1000,
                           void *wireObj = nullptr);

    static int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data,
                           uint16_t timeout = 1000, void *wireObj = nullptr);

    static int8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length,
                            uint8_t *data, uint16_t timeout = 1000, void *wireObj = nullptr);

    static int8_t readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length,
                            uint16_t *data, uint16_t timeout = 1000, void *wireObj = nullptr);

    static bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum,
                         uint8_t data, void *wireObj = nullptr);

    static bool writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart,
                          uint8_t length, uint8_t data, void *wireObj = nullptr);

    static bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data,
                          void *wireObj = nullptr);

    static bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length,
                           uint8_t *data, void *wireObj = nullptr);

    static bool writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data,
                          void *wireObj = nullptr);

    static bool writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length,
                           uint16_t *data, void *wireObj = nullptr);
};

#endif
