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

// show stack
void display(MyStack* top) {
    if (top == nullptr) {
        cout << "Stack is empty.\n";
        return;
    }

    MyStack* current = top; // start from top without changing original
    while (current != nullptr) {
        cout << current->topVal << " ";
        current = current->next; // go to next stack element
    }
    cout << endl;
}


// reverse elements from stack using other stack
void reverseUsingAnotherStack(MyStack*& top) {
    MyStack* temp1 = nullptr; // set pointer to null
    MyStack* temp2 = nullptr; // set pointer to null

    // from bottom to top - stack is reversed
    while (!isEmpty(top)) {
        push(temp1, pop(top));
    }

    // from bottom to top - stack is good
    while (!isEmpty(temp1)) {
        push(temp2, pop(temp1));
    }

    // from bottom to top - stack is reversed :))
    while (!isEmpty(temp2)) {
        push(top, pop(temp2));
    }
}

// reverse elements from stack without using other stack - using recursion
void insertAtBottom(MyStack*& top, int val) {
    // if stack is empty push directly
    if (isEmpty(top)) {
        push(top, val);
        return;
    }

    int temp = pop(top); // delete top element and set temp as value of popped element
    insertAtBottom(top, val); // insert new value at the bottom
    push(top, temp); // push popped element back on top
}

void reverseWithoutAnotherStack(MyStack*& top) {
    if (isEmpty(top)) return; // stack is empty, no elements to reverse
    
    int temp = pop(top); // remove top element
    reverseWithoutAnotherStack(top); // reverse using recoursion
    insertAtBottom(top, temp); // insert removed element at the bottom
}


int main()
{

    MyStack* s = nullptr; // initialize empty stack
    MyStack* s1 = nullptr;
    for (int i = 0; i < 10; i++) {
        push(s, i);
        push(s1, i);
    }

    cout << "original stack s: ";
    display(s);

    reverseUsingAnotherStack(s);
    cout << "after reverse (using another stack): ";
    display(s);

    cout << "original stack s1: ";
    display(s1);

    reverseWithoutAnotherStack(s1);
    cout << "after reverse (without another stack): ";
    display(s1);

    return 0;

}
