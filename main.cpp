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
	int num, x;
	srand(unsigned(time(NULL)));
	cout << "Nodes as they are inserted:  \n\n";
	for (int i = 0; i < 10; i++)
	{
		num = rand() % 100;
		cout << num << "  ";
		bstree.insert(to_string(num));
	}
	cout << endl;
	cout << "What number to you want to search for? ";
	cin >> x;
	if (bstree.search(to_string(x)))
		cout << "The number is in the list. \n";
	else
		cout << "The number is not in the list. \n";
	bstree.inOrderPrint();
	cout << "What number do you want to delete? ";
	cin >> x;
	bstree.deleteItem(to_string(x));
	bstree.inOrderPrint();
	cout << endl
		 << endl;
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