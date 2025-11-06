#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
public:
	struct Node {
    	T data;
		Node* prev;
    	Node* next;
	};
	// Behaviors
	void PrintForward() const {
		Node* huh = head;
		while (huh) {
			std::cout << huh->data << std::endl;
			huh = huh->tail;
		}
	}
	void PrintReverse() const {
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
	void AddHead(const T& data) {
		head->prev = new Node(data, nullptr, head);
		head = head->prev;
		count++;
	}
	void AddTail(const T& data) {
		tail->next = new Node(data, head, nullptr);
		tail = tail->next;
		count++;
	}

	// Removal
	bool RemoveTail() {
		if (!head) {
			return false;
		}
		Node temp = head->next;
		delete head;
		head = temp;
		count--;
		return true;
	}
	bool RemoveTail() {
		if (!tail) {
			return false;
		}
		Node temp = tail->prev;
		delete tail;
		tail = temp;
		count--;
		return true;
	}
	void clear() {
		Node* die = head;
		while (die) {
			Node temp = head->next;
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
		if (rhs.head = head) {
			return this;
		}
		LinkedList<T> temp;
		Node* copy = rhs.head;
		while (copy) {
			temp.AddTail(copy->data);
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

	LinkedList(const LinkedList<T>& list);
	LinkedList(LinkedList<T>&& other) noexcept : head(other.head), tail(other.tail), count(other.count){
		other.count() = 0;
		other.head = nullptr;
		other.tail = nullptr;
	}
	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


