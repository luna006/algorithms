#include <cstring>

#include <sort.h>

void mergeSort(int* array, std::size_t n) {
    if (n == 1) {
        return;
    }
    std::size_t mid = n / 2;
    std::size_t ln = mid;
    std::size_t rn = (n % 2) ? mid + 1 : mid;

    mergeSort(&array[0], ln);
    mergeSort(&array[mid], rn);

    int* mergeArray = new int[n];
    int *indexMergeArray = mergeArray;
    std::size_t indexL = 0;
    std::size_t indexR = mid;
    while (indexL < ln && indexR < mid + rn) {
        if (array[indexL] > array[indexR]) {
            *indexMergeArray = array[indexR++];
            ++indexMergeArray;
        } else {
            *indexMergeArray = array[indexL++];
            ++indexMergeArray;
        }
    }
    if (indexL == ln)
    {
        std::memcpy(indexMergeArray, &array[indexR], sizeof(int) * (mid + rn - indexR));
    }
    if (indexR == mid + rn)
    {
        std::memcpy(indexMergeArray, &array[indexL], sizeof(int) * (ln - indexL));
    }

    std::memcpy(array, mergeArray, sizeof(int) * n);
    delete[] mergeArray;
}