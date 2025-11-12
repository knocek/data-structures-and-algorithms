#include <iostream>
#include <windows.h>
#include <ctime>

/*
FIFO QUEUE SIMULATION
*/

class Queue {
public:
    Queue() : head(nullptr), tail(nullptr), nodeCount(0) {} // constructor
    ~Queue() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }; // destructor

    int size(); // size of queue
    void pushBack(int id, int priority); // add element to the end of queue
    void popFront(); // remove element from the front of queue
    void showQueue(); // display queue elements

private:
    struct Node {
        int id;
        int priority;
        Node* next;
    };
    Node* head;
    Node* tail;
    int nodeCount;
};

int Queue::size() {
    return nodeCount;
}

void Queue::pushBack(int id, int priority) {
	// new node to assign values
    Node* node = new Node;
    node->id = id;
	node->priority = priority;
    node->next = nullptr;

	// priority higher than head or empty queue insert at front
	// lower number == higher priority
    if (!head || priority < head->priority) {
        node->next = head;
        head = node;
        if (!tail) tail = node;
    }
    // priority lower or equal than tail 
    // fifo for equal priorities
    else {
        Node* cur = head;
        while (cur->next && cur->next->priority <= priority) {
            cur = cur->next;
        }

        // insert new node after cur
        node->next = cur->next;
        cur->next = node;

		// inserted at the end => update tail
        if (!node->next) tail = node; 
    }
    ++nodeCount;
};

void Queue::popFront() {
    if (!head) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    Node* tmp = head;
    head = head->next;
    if (!head) tail = nullptr;
    delete tmp;
    --nodeCount;

};

void Queue::showQueue()
{
    //system("CLS");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    std::cout << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "QUEUE ELEMENTS: " << std::endl;
    std::cout << "-------------------" << std::endl;


    if (!head) {
        std::cout << "empty queue";
    }
    else {
        for (Node* cur = head; cur; cur = cur->next) {
            std::cout << "ID: " << cur->id << ", priority: " << cur->priority << "\n";
        }
    }

    std::cout << "\n-------------------\n\n";


    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int main()
{
    Queue queue1;
    int random, randomPriority = 0;
    srand(time(0));
    int i = 0;

    do {
        random = rand() % 2; // random 0 or 1
		randomPriority = rand() % 3 + 1; // random priority between 1 and 4

        if (random == 0) {
            queue1.pushBack((i + 1), randomPriority);
            std::cout << "New customer in queue. ID: " << i + 1 << ", priority: " << randomPriority << std::endl;
            i++;
        }
        else if (random == 1 && queue1.size() != 0) {
            queue1.popFront();
            std::cout << "Customer served.\n";
        }
        else {
            std::cout << "Nothing happend to your queue.\n";
        }

        queue1.showQueue();
        std::cout << "\n\n--------------\n";
        std::cout << "NEXT ROUND OF LOOP\n";

        Sleep(1000);
    } while (i < 10);

    while (queue1.size() != 0) {
        queue1.popFront();
        std::cout << "Customer served.\n";
    }
    queue1.showQueue();

}
