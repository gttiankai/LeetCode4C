//
// Created by Tiankai on 2018-12-15.
//

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

/**
 *  Given a binary tree, return the inorder traversal of its nodes' values.
 *  Example:
 *  Input: [1,null,2,3]
   1
    \
     2
    /
   3
   Output: [1,3,2]
   Follow up: Recursive solution is trivial, could you do it iteratively?
 *
 *
 * 中序遍历的所有的常规操作就是使用递归的方式对方法进行遍历
 * */


struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

int *MergerArray(int *left_array, int left_size,
                 int *right_array, int right_size,
                 int *total_size) {
    *total_size = left_size + right_size;
    int *new_array = calloc(*total_size, sizeof(int));
    if (NULL == new_array) {
        return NULL;
    }

    if (left_size != 0 && left_array != NULL) {
        memcpy(new_array, left_array, left_size * sizeof(int));
    }
    if (right_size != 0 && right_array != NULL) {
        memcpy(new_array + left_size, right_array, right_size* sizeof(int));
    }
    return new_array;
}

int *inorderTraversal(struct TreeNode *root, int *returnSize) {
    if (NULL == root) {
        return NULL;
    }
    int left_size = 0;
    int right_size = 0;
    int middle_size = 0;

    // 遍历左子树
    int *left_value = inorderTraversal(root->left, &left_size);
    // 遍历中间节点
    // 中间遍历，然后做需要的操作
    int *new_array = MergerArray(left_value, left_size, &(root->val), 1, &middle_size);
    // 遍历右子树
    int *right_value = inorderTraversal(root->right, &right_size);

    // 最后做需要的操作
    int *result = MergerArray(new_array, middle_size, right_value, right_size, returnSize);
    return result;
}

//int main(int argc, char* argv[]) {
//    struct TreeNode node1;
//    struct TreeNode node2;
//    struct TreeNode node3;
//    node1.val = 1;
//    node1.left = NULL;
//    node1.right = &node2;
//
//    node2.val = 2;
//    node2.left = &node3;
//    node2.right = NULL;
//
//    node3.val = 3;
//    node3.left = NULL;
//    node3.right = NULL;
//    int returnSize = 0;
//    int* result ;
//    result = inorderTraversal(&node1, &returnSize);
//    for (int i = 0; i < returnSize ; ++i) {
//        printf("%d ", result[i]);
//    }
//}

