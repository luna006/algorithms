#include <sort.h>
#include <gtest/gtest.h>

TEST(MergeSort, SortingTenElements) {
    const int N = 10;
    int array[N] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int expectArray[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    mergeSort(array, N);

    auto endExpectIt = std::end(expectArray);
    for (auto testIt = std::begin(array), expectIt = std::begin(expectArray); expectIt != endExpectIt; ++testIt, ++expectIt) {
        EXPECT_EQ(*testIt, *expectIt);
    }
}

