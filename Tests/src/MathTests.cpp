#include <gtest/gtest.h>

#include <GameEngine.h>

TEST(Vector, EmptyConstructor)
{
    Math::Vector vec = Math::Vector();

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.Length(), 0.0f);

    vec.Normalize();

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.Length(), 0.0f);
}

TEST(Vector, ScalarConstructor)
{
    float expectedValue = 3.111f;
    Math::Vector vec = Math::Vector(expectedValue);

    EXPECT_EQ(vec.x, expectedValue);
    EXPECT_EQ(vec.Length(), expectedValue);

    vec.Normalize();

    EXPECT_EQ(vec.x, 1);
    EXPECT_EQ(vec.Length(), 1);
}

TEST(Vector2, EmptyConstructor)
{
    Math::Vector2 vec = Math::Vector2();

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.y, 0.0f);
    EXPECT_EQ(vec.Length(), 0.0f);

    vec.Normalize();

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.y, 0.0f);
    EXPECT_EQ(vec.Length(), 0.0f);
}

TEST(Vector2, ScalarConstructor)
{
    float expectedValue = 3.0f;
    Math::Vector2 vec = Math::Vector2(expectedValue);

    EXPECT_EQ(vec.x, expectedValue);
    EXPECT_EQ(vec.y, expectedValue);
    EXPECT_EQ(vec.Length(), 4.2426405f);

    vec.Normalize();

    EXPECT_EQ(vec.x, 0.707106829f);
    EXPECT_EQ(vec.y, 0.707106829f);
    EXPECT_EQ(vec.Length(), 1);
}

TEST(Vector2, ValuesConstructor)
{
    float expectedX = 4.0f;
    float expectedY = 3.0f;
    Math::Vector2 vec = Math::Vector2(expectedX, expectedY);

    EXPECT_EQ(vec.x, expectedX);
    EXPECT_EQ(vec.y, expectedY);
    EXPECT_EQ(vec.Length(), 5.0f);

    vec.Normalize();

    EXPECT_EQ(vec.x, 0.8f);
    EXPECT_EQ(vec.y, 0.6f);
    EXPECT_EQ(vec.Length(), 1);
}