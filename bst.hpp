// Header file for binary search tree class
#ifndef BST_TEMPLATE
#define BST_TEMPLATE
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// A binary search tree is a binary tree with the additional property
// that at any node, all values in the left subtree are less than or equal
// to the node and all nodes in the right subtree are greater than the node.

template <class T>
class BinarySearchTree
{
private:
	struct Node
	{
		T data{};
		Node *left{nullptr};
		Node *right{nullptr};

		Node() {}

		Node(T data, Node *left = nullptr, Node *right = nullptr) : data(this->data), left(this->left), right(this->right) {}
	};
	Node *root;

	// Recursive private function to insert a value into the tree
	void insertNode(Node *&ptr, T x);

	// Recursive private function to print an in order listing of nodes in tree
	void inOrder(Node *ptr) const;

	// Recursive private function to print a pre-order listing of nodes in tree
	void preOrder(Node *ptr) const;

	// Recursive private function to print a post-order listing of nodes in tree
	void postOrder(Node *ptr) const;

	// Pivate function to delete a node from tree that is pointed to by the
	// reference pointer ptr
	void del(Node *&ptr);

	// Recursive private function to delete node containing specific value, x
	void deleteNode(Node *&ptr, T x);

	// Recursive private function to delete all nodes in the tree
	void destroySubtree(Node *&ptr);

	bool searchItem(Node *ptr, T x);

	// Credit to:  Terry Griffin
	// Creates GraphViz code so the tree can be visualized.  Prints
	// unique node id's by traversing the tree.
	void GraphVizGetIds(Node *nodePtr, ofstream &VizOut);

	// Credit to:  Terry Griffin
	// Partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	void GraphVizMakeConnections(Node *nodePtr, ofstream &VizOut);

public:
	// Constructor
	BinarySearchTree();

	// Destructor - deallocates all memory by calling destroySubtree
	~BinarySearchTree();

	// Public function to insert item x into the tree; calls insertNode
	void insert(T x);

	// Public function to delete item x from the tree; calls deleteNode
	void deleteItem(T x);

	// Public function to delete all items from the tree
	void deleteAll();

	// Public function to print all nodes in order; calls inOrder
	void inOrderPrint();

	// Public function to print all nodes pre-order; calls preOrder
	void preOrderPrint();

	// Public function to print all nodes post order; calls postOrder
	void postOrderPrint();

	// Public function to search for an item in the tree
	bool search(T x);

	// Credit to:  Terry Griffin
	// Receives a filename and stores a GraphViz readable file;
	// calls 	GraphVizGetIds and GraphVizMakeConnections
	void GraphVizOut(string filename);
};

template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = nullptr;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	destroySubtree(root);
}

// destroySubtree recursively visits and deletes each node
// from the lowest level (leaves) up
template <class T>
void BinarySearchTree<T>::destroySubtree(Node *&ptr)
{
	if (ptr)
	{
		destroySubtree(ptr->left);
		destroySubtree(ptr->right);
		delete ptr;
		ptr = nullptr;
	}
}

template <class T>
void BinarySearchTree<T>::insertNode(Node *&ptr, T x)
{
	// If ptr points to nullptr, the insertion position has been found
	if (ptr == nullptr)
		ptr = new Node(x);

	// If ptr does not point to nullptr, decide whether to traverse
	// down the left subtree or right subtree by comparing value
	// to be inserted with current node.
	else if (x <= ptr->data) // Node should be inserted in left subtree
		insertNode(ptr->left, x);
	else // Node should be inserted in right subtree
		insertNode(ptr->right, x);
}

// Public function that passes root to private helper function, insertNode
template <class T>
void BinarySearchTree<T>::insert(T x)
{
	insertNode(root, x);
}

template <class T>
void BinarySearchTree<T>::inOrder(Node *ptr) const
{
	if (ptr) // Equivalent to if(ptr != nullptr)
	{
		inOrder(ptr->left);
		cout << ptr->data << "   ";
		inOrder(ptr->right);
	}
}

template <class T>
void BinarySearchTree<T>::inOrderPrint()
{
	inOrder(root);
	cout << '\n';
}

template <class T>
void BinarySearchTree<T>::preOrder(Node *ptr) const
{
	if (ptr) // same as if (ptr != nullptr)
	{
		cout << ptr->data << "   ";
		preOrder(ptr->left);
		preOrder(ptr->right);
	}
}

template <class T>
void BinarySearchTree<T>::preOrderPrint()
{
	preOrder(root);
	cout << '\n';
}

template <class T>
void BinarySearchTree<T>::postOrder(Node *ptr) const
{
	if (ptr)
	{
		postOrder(ptr->left);
		postOrder(ptr->right);
		cout << ptr->data << "   ";
	}
}

template <class T>
void BinarySearchTree<T>::postOrderPrint()
{
	postOrder(root);
	cout << '\n';
}

// Deletes a node using right child promotion
template <class T>
void BinarySearchTree<T>::del(Node *&ptr)
{
	Node *delPtr = ptr;
	Node *attach;
	if (ptr->left == nullptr && ptr->right == nullptr) // no children
		ptr = nullptr;
	else if (ptr->right == nullptr) // only left child
		ptr = ptr->left;
	else if (ptr->left == nullptr) // only right child
		ptr = ptr->right;
	else // two children
	{
		attach = ptr->right;
		while (attach->left != nullptr)
			attach = attach->left;
		attach->left = ptr->left;
		ptr = ptr->right;
	}
	delete delPtr;
}

// Recursive function that searches for node to be deleted and then
// passes the appropriate pointer to method del
template <class T>
void BinarySearchTree<T>::deleteNode(Node *&ptr, T x)
{
	if (ptr)
	{
		if (ptr->data == x)
			del(ptr);
		else if (x < ptr->data)
			deleteNode(ptr->left, x);
		else
			deleteNode(ptr->right, x);
	}
}

// Public function that passes root to private helper function, deleteNode
template <class T>
void BinarySearchTree<T>::deleteItem(T x)
{
	deleteNode(root, x);
}

template <class T>
void BinarySearchTree<T>::deleteAll()
{
	destroySubtree(root);
}

template <class T>
bool BinarySearchTree<T>::searchItem(Node *ptr, T x)
{
	if (ptr)
	{
		if (x == ptr->data)
			return true;
		else if (x < ptr->data)
			return searchItem(ptr->left, x);
		else
			return searchItem(ptr->right, x);
	}
	return false;
}

template <class T>
bool BinarySearchTree<T>::search(T x)
{
	return searchItem(root, x);
}

template <class T>
void BinarySearchTree<T>::GraphVizGetIds(Node *nodePtr, ofstream &VizOut)
{
	if (nodePtr)
	{
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << " node" << nodePtr->data << " [label=\"" << nodePtr->data << "\"];" << '\n';
		GraphVizGetIds(nodePtr->right, VizOut);
	}
}

template <class T>
void BinarySearchTree<T>::GraphVizMakeConnections(Node *nodePtr, ofstream &VizOut)
{
	if (nodePtr)
	{
		if (nodePtr->left)
			VizOut << "  node" << nodePtr->data << "->" << " node" << nodePtr->left->data << '\n';
		if (nodePtr->right)
			VizOut << "  node" << nodePtr->data << "->" << " node" << nodePtr->right->data << '\n';
		GraphVizMakeConnections(nodePtr->left, VizOut);
		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}

template <class T>
void BinarySearchTree<T>::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "digraph g { \n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "} \n";
	VizOut.close();
}
#endif