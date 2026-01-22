#include <gtest/gtest.h>
#include <cmath>
#include "helper_3dmath.h"

// Quaternion Tests
TEST(QuaternionTest, DefaultConstructor)
{
    Quaternion q;
    EXPECT_FLOAT_EQ(q.w, 1.0f);
    EXPECT_FLOAT_EQ(q.x, 0.0f);
    EXPECT_FLOAT_EQ(q.y, 0.0f);
    EXPECT_FLOAT_EQ(q.z, 0.0f);
}

TEST(QuaternionTest, ParameterizedConstructor)
{
    Quaternion q(0.5f, 0.5f, 0.5f, 0.5f);
    EXPECT_FLOAT_EQ(q.w, 0.5f);
    EXPECT_FLOAT_EQ(q.x, 0.5f);
    EXPECT_FLOAT_EQ(q.y, 0.5f);
    EXPECT_FLOAT_EQ(q.z, 0.5f);
}

TEST(QuaternionTest, GetProduct)
{
    Quaternion q1(1.0f, 0.0f, 1.0f, 0.0f);
    Quaternion q2(1.0f, 0.5f, 0.5f, 0.5f);

    // (Q1 * Q2).w = (w1w2 - x1x2 - y1y2 - z1z2) = (1*1 - 0*0.5 - 1*0.5 - 0*0.5) = 0.5
    // (Q1 * Q2).x = (w1x2 + x1w2 + y1z2 - z1y2) = (1*0.5 + 0*1 + 1*0.5 - 0*0.5) = 1.0
    // (Q1 * Q2).y = (w1y2 - x1z2 + y1w2 + z1x2) = (1*0.5 - 0*0.5 + 1*1 + 0*0.5) = 1.5
    // (Q1 * Q2).z = (w1z2 + x1y2 - y1x2 + z1w2) = (1*0.5 + 0*0.5 - 1*0.5 + 0*1) = 0.0

    Quaternion q3 = q1.getProduct(q2);
    EXPECT_FLOAT_EQ(q3.w, 0.5f);
    EXPECT_FLOAT_EQ(q3.x, 1.0f);
    EXPECT_FLOAT_EQ(q3.y, 1.5f);
    EXPECT_FLOAT_EQ(q3.z, 0.0f);
}

TEST(QuaternionTest, GetConjugate)
{
    Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion conj = q.getConjugate();
    EXPECT_FLOAT_EQ(conj.w, 1.0f);
    EXPECT_FLOAT_EQ(conj.x, -2.0f);
    EXPECT_FLOAT_EQ(conj.y, -3.0f);
    EXPECT_FLOAT_EQ(conj.z, -4.0f);
}

TEST(QuaternionTest, GetMagnitude)
{
    Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);
    EXPECT_FLOAT_EQ(q.getMagnitude(), 2.0f); // sqrt(1+1+1+1) = 2
}

TEST(QuaternionTest, Normalize)
{
    Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);
    q.normalize();
    EXPECT_FLOAT_EQ(q.getMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(q.w, 0.5f);
    EXPECT_FLOAT_EQ(q.x, 0.5f);
    EXPECT_FLOAT_EQ(q.y, 0.5f);
    EXPECT_FLOAT_EQ(q.z, 0.5f);
}

TEST(QuaternionTest, GetNormalized)
{
    Quaternion q(1.0f, 1.0f, 1.0f, 1.0f);
    Quaternion norm = q.getNormalized();
    EXPECT_FLOAT_EQ(norm.getMagnitude(), 1.0f);
    EXPECT_FLOAT_EQ(q.getMagnitude(), 2.0f); // Original should remain same
}
