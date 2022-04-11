#include <iostream>
#include <string>
#include <stdio.h>
#include "simplecanvas/simplecanvas.h"
using namespace std;

class TreeNode {
    public:
        int value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int value) {
            this->value = value;
            left = NULL;
            right = NULL;
        }
        void draw(int res) {

        }
        void inorder() {
            if (left != NULL) {
                left->inorder();
            }
            printf("%i ", value);
            if (right != NULL) {
                right->inorder();
            }
        }
};

class BinaryTree {
    private:
        void cleanup(TreeNode* N) {
            if (N != NULL) {
                cleanup(N->left);
                cleanup(N->right);
                delete N;
            }
        }
    public:
        TreeNode* root;
        BinaryTree() {
            root = NULL;
        }
        ~BinaryTree() {
            cleanup(root);
        }
        void draw(int res) {
            SimpleCanvas canvas(res, res);
            canvas.clearRect(255, 255, 255);
            canvas.drawString("A Tree!", 10, 10, "simplecanvas/");
            root->draw(res);
            canvas.write("tree.png");
        }
        void inorder() {
            if (root != NULL) {
                root->inorder();
            }
        }
        void add(int value) {
            if (root == NULL) {
                root = new TreeNode(value);
            }
            else {
                TreeNode* node = root;
                while (node != NULL && node->value != value) {
                    if (value < node->value) {
                        if (node->left != NULL) {
                            node = node->left;
                        }
                        else {
                            node->left = new TreeNode(value);
                            break;
                        }
                    }
                    else {
                        if (node->right != NULL) {
                            node = node->right;
                        }
                        else {
                            node->right = new TreeNode(value);
                            break;
                        }
                    }
                }
            }
        }
};

BinaryTree* makeTree() {
    BinaryTree* T = new BinaryTree();
    T->root = new TreeNode(9);
    T->root->left = new TreeNode(4);
    // TODO: Finish this
    T->root->right = new TreeNode(15);

    T->root->left->left = new TreeNode(1);
    T->root->left->right = new TreeNode(6);

    T->root->right->left = new TreeNode(12);
    T->root->right->right = new TreeNode(20);

    T->root->right->right->left = new TreeNode(18);
    T->root->right->right->right = new TreeNode(25);
    return T;
}


BinaryTree* makeTree2() {
    BinaryTree* T = new BinaryTree();
    int x[20] = {65, 23, 56, 56, 95, 54, 85, 83,  0, 67, 83, 27, 52, 33, 79, 82, 37, 19, 94, 9};
    for (int i = 0; i < 20; i++) {
        T->add(x[i]);
    }
    return T;
}


int main() {
    BinaryTree* T = makeTree2();
    T->inorder();
    T->draw(400);
    printf(".\n");
    delete T;
    return 0;
}