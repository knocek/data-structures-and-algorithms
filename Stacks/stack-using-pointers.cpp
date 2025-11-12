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

// return true if full
bool isFull(MyStack* top) {
    return counter >= MAX_SIZE;
}

// free memory
void freeStack(MyStack*& top) {
    while (top != nullptr) {
        MyStack* temp = top;
        top = top->next;
        delete temp;
    }
    counter = 0;
}

int main()
{
    MyStack* s = nullptr;
    cout << "Empty? " << (isEmpty(s) ? "yes" : "no") << "\n";
    push(s, 10);
    push(s, 20);

    cout << "Top = " << top(s) << "\n";

    cout << "Popped = " << pop(s) << "\n";
    cout << "Top = " << top(s) << "\n";
    cout << "Push 100";
    push(s, 100);
    cout << "\n";
    cout << "Top = " << top(s) << "\n";
    cout << "Empty? " << (isEmpty(s) ? "yes" : "no") << "\n";

    freeStack(s);
    return 0;
}
