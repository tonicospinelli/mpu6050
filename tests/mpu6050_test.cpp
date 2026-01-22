#include <gtest/gtest.h>
#include "stubs/Arduino.h"
#include "stubs/I2Cdev.h"
#include "MPU6050.h"

class MPU6050Test : public ::testing::Test
{
protected:
    MPU6050 *mpu{};

    void SetUp() override
    {
        I2CDevSimulator::reset();
        mpu = new MPU6050(MPU6050_DEFAULT_ADDRESS);

        // Simulate MPU6050 WHO_AM_I response
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, 0x68);
    }

    void TearDown() override
    {
        delete mpu;
    }

    // Helper: Simulate sensor data
    static void simulateAccelData(int16_t x, int16_t y, int16_t z)
    {
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, (x >> 8) & 0xFF);
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_XOUT_L, x & 0xFF);
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_YOUT_H, (y >> 8) & 0xFF);
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_YOUT_L, y & 0xFF);
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H, (z >> 8) & 0xFF);
        I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L, z & 0xFF);
    }
};

TEST_F(MPU6050Test, InitializeSetsCorrectRegisters)
{
    mpu->initialize();

    // Verify the clock source was set (register 0x6B)
    uint8_t pwrMgmt = I2CDevSimulator::getRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_PWR_MGMT_1);
    EXPECT_EQ(pwrMgmt & 0x07, 0x01); // PLL with X gyro reference

    // Verify sleep is disabled (bit 6 of 0x6B should be 0)
    EXPECT_EQ((pwrMgmt >> 6) & 0x01, 0);
}

TEST_F(MPU6050Test, GetAccelerationReadsCorrectRegisters)
{
    simulateAccelData(1000, 2000, 3000);

    int16_t ax, ay, az;
    mpu->getAcceleration(&ax, &ay, &az);

    EXPECT_EQ(ax, 1000);
    EXPECT_EQ(ay, 2000);
    EXPECT_EQ(az, 3000);
}

TEST_F(MPU6050Test, TestConnection)
{
    // Simulate correct device ID
    I2CDevSimulator::setRegister(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, 0x34 << 1);
    // 0x68 because WHO_AM_I is bits [6:1]

    bool connected = mpu->testConnection();
    EXPECT_TRUE(connected);
}

// Memory footprint test
TEST_F(MPU6050Test, MemoryFootprint)
{
    size_t objectSize = sizeof(MPU6050);

    std::cout << "MPU6050 object size: " << objectSize << " bytes" << std::endl;

    // Assert reasonable size (adjust based on your requirements)
    EXPECT_LT(objectSize, 100); // Should be less than 100 bytes
}

// Performance characterization
TEST_F(MPU6050Test, ReadPerformance)
{
    simulateAccelData(100, 200, 300);

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; i++) {
        int16_t ax, ay, az;
        mpu->getAcceleration(&ax, &ay, &az);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "1000 reads took: " << duration.count() << " microseconds" << std::endl;
    std::cout << "Average per read: " << duration.count() / 1000 << " μs" << std::endl;
}
