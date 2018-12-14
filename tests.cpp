#include <iostream>
#include <cassert>

#include "AVLTree.hpp"

int main() {
	AVLTree<int> tree;

	std::cout << "Tests empty tree: ";

	assert(tree.GetSize() == 0);
	assert(tree.GetHeight() == 0);

	std::cout << "OK" << std::endl;

	std::cout << "Tests of insert: ";
	tree.Insert(1);

	assert(tree.GetSize() == 1);
	assert(tree.GetHeight() == 1);
	assert(tree.Find(1));
	assert(!tree.Find(0));
	assert(!tree.Find(2));

	tree.Insert(2);
	tree.Insert(3);
	tree.Insert(4);
	tree.Insert(5);
	tree.Insert(6);


	assert(tree.GetSize() == 6);
	assert(tree.GetHeight() == 3);
	assert(tree.Find(1));
	assert(!tree.Find(0));
	assert(tree.Find(2));
	assert(tree.Find(3));
	assert(tree.Find(4));
	assert(tree.Find(5));
	assert(tree.Find(6));
	assert(!tree.Find(7));

	std::cout << "OK" << std::endl;

	std::cout << "Tests of remove: ";

	tree.Remove(4);

	assert(tree.GetSize() == 5);
	assert(tree.GetHeight() == 3);
	assert(tree.Find(1));
	assert(!tree.Find(0));
	assert(tree.Find(2));
	assert(tree.Find(3));
	assert(!tree.Find(4));
	assert(tree.Find(5));
	assert(tree.Find(6));
	assert(!tree.Find(7));

	tree.Remove(6);

	assert(tree.GetSize() == 4);
	assert(tree.GetHeight() == 3);
	assert(tree.Find(1));
	assert(!tree.Find(0));
	assert(tree.Find(2));
	assert(tree.Find(3));
	assert(!tree.Find(4));
	assert(tree.Find(5));
	assert(!tree.Find(6));
	assert(!tree.Find(7));

	tree.Remove(2);

	assert(tree.GetSize() == 3);
	assert(tree.GetHeight() == 2);
	assert(tree.Find(1));
	assert(!tree.Find(0));
	assert(!tree.Find(2));
	assert(tree.Find(3));
	assert(!tree.Find(4));
	assert(tree.Find(5));
	assert(!tree.Find(6));
	assert(!tree.Find(7));

	std::cout << "OK" << std::endl;
}