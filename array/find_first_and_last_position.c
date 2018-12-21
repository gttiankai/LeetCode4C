//
// Created by tiankai on 18-12-21.
//
#include <stdlib.h>

/**
 *
 * 写这个代码是为了这个证明意见事情,使用相同的编程思想, C语言就可以达到"faster then 100%"
 * 使用Java语言就有问题
 * */
int* binararySearch(int* nums, int numsSize, int target, int left, int right) {
    int* result = (int*)calloc(2, sizeof(int));
    int firstPosition = -1;
    int lastPosition = -1;
    if (left > right) {
        result[0] = firstPosition;
        result[1] = lastPosition;
        return result;
    }
    int mid = (left + right) /2;
    if (nums[mid] == target) {
        int i = mid;
        int j = mid;
        while (i > -1) {
            if (nums[i] == target) {
                firstPosition = i;
                i--;
            } else{
                break;
            }
        }
        while (j < numsSize) {
            if (nums[j] == target) {
                lastPosition = j;
                j++;
            } else {
                break;
            }
        }

    } else if (nums[mid] > target) {
        return binararySearch(nums, numsSize, target, left, mid-1);
    } else {
        return binararySearch(nums, numsSize, target, mid+1, right);
    }

    result[0] = firstPosition;
    result[1] = lastPosition;
    return result;
}


int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)calloc(2, sizeof(int));
    if (NULL == result) return NULL;
    result[0] = -1;
    result[1] = -1;
    *returnSize = 2;
    if (nums == NULL || numsSize == 0) {
        return result;
    }
    return binararySearch(nums, numsSize, target, 0, numsSize-1);
}

