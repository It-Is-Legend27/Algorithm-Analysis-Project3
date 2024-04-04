#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include "bst.hpp"

using namespace std;

int main()
{
	BinarySearchTree<string> b;
	int num, x;
	srand(unsigned(time(NULL)));
	cout << "Nodes as they are inserted:  \n\n";
	for (int i = 0; i < 10; i++)
	{
		num = rand() % 100;
		cout << num << "  ";
		b.insert(to_string(num));
	}
	cout << endl;
	cout << "What number to you want to search for? ";
	cin >> x;
	if (b.search(to_string(x)))
		cout << "The number is in the list. \n";
	else
		cout << "The number is not in the list. \n";
  b.inOrderPrint();
  cout << "What number do you want to delete? ";
  cin >> x;
  b.deleteItem(to_string(x));
  b.inOrderPrint();
	cout << endl << endl;
	cout << "Nodes printed in order:  \n";
	b.inOrderPrint();
	cout << endl;
	cout << "Nodes printed pre-order:  \n";
	b.preOrderPrint();
	cout << endl;
	cout << "Nodes printed in post-order:  \n";
	b.postOrderPrint();
	cout << endl;
	b.GraphVizOut("mygraph.dot");
	return 0;
}