/*
    💥Practical No: 03💥
 A book consists of chapters, chapters consist of sections and sections 
 consist of subsections. Construct a tree and print the nodes. 
 Find the time and space requirements of your method..
 Time complexity: O(n)
 Space complexity: O(n)
*/

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    string data;
    vector<TreeNode*> children;

    TreeNode(const string& value) : data(value) {}

    void addChild(TreeNode* child) {
        children.push_back(child);
    }
};

void printTree(TreeNode* node, int level = 0) {
    cout << string(level, ' ') << node->data << endl;
    for (TreeNode* child : node->children) {
        printTree(child, level + 1);
    }
}

int main() {
    TreeNode* book = new TreeNode("Book");

    // Add chapters
    TreeNode* chapter1 = new TreeNode("Chapter 1");
    TreeNode* chapter2 = new TreeNode("Chapter 2");
    book->addChild(chapter1);
    book->addChild(chapter2);

    // Add sections to Chapter 1
    TreeNode* section1_1 = new TreeNode("Section 1.1");
    TreeNode* section1_2 = new TreeNode("Section 1.2");
    chapter1->addChild(section1_1);
    chapter1->addChild(section1_2);

    // Add subsections to Section 1.1
    TreeNode* subsection1_1_1 = new TreeNode("Subsection 1.1.1");
    TreeNode* subsection1_1_2 = new TreeNode("Subsection 1.1.2");
    section1_1->addChild(subsection1_1_1);
    section1_1->addChild(subsection1_1_2);

    // Print the tree
    printTree(book);

    // Cleanup - deallocate memory
    delete subsection1_1_1;
    delete subsection1_1_2;
    delete section1_1;
    delete section1_2;
    delete chapter1;
    delete chapter2;
    delete book;

    return 0;
}
