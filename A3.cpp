#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* right, * left;
    bool lthread;
    bool rthread;
};

Node* createNode(int key) {
    Node* temp = new Node();
    temp->key = key;//###################################
    temp->left = temp->right = nullptr;
    temp->lthread = temp->rthread = true;
    return temp;
}

Node* insert(Node* root, int key) {
    Node* newNode = createNode(key);
    if (root == nullptr) {
        return newNode;
    }
    Node* parent = nullptr;//###################################
    Node* current = root;//###################################

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            if (!current->lthread) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (!current->rthread) {
                current = current->right;
            } else {
                break;
            }
        }
    }

    if (key < parent->key) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->left = newNode;
        parent->lthread = false;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->right = newNode;
        parent->rthread = false;
    }

    return root;//###################################
}

void inorderTraversal(Node* root) {
    if (root == nullptr) return;
    
    Node* current = root;
    while (!current->lthread) {
        current = current->left;
    }

    while (current != nullptr) {//###################################
        cout << current->key << " ";
        
        if (current->rthread) {
            current = current->right;
        } else {
            current = current->right;
            while (current != nullptr && !current->lthread) {
                current = current->left;
            }
        }
    }
}

void preorderTraversal(Node* root) {
    Node* current = root;

    while (current != nullptr) {
        cout << current->key << " ";

        if (!current->lthread) {
            current = current->left;
        } else if (!current->rthread) {
            current = current->right;
        } else {
            
            while (current != nullptr && current->rthread) {
                current = current->right;//###################################
            }
            if (current != nullptr) {
                current = current->right;
            }
        }
    }
}


Node* deleteNode(Node* root, int key) {
    if (root == nullptr) {
        cout << "Key not found!\n";
        return root;
    }

    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr && current->key != key) {
        parent = current;
        if (key < current->key) {
            if (!current->lthread) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (!current->rthread) {
                current = current->right;
            } else {
                break;
            }
        }
    }

    if (current == nullptr || current->key != key) {
        cout << "Key not found!\n";
        return root;
    }

    if (current->lthread && current->rthread) {
        if (parent == nullptr) {
            return nullptr;
        }

        if (parent->left == current) {
            parent->left = current->left;
            parent->lthread = true;
        } else {
            parent->right = current->right;
            parent->rthread = true;
        }

        delete current;
    }
    else if (current->lthread || current->rthread) {
        Node* child = (!current->lthread) ? current->left : current->right;

        if (!current->lthread) {
            Node* temp = child;
            while (!temp->rthread) {
                temp = temp->right;
            }
            temp->right = current->right;
        } else {
            Node* temp = child;
            while (!temp->lthread) {
                temp = temp->left;
            }
            temp->left = current->left;
        }

        if (parent == nullptr) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }

        delete current;
    }
    else {
        Node* successor = current->right;
        Node* successorParent = current;

        while (!successor->lthread) {
            successorParent = successor;
            successor = successor->left;
        }

        current->key = successor->key;

        if (successor->rthread) {
            if (successorParent->left == successor) {
                successorParent->left = successor->left;
                successorParent->lthread = true;
            } else {
                successorParent->right = successor->right;
                successorParent->rthread = true;
            }
        } else {
            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }
        }

        delete successor;
    }

    return root;
}

void displayMenu() {
    cout << "\n---Menu---\n";
    cout << "1. Insert a node\n";
    cout << "2. Delete a node\n";
    cout << "3. Inorder traversal\n";
    cout << "4. Preorder traversal\n";
    cout << "5. Exit...\n";
    cout << "Enter your choice: ";
}

int main() {
    Node* root = nullptr;//###################################
    int key, choice;
    
    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> key;
                root = insert(root, key);
                cout << "Inserted " << key << " successfully!\n";
                break;

            case 2:
                cout << "Enter the value to be deleted: ";
                cin >> key;
                root = deleteNode(root, key);
                break;

            case 3:
                cout << "Inorder traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;

            case 4:
                cout << "Preorder traversal: ";
                preorderTraversal(root);
                cout << endl;
                break;

            case 5:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again!\n";
        }
    }

    return 0;
}
