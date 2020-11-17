// Chapter9-Question4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Chapter9-Question4.h"

int main()
{
	BinaryTree tree;

	for (int i{}; i < 100; i++)
		tree.insert(rand() % 100);

	tree.print();
}

// Inserts a value into the binary tree
void BinaryTree::insert(int value)
{
	if(!rootNode)
	{
		rootNode = new Node{ value };
		return;
	}
	rootNode->insert(value);
}

// Inserts a value into this node, or passes along to child nodes if it already contains a value.
void BinaryTree::Node::insert(int value)
{
	if (value >= this->value)
	{
		right = Node::insert(right, value);
	} else
	{
		left = Node::insert(left, value);
	}
}

// Static method to create a new node if the pointer is null, or call the insert function for that node.
// Returns the pointer to the node used or created.
BinaryTree::Node* BinaryTree::Node::insert(Node* node, int& val)
{
	if (node)
		node->insert(val);
	else
		node = new Node{ val };
	return node;
}

// Prints the tree in ascending order.
void BinaryTree::Node::print()
{
	if (left) left->print();
	std::cout << value << std::endl;
	if (right) right->print();
}