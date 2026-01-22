#ifndef ARDUINO_H
#define ARDUINO_H

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

// Stub Serial for printing
class SerialStub
{
public:
    void print(const char *str)
    {
        printf("%s", str);
    }

    void print(int val)
    {
        printf("%d", val);
    }

    void print(float val, int decimals)
    {
        printf("%.*f", decimals, val);
    }

    void println(const char *str)
    {
        printf("%s\n", str);
    }

    void write(char c)
    {
        putchar(c);
    }
};

extern SerialStub Serial;

// Arduino functions
inline void delay(uint32_t ms)
{
    /* stub */
}

inline uint32_t millis()
{
    return 0;
}

inline uint32_t micros()
{
    return 0;
}

inline long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#define pgm_read_byte(addr) (*(const uint8_t *)(addr))

using std::abs;
using std::round;

#endif
