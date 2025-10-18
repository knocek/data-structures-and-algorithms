#include <iostream>
using namespace std;

const int MAX = 100;

class MyStack {
    int topVal;
    int a[MAX];

public:
    MyStack() {
        topVal = -1;
    }
    void push(int val);
    int pop();
    int top();
    bool isEmpty();
    bool isFull();
};

// add element to stack
void MyStack::push(int val) {
    if (topVal >= MAX-1) {
        printf("Stack overflow!");
        return;
    }
    else {
        topVal++;
        a[topVal] = val;
    }
}

// delete from top and return value, if empty return fail
int MyStack::pop() {
    if (topVal < 0) {
        cout << "Stack underflow!" << endl;
        return -1;
    }
    return a[topVal--];
}

// return element from the top, not delete it, if fail return fail
int MyStack::top() {
    if (topVal < 0) {
        cout << "Stack is empty!" << endl;
        return -1;
    }
    return a[topVal];
}

// return true if empty
bool MyStack::isEmpty() {
    return (topVal < 0);
}

// return true if full
bool MyStack::isFull() {
    return (topVal >= MAX - 1);
}

int main()
{
    MyStack s;
    cout << "Empty? " << (s.isEmpty() ? "yes" : "no") << "\n";
    s.push(10);
    s.push(20);
    cout << "Top = " << s.top() << "\n";
    cout << "Popped = " << s.pop() << "\n";
    cout << "Top = " << s.top() << "\n";
    cout << "Push 100";
    s.push(100);
    cout << "\n";
    cout << "Top = " << s.top() << "\n";
    cout << "Empty? " << (s.isEmpty() ? "yes" : "no") << "\n";
}
