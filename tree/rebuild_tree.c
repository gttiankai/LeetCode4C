//
// Created by Tiankai on 2018-12-08.
//
#include <stdlib.h>

typedef struct  TreeNode {
    struct Node *left;
    struct Node *right;
    int value;
} TreeNode;

/**
 *  我写的这个代码,终于通过了leetcode 的测试.
 * */
void rebuild(int *pPreOrder, int *pInOrder, int nTreeLen, TreeNode **pRoot) {
    //check pPreOder and pInOrder
    if (NULL == pPreOrder || NULL == pInOrder) {
        return;
    }
    // 获取前序遍历的第一个节点
    TreeNode* node = (TreeNode*)calloc(1, sizeof(TreeNode));
    node->value = *pPreOrder;
    node->left = NULL;
    node->right = NULL;
    // 当前为空的话,创建节点
    if (*pRoot == NULL) {
        *pRoot = node;
    }
    // 这个是最重要的退出条件,如果没有这个条件,这个递归调用就会出问题.
    if (nTreeLen == 1) {
        return;
    }

    //计算左子树的长度
    int* pLeftEnd = pInOrder;
    int nLeftLen = 0;
    while (*pPreOrder != *pLeftEnd) {

        if (nLeftLen > nTreeLen) {
            return;
        }
        nLeftLen++;
        pLeftEnd++;
    }
    // 右子树的长度
    int nRightLen = nTreeLen - nLeftLen -1;
    // 重建左子树
    if (nLeftLen > 0){
        rebuild(pPreOrder+1, pInOrder, nLeftLen, &((*pRoot)->left));
    }

    if (nRightLen > 0) {
        rebuild(pPreOrder + nLeftLen +1, pInOrder + nLeftLen +1,
                nRightLen, &((*pRoot)->right));
    }


}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {

    if (preorderSize == 0 || inorderSize == 0) {
        return NULL;
    }
    TreeNode *pRoot = NULL;
    rebuild(preorder, inorder, preorderSize, &pRoot);
    return pRoot;
}

int main(int argc, char *argv[]) {
    int preOrder[6] = {3,9,20,15,7};
    int inOrder[6] = {9,3,15,20,7};
    TreeNode *pRoot = NULL;
    buildTree(preOrder, 6, inOrder, 6);
    return 0;
}

