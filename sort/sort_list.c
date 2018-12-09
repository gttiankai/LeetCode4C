//
// Created by Tiankai on 2018-12-08.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

#include <stddef.h>
#include <printf.h>

/**
 * 快速排序
 *
 * */

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int partition(int *array, int low, int hight) {
    int pivot = array[hight];
    int i = (low - 1);
    for (int j = low; j < hight - 1; ++j) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[hight]);
    return (i + 1);
}


void quickSortMy(int *array, int low, int hight) {
    // 这个地方一定要保证 low >= hight,这样做是为了保证只有一个元素的时候,不会出现栈溢出的情况
    if (low >= hight) {
        return;
    }
    int pivot = low;
    int i = low+1;
    int j = hight;
    while (i < j) {
        // 一定要保证 i < j
        while (array[j] > array[pivot] && i < j) {
            j--;
        }
        while (array[i] < array[pivot] && i < j) {
            i++;
        }
        swap(&array[i], &array[j]);
    }
    // 此时 i equals j
//    if (array[pivot] >= array[i]){
//        swap(&array[pivot], &array[i]);
//    } else {
//        swap(&array[pivot], &array[i-1]);
//    }
    swap(&array[pivot], &array[i]);
    quickSortMy(array, low, i-1);
    quickSortMy(array, i+1, hight);

}


void quickSort(int *array, int low, int hight) {
    if (low > hight) {
        return;
    }
    int pi = partition(array, low, hight);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, hight);

}

struct ListNode *sortList(struct ListNode *head) {
    return NULL;
}


//int main(int argc, char* argv[]) {
//
////    int array[] = {6};
////    quickSortMy(array, 0, 0);
//    int array[] = {6, 1 , 2, 7, 9, 11, 4, 5, 10, 8};
//    quickSortMy(array, 0, 9);
//
//    for (int i = 0; i < 10 ; ++i) {
//        printf("%d ", array[i]);
//    }
//    return 0;
//}


