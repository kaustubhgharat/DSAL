#include <bits/stdc++.h>
using namespace std;

// Node structure for BST
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Pretty-print the BST structure with indentation
void printTree(Node* root, int level = 0) {
    if (root == nullptr) return;
    cout << string(level * 2, ' ') << root->key << endl;
    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

// Function to build the Optimal BST and return its minimum expected search cost
double buildOptimalBST(int keys[], double successProbs[], double unsuccessProbs[], int n, Node*& root) {
    vector<double> prefix_sum_s(n + 1, 0);     // prefix sum of success probs
    vector<double> prefix_sum_u(n + 2, 0);     // prefix sum of unsuccess probs (one extra for q[n])

    // Compute prefix sums for easier range sum calculations
    for (int i = 1; i <= n; i++) {
        prefix_sum_s[i] = prefix_sum_s[i - 1] + successProbs[i - 1];
        prefix_sum_u[i] = prefix_sum_u[i - 1] + unsuccessProbs[i - 1];
    }
    prefix_sum_u[n + 1] = prefix_sum_u[n] + unsuccessProbs[n];  // include q[n]

    // Initialize DP and root choice tables
    vector<vector<double>> dp(n + 2, vector<double>(n + 1, 0));       // dp[i][j] = min cost of tree from i to j
    vector<vector<int>> rootChoice(n + 2, vector<int>(n + 1, -1));    // to store root for subtree i..j

    // Base case: cost of empty subtree (i > j)
    for (int i = 1; i <= n + 1; i++) {
        dp[i][i - 1] = unsuccessProbs[i - 1];  // dp[i][i-1] = q[i-1]
    }

    // Fill DP table for increasing lengths
    for (int length = 1; length <= n; length++) {
        for (int i = 1; i <= n - length + 1; i++) {
            int j = i + length - 1;
            dp[i][j] = DBL_MAX;

            // Try each key k in range i to j as root
            for (int k = i; k <= j; k++) {
                double leftCost = dp[i][k - 1];
                double rightCost = dp[k + 1][j];

                double totalSuccess = prefix_sum_s[j] - prefix_sum_s[i - 1];
                double totalUnsuccess = prefix_sum_u[j + 1] - prefix_sum_u[i - 1];

                double cost = leftCost + rightCost + totalSuccess + totalUnsuccess;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    rootChoice[i][j] = k;
                }
            }
        }
    }

    // Lambda function to construct tree recursively using rootChoice table
    function<Node*(int, int)> buildTree = [&](int i, int j) -> Node* {
        if (i > j) return nullptr;
        int k = rootChoice[i][j];
        Node* node = new Node(keys[k - 1]);  // keys[] is 0-indexed
        node->left = buildTree(i, k - 1);
        node->right = buildTree(k + 1, j);
        return node;
    };

    root = buildTree(1, n);
    return dp[1][n];  // return minimum cost
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    int keys[100];
    double successProbs[100];
    double unsuccessProbs[101];

    cout << "Enter the sorted keys: ";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the successful search probabilities (p0 to p" << n - 1 << "): ";
    for (int i = 0; i < n; i++) {
        cin >> successProbs[i];
    }

    cout << "Enter the unsuccessful search probabilities (q0 to q" << n << "): ";
    for (int i = 0; i <= n; i++) {
        cin >> unsuccessProbs[i];
    }

    Node* root = nullptr;
    double min_cost = buildOptimalBST(keys, successProbs, unsuccessProbs, n, root);

    cout << "\nMinimum expected search cost: " << min_cost << endl;
    cout << "\nOptimal Binary Search Tree structure:\n";
    printTree(root);

    return 0;
}
