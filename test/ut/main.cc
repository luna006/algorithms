#include <gtest/gtest.h>
#include <gmock/gmock.h>

/*int factorial(int n);

TEST(FactorialTest, HandlesZeroInput) {
    ASSERT_EQ(factorial(0), 1);
}

TEST(FactorialTest, HandlesPositiveInput) {
    ASSERT_EQ(factorial(1), 1);
    ASSERT_EQ(factorial(2), 2);
    ASSERT_EQ(factorial(3), 6);
    ASSERT_EQ(factorial(8), 40320);
}*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    int result = 1;
    while (n > 1) {
        result *= n--;
    }
    return result;
}*/