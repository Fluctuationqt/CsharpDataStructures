#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Node
{
	double value;
	Node *left;
	Node *right;
	int height;

	Node(double value, Node *left, Node *right, int height)
	{
		this->value = value;
		this->left = left;
		this->right = right;
		this->height = height;
	}
};

class AVLTree
{
private:
	Node *root;

	bool containsRecursive(Node *current, double value)
	{
		if (current == NULL)
		{
			return false;
		}

		if (current->value == value)
		{
			return true;
		}

		if (value < current->value)
		{
			return containsRecursive(current->left, value);
		}
		else
		{
			return containsRecursive(current->right, value);
		}
	}

	void printRecursive(Node *current)
	{
		if (current == NULL)
		{
			return;
		}

		printRecursive(current->left);
		cout << current->value << " ";
		printRecursive(current->right);
	}

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

	// Get Balance factor of node N 
	int getBalance(Node *node)
	{
		if (node == NULL)
			return 0;
		return height(node->left) - height(node->right);
	}

	/* Given a non-empty binary search tree, return the
	node with minimum key value found in that tree.
	Note that the entire tree does not need to be searched. */
	Node * minValueNode(Node* node)
	{
		Node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}

	// A utility function to right rotate subtree rooted with y 
	// See the diagram given below. 
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
	// See the diagram given below. 
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

	// Recursive function to insert a data in the subtree rooted 
	// with node and returns the new root of the subtree. 
	Node* insert(Node* cur, double value, bool &isDuplicate)
	{
		/* 1.  Perform the normal BST insertion */
		if (cur == NULL)
			return(new Node(value, NULL, NULL, 1));

		if (value < cur->value)
			cur->left = insert(cur->left, value, isDuplicate);
		else if (value > cur->value)
			cur->right = insert(cur->right, value, isDuplicate);
		else
		{
			// Equal keys are not allowed in BST so return root and don't insert
			isDuplicate = true;
			return cur;
		}

		/* 2. Update height of this ancestor node */
		cur->height = 1 + max(height(cur->left), height(cur->right));

		/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
		int balance = getBalance(cur);

		// If this node becomes unbalanced, then 
		// there are 4 cases 

		// Left Left Case 
		if (balance > 1 && value < cur->left->value)
			return rightRotate(cur);

		// Right Right Case 
		if (balance < -1 && value > cur->right->value)
			return leftRotate(cur);

		// Left Right Case 
		if (balance > 1 && value > cur->left->value)
		{
			cur->left = leftRotate(cur->left);
			return rightRotate(cur);
		}

		// Right Left Case 
		if (balance < -1 && value < cur->right->value)
		{
			cur->right = rightRotate(cur->right);
			return leftRotate(cur);
		}

		/* return the (unchanged) node pointer */
		return cur;
	}

	// Recursive function to delete a node with given key 
	// from subtree with given root. It returns root of 
	// the modified subtree. 
	Node* deleteNode(Node* cur, double value, bool &isDeleted)
	{
		// STEP 1: PERFORM STANDARD BST DELETE 

		if (cur == NULL)
			return cur;

		// If the key to be deleted is smaller than the 
		// root's key, then it lies in left subtree 
		if (value < cur->value)
			cur->left = deleteNode(cur->left, value, isDeleted);

		// If the key to be deleted is greater than the 
		// root's key, then it lies in right subtree 
		else if (value > cur->value)
			cur->right = deleteNode(cur->right, value, isDeleted);

		// if key is same as root's key, then This is 
		// the node to be deleted 
		else if(value == cur->value)
		{
			isDeleted = true;
			// node with only one child or no child 
			if ((cur->left == NULL) || (cur->right == NULL))
			{
				Node *temp = cur->left ? cur->left : cur->right;

				// No child case 
				if (temp == NULL)
				{
					temp = cur;
					cur = NULL;
				}
				else // One child case 
					*cur = *temp; // Copy the contents of 
								  // the non-empty child 
				delete temp;
			}
			else
			{
				// node with two children: Get the inorder 
				// successor (smallest in the right subtree) 
				Node* temp = minValueNode(cur->right);

				// Copy the inorder successor's data to this node 
				cur->value = temp->value;

				// Delete the inorder successor 
				cur->right = deleteNode(cur->right, temp->value, isDeleted);
			}
		}
		
		// If the tree had only one node then return 
		if (cur == NULL) 
			return cur;

		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
		cur->height = 1 + max(height(cur->left),
			height(cur->right));

		// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
		// check whether this node became unbalanced) 
		int balance = getBalance(cur);

		// If this node becomes unbalanced, then there are 4 cases 

		// Left Left Case 
		if (balance > 1 && getBalance(cur->left) >= 0)
			return rightRotate(cur);

		// Left Right Case 
		if (balance > 1 && getBalance(cur->left) < 0)
		{
			cur->left = leftRotate(cur->left);
			return rightRotate(cur);
		}

		// Right Right Case 
		if (balance < -1 && getBalance(cur->right) <= 0)
			return leftRotate(cur);

		// Right Left Case 
		if (balance < -1 && getBalance(cur->right) > 0)
		{
			cur->right = rightRotate(cur->right);
			return leftRotate(cur);
		}

		return cur;
	}

public:
	AVLTree()
	{
		root = NULL;
	}

