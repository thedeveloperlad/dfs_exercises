#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int data;
	Node* left, * right;

	Node(int val) {
		data = val;
		left = nullptr;
		right = nullptr;
	}
};

int getSize(Node* root) {
	if(root == nullptr)
	{
		return 0;
	}
	else
	{
		return getSize(root->left) + getSize(root->right) + 1;
	}
}

// Recursive insertion for a Binary Search Tree.
void insertBST(Node* root, int data)
{
	if (root == nullptr)
	{
		root = new Node(data);
		return;
	}
	else
	{
		if (data < root->data)
		{
			insertBST(root->left, data);
		}
		else {
			insertBST(root->right, data);
		}
	}
}

// Level-order insertion using a tracking queue
Node* insertNode(Node* root, int data)
{
	if (root == nullptr) {
		Node* root = new Node(data);
		return root;
	}
	else
	{
		queue<Node*> q;
		q.push(root);

		Node* curr = q.front();
		q.pop();

		while (!q.empty())
		{

			if (curr->left == nullptr)
			{
				q.push(curr->left);
			}
			else {
				curr->left = new Node(data);
				return root;
			}

			if (curr->right == nullptr)
			{
				q.push(curr->right);
			}
			else {
				curr->right = new Node(data);
				return root;
			}
		}
	}
}

void printInOrder(Node* root)
{
	if (root == nullptr)
	{
		return;
	}
	else {
		printInOrder(root->left);
		cout << "Tree Size: " << root->data << '\n';
		printInOrder(root->right);
	}
}

/*

		2
	3		4
5		6
*/

void testRoot()
{
	// Initilize and allocate memory for tree nodes
	Node* firstNode = new Node(2);
	Node* secondNode = new Node(3);
	Node* thirdNode = new Node(4);
	Node* fourthNode = new Node(5);
	Node* fiveNode = new Node(6);

	firstNode->left = secondNode;
	firstNode->right = thirdNode;

	secondNode->left = fourthNode;
	thirdNode->left = fiveNode;


	cout << "Tree Size: " << getSize(firstNode) << '\n';
}

int main() {
    // Initilize and allocate memory for tree nodes
	Node* root = nullptr;

	//Using the BST approach
	insertBST(root, 2);
	insertBST(root, 3);
	insertBST(root, 4);
	insertBST(root, 5);
	insertBST(root, 6);

	cout << "BST In-Order tranversal: ";
	printInOrder(root);

    return 0;
}