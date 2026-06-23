#pragma once

template <typename E>
class StackNode {
public:
	E element;
	StackNode<E>* next;

	StackNode(E element, StackNode<E>* next = nullptr) {
		this->element = element;
		this->next = next;
	}

	StackNode(StackNode<E>* next = nullptr) {
		this->next = next;

	}
};

