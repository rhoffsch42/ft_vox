#include "Node.hpp"
unsigned int Node::amount = 0;

Node::Node(int v) {
	this->value = v;
	this->left = nullptr;
	this->right = nullptr;

	Node::amount++;
}

int	Node::contain(int v) const {
	const Node* current = this;
	int test = 0;
	while (current) {
		test++;
		if (current->value == v) {
			return test;
		} else if (v <= current->value) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return -test;
}

void	Node::insert(int v) {
	bool inserted = false;
	Node* current = this;

	while (inserted == false) {
		if (v <= current->value) {
			if (current->left) {
				current = current->left;
			} else {
				current->left = new Node(v);
				inserted = true;
			}
		} else {
			if (current->right) {
				current = current->right;
			} else {
				current->right = new Node(v);
				inserted = true;
			}
		}
	}
}

