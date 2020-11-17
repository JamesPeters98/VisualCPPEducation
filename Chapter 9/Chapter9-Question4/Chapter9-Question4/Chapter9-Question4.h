#pragma once
#include <cstdarg>
#include <iostream>

class BinaryTree
{
	
	class Node
	{
	public:
		int value;
		Node* left = nullptr;
		Node* right = nullptr;

		void insert(int value);
		static Node* insert(Node* node, int& val);
		void print();
	};

private:
	Node* rootNode{};

public:
	BinaryTree() = default;
	void insert(int value);

	BinaryTree(int rootValue)
	{
		rootNode = new Node{ rootValue };
	}

	void print()
	{
		rootNode->print();
	}

};