// Angel Badillo, Samuel Olatunde
// CMPS 5243 270 - Project 3
// Description:
// Text here.
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
	while(infile && infile >> word)
	{
		bstree.insert(word);
		avltree.insert(word);
	}

	cout << "Nodes printed in order:  \n";
	bstree.in_order_print();
	avltree.in_order_print();

	cout << bstree.size() << '\n';
	cout << avltree.size() << '\n';
	return 0;
}