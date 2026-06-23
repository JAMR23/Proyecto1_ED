#pragma once
#include <stdexcept>
#include <iostream>
#include "StackNode.h"
#include "Stack.h"

using std::cout;
using std::endl;
using std::runtime_error;

template <typename E>
class LinkedStack : public Stack<E> {
private:
	StackNode<E>* top;
	int size;

public:
	LinkedStack() {
		size = 0;
		top = nullptr;
	}
	~LinkedStack() {
		clear();
	}
	void push(E element) {
		top = new StackNode<E>(element, top);
		size++;
	}
	E pop() {
		if (size == 0)
			throw runtime_error("Stack is empty.");
		E result = top->element;
		StackNode<E>* temp = top;
		top = top->next;
		delete temp;
		size--;
		return result;
	}
	E topValue() {
		if (size == 0)
			throw runtime_error("Stack is empty.");
		return top->element;
	}

	void clear() {
		StackNode<E>* temp;
		while (size > 0) {
			temp = top;
			top = top->next;
			delete temp;
		}
		size = 0;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getSize() {
		return size;
	}
	void print() {
		cout << "[ ";
		StackNode<E>* temp = top;
		while (temp != nullptr) {
			cout << temp->element;
			if (temp->next != nullptr)
				cout << ", ";
			temp = temp->next;
		}
		cout << " ]" << endl;
	}

};

