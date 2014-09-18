//
//  main.cpp
//  TCAP_BST
//
//  Created by Aoisorani on 9/16/14.
//  Copyright (c) 2014 Aozorany. All rights reserved.
//

#include <iostream>

using namespace std;

typedef struct _BinaryTreeNode {
    struct _BinaryTreeNode *left, *right, *parent;
    int key;
} BinaryTreeNode;

typedef enum {
    BinaryTreeNodeChildModeLeft,
    BinaryTreeNodeChildModeRight,
} BinaryTreeNodeChildMode;

BinaryTreeNode *createBinaryTreeNode(int _key, BinaryTreeNode *pParentNode, BinaryTreeNodeChildMode childMode);
void binaryTreeInOrderWalk(BinaryTreeNode *pTree);

BinaryTreeNode *createBinaryTreeNode(int _key, BinaryTreeNode *pParentNode, BinaryTreeNodeChildMode childMode) {
    BinaryTreeNode *pNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
    pNode->left = NULL; pNode->right = NULL; pNode->parent = pParentNode; pNode->key = _key;
    if (pParentNode) {
        if (childMode == BinaryTreeNodeChildModeLeft) {
            pParentNode->left = pNode;
        } else if (childMode == BinaryTreeNodeChildModeRight) {
            pParentNode->right = pNode;
        }
    }
    return pNode;
}

void binaryTreeInOrderWalk(BinaryTreeNode *pTree) {
    if (pTree) {
        binaryTreeInOrderWalk(pTree->left);
        cout << pTree->key << endl;
        binaryTreeInOrderWalk(pTree->right);
    }
}

int main(int argc, const char * argv[]) {
    BinaryTreeNode *pBinaryTree = createBinaryTreeNode(5, NULL, BinaryTreeNodeChildModeLeft);
    createBinaryTreeNode(3, pBinaryTree, BinaryTreeNodeChildModeLeft);
    createBinaryTreeNode(8, pBinaryTree, BinaryTreeNodeChildModeRight);
    binaryTreeInOrderWalk(pBinaryTree);
    return 0;
}
