#include <iostream>
using namespace std;

struct node {
	int key;
	node *left, *right;
	node(int _key) {
		key = _key;
		left = right = NULL;
	}
};

node* insert(node* root, int key) {
	if (root == NULL) 
		return new node(key);

	if (key < root->key)
		root->left = insert(root->left, key);
	else if (key > root->key)
		root->right = insert(root->right, key);
	return root;
}

void inorder(node *root) {
	if (root != NULL) {
		inorder(root->left);
		cout << root->key << endl;
		inorder(root->right);
	}
}

// get smallest element in right subtree ( successor )
node * minValueNode(node* n)
{
	node* current = n;
	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;
	return current;
}

node* deleteNode(struct node* root, int key) {
	if (root == NULL) 
		return root;

	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else {
		if (root->left == NULL) {
			node *temp = root->right;
			delete root; // free(root)
			return temp;
		}
		else if (root->right == NULL) {
			node *temp = root->left;
			delete root; // free(root)
			return temp;
		}
		// now we are at the case of node with two children
		// Get the inorder successor (smallest in the right subtree)
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node
		root->key = temp->key;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

int main() {
	int n, k;
	cin >> n >> k;
	node* root = new node(k);
	for(int i=0;i < n-1;i++) {
		cin >> k;
		insert(root, k);
	}

	inorder(root); cout << endl;
	root = deleteNode(root, 3);
	inorder(root); cout << endl;
	return 0;
}
