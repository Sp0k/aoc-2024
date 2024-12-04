#include "heapsort.h"

/**
 * @brief Sorts the integer heap recursively
 *
 * This function sorts the integer heap using recursion by moving the biggest
 * new numbers up to the top of the heap.
 *
 * @param arr An unsorted integer array
 * @param arrSize The size of the unsorted array
 * @param index The index of the current integer
 */
void heapify(int *arr, int arrSize, int index) {
  // Set initial max index
  int max = index;

  // Get the index of the left and right children
  int lIdx = 2 * index + 1;
  int rIdx = 2 * index + 2;

  // Check if left index is valid and holds a bigger integer
  if (lIdx < arrSize && arr[lIdx] > arr[max])
    max = lIdx;

  // Check if right index is valid and holds a bigger integer
  if (rIdx < arrSize && arr[rIdx] > arr[max])
    max = rIdx;

  // Check if a new bigger integer was found
  if (max != index) {
    // Switch current integer with the new bigger one
    int tmp = arr[index];
    arr[index] = arr[max];
    arr[max] = tmp;

    // Keep sorting
    heapify(arr, arrSize, max);
  }
}

/**
 * @brief Sorts an integer array using the heap sort algorithm
 *
 * This function starts by creating a max heap and then it sorts the integer
 * array using the heap sort algorithm leaving a sorted array.
 *
 * @param arr An unsorted integer array
 * @param arrSize The size of the unsorted array
 */
void heapsort(int *arr, int arrSize) {
  // Build max heap
  for (int i = (arrSize / 2) - 1; i >= 0; i--) {
    heapify(arr, arrSize, i);
  }

  // Order the array in ascending order
  int tmp;
  for (int i = arrSize - 1; i > 0; i--) {
    // Swap next biggest integer with current smallest
    tmp = arr[0];
    arr[0] = arr[i];
    arr[i] = tmp;

    // Reorder the heap
    heapify(arr, i, 0);
  }
}
