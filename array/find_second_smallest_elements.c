//
// Created by Tiankai on 2018-12-08.
//
/**
 * 解决这个问题问题有三种方式:
 * 1. 首先将数组升序排列,然后将找到第二个元素.这个方式我没有想到. 时间复杂度O(nlogn)
 * 2. 搜索数组两次,第一次找到数组中最小的那个,并将该元素赋值成,最大的元素, INT_MAX
 *    第二次搜索的时候,再进行新的查找,查找最小的元素.时间复杂度:O(n),两边遍历.
 * 3. 通过一次遍历找到最小的和次小的元素,这种方式最好了.
 *
 * */


#include <stdio.h>

#define INT_MAX 0x7fffffff // 由于是有符号的数,所以必须是这个

int findFirstSmallestElements(int* array, int size) {
    return 0;
}



int findSecondSmallestElements(int* array, int size) {
    if (size < 2) {
        printf("the array size must be more then 2");
        return 0;
    }
    int firstSmallest = INT_MAX;
    int secondSmallest = INT_MAX;

    for (int i = 0; i < size; ++i) {
        if (array[i] < firstSmallest) {
            // 这一步中有个关键的步骤,就是要对 secondSmallest 进行赋值
            secondSmallest = firstSmallest;
            firstSmallest = array[i];
        } else if (array[i] < secondSmallest){
            secondSmallest = array[i];
        }
    }

    return secondSmallest;

}




//int main(int argc, char* argv[]) {
//    //int array[6] = {12, 13, 1, 10, 34, 2};
//    int array[6] = {12, 13, 1, 10, 34, 2};
//
//    printf("the second smallest elements: %d", findSecondSmallestElements(array, 6));
//    return 0;
//}