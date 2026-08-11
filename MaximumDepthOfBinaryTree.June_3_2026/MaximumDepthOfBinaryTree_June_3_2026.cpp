/*
104. Maximum Depth of Binary Tree

Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

source: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/?envType=problem-list-v2&envId=depth-first-search

*/
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>

using namespace std;

#define N_MAX 11
// #define M_MAX 10

int N = 0; // row
int sequentialArray[N_MAX];
int maximumLevel = 0;
bool isRecursonDepth = false;
// int currentIndex = 0;
int globalIndex = 0;

struct TreeNode {
	int data;
	TreeNode* left, * right;

	TreeNode(int val) {
		data = val;
		left = nullptr;
		right = nullptr;
	}
};


/*bool isSafe(int row, int col)
{
	if (row >= 0 && row < M && col >= 0 && col < N)
		return true;
	return false;
}*/

TreeNode* insertNodeBST(TreeNode* root, int value)
{

	if (value == 0) {
		return nullptr;
	}

	/* if (root == nullptr)
	{
		return new TreeNode(value);
	} */
	else
	{
		
		/*if (value < root->data)
		{
			root->left = insertNodeBST(root->left, value);
		} else {
			root->right = insertNodeBST(root->right, value);
		}*/

		int currentIndex = globalIndex;

		root = new TreeNode(value);

		int leftIdx = (2 * currentIndex) + 1;
		if (leftIdx <= N && sequentialArray[leftIdx] != 0) {
			globalIndex = leftIdx; // Update global tracker for the recursive call
			root->left = insertNodeBST(root->left, sequentialArray[leftIdx]);
		}

		int rightIdx = (2 * currentIndex) + 2;
		if (rightIdx <= N && sequentialArray[rightIdx] != 0) {
			globalIndex = rightIdx; // Update global tracker for the recursive call
			root->right = insertNodeBST(root->right, sequentialArray[rightIdx]);
		}
	}
	return root;
}

int maxDepth(TreeNode *root)
{
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		/*cout << "\n -> maxDepth().left= " << maxDepth(root->left) << " maxDepth().right= " << maxDepth(root->right) << "\n";
		cout << "\n -> maxDepth().total step= " << maxDepth(root->left) + maxDepth(root->right) + 1 << "\n";*/
		return maxDepth(root->left) + maxDepth(root->right) + 1;
	}
}

void maximiumDepthLevel(TreeNode* root, int level)
{
	if (root == nullptr)
	{
		maximumLevel = level;
		return;
	}

	maximiumDepthLevel(root->left, level + 1);
	maximiumDepthLevel(root->right, level + 1);
}

int maxDepthLevel(TreeNode* root, int level)
{
	if (root == nullptr && isRecursonDepth == false)
	{
		maximumLevel = level;
		isRecursonDepth = true;
		return maximumLevel;
	}

	if (isRecursonDepth == false)
	{
		maxDepthLevel(root->left, level + 1);
		maxDepthLevel(root->right, level + 1);
	}
}

void clearData()
{
	for (int row = 0; row < N_MAX; ++row)
	{
		sequentialArray[row] = 0;
	}
}

int main()
{
	int T = 0;
	freopen("input.txt", "r", stdin);
	cin >> T;

	for (int test_cases = 0; test_cases < T; ++test_cases)
	{
		cin >> N; //row

		for (int row = 0; row <= N; ++row)
		{
			cin >> sequentialArray[row];
		}

		// insert values into tree
		TreeNode* node = nullptr;

		/*for (int row = 0; row < N; ++row)
		{
				node = insertNodeBST(node, sequentialArray[row]);
		}*/

		node = insertNodeBST(node, sequentialArray[0]);

		maxDepthLevel(node, maximumLevel);

		cout << "#" << test_cases << ' ' << maximumLevel + 1 << '\n';
		maximumLevel = 0;
		globalIndex = 0;
		isRecursonDepth = false;
		clearData();
		
		int breaks = 0;
	}

	return 0;
}