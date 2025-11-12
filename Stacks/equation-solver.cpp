#include <iostream>
using namespace std;

// stack using pointers
struct MyStack {
    int topVal;
    MyStack* next;
};

// max size of stack: 100
const int MAX_SIZE = 100;
int counter = 0;

// add element to stack
void push(MyStack*& top, int val) {
    if (counter >= MAX_SIZE) {
        cout << "Stack overflow! max size of stack: " << MAX_SIZE << endl;
        return;
    }

    MyStack* newNode = new MyStack;
    if (newNode == nullptr) {
        printf("Stack overflow!");
        return;
    }
    newNode->topVal = val;
    newNode->next = top; // new node points to previous top
    top = newNode;       // move top of the stack
    counter++;
}

// delete from top and return value, if empty return fail
int pop(MyStack*& top) {
    if (top == nullptr) {
        cout << "Stack underflow!" << endl;
        return -1;
    }
    int poppedVal = top->topVal; // save the value stored at the top
    MyStack* temp = top; // temp store current top
    top = top->next; // move top pointer to the next node in stack
    delete temp; // free memory from old top node
    counter--;
    return poppedVal; // return new top pointer
}

// return element from the top, not delete it, if fail return fail
int top(MyStack* top) {
    if (top == nullptr) {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    return top->topVal;
}

// return true if empty
bool isEmpty(MyStack* top) {
    return (top == nullptr);
}

// function to return precedence of operators
int precedence(int operators) {
    if (operators == '+' || operators == '-') return 1;
    if (operators == '*' || operators == '/') return 2;
    return 0;
}

// function to perform arithmetic operations
int applyOp(int a, int b, int operators) {
    switch (operators) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
    return 0;
}

// function to perform a single reduction
void reduceOnce(MyStack*& values, MyStack*& operators) {
    int op = pop(operators);
    int b = pop(values);
    int a = pop(values);
    push(values, applyOp(a, b, op)); // wynik z powrotem na stos wartości
}

int evaluate(const string& s) {
    MyStack* values = nullptr; // stack for numbers
    MyStack* operators = nullptr; // stack for operators

	// loop through string
    for (size_t i = 0; i < s.size();) {
		if (isspace(s[i])) { ++i; continue; } // skip spaces

		// if digit, parse number
        if (isdigit(s[i])) {
            int val = 0;
            while (i < s.size() && isdigit(s[i])) {
                val = val * 10 + (s[i] - '0'); // convert char to int
                ++i;
            }
            push(values, val); // put number to stack
            continue;
        }

        char c = s[i];
        if (c == '(') {
            push(operators, (int)c);
            ++i;
        }
        else if (c == ')') {
			// solve brace, count until (
            while (!isEmpty(operators) && top(operators) != '(') {
                reduceOnce(values, operators); // pop operator
            }
			pop(operators); // remove '('
            ++i;
        }
		else { // operator + - * /
            while (!isEmpty(operators) && top(operators) != '(' &&
                precedence(top(operators)) >= precedence(c)) {
                reduceOnce(values, operators); 
            }
            push(operators, (int)c); 
            ++i;
        }
    }

    while (!isEmpty(operators)) {
        reduceOnce(values, operators);
    }

	return pop(values); // final result
}


int main (){

    string equation;
    cout << "Enter equation: ";
    cin >> equation;

	int result = evaluate(equation);
	cout << "Result: " << result << endl;

	return 0;
}
