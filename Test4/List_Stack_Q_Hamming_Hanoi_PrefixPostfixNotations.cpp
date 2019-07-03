// ############## LIST IMPLEMENTATION #################
template<typename T>
struct Node {
	Node* next;
	T data;
};

template<typename T>
class List {
private:
	Node<T> *head, *tail;
public:
	List() {
		head = nullptr;
		tail = nullptr;
	}
	void pushBack(T val) {
		Node<T>* newElement = new Node<T>();
		newElement->data = val;
		newElement->next = nullptr;
		if (empty()) {
			head = newElement;
			tail = newElement;
		}
		else {
			tail->next = newElement;
			tail = newElement;
		}
	}

	int popFront() {
		if (empty()) {
			throw std::exception("List is empty.");
		}

		int val = head->data;
		Node<T>* forDel = head;
		head = head->next;
		delete forDel;
		return val;
	}
	
	void reverse() {
		Node<T> *current = head;
		Node<T> *prev = nullptr, *next = nullptr;
		tail = head;
		while (current != nullptr)
		{
			next = current->next;
			current->next = prev; 
			prev = current;
			current = next;
		}
		head = prev;
	}

	bool empty() {
		return head == nullptr;
	}

	void print() {
		Node<T>* it = head;
		while (it != nullptr) {
			cout << it->data << " ";
			it = it->next;
		}
		cout << endl;
	}
};



// ################ STACK IMPLEMENTATION #############
template <typename T>
class Stack {
private:
	template <typename T>
	struct Node {
		Node<T>* next;
		T data;
	};

	Node<T> *top;

public:
	Stack() {
		top = nullptr;
	}

	void push(T element) {
		if (isEmpty()) {
			top = new Node<T>();
			top->data = element;
			top->next = nullptr;
		}
		else {
			Node<T>* newTop = new Node<T>();
			newTop->data = element; 
			newTop->next = top;
			top = newTop;
		}
	}

	T pop() {
		if (isEmpty()) {
			throw std::exception("Stack is Empty, cannot pop().");
		}

		T element = top->data;
		Node<T>* forDel = top;
		top = top->next;
		delete forDel;
		return element;
	}

	bool isEmpty() {
		return top == nullptr;
	}

	void print() {
		Node<T>* it = top;
		cout << "TOP" << endl;
		while (it != nullptr) {
			cout << it->data << endl;
			it = it->next;
		}
		cout << "BOTTOM" << endl << endl;
	}
};

void printStack(Stack<int>& st) {
	Stack<int> rev;
	while (!st.isEmpty()) {
		int el = st.pop();
		rev.push(el);
	}
	while (!rev.isEmpty()) {
		cout << rev.pop() << endl;
	}
}



// ################ PREFIX/POSTFIX EVAL ###############
double evalPostfix(string expr) {
	Stack<double> st;
	double opnd1, opnd2;
	
	for (int i = 0; i < expr.size(); i++) {
		int current = expr[i];
		switch(current) {
			case '+': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd1 + opnd2);
			}break;
		
			case '-': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd2 - opnd1);
			}break;

			case '/': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd2 / opnd1);
			}break;

			case '*': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd1 * opnd2);
			}break;

			default: st.push(current - '0');
		}
	}
	
	double result;
	try {
		result = st.pop();
	}
	catch (exception ex) {
		throw std::invalid_argument("Invalid Expression");
	}

	if (!st.isEmpty()) {
		throw std::invalid_argument("Invalid Expression");
	}
	return result;
}

double evalPrefix(string expr) {
	Stack<double> st;
	double opnd1, opnd2;

	for (int i = expr.size()-1; i >= 0; i--) {
		int current = expr[i];
		switch (current) {
			case '+': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd1 + opnd2);
			}break;

			case '-': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd1 - opnd2);
			}break;

			case '/': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd1 / opnd2);
			}break;

			case '*': {
				opnd1 = st.pop();
				opnd2 = st.pop();
				st.push(opnd1 * opnd2);
			}break;

			default: st.push(current - '0');
		}
	}

	double result;
	try {
		result = st.pop();
	}
	catch (exception ex) {
		throw std::invalid_argument("Invalid Expression");
	}

	if (!st.isEmpty()) {
		throw std::invalid_argument("Invalid Expression");
	}
	return result;
}



// ########## INFIX TO POSTFIX ############

// A utility function to check if the given character is operand 
int isOperand(char ch) 
{ 
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); 
} 
  
