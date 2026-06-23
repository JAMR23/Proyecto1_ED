// Autor: Mauricio Avilés
// Fecha: 12/05/2026
// Descripción: Implementacion de una lista enlazada simple
//				usando nodos, deriva de la lista.

#pragma once
#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Node.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedList : public List<E> {
private:
	Node<E>* head;
	Node<E>* tail;
	Node<E>* current;
	int size;

public:
	LinkedList() {
		head = tail = current = new Node<E>();
		size = 0;
	}
	~LinkedList() {
		clear();
	}
	void insert(E element) {
		current->next = new Node<E>(element, current->next);
		if (current == tail)
			tail = tail->next;
		size++;
	}
	void append(E element) {
		tail = tail->next = new Node<E>(element, nullptr);
		size++;
	}
	void setElement(E element) {
		if (size == 0)
			throw runtime_error("ERROR: List is empty.");
		if (current == tail)
			throw runtime_error("ERROR: No current element.");
		current->next->element = element;
	}
	E getElement() {
		if (size == 0)
			throw runtime_error("ERROR: List is empty.");
		if (current == tail)
			throw runtime_error("ERROR: No current element.");
		return current->next->element;
	}
	E remove() {
		if (size == 0)
			throw runtime_error("ERROR: List is empty.");
		if (current == tail)
			throw runtime_error("ERROR: No current element.");
		E res = current->next->element;
		Node<E>* temp = current->next;
		current->next = temp->next;
		delete temp;
		size--;
		if (current->next == nullptr)
			tail = current;
		return res;
	}
	void clear() {
		current = head->next;
		while (head->next != nullptr) {
			head->next = current->next;
			delete current;
			current = head->next;
			size--;
		}
		tail = current = head;
	}
	void goToStart() {
		current = head;
	}
	void goToEnd() {
		current = tail;
	}
	void goToPos(int pos) {
		if (pos > size or pos < 0)
			throw runtime_error("ERROR: Index out of bounds.");
		current = head;
		for (int i = 0; i != pos; i++) {
			current = current->next;
		}
	}
	void next() {
		if (current != tail)
			current = current->next;
	}
	void previous() {
		if (current != head) {
			Node<E>* temp = head;
			while (temp->next != current) {
				temp = temp->next;
			}
			current = temp;
		}
	}
	bool atStart() {
		return current == head;
	}
	bool atEnd() {
		return current == tail;
	}
	int getPos() {
		int pos = 0;
		Node<E>* temp = head;
		while (temp != current) {
			temp = temp->next;
			pos++;
		}
		return pos;
	}
	int getSize() {
		return size;
	}
	void print() {
		Node<E>* temp = head->next;
		cout << "[ ";
		while (temp != nullptr) {
			cout << temp->element;
			if (temp == tail)
				cout << " ";
			else
				cout << ", ";
			temp = temp->next;
		}
		cout << "]" << endl;
	}
};