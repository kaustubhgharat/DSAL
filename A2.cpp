#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;       
    Node* left;     
    Node* right;    

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class Tree {
public:
    Node* root;
    bool isMirrored;
    
    Tree() {
        root = NULL;
        isMirrored = false;
    }

    Node* insert(Node*& root, int data) {
        if (!root) return new Node(data);

        if (data <= root->data) {
            root->left = insert(root->left, data);//###################################
        } else {
            root->right = insert(root->right, data);
        }

        return root;
    }

    void inorder(Node* root) {
        if (root == NULL) {
            return;
        }

        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void mirror(Node* root) {
        if (root == NULL) {
            return;
        }

        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    void toggleMirror() {
        mirror(root);
        isMirrored = !isMirrored;
        cout << "BST has been mirrored!" << endl;
    }

    void search(Node* root, int data) {
        if (!root) {
            cout << "Not Found" << endl;
            return;
        }

        cout << "Comparing with: " << root->data << endl;
        
        if (root->data == data) {//###################################
            cout << "Node " << root->data << " Found!" << endl;
            return;
        }

        if ((isMirrored && data > root->data) || (!isMirrored && data < root->data)) {//###################################
            search(root->left, data);
        } else {
            search(root->right, data);
        }
    }

    int minimum(Node* root) {
        if (root->left) {
            return minimum(root->left);
        } else {
            return root->data;
        }
    }

    int maximum(Node* root) {
        if (root->right) {
            return maximum(root->right);
        } else {
            return root->data;
        }
    }

    Node* deleteNode(Node* root, int data) {
        if (!root) return root;

        if ((isMirrored && data > root->data) || (!isMirrored && data < root->data)) {
            root->left = deleteNode(root->left, data);//###################################
        } else if ((isMirrored && data < root->data) || (!isMirrored && data > root->data)) {
            root->right = deleteNode(root->right, data);
        } else {
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* succ = root->right;
            while (succ->left) succ = succ->left;
            root->data = succ->data;
            root->right = deleteNode(root->right, succ->data);
        }
        return root;
    }
};

void displayMenu() {
    cout << "\nMenu: " << endl;
    cout << "1. Insert Nodes" << endl;
    cout << "2. Inorder Traversal" << endl;
    cout << "3. Mirror the BST" << endl;
    cout << "4. Search a key" << endl;
    cout << "5. Delete a Node" << endl;
    cout << "6. Minimum Value of BST" << endl;
    cout << "7. Maximum Value of BST" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Tree tree;
    int choice, data;
    bool flag = false;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                
                while (true) {
                    cout << "Enter data to insert (-1 to stop): ";
                    cin >> data;
                    if (data == -1) break;
                    tree.root = tree.insert(tree.root, data);
                }
                
            break;

            case 2:
                cout << "Inorder Traversal: ";
                tree.inorder(tree.root);
                cout << endl;
            break;

            case 3:
                flag = (flag)? false:true ;
                tree.toggleMirror();
            break;

            case 4:
                cout << "Enter data to search: ";
                cin >> data;
                tree.search(tree.root, data);
            break;

            case 5:
                cout << "Enter data to delete: ";
                cin >> data;
                tree.root = tree.deleteNode(tree.root, data);
                cout << "Node is deleted..." << endl;
            break;

            case 6:
				if(!flag){
                	if (tree.root) {//###################################
                	    cout << "Minimum value in the BST: " << tree.minimum(tree.root) << endl;
                	} else {
                	    cout << "Tree is empty!" << endl;
                	}
				}
				else{
					if (tree.root) {
                    	cout << "Minimum value in the BST: " << tree.maximum(tree.root) << endl;
                	} else {
                    cout << "Tree is empty!" << endl;
                }

				}
            break;

            case 7:
                if(flag){
                	if (tree.root) {
                	    cout << "Maximum value in the BST: " << tree.minimum(tree.root) << endl;
                	} else {
                	    cout << "Tree is empty!" << endl;
                	}
				}
				else{
					if (tree.root) {
                    	cout << "Maximum value in the BST: " << tree.maximum(tree.root) << endl;
                	} else {
                    cout << "Tree is empty!" << endl;
                }

				}
            break;


            case 0:
                cout << "Exiting...." << endl;
                return 0;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
