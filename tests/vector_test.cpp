#include <gtest/gtest.h>
#include <cmath>
#include "helper_3dmath.h"

// VectorInt16 Tests
TEST(VectorInt16Test, DefaultConstructor)
{
    VectorInt16 v;
    EXPECT_EQ(v.x, 0);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(VectorInt16Test, ParameterizedConstructor)
{
    VectorInt16 v(1, 2, 3);
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 2);
    EXPECT_EQ(v.z, 3);
}

TEST(VectorInt16Test, GetMagnitude)
{
    VectorInt16 v(3, 4, 0);
    EXPECT_FLOAT_EQ(v.getMagnitude(), 5.0f); // sqrt(9 + 16 + 0) = 5
}

TEST(VectorInt16Test, Normalize)
{
    VectorInt16 v(10, 0, 0);
    v.normalize();
    EXPECT_EQ(v.x, 1);
    EXPECT_EQ(v.y, 0);
    EXPECT_EQ(v.z, 0);
}

TEST(VectorInt16Test, Rotate)
{
    VectorInt16 v(100, 0, 0);
    // Rotate 90 degrees around Z axis
    // w = cos(pi/4), z = sin(pi/4)
    float s = sin(M_PI / 4.0);
    float c = cos(M_PI / 4.0);
    Quaternion q(c, 0, 0, s);
    
    v.rotate(&q);
    
    // After 90 deg rotation around Z, (100,0,0) should become (0,100,0)
    EXPECT_NEAR(v.x, 0, 1);
    EXPECT_NEAR(v.y, 100, 1);
    EXPECT_NEAR(v.z, 0, 1);
}

TEST(VectorInt16Test, GetNormalized)
{
    VectorInt16 v(10, 0, 0);
    VectorInt16 norm = v.getNormalized();
    EXPECT_EQ(norm.x, 1);
    EXPECT_EQ(v.x, 10); // Original should remain same
}

TEST(VectorInt16Test, GetRotated)
{
    VectorInt16 v(100, 0, 0);
    float s = sin(M_PI / 4.0);
    float c = cos(M_PI / 4.0);
    Quaternion q(c, 0, 0, s);
    VectorInt16 rot = v.getRotated(&q);
    EXPECT_NEAR(rot.x, 0, 1);
    EXPECT_NEAR(rot.y, 100, 1);
    EXPECT_EQ(v.x, 100); // Original should remain same
}

// VectorFloat Tests
TEST(VectorFloatTest, DefaultConstructor)
{
    VectorFloat v;
    EXPECT_FLOAT_EQ(v.x, 0.0f);
    EXPECT_FLOAT_EQ(v.y, 0.0f);
    EXPECT_FLOAT_EQ(v.z, 0.0f);
}

TEST(VectorFloatTest, ParameterizedConstructor)
{
    VectorFloat v(1.1f, 2.2f, 3.3f);
    EXPECT_FLOAT_EQ(v.x, 1.1f);
    EXPECT_FLOAT_EQ(v.y, 2.2f);
    EXPECT_FLOAT_EQ(v.z, 3.3f);
}

TEST(VectorFloatTest, GetMagnitude)
{
    VectorFloat v(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.getMagnitude(), 5.0f);
}

TEST(VectorFloatTest, Normalize)
{
    VectorFloat v(1.0f, 2.0f, 3.0f);
    float mag = sqrt(1*1 + 2*2 + 3*3);
    v.normalize();
    EXPECT_FLOAT_EQ(v.getMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(v.x, 1.0f / mag);
    EXPECT_FLOAT_EQ(v.y, 2.0f / mag);
    EXPECT_FLOAT_EQ(v.z, 3.0f / mag);
}

TEST(VectorFloatTest, Rotate)
{
    VectorFloat v(1.0f, 0.0f, 0.0f);
    float s = sin(M_PI / 4.0);
    float c = cos(M_PI / 4.0);
    Quaternion q(c, 0, s, 0);
    v.rotate(&q);
    EXPECT_NEAR(v.z, -1.0f, 1e-6);
}

TEST(VectorFloatTest, GetNormalized)
{
    VectorFloat v(1.0f, 2.0f, 3.0f);
    VectorFloat norm = v.getNormalized();
    EXPECT_FLOAT_EQ(norm.getMagnitude(), 1.0f);
    EXPECT_GT(v.getMagnitude(), 3.0f); // Original should remain same
}

TEST(VectorFloatTest, GetRotated)
{
    VectorFloat v(1.0f, 0.0f, 0.0f);
    float s = sin(M_PI / 4.0);
    float c = cos(M_PI / 4.0);
    Quaternion q(c, 0, s, 0);
    VectorFloat rot = v.getRotated(&q);
    EXPECT_NEAR(rot.z, -1.0f, 1e-6);
    EXPECT_FLOAT_EQ(v.x, 1.0f); // Original should remain same
}
