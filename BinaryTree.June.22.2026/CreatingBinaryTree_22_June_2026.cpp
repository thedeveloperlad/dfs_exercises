#include <iostream>
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

/*

		2
	3		4
5		6
*/

int main() {
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
    return 0;
}