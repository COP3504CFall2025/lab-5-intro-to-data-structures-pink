#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
    	Node* next;
	};
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;
	// Behaviors
	public:
	void printForward() const {
		Node* huh = head;
		while (huh) {
			std::cout << huh->data << std::endl;
			huh = huh->tail;
		}
	}
	void printReverse() const {
		Node* huh = tail;
		while (huh) {
			std::cout << huh->data << std::endl;
			huh = huh->head;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		head = new Node(data, nullptr, head);
		if (head->next) {
			head->next->prev = head;
		}
		count++;
	}
	void addTail(const T& data) {
		tail = new Node(data, tail, nullptr);
		if (tail->prev) {
			tail->prev->next = tail;
		}
		count++;
	}

	// Removal
	bool removeHead() {
		if (!head) {
			return false;
		}
		Node* temp = head->next;
		delete head;
		head = temp;
		count--;
		return true;
	}
	bool removeTail() {
		if (!tail) {
			return false;
		}
		Node* temp = tail->prev;
		delete tail;
		tail = temp;
		count--;
		return true;
	}
	void clear() {
		Node* die = head;
		while (die) {
			Node* temp = head->next;
			delete tail;
			die = temp;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (other.head == head) {
			return *this;
		}
		clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		LinkedList<T> temp;
		Node* copy = rhs.head;
		while (copy) {
			temp.addTail(copy->data);
			copy = copy->next;
		}
		clear();
		head = temp.head;
		tail = temp.tail;
		count = temp.count;
		temp.head = nullptr;
		temp.tail = nullptr;
		temp.count = 0;
		return *this;
	}
	
	// Construction/Destruction
	LinkedList() : count(0), head(nullptr), tail(nullptr){}

	LinkedList(const LinkedList<T>& list) {
		Node* curr = list.head;
		if (curr) head = new Node(curr->data, nullptr, nullptr);
		while (curr->next) {
			addTail(curr->next->data);
			curr = curr->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count){
		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}
	~LinkedList() {
		clear();
	}

};


