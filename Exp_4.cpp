/*
    💥Practical No: 4💥
Beginning with an empty binary search tree, Construct binary search tree by inserting the
values in the order given. (Any Four Operation) After constructing a binary tree-
    1. Insert new node
    2. Find number of nodes in longest path from root
    3. Minimum data value found in the tree
    4. Change a tree so that the roles of the left and
    5. right pointers are swapped at every node
    6. Search a value.
*/

#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insertNode(TreeNode* root, int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else if (value < root->data) {
            root->left = insertNode(root->left, value);
        } else {
            root->right = insertNode(root->right, value);
        }
        return root;
    }

    int findHeight(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int leftHeight = findHeight(root->left);
        int rightHeight = findHeight(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

    TreeNode* findMinimum(TreeNode* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    TreeNode* swapChildren(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* temp = root->left;
        root->left = swapChildren(root->right);
        root->right = swapChildren(temp);
        return root;
    }

    bool searchValue(TreeNode* root, int value) {
        if (root == nullptr) {
            return false;
        }
        if (root->data == value) {
            return true;
        }
        if (value < root->data) {
            return searchValue(root->left, value);
        } else {
            return searchValue(root->right, value);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insertNode(root, value);
    }

    int longestPathFromRoot() {
        return findHeight(root) - 1;
    }

    int minimumValue() {
        TreeNode* minNode = findMinimum(root);
        return minNode->data;
    }

    void swapChildRoles() {
        root = swapChildren(root);
    }

    bool search(int value) {
        return searchValue(root, value);
    }
};

int main() {
    BinarySearchTree bst;

    // Construct the binary search tree
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    // Perform operations on the tree
    bst.insert(9);

    int longestPath = bst.longestPathFromRoot();
    cout << "Number of nodes in the longest path from root: " << longestPath << endl;

    int minValue = bst.minimumValue();
    cout << "Minimum value in the tree: " << minValue << endl;

    bst.swapChildRoles();

    bool found = bst.search(4);
    cout << "Searching for value 4: " << (found ? "Found" : "Not found") << endl;

    return 0;
}
