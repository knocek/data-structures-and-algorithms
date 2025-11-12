#include <iostream>
#include <windows.h>
#include <thread>

/*

ELEVATOR SYSTEM
-2 different queues for up and down
-if elevator goes in one direction, it couldnot change director untill reach tle lowest or the higest floor
-when elevator go up and reach the highest floor, it couldnt serve up requests
-when elevator reach the lowest floor, it couldnt serve down requests

*/

// double linked list node
class Node {
public:
    int value;
	Node* next; // pointer to nxt node
	Node* prev; // pointer to prev node

	Node(int val) : value(val), next(nullptr), prev(nullptr) {} // constructor
};

class CustomQueue {
private:
    Node* head;
    Node* tail;
    int size;

public:
    CustomQueue() : head(nullptr), tail(nullptr), size(0) {}

    ~CustomQueue() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void push(int value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Queue is empty.\n";
            return -1;
        }
        Node* temp = head;
        int value = temp->value;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    int peek() const {
        if (isEmpty()) {
            std::cout << "Queue is empty.\n";
            return -1;
        }
        return head->value;
    }

    int getSize() const {
        return size;
    }

	// bubble sort for ascending order
    // how bubble sort works? 
	// step through list, compare pair and swap if out of order
    void sortAscending() {
        if (size > 1) {
            bool swapped;
            do {
                swapped = false;
                Node* current = head;
                while (current != nullptr && current->next != nullptr) {
                    if (current->value > current->next->value) {
                        std::swap(current->value, current->next->value);
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }
    }

	// bubble sort for descending order
    void sortDescending() {
        if (size > 1) {
            bool swapped;
            do {
                swapped = false;
                Node* current = head;
                while (current != nullptr && current->next != nullptr) {
                    if (current->value < current->next->value) {
                        std::swap(current->value, current->next->value);
                        swapped = true;
                    }
                    current = current->next;
                }
            } while (swapped);
        }
    }
};

class ElevatorSystem {
private:
    int currentFloor;
	bool movingUp; // true - up, false - down
    CustomQueue upQueue;   // queue to up
	CustomQueue downQueue; // queue to down

public:
    ElevatorSystem() : currentFloor(0), movingUp(true) {}

	// add request to good queue
    void request(int floor) {
		// if floor higher than currentFloor add to upQueue
        if (floor > currentFloor) {
            upQueue.push(floor);
            std::cout << "ADDED -> UP " << floor << "\n";
        }
		// if floor lower add to downQueue
        else if (floor < currentFloor) {
            downQueue.push(floor);
            std::cout << "ADDED -> DOWN " << floor << "\n";
        }
        else {
            std::cout << "elevator is ALREADY AT floor " << floor << "\n";
        }
    }

	// process requests in the right order
    void processRequests() {
		// while requests in queues
        while (!upQueue.isEmpty() || !downQueue.isEmpty()) {
            if (movingUp) {
                std::cout << "\nElevator goes up.\n";
                processUpQueue();
				movingUp = false; // if go to the highest floor change direction
            }
            else {
                std::cout << "\nElevator goes down.\n";
                processDownQueue();
				movingUp = true; // if go to the lowest floor change direction
            }
        }
        std::cout << "\nElevator ended working. Now is on " << currentFloor << " floor.\n";
    }

    bool processStep() {
		// if no requests
        if (upQueue.isEmpty() && downQueue.isEmpty()) return false;

        if (movingUp) {
            if (!upQueue.isEmpty()) {
				upQueue.sortAscending(); // sort in ascending order
				moveToFloor(upQueue.pop()); // move to next up
            }
            else {
				// no more up requests change direction
                movingUp = false;
            }
        }
        else {
            if (!downQueue.isEmpty()) {
				downQueue.sortDescending(); // sort in descending order
				moveToFloor(downQueue.pop()); // move to next down
            }
            else {
				// no more down requests change direction
                movingUp = true;
            }
        }
		return !upQueue.isEmpty() || !downQueue.isEmpty(); // return true if requests left
    }


private:
    void processUpQueue() {
		upQueue.sortAscending(); // sort in ascending order to serve lowest first
		// serve all requests in upQueue 
        while (!upQueue.isEmpty()) {  
            moveToFloor(upQueue.pop());
        }
    }

    void processDownQueue() {
		downQueue.sortDescending(); // sort in descending order to serve highest first
        while (!downQueue.isEmpty()) {
            moveToFloor(downQueue.pop());
        }
    }

    void moveToFloor(int floor) {
        int step;

		if (floor > currentFloor) {
			step = 1; // going up
		}
		else {
			step = -1; // going down
		}

		// simulate moving
        while (currentFloor != floor) {
            currentFloor += step;
            std::cout << "Floor: " << currentFloor << std::endl;
            Sleep(800); // moving effect
        }

        std::cout << ">>> Stopped at " << floor << " floor.\n";
    }
};

// MAIN FUNCTION WAS 100% GENERATED BY AI //

int main() {
    ElevatorSystem elevator;

    elevator.request(3);
    elevator.request(13);

    int tick = 0;

    std::cout << "\n=== ELEVATOR SIMULATION ===\n";

    while (true) {
        tick++;
        std::cout << "\n--- STEP " << tick << " ---\n";

		// new dynamic requests
        if (tick == 2) {
            std::cout << "(New requests: floor 0 and 10)\n";
            elevator.request(0);
            elevator.request(10);
        }

        if (tick == 3) {
            std::cout << "(New request: 12 floor)\n";
            elevator.request(12);
        }

		// process one step
        bool hasWork = elevator.processStep();

        Sleep(500);

		if (!hasWork) {
			std::cout << "\nNo more requests.\n";
			break;
		}
    }

    return 0;
}
