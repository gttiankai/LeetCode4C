//
// Created by Tiankai on 2019-06-12.
//
#include "tree.h"
#include <stddef.h>
#include <printf.h>

/**
 * 彻底失败了，不知道该怎么处理了
 *
 * */
int smallest(struct TreeNode *root) {
    int ans = 0;
    if (root->left == NULL) {
        ans = root->val;
        if (root->right != NULL) {
            root->val = root->right->val;
            root->right = NULL;
        }
        return ans;
    }
    struct TreeNode *pointer = root;
    while (pointer->left->left != NULL) {
        pointer = pointer->left;
    }
    ans = pointer->left->val;
    if (pointer->left->right != NULL) {
        pointer->left->val = pointer->left->right->val;
        pointer->left->right = NULL;
    } else{
        pointer->left = NULL;
    }
    return ans;
}

int kthSmallest(struct TreeNode *root, int k) {
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans = smallest(root);
    }
    return ans;
}

int main(int argc, char* argv[]) {

    struct TreeNode node1;
    struct TreeNode node2;
    struct TreeNode node3;
    struct TreeNode node4;
    node1.val = 1;
    node2.val = 2;
    node3.val = 3;
    node4.val = 4;

    node3.left = &node1;
    node3.right = &node4;

    node1.left = NULL;
    node1.right = &node2;

    node2.left = NULL;
    node2.right = NULL;

    node4.left = NULL;
    node4.right = NULL;

    int ans = kthSmallest(&node3, 2);
    printf("the ans %d", ans);
}




