#include "I2Cdev.h"

std::map<uint8_t, std::map<uint8_t, uint8_t>> I2CDevSimulator::deviceRegisters;

const uint16_t I2Cdev::readTimeout = 1000;

int8_t I2Cdev::readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, uint16_t timeout, void *wireObj)
{
    uint8_t byte = I2CDevSimulator::getRegister(devAddr, regAddr);
    *data = (byte >> bitNum) & 0x01;
    return 1;
}

int8_t I2Cdev::readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data,
                        uint16_t timeout, void *wireObj)
{
    uint8_t byte = I2CDevSimulator::getRegister(devAddr, regAddr);
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    byte &= mask;
    byte >>= (bitStart - length + 1);
    *data = byte;
    return 1;
}

int8_t I2Cdev::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout, void *wireObj)
{
    *data = I2CDevSimulator::getRegister(devAddr, regAddr);
    return 1;
}

int8_t I2Cdev::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout,
                         void *wireObj)
{
    for (uint8_t i = 0; i < length; i++) {
        data[i] = I2CDevSimulator::getRegister(devAddr, regAddr + i);
    }
    return length;
}

int8_t I2Cdev::readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, uint16_t timeout,
                         void *wireObj)
{
    for (uint8_t i = 0; i < length; i++) {
        uint8_t msb = I2CDevSimulator::getRegister(devAddr, regAddr + (i * 2));
        uint8_t lsb = I2CDevSimulator::getRegister(devAddr, regAddr + (i * 2) + 1);
        data[i] = (msb << 8) | lsb;
    }
    return length;
}

bool I2Cdev::writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data, void *wireObj)
{
    uint8_t byte = I2CDevSimulator::getRegister(devAddr, regAddr);
    byte = (data != 0) ? (byte | (1 << bitNum)) : (byte & ~(1 << bitNum));
    I2CDevSimulator::setRegister(devAddr, regAddr, byte);
    return true;
}

bool I2Cdev::writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data, void *wireObj)
{
    uint8_t byte = I2CDevSimulator::getRegister(devAddr, regAddr);
    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    data <<= (bitStart - length + 1);
    data &= mask;
    byte &= ~mask;
    byte |= data;
    I2CDevSimulator::setRegister(devAddr, regAddr, byte);
    return true;
}

bool I2Cdev::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data, void *wireObj)
{
    I2CDevSimulator::setRegister(devAddr, regAddr, data);
    return true;
}

bool I2Cdev::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, void *wireObj)
{
    for (uint8_t i = 0; i < length; i++) {
        I2CDevSimulator::setRegister(devAddr, regAddr + i, data[i]);
    }
    return true;
}

bool I2Cdev::writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data, void *wireObj)
{
    I2CDevSimulator::setRegister(devAddr, regAddr, (data >> 8) & 0xFF);
    I2CDevSimulator::setRegister(devAddr, regAddr + 1, data & 0xFF);
    return true;
}

bool I2Cdev::writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, void *wireObj)
{
    for (uint8_t i = 0; i < length; i++) {
        writeWord(devAddr, regAddr + (i * 2), data[i], wireObj);
    }
    return true;
}
