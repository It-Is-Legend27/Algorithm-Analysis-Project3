// Angel Badillo, Samuel Olatunde
// CMPS 5243 270 - Project 3
// Description:
// This program constructs a Binary Search Tree and an AVL Tree from words
// in a text file. After constructing the trees, the program reports the height
// of each tree and the average node height of each tree.
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include "bst.hpp"
#include "avlt.hpp"

using namespace std;

int main()
{
	BinarySearchTree<string> bstree;
	AVLTree<string> avltree;
	ifstream infile("words.txt");
	string word;

	// Read in all words from file
	while (infile && infile >> word)
	{
		bstree.insert(word);
		avltree.insert(word);
	}

	cout << "Angel Badillo, Samuel Olatunde\n"
		 << "CMPS 5243 270 - Project 3\n"
		 << "Description:\n"
		 << "This program constructs a Binary Search Tree and an AVL Tree from words\n"
		 << "in a text file. After constructing the trees, the program reports the height\n"
		 << "of each tree and the average node height of each tree.\n";
		
	cout << string(100, '-') << "\n\n";

	// Print out heights of each tree
	cout << "Height of Binary Search Tree:              " << bstree.height() << '\n';
	cout << "Height of AVL Tree:                        " << avltree.height() << '\n';

	// Print out average node heights of each tree
	cout << "Average Node Height of Binary Search Tree: " << bstree.average_height() << '\n';
	cout << "Average Node Height of AVL Tree:           " << avltree.average_height() << '\n';

	// Print out total number of nodes in each tree
	cout << "Number of Nodes in Binary Search Tree:     " << bstree.size() << '\n';
	cout << "Number of Nodes in AVL Tree:               " << avltree.size() << '\n';
	
	return 0;
}