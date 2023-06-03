/*
    💥Practical No: 5💥
 Construct an expression tree from the given prefix expression and traverse it using 
 postorder traversal (non recursive) and then delete the entire tree. 
 eg. +-abc/def.

*/

#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

// Expression Tree Node
struct ExpressionNode {
    char data;
    ExpressionNode* left;
    ExpressionNode* right;

    ExpressionNode(char value) : data(value), left(nullptr), right(nullptr) {}
};

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to construct the expression tree from prefix expression
ExpressionNode* constructExpressionTree(const char* prefixExpression) {
    stack<ExpressionNode*> stk;

    int length = strlen(prefixExpression);
    for (int i = length - 1; i >= 0; i--) {
        char symbol = prefixExpression[i];

        ExpressionNode* newNode = new ExpressionNode(symbol);
        if (isOperator(symbol)) {
            newNode->left = stk.top();
            stk.pop();
            newNode->right = stk.top();
            stk.pop();
        }
        stk.push(newNode);
    }

    return stk.top();
}

// Function to perform postorder traversal (non-recursive) on the expression tree
void postorderTraversal(ExpressionNode* root) {
    if (root == nullptr)
        return;

    stack<ExpressionNode*> stk;
    stack<char> result;
    stk.push(root);

    while (!stk.empty()) {
        ExpressionNode* current = stk.top();
        stk.pop();
        result.push(current->data);

        if (current->left)
            stk.push(current->left);
        if (current->right)
            stk.push(current->right);
    }

    // Print the result in postorder
    while (!result.empty()) {
        cout << result.top() << " ";
        result.pop();
    }
}

// Function to delete the expression tree
void deleteExpressionTree(ExpressionNode* root) {
    if (root == nullptr)
        return;

    deleteExpressionTree(root->left);
    deleteExpressionTree(root->right);
    delete root;
}

int main() {
    const char* prefixExpression = "+-abc/def";

    // Construct the expression tree
    ExpressionNode* root = constructExpressionTree(prefixExpression);

    // Perform postorder traversal on the expression tree
    cout << "Postorder Traversal: ";
    postorderTraversal(root);
    cout << endl;

    // Delete the expression tree
    deleteExpressionTree(root);

    return 0;
}
