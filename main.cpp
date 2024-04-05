#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include "bst.hpp"
// #include "avlt.hpp"

using namespace std;

int main()
{
	BinarySearchTree<string> bstree;
	ifstream infile("words.txt");
	string word;

	while(infile && infile >> word)
	{
		bstree.insert(word);
	}

	cout << "Nodes printed in order:  \n";
	bstree.inOrderPrint();
	cout << '\n';
	cout << "Nodes printed pre-order:  \n";
	bstree.preOrderPrint();
	cout << '\n';
	cout << "Nodes printed in post-order:  \n";
	bstree.postOrderPrint();
	cout << '\n';
	bstree.GraphVizOut("mygraph.dot");
	return 0;
}