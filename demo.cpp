#include <bits/stdc++.h> 
using namespace std; 
 
struct Node { 
   int key; 
   Node* left; 
   Node* right; 
   Node(int k) : key(k), left(nullptr), right(nullptr) {} 
}; 
 
void printTree(Node* root, int level = 0) { 
   if (root == nullptr) return; 
   cout << string(level * 2, ' ') << root->key << endl; 
   printTree(root->left, level + 1); 
   printTree(root->right, level + 1); 
} 
 
double buildOptimalBST(int keys[], double successProbs[], double 
unsuccessProbs[], int n, Node*& root) { 
   vector<double> prefix_sum_s(n + 1, 0); 
   vector<double> prefix_sum_u(n + 1, 0); 
   
   for (int i = 1; i <= n; i++) { 
       prefix_sum_s[i] = prefix_sum_s[i - 1] + successProbs[i - 1]; 
       prefix_sum_u[i] = prefix_sum_u[i - 1] + unsuccessProbs[i - 1]; 
   } 
 
   vector<vector<double>> dp(n + 1, vector<double>(n + 1, 0)); 
   vector<vector<int>> rootChoice(n + 1, vector<int>(n + 1, -1)); 
 
   for (int i = 1; i <= n; i++) { 
       dp[i][i] = successProbs[i - 1] + unsuccessProbs[i - 1] + 
unsuccessProbs[i]; 
       rootChoice[i][i] = i; 
   } 
 
   for (int length = 2; length <= n; length++) { 
       for (int i = 1; i <= n - length + 1; i++) { 
           int j = i + length - 1; 
           dp[i][j] = DBL_MAX; 
 
           for (int k = i; k <= j; k++) { 
               double leftCost = (i <= k - 1) ? dp[i][k - 1] : 0; 
               double rightCost = (k + 1 <= j) ? dp[k + 1][j] : 0; 
               
           
               double cost = leftCost + rightCost + 
                           (prefix_sum_s[j] - prefix_sum_s[i - 1]) + 
                           (prefix_sum_u[j] - prefix_sum_u[i - 1]) +  
                           unsuccessProbs[j];                         
 
               if (cost < dp[i][j]) { 
                   dp[i][j] = cost; 
                   rootChoice[i][j] = k; 
               } 
           } 
       } 
   } 
 
   auto buildTree = [&](auto& self, int i, int j) -> Node* { 
       if (i > j) return nullptr; 
       int k = rootChoice[i][j]; 
       Node* node = new Node(keys[k - 1]); 
       node->left = self(self, i, k - 1); 
       node->right = self(self, k + 1, j); 
       return node; 
   }; 
 
   root = buildTree(buildTree, 1, n); 
   return dp[1][n]; 
} 
 
int main() { 
   int n; 
   cout << "Enter number of keys: "; 
   cin >> n; 
   
   int keys[100]; 
   double successProbs[100];  
   double unsuccessProbs[100 + 1];  
   
   cout << "Enter the sorted keys: "; 
   for (int i = 0; i < n; i++) { 
       cin >> keys[i]; 
   } 
   
   cout << "Enter the successful search probabilities (pi): "; 
   for (int i = 0; i < n; i++) { 
       cin >> successProbs[i]; 
   } 
   
   cout << "Enter the unsuccessful search probabilities (q0 to qn): "; 
   for (int i = 0; i <= n; i++) { 
       cin >> unsuccessProbs[i]; 
   } 
 
   Node* root = nullptr; 
   double min_cost = buildOptimalBST(keys, successProbs, unsuccessProbs, 
n, root); 
   
   cout << "\nMinimum expected search cost: " << min_cost << endl; 
   
   cout << "\nOptimal Binary Search Tree structure:\n"; 
   printTree(root); 
   
 
 
   return 0; 
}