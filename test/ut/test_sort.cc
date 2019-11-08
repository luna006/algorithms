#include <cstddef>
#include <vector>
#include <gtest/gtest.h>
#include <sort.h>

class SortTest : public ::testing::Test {
protected:
    static const std::size_t N = 10;
    int reverseArray[N] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int sortedArray[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int expectedArray[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    template<typename T> void compareArrays(const std::vector<T>& checked, const std::vector<T>& expected) {
        auto endExpectIt = expected.cend();
        for (auto testIt = checked.cbegin(), expectIt = expected.cbegin(); expectIt != endExpectIt; ++testIt, ++expectIt) {
            EXPECT_EQ(*testIt, *expectIt);
        }
    }
};

TEST_F(SortTest, TestMergeSortWithReverseArray) {
    mergeSort(reverseArray, N);

    compareArrays(std::vector<int>(std::begin(reverseArray), std::end(reverseArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

TEST_F(SortTest, TestMergeSortWithAlreadySortedArray) {
    mergeSort(sortedArray, N);

    compareArrays(std::vector<int>(std::begin(sortedArray), std::end(sortedArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

TEST_F(SortTest, TestInsertSortWithReverseArray) {
    insertSort(reverseArray, N);

    compareArrays(std::vector<int>(std::begin(reverseArray), std::end(reverseArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

TEST_F(SortTest, TestInsertSortWithAlreadySortedArray) {
    insertSort(sortedArray, N);

    compareArrays(std::vector<int>(std::begin(sortedArray), std::end(sortedArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

TEST_F(SortTest, TEstSelectSortWithReverseArray) {
    selectSort(reverseArray, N);

    compareArrays(std::vector<int>(std::begin(reverseArray), std::end(reverseArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

TEST_F(SortTest, TestSelectSortWithAlreadySortedArray) {
    selectSort(sortedArray, N);

    compareArrays(std::vector<int>(std::begin(sortedArray), std::end(sortedArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

