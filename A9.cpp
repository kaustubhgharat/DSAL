#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Node {
public:
    string keyword;
    string meaning;
    Node *left, *right;
    int height;

    Node(string key, string mean) {
        keyword = key;
        meaning = mean;
        left = right = nullptr;
        height = 1;
    }
};

class Dictionary {
private://###################################
    Node* root;

    int height(Node* node) {//#######################################
        if (!node) return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node* y) {//#######################################
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, string key, string mean) {
        if (!node) return new Node(key, mean);

        if (key < node->keyword)
            node->left = insert(node->left, key, mean);
        else if (key > node->keyword)
            node->right = insert(node->right, key, mean);
        else {
            node->meaning = mean;
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;//#######################################
        int balance = getBalance(node);//#######################################

        // LL Rotation
        if (balance > 1 && key < node->left->keyword) {
            cout << "Performing LL rotation at node " << node->keyword << endl;
            return rightRotate(node);
        }

        // RR Rotation
        if (balance < -1 && key > node->right->keyword) {
            cout << "Performing RR rotation at node " << node->keyword << endl;
            return leftRotate(node);
        }

        // LR Rotation
        if (balance > 1 && key > node->left->keyword) {
            cout << "Performing LR rotation at node " << node->keyword << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Rotation
        if (balance < -1 && key < node->right->keyword) {
            cout << "Performing RL rotation at node " << node->keyword << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    void inOrder(Node* root) {//#######################################
        if (root) {
            inOrder(root->left);
            cout << root->keyword << ": " << root->meaning << endl;
            inOrder(root->right);
        }
    }

    void reverseOrder(Node* root) {
        if (root) {
            reverseOrder(root->right);
            cout << root->keyword << ": " << root->meaning << endl;
            reverseOrder(root->left);
        }
    }

    Node* search(Node* root, string key, int& comparisons) {
        comparisons++;
        if (!root || root->keyword == key)
            return root;
        if (key < root->keyword)
            return search(root->left, key, comparisons);
        return search(root->right, key, comparisons);
    }

    void printTreeWithBalance(Node* root, int level ) {//#######################################
        if (!root) return;
        cout << string(level * 4, ' ');
        if (level > 0) cout << "|-- ";
        cout << root->keyword << " (BF: " << getBalance(root) << ")" << endl;
        printTreeWithBalance(root->left, level + 1);
        printTreeWithBalance(root->right, level + 1);
    }

public:
    Dictionary() {
        root = nullptr;
    }

    void add(string key, string mean) {
        cout << "Inserting '" << key << "'...\n";
        root = insert(root, key, mean);
        cout << "Tree structure with balance factors after insertion:\n";
        printTreeWithBalance(root,0);
        cout << endl;
    }

    void update(string key, string mean) {
        root = insert(root, key, mean);
    }

    void displayAscending() {
        cout << "Dictionary (Ascending Order):\n";
        inOrder(root);
        cout << endl;
    }

    void displayDescending() {
        cout << "Dictionary (Descending Order):\n";
        reverseOrder(root);
        cout << endl;
    }

    void find(string key) {//#######################################
        int comparisons = 0;
        Node* result = search(root, key, comparisons);
        if (result)
            cout << "Found: " << result->keyword << ": " << result->meaning
                 << "\nComparisons needed: " << comparisons << endl;
        else
            cout << "Keyword not found\nComparisons needed: " << comparisons << endl;
    }

    void displayTreeWithBalance() {
        cout << "Current tree structure with balance factors:\n";
        printTreeWithBalance(root,0);
        cout << endl;
    }
};

void displayMenu() {
    cout << "\nDictionary Menu\n";
    cout << "1. Add a new word\n";
    cout << "2. Update a word\n";
    cout << "3. Display dictionary (ascending)\n";
    cout << "4. Display dictionary (descending)\n";
    cout << "5. Search for a word\n";
    cout << "6. Exit\n";
    cout << "Enter your choice (1-6): ";
}

int main() {
    Dictionary dict;
    int choice;
    string keyword, meaning;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();//#######################################

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, keyword);//#######################################
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dict.add(keyword, meaning);
                cout << "Word added successfully!\n";
                break;

            case 2:
                cout << "Enter keyword to update: ";
                getline(cin, keyword);
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dict.update(keyword, meaning);
                cout << "Word updated successfully!\n";
                break;

            case 3:
                dict.displayAscending();
                break;

            case 4:
                dict.displayDescending();
                break;

            case 5:
                cout << "Enter keyword to search: ";
                getline(cin, keyword);
                dict.find(keyword);
                break;

            case 6:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}
