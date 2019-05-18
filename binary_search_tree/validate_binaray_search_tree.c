//
// Created by Tiankai on 2018-12-13.
//

#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * 递归的办法判断：
 * 1. 首先判断当前节点是否是二叉查找树。
 * 2. 如果当前节点是二叉查找树，则对他的左子树以及右子树分别进行二叉查找树的判断
 * 3. 如果在递归结束之后，都是二叉查找树，则整棵树书二叉查找树。否则这棵树不是二叉查找树。
 *
 * 以上的做法是错误的，这种算法没有充分考虑到二叉查找树的定义。二叉查找树要对根节点的值要大于所有左子树的值
 * 所以使用递归的方式是有问题的，这种情况没有办法保证.
 * 所以比较好的做法是采取从下到上的方式进行判断
 *
 * **/
bool isValidBSTFailed(struct TreeNode *root) {
    //
    if (NULL == root) {
        // ?
        return true;
    }
    if (NULL != root->left &&
        isValidBSTFailed(root->left)) {
    }
    bool right_is_valid = true;
    if (NULL != root->right) {
        right_is_valid = isValidBSTFailed(root->right);
    }
    return false;
}

bool validate(struct TreeNode *node, struct TreeNode *pre) {
    if (node == NULL) return true;
    if (!validate(node->left, pre)) {
        return false;
    }
    // 按照中序遍历整个二叉树，如果遍历出来的节点是按照升序排列的,
    // 则整个二叉树是二叉查找树,否则就不是二叉查找树.
    // 一开始的思路是最后生成一个数组,然后最后判断数组,其实不用这么麻烦,
    // 在遍历的的时候,设置一个前序节点,比较当前节点以及前驱节点的大小就可以.
    if (pre != NULL && pre->val >= node->val) {
        return false;
    }
    pre = node;
    if (validate(node->right, pre)) {
        return true;
    } else {
        return false;
    }
}

bool isValidBST(struct TreeNode *root) {
    if (NULL == root) {
        // ?
        return true;
    }
    struct TreeNode *pre = NULL;
    return validate(root, pre);
}

bool isValidBSTInOrder(struct TreeNode *root) {
    if (NULL == root) {
        return true;
    }
    // 中序遍历二叉树

    return false;
}

bool inOrderTraverse(struct TreeNode* node , struct TreeNode* preNode) {

    return false;
}

