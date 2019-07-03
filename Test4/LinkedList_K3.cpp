#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    Node* next;
    int val;
};

class LinkedList {
public:
    void add(int val, int pos) {
        Node* newNode = new Node();
        newNode->val = val;

        if (isEmpty()) {
            if (pos != 0)
                cout << "add_last";
            head = tail = newNode;
            newNode->next = nullptr;
            size++;
            return;
        }

        pos = clamp(pos, size);
        if (pos == 0) {
            newNode->next = head;
            head = newNode;
            size++;
            return;
        } 
        else if (pos == size) {
            tail->next = newNode;
            newNode->next = nullptr;
            tail = newNode;
            size++;
            return;
        }
        else {
            int currentPos = 0;
            for (Node* it = head; it != nullptr; it = it->next) {
                if (pos-1 == currentPos) {
                    newNode->next = it->next;
                    it->next = newNode;
                    size++;
                    return;
                }
                currentPos++;
            }
        }
    }

    void print() {
        Node* it = head;
        while (it != nullptr) {
            cout << it->val << "#";
            it = it->next;
        }
    }

    void remove(int pos) {
        if (pos < 0 || pos >= size) {
            cout << "remove_failed";
            return;
        }

        Node* selected;
        if (pos == 0) {
            selected = head;
            head = head->next;
            delete selected;
            size--;
        }
        else {
            Node* it = head;
            for (int i = 0; i < pos - 1; i++) {
                it = it->next;
            }

            if (pos == size - 1) {
                tail = it;
            }

            selected = it->next;
            it->next = it->next->next;
            delete selected;
            size--;
        }
    }

    void reverse() {
        Node *prev = nullptr,
             *current = head,
             *next = nullptr;
        
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        tail = head;
        head = prev;
    }

    void remove_all(int val) {
        if(isEmpty()){
            return;
        }
        
        Node *selected, *prev, *current;;
        current = prev = head;
        while (current->next != nullptr) {
            current = current->next;

            if (current->val == val) {
                selected = current;
                prev->next = current->next;
                current = prev;
                delete selected;
                size--;
            }
            else {
                prev = prev->next;
            }
        }

        if (head->val == val) {
            selected = head;
            head = head->next;
            delete selected;
            size--;
        }
    }

    void group(int a, int b) {
        if(a < 0 || a >= size)
        {
            cout<<"fail_grouping";
            return;
        }
        
        if(b < 0 || b >= size){
            cout<<"fail_grouping";
            return;
        }
        
        if(a > b){
            cout << "fail_grouping";
            return;
        }
        
        if(a == b){
            return;
        }
        
        Node *from = head, *to = head;
        for(int i = 0; i < a; i++){
            from = from->next;
        }
        for(int i = 0; i < b; i++){
            to = to->next;
        }
        
        Node *it = from->next, *selected;
        int sum = 0;
        
        if(from->next == to){
            from->val += to->val;
            selected = to;
            from->next = to->next;
            size--;
            delete selected;
        }
        else
        {
            if (to->next == nullptr) 
            {
               while (it != nullptr) 
               {
                    selected = it;
                    it = it->next;
                    sum += selected->val;
                    size--;
                    delete selected;
                }

                from->next = nullptr;
                from->val += sum;
                tail = from;
            }
            else
            {
                to = to->next;
                while (it != to) 
                {
                    selected = it;
                    it = it->next;
                    sum += selected->val;
                    size--;
                    delete selected;
                }

                from->next = to;
                from->val += sum;
            }
        }
    }

    void count(int val) {
        int ctr = 0;
        for (Node* it = head; it != nullptr; it = it->next) {
            if (it->val == val)
                ctr++;
        }
        cout << ctr;
    }

    void is_palindrome() {
        LinkedList* reversed = new LinkedList(*this);
        reversed->reverse();
        
        Node *it1 = head, *it2 = reversed->begin();
        for (int i = 0; i < size; i++) {
            if (it1->val != it2->val){
                cout << "false";
                delete reversed;
                return;
            }
        }
        cout << "true";
        delete reversed;
    }

    Node* begin(){
        return head;
    }
    
    Node* end(){
        return tail;
    }
    
    int getSize(){
        return size;
    }
    
    bool isEmpty() {
        return head == nullptr;
    }

    LinkedList() {
        size = 0;
        head = nullptr;
    }
    
    void push_back(int val){
        Node* newNode = new Node();
        newNode->val = val;
        newNode->next = nullptr;
        if(isEmpty()){
            head = tail = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    LinkedList(LinkedList& other) {
        head = tail = nullptr;
        size = 0;
        Node* it = other.begin();
        while(it!=nullptr){
            push_back(it->val);
            it=it->next;
        }
    }

    ~LinkedList() {
       Node *it = head, *selected;
        while (it != nullptr) {
            selected = it;
            it = it->next;
            delete selected;
        }
        head = tail = nullptr;
        size = 0;
    }

private:
    Node *head, *tail;
    int size;

    // clamp a value between 0 and max-1
    int clamp(int pos, int max) {
        if (pos < 0 || pos > max) {
            cout << "add_last";
            return max;
        }
        return pos;
    }
};

int main() {
    //test();
    int cases;
    std::cin >> cases;
    for (int i = 0; i < cases; i++) {
        LinkedList ll;
        int ops;
        std::string op;
        std::cin >> ops;
        for (int j = 0; j < ops; j++) {
            std::cin >> op;

            if (op == "count") {
                int arg1;
                std::cin >> arg1;
                ll.count(arg1);
            }

            if (op == "add") {
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                ll.add(arg1, arg2);
            }

            if (op == "print") {
                ll.print();
            }

            if (op == "remove") {
                int arg1;
                std::cin >> arg1;
                ll.remove(arg1);
            }

            if (op == "reverse") {
                ll.reverse();
            }

            if (op == "remove_all") {
                int arg1;
                std::cin >> arg1;
                ll.remove_all(arg1);
            }

            if (op == "group") {
                int arg1, arg2;
                std::cin >> arg1 >> arg2;
                ll.group(arg1, arg2);
            }

            if (op == "is_palindrom") {
                ll.is_palindrome();
            }
        }

        std::cout << std::endl;

    }
    return 0;
}