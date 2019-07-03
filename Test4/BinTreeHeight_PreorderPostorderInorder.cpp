using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }
	
	int height(Node* root) {
        if(root == NULL)
            return -1;
        int hL = height(root->left),
            hR = height(root->right);
        return 1 + (hL > hR ? hL : hR);
    }
	
	void preOrder(Node *root) {
        if(root == NULL){
            return;
        }

        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
	
	void inOrder(Node *root) {
        if(root == NULL){
            return;
        }

        preOrder(root->left);
		cout << root->data << " ";
        preOrder(root->right);
    }
	
	void postOrder(Node *root) {
        if(root == NULL){
            return;
        }

        preOrder(root->left);
        preOrder(root->right);
		cout << root->data << " ";
    }
	
	// analogous for other traversals
	void preOrder2(Node *root) {
        if(root == NULL){
            return;
        }

		cout << root->data << " ";
        preOrder(root->right);
        preOrder(root->left);
    }
}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
    int height = myTree.height(root);
    
  	std::cout << height;

    return 0;
}
