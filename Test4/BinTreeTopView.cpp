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
		
		// START OF SOLUTION
		#include<queue>
		#include<vector>
		typedef pair<int, Node*> p;

		void addToVisited(vector<p> &visited, p cur) {
			for (auto& it : visited) 
				if (it.first == cur.first) 
					return;

			visited.push_back(cur);
		}


		void topView(Node *root) {
			if (root == NULL)
				return;

			queue<p> queue;
			vector<p> visited;

			queue.push(p(0, root));
			while (!queue.empty()) 
			{
				p cur = queue.front();
				addToVisited(visited, cur);
				queue.pop();
				
				if (cur.second->left != NULL) {
					p successor(cur.first - 1, cur.second->left);
					queue.push(successor);
				}

				if (cur.second->right != NULL) {
					p successor(cur.first + 1, cur.second->right);
					queue.push(successor);
				}
			}

			sort(visited.begin(), visited.end(),
				[](const p &lho, const p &rho) { return lho.first < rho.first; });

			for (auto& cur : visited) {
				cout << cur.second->data << " ";
			}
		}
}; // END OF SOLUTION

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
  
	myTree.topView(root);
    return 0;
}