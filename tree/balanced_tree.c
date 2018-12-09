//
// Created by Tiankai on 2018/12/7.
//

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX(x, y) ( x>y? x:y)


typedef struct TreeNode{
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

int depth(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    return MAX(depth(root->left), depth(root->right)) + 1;
}

bool isBalanced(TreeNode* root) {
    if (root == NULL){
        return true;
    }
    bool left_balanced = isBalanced(root->left);
    if (left_balanced == false) {
        return false;
    }

    bool right_balanced = isBalanced(root->right);
    if (right_balanced == false) {
        return false;
    }

    int left_count = depth(root->left);
    int right_count = depth(root->right);

    if (abs(left_count - right_count) > 1){
        return false;
    } else {
        return true;
    }
}