// A utility function to return precedence of a given operator 
// Higher returned value means higher precedence 
int Prec(char ch) 
{ 
    switch (ch) 
    { 
    case '+': 
    case '-': 
        return 1; 
  
    case '*': 
    case '/': 
        return 2; 
  
    case '^': 
        return 3; 
    } 
    return -1; 
} 
  
  
// The main function that converts given infix expression 
// to postfix expression.  
int infixToPostfix(char* exp) 
{ 
    int i, k; 
  
    // Create a stack of capacity equal to expression size  
    struct Stack* stack = createStack(strlen(exp)); 
    if(!stack) // See if stack was created successfully  
        return -1 ; 
  
    for (i = 0, k = -1; exp[i]; ++i) 
    { 
        // If the scanned character is an operand, add it to output. 
        if (isOperand(exp[i])) 
            exp[++k] = exp[i]; 
          
        // If the scanned character is an ‘(‘, push it to the stack. 
        else if (exp[i] == '(') 
            push(stack, exp[i]); 
          
        // If the scanned character is an ‘)’, pop and output from the stack  
        // until an ‘(‘ is encountered. 
        else if (exp[i] == ')') 
        { 
            while (!isEmpty(stack) && peek(stack) != '(') 
                exp[++k] = pop(stack); 
            if (!isEmpty(stack) && peek(stack) != '(') 
                return -1; // invalid expression              
            else
                pop(stack); 
        } 
        else // an operator is encountered 
        { 
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack))) 
                exp[++k] = pop(stack); 
            push(stack, exp[i]); 
        } 
  
    } 
  
    // pop all the operators from the stack 
    while (!isEmpty(stack)) 
        exp[++k] = pop(stack ); 
  
    exp[++k] = '\0'; 
    printf( "%sn", exp ); 
} 



// ########### TOWER OF HANOI #############
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) 
{ 
    if (n == 1) 
    { 
        printf("\n Move disk 1 from rod %c to rod %c", from_rod, to_rod); 
        return; 
    } 
    towerOfHanoi(n-1, from_rod, aux_rod, to_rod); 
    printf("\n Move disk %d from rod %c to rod %c", n, from_rod, to_rod); 
    towerOfHanoi(n-1, aux_rod, to_rod, from_rod); 
} 
  
int main() 
{ 
    int n = 4; // Number of disks 
    towerOfHanoi(n, 'A', 'C', 'B');  // A, B and C are names of rods 
    return 0; 
} 




// ############# HAMMING NUMBERS (DIVISIBLE BY 2 or 3 or 5 ##########
string min3(int a, int b, int c) {
	if (a <= b && a <= c) {
		return "twos";
	}
	else if (b <= a && b <= c) {
		return "threes";
	}
	else if (c <= a && c <= b) {
		return "fives";
	}
}


int main()
{
	/*
	string expr = "12+345/-*";
	cout << expr << " = " << evalPostfix(expr) << endl;

	string expr2 = "*+12-3/45";
	cout << expr2 << " = " << evalPrefix(expr2) << endl;
	*/

	queue<int> twos;
	queue<int> threes;
	queue<int> fives;
	int n;
	cin >> n;

	for (int i = 2; i <= n; i+=2) {
		twos.push(i);
	}
	for (int i = 3; i <= n; i+=3) {
		threes.push(i);
	}
	for (int i = 5; i <= n; i+=5) {
		fives.push(i);
	}

	list<int> result;
	result.push_back(1);
	while (!twos.empty() || !threes.empty() || !fives.empty()) {
		int a, b, c;

		if (twos.empty()) {
			a = INT_MAX;
		}
		else {
			a = twos.front();
		}

		if (threes.empty()) {
			b = INT_MAX;
		}
		else {
			b = threes.front();
		}

		if (fives.empty()) {
			c = INT_MAX;
		}
		else {
			c = fives.front();
		}

		int last = result.back();
		if (min3(a, b, c) == "twos") {
			if (last == twos.front()) {
				twos.pop();
				continue;
			}

			result.push_back(twos.front());
			twos.pop();
		}
		else if (min3(a, b, c) == "threes") {
			if (last == threes.front()) {
				threes.pop();
				continue;
			}

			result.push_back(threes.front());
			threes.pop();
		}
		else {
			if (last == fives.front()) {
				fives.pop();
				continue;
			}

			result.push_back(fives.front());
			fives.pop();
		}
	}

	for (auto& it : result) {
		cout << it << " ";
	}
  
    return 0;
}