//
// Created by lucas on 23/01/23.
//
#include "../googletest/gtest.h"

class BitsetTest : public testing::Test {
protected:
    void SetUp() override {

    }

    void TearDown() override {

    }


};

// Demonstrate some basic assertions.
TEST(BitsetTest, HelloTest) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(BitsetTest, CreateBitset) {

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}