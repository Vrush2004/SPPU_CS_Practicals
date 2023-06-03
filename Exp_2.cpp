/*  💥Practical no: 02💥
Implement all the functions of a dictionary (ADT) using hashing 
and handle collisions using chaining with/without replacement. 
Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be comparable, 
Keys must be unique Standard Operations: 
Insert(key. value). Find(key), Delete(key)
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Node structure for chaining
struct Node {
    string key;
    string value;
    Node* next;
    /*
    Node* is a pointer to a Node object. In this code, it is used to create a dynamic array of pointers 
    to Node objects. This is used to implement the hash table data structure where each index of the 
    array holds a linked list of Node objects.
    */
};

class Dictionary {
private:
    vector<Node*> table;  // vector of Node pointers to store the hash table
    /* 👆👆
    This line declares a private member variable table of type vector<Node*>, 
    which is a dynamic array that can hold pointers to Node structures. 
    In this implementation, it is used to store the buckets of the hash table, where each bucket 
    is a linked list of nodes that have the same hash value.
    */ 
    
    int capacity;         // maximum capacity of the hash table -> here capacity is 10
    int size;             // number of key-value pairs in the hash table

    // Hash function to compute the index for a given key
    int hash(string key) {
        int hashVal = 0;
        for (int i = 0; i < key.length(); i++) {
            hashVal += key[i];  // 👉 see the documentation 👈
        }
        return hashVal % capacity;
    }
 
    // ***** Helper function to find node given a key  ****
    /*
        The -> operator is used to access a member of a pointer. 
        In this case, curr->key is used to access the key member of the curr pointer. 
        This is equivalent to (*curr).key, but is more concise and easier to read. 
        Similarly, curr->next is used to access the next member of the curr pointer, 
        which is a pointer to the next node in the linked list.
    */

    Node* findNode(string key) {
        int index = hash(key);
        Node* curr = table[index];
        while (curr != NULL) {
            if (curr->key == key) {
                return curr;
            }
            curr = curr->next;
        }
        return NULL;
    }

public:
   // Constructor to initialize the hash table
    Dictionary(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        table.resize(capacity);
        for (int i = 0; i < capacity; i++) {
            table[i] = NULL;
        }
    }

     // Destructor to deallocate memory for the hash table
    ~Dictionary() {
        for (int i = 0; i < capacity; i++) {
            Node* curr = table[i];
            while (curr != NULL) {
                Node* temp = curr->next;
                delete curr;
                curr = temp;
            }
        }
    }

     // Method to insert a key-value pair into the hash table
    void insert(string key, string value) {
       // Check if the key already exists in the hash table
        if (findNode(key) != NULL) {
            cout << "Key already exists." << endl;
            return;
        }

         // Compute the index for the key using the hash function
        int index = hash(key);

    // it creates a new Node with the given key and value, and sets its next pointer to NULL.
        Node* newNode = new Node;
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;

        // Handle collision using chaining with replacement
        if (table[index] == NULL) { 
            // if the there is no element at 'index' location then add the 'newNode' in the table
            table[index] = newNode;
        }
        // else handle the collision
         /*
             if there is already an element present, a collision has occurred, and chaining with replacement is used. 
             In this method, the new node is added to the end of the linked list 
             starting at the index in the hash table.
        */
        else { 
       
            Node* curr = table[index];
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newNode;
            /*
            this loop finds the end of the linked list at the given index and appends the new node 
            to the end of the list to handle collisions.
            */
        }

        // the size of the hash table is incremented.
        size++;
    }

    // Find the value given a key
    string find(string key) {
        Node* node = findNode(key);
        if (node == NULL) {
            return "Key not found.";
        }
        else {
            return node->value;
        }
    }

    // Delete a key-value pair given a key
    void remove(string key) {
        // Check if key exists
        Node* node = findNode(key);
        if (node == NULL) {
            cout << "Key not found." << endl;
            return;
        }

        // Compute hash index and find previous node
        int index = hash(key);
        Node* curr = table[index];
        Node* prev = NULL;
        while (curr != NULL && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        // Remove node from linked list
        if (prev == NULL) {
            table[index] = curr->next;
        }
        else {
            prev->next = curr->next;
        }
        delete node;

        size--;
    }

    // Print all key-value pairs in the dictionary
    void print() {
        for (int i= 0; i < capacity; i++) {
            Node* curr = table[i];
            while (curr != NULL) {
                cout << curr->key << ": " << curr->value << endl;
                curr = curr->next;
            }
        }
    }

    // Get the size of the dictionary
    int getSize() {
        return size;
    }

}; // end of the class

int main() {
    // Create dictionary
    Dictionary dict(10);
    // Insert key-value pairs
    dict.insert("apple", "a sweet fruit");
    dict.insert("banana", "a yellow fruit");
    dict.insert("carrot", "a root vegetable");
    dict.insert("dog", "a domesticated mammal");
    dict.insert("elephant", "a large herbivorous mammal");
    dict.insert("fox", "a small carnivorous mammal");

    // Print all key-value pairs
    dict.print();

    cout<<"--------------------------------"<<endl;

    // Find value given a key
    cout << "The value of 'banana' is: " << dict.find("banana") << endl;

    cout<<"--------------------------------"<<endl;

    // Delete key-value pair given a key
    cout<<"\n Delete key-value pair given a key -->  elephant"<<endl;
    dict.remove("elephant");

    cout<<"--------------------------------"<<endl;
    dict.print();

    cout<<"--------------------------------"<<endl;
    // Get size of dictionary
    cout << "The size of the dictionary is: " << dict.getSize() << endl;

    return 0;
}
