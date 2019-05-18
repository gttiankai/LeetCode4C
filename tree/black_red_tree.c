//
// Created by Tiankai on 2018-12-15.
//

enum Color {
    RED = 0,
    BLACK = 1
};

struct RBNode {
    int value;
    enum Color color;
    struct RBNode* left;
    struct RBNode* right;
    struct PBNode* parent;
};



