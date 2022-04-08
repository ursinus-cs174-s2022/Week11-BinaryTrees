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
};

BinaryTree* makeTree() {
    BinaryTree* T = new BinaryTree();
    T->root = new TreeNode(9);
    T->root->left = new TreeNode(4);
    // TODO: Finish this

    return T;
}



void traverse(TreeNode* N) {
    if (N != NULL) {
        traverse(N->left);
        printf("%i ", N->value);
        traverse(N->right);
    }
}

int main() {
    BinaryTree* T = makeTree();
    traverse(T->root);
    T->draw(400);
    printf(".\n");
    delete T;
    return 0;
}