	void add(double value)
	{
		bool isDuplicate = false;
		root = insert(root, value, isDuplicate);
		if (isDuplicate)
			cout << value << " already added" << endl;
	}

	void remove(double value)
	{
		bool isDeleted = false;
		root = deleteNode(root, value, isDeleted);
		if (!isDeleted)
			cout << value << " not found to remove" << endl;
	}

	bool contains(double value)
	{
		if (root == NULL)
		{
			return false;
		}

		return containsRecursive(root, value);
	}

	void print()
	{
		if (root == NULL)
		{
			return;
		}

		printRecursive(root);
		cout << endl;
	}
};

int main()
{
	AVLTree tree;
	string operation;
	double number;
	int N;

	cin >> N;
	cout << fixed;

	for (size_t i = 0; i < N; i++)
	{
		cin >> operation;
		if (operation != "print")
		{
			cin >> number;
		}

		if (operation == "add")
		{
			tree.add(number);
		}
		else if (operation == "remove")
		{
			tree.remove(number);
		}
		else if (operation == "contains")
		{
			if (tree.contains(number))
			{
				cout << "yes" << endl;
			}
			else
			{
				cout << "no" << endl;
			}
		}
		else if (operation == "print")
		{
			tree.print();
		}
	}

	return 0;
}

/*
################################################################
########################## INSERTION ###########################
################################################################

Let the newly inserted node be w
1) Perform standard BST insert for w.
2) Starting from w, travel up and find the first unbalanced node. 
   Let z be the first unbalanced node, y be the child of z that comes
   on the path from w to z and x be the grandchild of z that comes on
   the path from w to z.
3) Re-balance the tree by performing appropriate rotations on the 
   subtree rooted with z. There can be 4 possible cases that needs
   to be handled as x, y and z can be arranged in 4 ways. 
    Following are the possible 4 arrangements:
	a) y is left child of z and x is left child of y (Left Left Case)
	b) y is left child of z and x is right child of y (Left Right Case)
	c) y is right child of z and x is right child of y (Right Right Case)
	d) y is right child of z and x is left child of y (Right Left Case)

################################################################
########################## DELETION ############################
################################################################

1) Perform the normal BST deletion.
2) The current node must be one of the ancestors of the deleted node.
   Update the height of the current node.
3) Get the balance factor (left subtree height – right subtree height)
   of the current node.
4) If balance factor is greater than 1, then the current node is unbalanced
   and we are either in Left Left case or Left Right case. 
   To check whether it is Left Left case or Left Right case,
   get the balance factor of left subtree. If balance factor of the 
   left subtree is greater than or equal to 0, then it is Left Left case,
   else Left Right case.
5) If balance factor is less than -1, then the current node is unbalanced
   and we are either in Right Right case or Right Left case.
   To check whether it is Right Right case or Right Left case,
   get the balance factor of right subtree. If the balance factor of the
   right subtree is smaller than or equal to 0, then it is Right Right case,
   else Right Left case.

################################################################
########################### ROTATIONS ##########################
################################################################
* Let T1, T2 and T3 be subtrees of the tree rooted
  with y (on the left side) or x (on the right side)

     y                               x
    / \     Right Rotation          /  \
   x   T3   – – – – – – – >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3

* Keys in both of the above trees follow the following order 
  keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)
  So BST property is not violated anywhere.

################################################################
######################## ROTATION CASES ########################
################################################################
* Let T1, T2, T3 and T4 be subtrees.

1. Left Left case:
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

2. Left Right case:
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

3. Right Right case:
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

4. Right Left case:
   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4

*/