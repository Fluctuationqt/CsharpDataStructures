#include <iostream>
#include <queue>
#include <list>
#include <iomanip>
using namespace std;

struct Node{
    int data;
    Node *leftChild, *rightChild;
    Node(int d){
        data=d;
        leftChild=NULL;
        rightChild=NULL;
    }
};

void buildTree(Node* root, int value){
    if (value==root->data){
        if(root->rightChild==NULL)
        {
            Node* temp=new Node(value);
            root->rightChild=temp;
            return;
        }
        buildTree(root->rightChild,value);
    }
    if (value<root->data){
        if(root->leftChild==NULL)
        {
            Node* temp=new Node(value);
            root->leftChild=temp;
            return;
        }
        buildTree(root->leftChild,value);
    }
    if (value>root->data)
    {
        if(root->rightChild==NULL)
        {
            Node* temp=new Node(value);
            root->rightChild=temp;
            return;
        }
        buildTree(root->rightChild,value);
    }
}

void BFS(Node* root){
    queue<Node*> q;
    long long sum=0;
    double cntr=0.00;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* curr=q.front();
        q.pop();
        if (curr==NULL){
            cout<<fixed<<setprecision(2)<<sum/cntr<<endl;
            sum=0;
            cntr=0.00;
            if(q.empty())
                break;
            q.push(NULL);
            continue;
        }
        sum+=curr->data;
        cntr+=1.00;
        if(curr->leftChild!=NULL)
            q.push(curr->leftChild);
        if(curr->rightChild!=NULL)
            q.push(curr->rightChild);
    }
}

int main()
{
   int n;
   cin>>n;
   int temp;
   cin>>temp;
   Node* root=new Node(temp);
   for (int i=0;i<n-1;i++){
        cin>>temp;
            buildTree(root, temp);
   }
   BFS(root);
   return 0;
}
