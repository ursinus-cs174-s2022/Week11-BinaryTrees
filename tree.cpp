#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include "simplecanvas/simplecanvas.h"
using namespace std;

class TreeNode {
    public:
        int key;
        int x, y; // Relative coordinates of node
        TreeNode* left;
        TreeNode* right;
        TreeNode(int key) {
            this->key = key;
            left = NULL;
            right = NULL;
        }

        /**
         * @brief Recursively draw the tree, based on precomputed coordinates
         * 
         * @param canvas Canvas to which to draw the tree
         * @param xMax Maximum x coordinate, used to scale tree to canvas
         * @param maxDepth Maximum y coordinate, used to scale tree to canvas
         */
        void draw(SimpleCanvas& canvas, int xMax, int maxDepth) {
            int x1 = 10+x*(canvas.width-20)/xMax;
            int y1 = 10+y*(canvas.height-20)/maxDepth;
            stringstream stream;
            stream << key;
            canvas.fillCircle(x1, y1, 10, 0, 0, 0);
            canvas.drawString(stream.str(), x1+12, y1-10, "simplecanvas/");

            if (left != NULL) {
                int x2 = 10+left->x*(canvas.width-20)/xMax;
                int y2 = 10+left->y*(canvas.height-20)/maxDepth;
                canvas.drawLine(x1, y1, x2, y2, 0, 0, 0); 
                left->draw(canvas, xMax, maxDepth);
            }
            if (right != NULL) {
                int x2 = 10+right->x*(canvas.width-20)/xMax;
                int y2 = 10+right->y*(canvas.height-20)/maxDepth;
                canvas.drawLine(x1, y1, x2, y2, 0, 0, 0);   
                right->draw(canvas, xMax, maxDepth);
            }
        }

        /**
         * @brief Recursively do an inorder traversal, printing
         * out the keys of the nodes as it goes along
         */
        void inorder() {
            if (left != NULL) {
                left->inorder();
            }
            printf("%i ", key);
            if (right != NULL) {
                right->inorder();
            }
        }

        /**
         * @brief Recursively precompute the x and y coordinates
         * of the tree nodes
         * 
         * @param depth Depth of recursion
         * @param x Inorder x coordinate (by reference)
         * @param maxDepth Maximum depth seen so far (by reference)
         */
        void getCoords(int depth, int* x, int* maxDepth) {
            if (left != NULL) {
                left->getCoords(depth+1, x, maxDepth);
            }
            this->x = *x;
            (*x)++;
            this->y = depth;
            if (depth > *maxDepth) {
                *maxDepth = depth;
            }
            if (right != NULL) {
                right->getCoords(depth+1, x, maxDepth);
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
        
        /**
         * @brief Draw the tree and save it to a file
         * 
         * @param res Resolution of canvas to which to draw tree
         * @param filename Filename to which to save tree image
         */
        void draw(int res, string filename) {
            SimpleCanvas canvas(res, res);
            canvas.clearRect(255, 255, 255);
            int x = 0;
            int maxDepth = 0;
            if (root != NULL) {
                root->getCoords(0, &x, &maxDepth);
                root->draw(canvas, x, maxDepth);
            }
            canvas.write(filename);
        }

        /**
         * @brief Kick off an inorder traversal of the tree
         * 
         */
        void inorder() {
            if (root != NULL) {
                root->inorder();
            }
        }

        /**
         * @brief Add a node to the tree; iterative version
         * 
         * @param key key to which to add to tree
         */
        void add(int key) {
            if (root == NULL) {
                root = new TreeNode(key);
            }
            else {
                TreeNode* node = root;
                while (node != NULL && node->key != key) {
                    if (key < node->key) {
                        if (node->left != NULL) {
                            node = node->left;
                        }
                        else {
                            node->left = new TreeNode(key);
                            break;
                        }
                    }
                    else {
                        if (node->right != NULL) {
                            node = node->right;
                        }
                        else {
                            node->right = new TreeNode(key);
                            break;
                        }
                    }
                }
            }
        }
};


BinaryTree* makeTree() {
    BinaryTree* T = new BinaryTree();
    int x[20] = {65, 23, 56, 56, 95, 54, 85, 83,  0, 67, 83, 27, 52, 33, 79, 82, 37, 19, 94, 9};
    for (int i = 0; i < 20; i++) {
        T->add(x[i]);
    }
    return T;
}


int main() {
    BinaryTree* T = makeTree();
    T->inorder();
    T->draw(400, "tree.png");
    printf(".\n");
    delete T;
    return 0;
}