#include <cstddef>
#include <vector>
#include "sort.h"
#include "gtest/gtest.h"


class SortTest : public ::testing::Test {
protected:
    static const std::size_t N = 10;
    int randomArray[N] = {13, 19, 9, 5, 12, 8, 7, 2, 6, 21};
    int reverseArray[N] = {21, 19, 13, 12, 9, 8, 7, 6, 5, 2};
    int sortedArray[N] = {2, 5, 6, 7, 8, 9, 12, 13, 19, 21};
    int expectedArray[N] = {2, 5, 6, 7, 8, 9, 12, 13, 19, 21};


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

TEST_F(SortTest, TestMergeSortWithRandomArray) {
    mergeSort(randomArray, N);

    compareArrays(std::vector<int>(std::begin(randomArray), std::end(randomArray)),
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

TEST_F(SortTest, TestQuickSortWithRandomArray) {
    quickSort(randomArray, 0, N);

    compareArrays(std::vector<int>(std::begin(randomArray), std::end(randomArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

/*TEST_F(SortTest, TestQuickSortWithAlreadySortedArray) {
    quickSort(sortedArray, 0, N - 1);

    compareArrays(std::vector<int>(std::begin(sortedArray), std::end(sortedArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}

TEST_F(SortTest, TestQuickSortWithReverseArray) {
    quickSort(reverseArray, 0, N - 1);

    compareArrays(std::vector<int>(std::begin(reverseArray), std::end(reverseArray)),
                  std::vector<int>(std::begin(expectedArray), std::end(expectedArray)));
}*/

