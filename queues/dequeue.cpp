#include <iostream>
#include <windows.h>

/*  DEQUE WITH PRIORITY, LIFO  */

class Deque {
private:
	struct Node {
		int id; // task ID
		bool highPriority; // priority of task
		Node* next; // pointer to next node
		Node* prev; // pointer to previous node
	};

	Node* head;
	Node* tail;
	int counter;

public:
	Deque() : head(nullptr), tail(nullptr), counter(0) {};
	~Deque() {
		while (head) {
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		tail = nullptr;
		counter = 0;
	}

	bool empty() const; // check if empty
	int size() const; // return size
	void pushFrontLifo(int id); // add to front - high priority - LIFO
	void pushFrontFifo(int id); // add to front - high priority - FIFO 
	void pushBack(int id); // add to back - low priority
	void popFront(); // delete from front
	void popBack(); // delete from back
	void showQueue() const; // display deque

};

bool Deque::empty() const {
	return counter == 0;
}

int Deque::size() const {
	return counter;
}

void Deque::pushFrontLifo(int id) {
	Node* node = new Node{ id, true, head, nullptr };
	
	if (head) head->prev = node; // update previous head prev
	head = node; // update head to new node

	if (!tail) tail = node; // if tail null set tail to new node
	++counter;
}

void Deque::pushFrontFifo(int id) {
	Node* node = new Node{ id, true, nullptr, nullptr };
	if (!head) {
		head = tail = node;
	}
	else if (!head->highPriority) {
		node->next = head;
		head->prev = node;
		head = node;
	}
	else {
		Node* cur = head; // find last high priority
		while (cur->next && cur->next->highPriority) {
			cur = cur->next;
		}
		node->next = cur->next; // insert after cur
		node->prev = cur; // set prev to cur
		cur->next = node; // update cur next
		if (node->next) node->next->prev = node; // update next node prev
		else tail = node;
	}
	++counter;
}

void Deque::pushBack(int id) {
	Node* node = new Node{ id, false, nullptr, tail};
	if (tail) tail->next = node; // update previous tail next
	tail = node; // update tail to new node
	if (!head) head = node; // if head null set head to new node
	++counter;
}

void Deque::popFront() {
	if (empty()) {
		std::cout << "Empty queue.\n";
		return;
	}
	Node* tmp = head;
	head = head->next; 
	if (head) head->prev = nullptr;
	else tail = nullptr;

	delete tmp;
	--counter;
}

void Deque::popBack() {
	if (empty()) {
		std::cout << "empty queue.\n";
		return;
	}
	Node* tmp = tail;
	tail = tail->prev;
	if (tail) tail->next = nullptr;
	else head = nullptr;

	delete tmp;
	--counter;
}

void Deque::showQueue() const {
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	std::cout << std::endl;
	std::cout << "-------------------" << std::endl;
	std::cout << "QUEUE ELEMENTS: " << std::endl;
	std::cout << "-------------------" << std::endl;


	if (!head) {
		std::cout << "Empty queue";
	}
	else {
		for (Node* cur = head; cur; cur = cur->next) {
			std::cout << "ID: " << cur->id << ", priority: ";
			if (cur->highPriority == 1) { std::cout << "high priority\n"; }
			else { std::cout << "normal priority\n"; }
		}
	}

	std::cout << "\n-------------------\n\n";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int main()
{
    std::cout << "Deque\n";

	Deque d1;
	int nextId = 1;
	int choice;

	do {
		d1.showQueue();
		std::cout << "1. Add to front (high priority) - LIFO\n";
		std::cout << "2. Add to front (high priority) - FIFO\n";
		std::cout << "3. Add to back (normal priority)\n";
		std::cout << "4. Remove from front\n";
		std::cout << "5. Remove from back\n";
		std::cout << "0. Exit\n";
		std::cout << "Choice: ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			d1.pushFrontLifo(nextId++);
			break;
		case 2:
			d1.pushFrontFifo(nextId++);
			break;
		case 3:
			d1.pushBack(nextId++);
			break;
		case 4:
			if (d1.size()>0) {
				d1.popFront();
			}
			else {
				std::cout << "Queue is empty. Cannot delete.\n";
			}
			Sleep(1000);
			break;
		case 5:
			if (d1.size()>0) {
				d1.popBack();
			}
			else {
				std::cout << "Queue is empty. Cannot delete.n";
			}
			Sleep(1000); 
			break;
		case 0:
			break;
		default:
			std::cout << "Invalid choice.\n";
			Sleep(1000);
			break;
		}

	} while (choice != 0);

	return 0;

}
