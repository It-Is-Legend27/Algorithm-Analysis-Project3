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
	avl_tree<string> bstree;
	ifstream infile("words.txt");
	string word;

	while(infile && infile >> word)
	{
		bstree.insert(word);
	}

	cout << "Nodes printed in order:  \n";
	bstree.in_order_print();
	cout << '\n';
	cout << "Nodes printed pre-order:  \n";
	bstree.pre_order_print();
	cout << '\n';
	cout << "Nodes printed in post-order:  \n";
	bstree.post_order_print();
	cout << '\n';
	bstree.graph_viz("mygraph.dot");
	return 0;
}