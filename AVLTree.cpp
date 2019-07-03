#include "stdafx.h"
#include <iostream>
using namespace std;

// An AVL tree node 
struct Node
{
	Node *left, *right;
	int data, height;

	Node(int _data) {
		data = _data;
		height = 1;
		left = right = NULL;
	}
};

// A utility function to get maximum of two integers 
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// A utility function to get the height of the tree 
int height(Node *node)
{
	if (node == NULL)
		return 0;
	return node->height;
}


// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
Node *rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation 
	x->right = y;
	y->left = T2;

	// Update heights 
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root 
	return x;
}

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
Node *leftRotate(Node *x)
{
	Node *y = x->right;
	Node *T2 = y->left;

	// Perform rotation 
	y->left = x;
	x->right = T2;

	//  Update heights 
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root 
	return y;
}

// Get Balance factor of node N 
int getBalance(Node *node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

// Recursive function to insert a data in the subtree rooted 
// with node and returns the new root of the subtree. 
Node* insert(Node* root, int data)
{
	/* 1.  Perform the normal BST insertion */
	if (root == NULL)
		return(new Node(data));

	if (data < root->data)
		root->left = insert(root->left, data);
	else if (data > root->data)
		root->right = insert(root->right, data);
	else // Equal keys are not allowed in BST so return root and don't insert
		return root;

	/* 2. Update height of this ancestor node */
	root->height = 1 + max(height(root->left), height(root->right));

	/* 3. Get the balance factor of this ancestor
	node to check whether this node became
	unbalanced */
	int balance = getBalance(root);

	// If this node becomes unbalanced, then 
	// there are 4 cases 

	// Left Left Case 
	if (balance > 1 && data < root->left->data)
		return rightRotate(root);

	// Right Right Case 
	if (balance < -1 && data > root->right->data)
		return leftRotate(root);

	// Left Right Case 
	if (balance > 1 && data > root->left->data)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Left Case 
	if (balance < -1 && data < root->right->data)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	/* return the (unchanged) node pointer */
	return root;
}

/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
Node * minValueNode(Node* node)
{
	Node* current = node;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}

// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 
Node* deleteNode(Node* root, int data)
{
	// STEP 1: PERFORM STANDARD BST DELETE 

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the 
	// root's key, then it lies in left subtree 
	if (data < root->data)
		root->left = deleteNode(root->left, data);

	// If the key to be deleted is greater than the 
	// root's key, then it lies in right subtree 
	else if (data > root->data)
		root->right = deleteNode(root->right, data);

	// if key is same as root's key, then This is 
	// the node to be deleted 
	else
	{
		// node with only one child or no child 
		if ((root->left == NULL) || (root->right == NULL))
		{
			struct Node *temp = root->left ? root->left :
				root->right;

			// No child case 
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case 
				*root = *temp; // Copy the contents of 
							   // the non-empty child 
			delete temp;
		}
		else
		{
			// node with two children: Get the inorder 
			// successor (smallest in the right subtree) 
			Node* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node 
			root->data = temp->data;

			// Delete the inorder successor 
			root->right = deleteNode(root->right, temp->data);
		}
	}

	// If the tree had only one node then return 
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
	root->height = 1 + max(height(root->left),
		height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
	// check whether this node became unbalanced) 
	int balance = getBalance(root);

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case 
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case 
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case 
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(Node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->data);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void testInsert() {
	Node *root = NULL;

	/* Constructing tree given in the above figure */
	root = insert(root, 10);
	root = insert(root, 20);
	root = insert(root, 30);
	root = insert(root, 40);
	root = insert(root, 50);
	root = insert(root, 25);

	/* The constructed AVL Tree would be
	30
	/  \
	20   40
	/  \     \
	10  25    50
	*/
	printf("Preorder traversal of the constructed AVL"
		" tree is \n");
	preOrder(root); // Output should be: 30 20 10 25 40 50	
}

void testDelete() {
	struct Node *root = NULL;

	/* Constructing tree given in the above figure */
	root = insert(root, 9);
	root = insert(root, 5);
	root = insert(root, 10);
	root = insert(root, 0);
	root = insert(root, 6);
	root = insert(root, 11);
	root = insert(root, -1);
	root = insert(root, 1);
	root = insert(root, 2);

	/* The constructed AVL Tree would be
	9
	/  \
	1    10
	/  \     \
	0    5     11
	/    /  \
	-1   2    6
	*/

	printf("Preorder traversal of the constructed AVL "
		"tree is \n");
	preOrder(root);

	root = deleteNode(root, 10);

	/* The AVL Tree after deletion of 10
	1
	/  \
	0    9
	/     /  \
	-1    5     11
	/  \
	2    6
	*/

	printf("\nPreorder traversal after deletion of 10 \n");
	preOrder(root);
	/* 
		Output should be:
			Preorder traversal of the constructed AVL tree is 
			9 1 0 -1 5 2 6 10 11 
			Preorder traversal after deletion of 10 
			1 0 -1 9 5 2 6 11 
	*/
}

int main()
{
	testInsert();
	testDelete();

	return 0;
}