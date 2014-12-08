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
void freeBinaryTree(BinaryTreeNode *pRoot);
void binaryTreeInOrderWalk(BinaryTreeNode *pTree);
BinaryTreeNode *binaryTreeSearch(BinaryTreeNode *pRoot, int key);
BinaryTreeNode *binaryTreeSearch_2(BinaryTreeNode *pRoot, int key);
BinaryTreeNode *binaryTreeMin(BinaryTreeNode *pRoot);
BinaryTreeNode *binaryTreeMinRecursive(BinaryTreeNode *pRoot);
BinaryTreeNode *binaryTreeMax(BinaryTreeNode *pRoot);
BinaryTreeNode *binaryTreeMaxRecursive(BinaryTreeNode *pRoot);
BinaryTreeNode *binaryTreeSuccessor(BinaryTreeNode *pTreeNode);
BinaryTreeNode *binaryTreePrecessor(BinaryTreeNode *pTreeNode);
void binaryTreeInsert(BinaryTreeNode **ppRoot, BinaryTreeNode *pNode);
void binaryTreeDelete(BinaryTreeNode **ppRoot, BinaryTreeNode *pNode);

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

void freeBinaryTree(BinaryTreeNode *pRoot) {
    if (pRoot) {
        freeBinaryTree(pRoot->left);
        freeBinaryTree(pRoot->right);
        free(pRoot);
    }
}

void binaryTreeInOrderWalk(BinaryTreeNode *pTree) {
    if (pTree) {
        binaryTreeInOrderWalk(pTree->left);
        cout << pTree->key << endl;
        binaryTreeInOrderWalk(pTree->right);
    }
}

BinaryTreeNode *binaryTreeSearch(BinaryTreeNode *pRoot, int key) {
    if (pRoot) {
        if (key == pRoot->key) {
            return pRoot;
        } else if (key > pRoot->key) {
            return binaryTreeSearch(pRoot->right, key);
        } else {
            return binaryTreeSearch(pRoot->left, key);
        }
    }
    return NULL;
}

BinaryTreeNode *binaryTreeSearch_2(BinaryTreeNode *pRoot, int key) {
    BinaryTreeNode *pTreeNode = pRoot;
    while (pTreeNode) {
        if (key == pTreeNode->key) {
            break;
        } else if (key > pTreeNode->key) {
            pTreeNode = pTreeNode->right;
        } else {
            pTreeNode = pTreeNode->left;
        }
    }
    return pTreeNode;
}

BinaryTreeNode *binaryTreeMin(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return NULL;
    }
    BinaryTreeNode *pMinKeyNode = pRoot;
    while (pMinKeyNode->left) {
        pMinKeyNode = pMinKeyNode->left;
    }
    return pMinKeyNode;
}

BinaryTreeNode *binaryTreeMinRecursive(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return NULL;
    }
    if (pRoot->left) {
        return binaryTreeMinRecursive(pRoot->left);
    }
    return pRoot;
}

BinaryTreeNode *binaryTreeMax(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return NULL;
    }
    BinaryTreeNode *pMaxKeyNode = pRoot;
    while (pMaxKeyNode->right) {
        pMaxKeyNode = pMaxKeyNode->right;
    }
    return pMaxKeyNode;
}

BinaryTreeNode *binaryTreeMaxRecursive(BinaryTreeNode *pRoot) {
    if (pRoot == NULL) {
        return NULL;
    }
    if (pRoot->right) {
        return binaryTreeMaxRecursive(pRoot->right);
    }
    return pRoot;
}

BinaryTreeNode *binaryTreeSuccessor(BinaryTreeNode *pTreeNode) {
    if (pTreeNode == NULL) {
        return NULL;
    }
    if (pTreeNode->right) {
        return binaryTreeMin(pTreeNode->right);
    }
    BinaryTreeNode *pCurrentNode = pTreeNode;
    while (pCurrentNode->parent && pCurrentNode->parent->right == pCurrentNode) {
        pCurrentNode = pCurrentNode->parent;
    }
    return pCurrentNode->parent;
}

BinaryTreeNode *binaryTreePrecessor(BinaryTreeNode *pTreeNode) {
    if (pTreeNode == NULL) {
        return NULL;
    }
    if (pTreeNode->left) {
        return binaryTreeMin(pTreeNode->left);
    }
    BinaryTreeNode *pCurrentNode = pTreeNode;
    if (pCurrentNode->parent && pCurrentNode->parent->left == pCurrentNode) {
        pCurrentNode = pCurrentNode->parent;
    }
    return pCurrentNode->parent;
}

void binaryTreeInsert(BinaryTreeNode **ppRoot, BinaryTreeNode *pNode) {
    if (ppRoot == NULL || pNode == NULL) {
        return;
    }
    //Find a proper slot (stored in y)
    BinaryTreeNode *y = NULL;
    BinaryTreeNode *x = *ppRoot;
    while (x) {
        y = x;
        x = ((pNode->key < x->key)? x->left: x->right);
    }
    //let y be parent of pNode, and pNode be left or right child to y
    pNode->parent = y;
    if (y == NULL) {
        *ppRoot = pNode;
    } else {
        (pNode->key < y->key)? (y->left = pNode): (y->right = pNode);
    }
}

void binaryTreeDelete(BinaryTreeNode **ppRoot, BinaryTreeNode *pNode) {
    if (pNode->left == NULL && pNode->right == NULL) {
        //If pNode has no left or right child, delete it and change parent node state
        if (pNode->parent) {
            if (pNode->parent->left == pNode) {
                pNode->parent->left = NULL;
            } else {
                pNode->parent->right = NULL;
            }
        } else {
            //If pNode has no parent, delete pNode will be an empty tree
            *ppRoot = NULL;
        }
    } else if ((pNode->left && pNode->right == NULL) || (pNode->left == NULL && pNode->right)) {
        //If pNode has only one left or right child, make a direct link to it's parentNode to it's child
        
    } else {
        //If pNode has both left or right child, find it's seceedor and move it to current node
    }
}

#pragma mark -
int main(int argc, const char * argv[]) {
//    BinaryTreeNode *pBinaryTree = createBinaryTreeNode(5, NULL, BinaryTreeNodeChildModeLeft);
//    BinaryTreeNode *pTreeNode1 = createBinaryTreeNode(3, pBinaryTree, BinaryTreeNodeChildModeLeft);
//    BinaryTreeNode *pTreeNode2 = createBinaryTreeNode(8, pBinaryTree, BinaryTreeNodeChildModeRight);
//    createBinaryTreeNode(2, pTreeNode1, BinaryTreeNodeChildModeLeft);
//    createBinaryTreeNode(4, pTreeNode1, BinaryTreeNodeChildModeRight);
//    createBinaryTreeNode(7, pTreeNode2, BinaryTreeNodeChildModeLeft);
//    createBinaryTreeNode(9, pTreeNode2, BinaryTreeNodeChildModeRight);
    BinaryTreeNode *pBinaryTree = NULL;
    BinaryTreeNode *insertNode = createBinaryTreeNode(6, NULL, BinaryTreeNodeChildModeLeft);
    binaryTreeInsert(&pBinaryTree, insertNode);
    freeBinaryTree(pBinaryTree);
    return 0;
}
