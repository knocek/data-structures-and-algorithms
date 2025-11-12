#include <iostream>
#include <windows.h>
#include <ctime>

/*  ROUND ROBIN QUEUE SIMULATION  */

class Queue {
public:
    Queue() : head(nullptr), tail(nullptr), nodeCount(0) {} // constructor
    ~Queue() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        nodeCount = 0;
    }; // destructor

    int size(); // size of queue
	bool empty(); // check if queue is empty
    void pushBack(int id, int burst); // add element to the end of queue
    void popFront(); // remove element from the front of queue
    void showQueue(); // display queue elements
    friend bool rrStep(Queue& q, int quantum, int& timeNow, int& ranPid, int& ranSlice, int& remBefore, int& remAfter);
	// RR step function

private:
    struct Node {
		int id; // process id
		int burst; // burst time
		int remaining; // remaining time
		Node* next; // pointer to next node
    };
    Node* head; 
    Node* tail;
    int nodeCount;

	// static helper functions for rrStep
    static Node* popFrontNode(Queue& q) {
		if (!q.head) return nullptr; // queue is empty
		Node* tmp = q.head; // remove front node
		q.head = q.head->next; // update head
		if (!q.head) q.tail = nullptr; // if queue is empty, update tail
		tmp->next = nullptr; // disconnect node
		--q.nodeCount; // decrease count
		return tmp; // return removed node
    }

	// push node to back of queue
    static void pushBackNode(Queue& q, Node* node) {
        node->next = nullptr;
		if (!q.head) { // queue is empty
            q.head = q.tail = node;
        }
		else {
            q.tail->next = node;
            q.tail = node;
        }
        ++q.nodeCount;
    }
};

int Queue::size() {
    return nodeCount;
}

bool Queue::empty() {
	return nodeCount == 0;
}

void Queue::pushBack(int id, int burst) {
    // new node to assign values
    Node* node = new Node;
    node->id = id;
    node->burst = burst;
	node->remaining = burst;
    node->next = nullptr;

    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        tail = node;
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
            std::cout << "ID: " << cur->id 
				<< ", burst: " << cur->burst
				<< ", remaining: " << cur->remaining
                << "\n";
        }
    }

    std::cout << "\n-------------------\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

bool rrStep(Queue& q, int quantum, int& timeNow, int& ranPid, int& ranSlice, int& remBefore, int& remAfter) {
	if (q.empty() || quantum <= 0) return false;

	Queue::Node* current = Queue::popFrontNode(q); // get front node
	ranPid = current->id; // process id
	remBefore = current->remaining; // remaining time before execution

	// if procces not finished
	if (current->remaining > quantum) {
		timeNow += quantum; // advance time
		current->remaining -= quantum;
		ranSlice = quantum; // time slice used
        remAfter = current->remaining; // remaining time after execution
		Queue::pushBackNode(q, current); // re-add to back of queue
	}
	else {
		timeNow += current->remaining;
		ranSlice = current->remaining; // time slice used
		remAfter = 0; // remaining time after execution
		current->remaining = 0;
		delete current; // process finished
		current = nullptr;
	}
	return true;
}

int main() {
    Queue queue1;
    srand((unsigned)time(nullptr));

    int quantum = 4; // quant if time
    int timeNow = 0; // clock
	int nextId = 1; // id process
	int maxArrivals = 5; // max number of procces
    int arrivals = 0;

	std::cout << "Quantum = " << quantum << "\n"; // info of quantum

    while (arrivals < maxArrivals || !queue1.empty()) {
        // max 5 process 
        if (arrivals < maxArrivals) {
            int random = rand() % 2;                 
            int randomBurst = (rand() % 20) + 10;    // time of process
            
            // if new process
            if (random == 0) {
                queue1.pushBack(nextId, randomBurst);
                std::cout << "New process: ID -> " << nextId
                    << " (burst=" << randomBurst << ")\n";
                ++nextId;
                ++arrivals;
            }
        }

		// if queue not empty, RR step
        if (!queue1.empty()) {
            int id, slice, before, after;
            bool did = rrStep(queue1, quantum, timeNow, id, slice, before, after);
            if (did) {
                std::cout << "[t=" << (timeNow - slice) << "] Runned " << id
                    << " for " << slice
                    << " (rem before=" << before
                    << ", after=" << after << ")\n";
            }
        }
        else {
            std::cout << "[t=" << timeNow << "] no processes\n";
        }

        queue1.showQueue();
        std::cout << "NEXT ROUND\n";
        Sleep(800); 
    }

    std::cout << "\nAll processes finished at t=" << timeNow << ".\n";
    return 0;
}
