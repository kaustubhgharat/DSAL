//Beginning with an empty binary tree, construct binary tree by inserting
 //the values in the order given. After constructing a binary tree perform
 //following operations on it
//• Perform,inorder,preorder and post order traversal
 //• Change a tree so that the roles of the left and right pointers are
 //swapped at every node
 //• Find the height of tree
 //• Copy this tree to another [operator=]
 //• Count number of leaves, number of internal nodes.
 //• Erase all nodes in a binary tree. (Implement both recursive and non
//recursive methods)
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class TreeNode {
public:
   int data;
   TreeNode* left;
   TreeNode* right;
   TreeNode(int val) {
       data = val;
       left = right = nullptr;
   }
};
class Tree {
public:
   TreeNode* root;
   Tree() {
       root = nullptr;
   }
   TreeNode* createTree() {
       int val;
       cout << "Enter node data: ";
       cin >> val;
       if (val == -1)return nullptr;
       TreeNode* newNode = new TreeNode(val);
       cout << "Enter left child of " << val << endl;
       newNode->left = createTree();
       cout << "Enter right child of " << val << endl;
       newNode->right = createTree();
       return newNode;
   }
   void inOrderTraversal(TreeNode* root) {
       if (root == nullptr)
           return;
       inOrderTraversal(root->left);
       cout << root->data << " ";
       inOrderTraversal(root->right);
   }
   void preOrderTraversal(TreeNode* root) {
       if (root == nullptr)
           return;
       cout << root->data << " ";
       preOrderTraversal(root->left);
       preOrderTraversal(root->right);
   }
   void postOrderTraversal(TreeNode* root) {
       if (root == nullptr)
           return;
       postOrderTraversal(root->left);
       postOrderTraversal(root->right);
       cout << root->data << " ";
   }
    void preOrderNR() {
       if (root == nullptr)
           return;
       stack<TreeNode*> s;
       s.push(root);
       while (!s.empty()) {
           TreeNode* current = s.top();
           s.pop();
           cout << current->data << " ";
           if (current->right) s.push(current->right);
           if (current->left) s.push(current->left);
       }
   }
   void inOrderNR() {
       if (root == nullptr)
           return;
       stack<TreeNode*> s;
       TreeNode* current = root;
       while (!s.empty() || current != nullptr) {
           if (current != nullptr) {
               s.push(current);
               current = current->left;
           } else {
               current = s.top();
               s.pop();
               cout << current->data << " ";
               current = current->right;
           }
       }
   }
   void postOrderNR() {
       if (root == nullptr)
           return;
       stack<TreeNode*> s1, s2;
       s1.push(root);
       while (!s1.empty()) {
           TreeNode* current = s1.top();
           s1.pop();
           s2.push(current);
           if (current->left) s1.push(current->left);
           if (current->right) s1.push(current->right);
       }
       while (!s2.empty()) {
           cout << s2.top()->data << " ";
           s2.pop();
       }
   }
   void swap(TreeNode* root) {
       if (root == nullptr)
           return;
       TreeNode* temp = root->left;
       root->left = root->right;
       root->right = temp;
       swap(root->left);
       swap(root->right);
   }
   int height(TreeNode* root) {
       if (root == nullptr) return -1;
       return 1 + std::max(height(root->left), height(root->right));
   }
   int countLeaves(TreeNode* root) {
       if (root == nullptr) return 0;
       if (root->left == nullptr && root->right == nullptr)
           return 1;
       return countLeaves(root->left) + countLeaves(root->right);
   }
   int countInternalNodes(TreeNode* root) {
       if (root == nullptr) {
           return 0;
       }
       int internal = (root->left != nullptr || root->right != nullptr) ? 1 : 0;
       return internal + countInternalNodes(root->left) + countInternalNodes(root->right);
   }
   void erase(TreeNode*& root) {
       if (root == nullptr)
           return;
       erase(root->left);
       erase(root->right);
       delete root;
       root = nullptr;
   }
   TreeNode* copy(TreeNode* root) {
       if (root == nullptr) return nullptr;
       TreeNode* temp = new TreeNode(root->data);
       temp->left = copy(root->left);
       temp->right = copy(root->right);
       return temp;
   }
};
int main() {
   Tree tree;
   int choice;
   do {
       cout << "\n--- Menu ---\n";
       cout << "1. Create Tree\n";
       cout << "2. In-order Traversal (Recursive)\n";
       cout << "3. Pre-order Traversal (Recursive)\n";
       cout << "4. Post-order Traversal (Recursive)\n";
       cout << "5. In-order Traversal (Non-Recursive)\n";
       cout << "6. Pre-order Traversal (Non-Recursive)\n";
       cout << "7. Post-order Traversal (Non-Recursive)\n";
       cout << "8. Swap Left and Right Subtrees\n";
       cout << "9. Height of Tree\n";
       cout << "10. Count Leaves\n";
       cout << "11. Count Internal Nodes\n";
       cout << "12. Erase tree\n";
       cout << "13. Copy Tree\n";
       cout << "14. Exit\n";
       cout << "Enter your Choice (1 to 13): ";
       cin >> choice;
       switch (choice) {
           case 1:
               tree.root = tree.createTree();
               break;
           case 2:
               tree.inOrderTraversal(tree.root);
               cout << endl;
               break;
           case 3:
               tree.preOrderTraversal(tree.root);
               cout << endl;
               break;
           case 4:
               tree.postOrderTraversal(tree.root);
               cout << endl;
               break;
           case 5:
               tree.inOrderNR();
               cout << endl;
               break;
           case 6:
               tree.preOrderNR();
               cout << endl;
               break;
           case 7:
               tree.postOrderNR();
               cout << endl;
               break;
           case 8:
               tree.swap(tree.root);
               cout << "Subtrees swapped.\n";
               break;
           case 9:
               cout << tree.height(tree.root) << endl;
               break;
           case 10:
               cout << tree.countLeaves(tree.root) << endl;
               break;
           case 11:
               cout << tree.countInternalNodes(tree.root)<< endl;
               break;
           case 12:
               tree.erase(tree.root);
               cout << endl;
               break;
           case 13: {
               Tree CT;
               CT.root = tree.copy(tree.root);
               CT.inOrderTraversal(CT.root);
               cout << endl;
               break;
           }
           case 14:
               break;
           default:
               cout << "Invalid choice\n";
       }
   } while (choice != 14);
   return 0;
}