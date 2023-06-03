/*
    💥Practical No: 9 💥
Read the marks obtained by students of second year in an online Examination of 
particular subject. Find out maximum and minimum marks obtained in that subject. 
Use heap data structure. Analyze the algorithm
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to build a max heap
void buildMaxHeap(vector<int>& marks) {
    int n = marks.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;

        // Find the largest among parent, left child, and right child
        int largest = parent;
        if (leftChild < n && marks[leftChild] > marks[largest]) {
            largest = leftChild;
        }
        if (rightChild < n && marks[rightChild] > marks[largest]) {
            largest = rightChild;
        }

        // Swap the largest element with the parent if necessary
        if (largest != parent) {
            swap(marks[parent], marks[largest]);

            // Recursively build the max heap for the affected subtree
            buildMaxHeap(marks);
        }
    }
}

// Function to build a min heap
void buildMinHeap(vector<int>& marks) {
    int n = marks.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i;
        int leftChild = 2 * parent + 1;
        int rightChild = 2 * parent + 2;

        // Find the smallest among parent, left child, and right child
        int smallest = parent;
        if (leftChild < n && marks[leftChild] < marks[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < n && marks[rightChild] < marks[smallest]) {
            smallest = rightChild;
        }

        // Swap the smallest element with the parent if necessary
        if (smallest != parent) {
            swap(marks[parent], marks[smallest]);

            // Recursively build the min heap for the affected subtree
            buildMinHeap(marks);
        }
    }
}

// Function to find the maximum and minimum marks
void findMaxMinMarks(const vector<int>& marks) {
    vector<int> maxHeap = marks;
    vector<int> minHeap = marks;

    // Build max heap and min heap
    buildMaxHeap(maxHeap);
    buildMinHeap(minHeap);

    int maxMark = maxHeap[0];
    int minMark = minHeap[0];

    cout << "Maximum mark: " << maxMark << endl;
    cout << "Minimum mark: " << minMark << endl;
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    vector<int> marks(n);
    cout << "Enter the marks obtained by students: ";
    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }

    findMaxMinMarks(marks);

    return 0;
}
