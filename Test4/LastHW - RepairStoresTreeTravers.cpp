#include <iostream>
#include <list>
using namespace std;

class Node {
private:
    int index;
    bool cafe;
    list<Node*>* relations;
public:
    Node() {
        index = 0;
        cafe = false;
        relations = new list<Node*>();
    }

    Node(int _index, bool _cafe) {
        index = _index;
        cafe = _cafe;
        relations = new list<Node*>();
    }

    void setIndex(int _data) { index = _data; }
    int getIndex() { return index; }

    bool isCafe() { return cafe; }
    void setCafe(bool _cafe) { cafe = _cafe; }

    void addRelation(Node* node) {
        relations->push_back(node);
    }

    bool hasRelation(Node* node) {
        for (auto& cur : *relations) {
            if (cur == node)
                return true;
        }
        return false;
    }

    list<Node*>* getRelations() {
        return relations;
    }
};

void relate(Node**& tree, int fromIndex, int toIndex) {

    // fetch nodes
    Node *from = tree[fromIndex],
         *to = tree[toIndex];

    /*
        // check if relation already exists
        for (auto& rel : *from->getRelations()) {
            if (rel->getIndex() == to->getIndex()) {
                return;
            }
        }
    */

    // if it doesn't relate the nodes
    from->addRelation(to);
    to->addRelation(from);
}

void print(list<Node*>& tree) {
    // print tree representation
    for (auto& node : tree) {
        cout << node->getIndex() << " ";
        if (node->isCafe()) {
            cout << "is a cafe";
        }
        else {
            cout << "not a cafe";
        }

        for (auto& rel : *node->getRelations()) {
            cout << " " << rel->getIndex();
        }
        cout << endl;
    }
}

void getPaths(Node* root, bool*& visited,
    list<Node*> path, int& paths, int k, int m)
{
    if (root->isCafe()) {
        k--;
    }
    else {
        k = m;
    }

    if (k < 0) {
        return;
    }

    path.push_back(root);
    visited[root->getIndex()] = true;
    if (root->getRelations()->size() == 1 && root->getIndex() != 1) {
        // reached service(leaf)
        paths++;
        return;
    }

    // for each relation of root
    for (auto& rel : *root->getRelations()) {
        // check if current rel is visited
        bool isVisited = visited[rel->getIndex()];

        // if it's not visited go for it.
        if (!isVisited)
            getPaths(rel, visited, path, paths, k, m);
    }
}

void printPaths(list<list<Node*>> paths) {
    cout << "Paths are :" << endl;
    for (auto& path : paths) {
        for (auto& node : path) {
            cout << "->" << node->getIndex();
        }
        cout << endl;
    }
    cout << paths.size() << endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    
    int n, m;
    cin >> n >> m;
    Node** tree;
    tree = new Node*[n + 1];
    for (int i = 1; i <= n; i++) {
        bool isCafe;
        cin >> isCafe;
        tree[i] = new Node(i, isCafe);
    }

    for (int i = 0; i < n - 1; i++) {
        int fromIndex, toIndex;
        cin >> fromIndex >> toIndex;
        relate(tree, fromIndex, toIndex);
    }

    // print(tree);
    bool* visited = new bool[n+1];
    list<Node*> path;
    int paths = 0;
    getPaths(tree[1], visited, path, paths, m, m);
    // printPaths(paths);
    cout << paths << endl;

    return 0;
}