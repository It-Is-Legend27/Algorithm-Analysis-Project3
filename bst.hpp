// Header file for binary search tree class
#ifndef BST_TEMPLATE
#define BST_TEMPLATE
#include <fstream>
#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

// A binary search tree is a binary tree with the additional property
// that at any node, all values in the left subtree are less than or equal
// to the node and all nodes in the right subtree are greater than the node.

template <class T>
class BinarySearchTree
{
private:
	template <class U>
	struct Node
	{
		U data{};
		Node *left{nullptr};
		Node *right{nullptr};

		Node() {}

		Node(U t_data, Node *t_left = nullptr, Node *t_right = nullptr) : data(t_data), left(t_left), right(t_right) {}
	};

	// Root of the tree
	Node<T> *m_root{nullptr};

	// size of the treel
	size_t m_size{0};

	// Recursive private function to insert a value into the tree
	void insert_node(Node<T> *&t_node_ptr, T t_data);

	// Recursive private function to print an in order listing of nodes in tree
	void in_order(Node<T> *t_node_ptr) const;

	// Recursive private function to print a pre-order listing of nodes in tree
	void pre_order(Node<T> *t_node_ptr) const;

	// Recursive private function to print a post-order listing of nodes in tree
	void post_order(Node<T> *t_node_ptr) const;

	// Pivate function to delete a node from tree that is pointed to by the
	// reference pointer t_node_ptr
	void remove_node(Node<T> *&t_node_ptr);

	// Recursive private function to delete node containing specific value, t_data
	void remove_node(Node<T> *&t_node_ptr, T t_data);

	// Recursive private function to delete all nodes in the tree
	void destroy_subtree(Node<T> *&t_node_ptr);

	bool search_value(Node<T> *t_node_ptr, T t_data);

	// Credit to:  Terry Griffin
	// Creates GraphViz code so the tree can be visualized.  Prints
	// unique node id's by traversing the tree.
	void graph_viz_ids(Node<T> *t_node_ptr, ofstream &VizOut);

	// Credit to:  Terry Griffin
	// Partnered with the above method, but on this pass it
	// writes out the actual data from each node.
	void graph_viz_connections(Node<T> *t_node_ptr, ofstream &VizOut);

public:
	// Constructor
	BinarySearchTree() {}

	// Destructor - deallocates all memory by calling destroy_subtree
	~BinarySearchTree() { clear(); }

	// Public function to insert item t_data into the tree; calls insert_node
	void insert(T t_data) { insert_node(m_root, t_data); }

	// Public function to delete item t_data from the tree; calls deleteNode
	void remove(T t_data) { remove_node(m_root, t_data); }

	// Public function to delete all items from the tree
	void clear() { destroy_subtree(m_root); }

	// Public function to print all nodes in order; calls in_order
	void in_order_print()
	{
		in_order(m_root);
		cout << '\n';
	}

	// Public function to print all nodes pre-order; calls pre_order
	void pre_order_print()
	{
		pre_order(m_root);
		cout << '\n';
	}

	// Public function to print all nodes post order; calls post_order
	void post_order_print()
	{
		post_order(m_root);
		cout << '\n';
	}

	// Public function to search for an item in the tree
	bool search(T t_data)
	{
		return search_value(m_root, t_data);
	}

	// Credit to:  Terry Griffin
	// Receives a file_path and stores a GraphViz readable file;
	// calls 	GraphVizGetIds and GraphVizMakeConnections
	void graph_viz(string file_path);
    
	size_t size();
};

// destroy_subtree recursively visits and deletes each node
// from the lowest level (leaves) up
template <class T>
void BinarySearchTree<T>::destroy_subtree(Node<T> *&t_node_ptr)
{
	if (t_node_ptr)
	{
		destroy_subtree(t_node_ptr->left);
		destroy_subtree(t_node_ptr->right);
		delete t_node_ptr;
		t_node_ptr = nullptr;
		m_size -= 1;
	}
}

template <class T>
void BinarySearchTree<T>::insert_node(Node<T> *&t_node_ptr, T t_data)
{
	// If t_node_ptr points to nullptr, the insertion position has been found
	if (!t_node_ptr)
	{
		t_node_ptr = new Node<T>(t_data);
		m_size += 1;
	}
	// If t_node_ptr does not point to nullptr, decide whether to traverse
	// down the left subtree or right subtree by comparing value
	// to be inserted with current node.
	else if (t_data <= t_node_ptr->data) // node should be inserted in left subtree
		insert_node(t_node_ptr->left, t_data);
	else // node should be inserted in right subtree
		insert_node(t_node_ptr->right, t_data);
}

template <class T>
void BinarySearchTree<T>::in_order(Node<T> *t_node_ptr) const
{
	if (t_node_ptr) // Equivalent to if(t_node_ptr != nullptr)
	{
		in_order(t_node_ptr->left);
		cout << t_node_ptr->data << "   ";
		in_order(t_node_ptr->right);
	}
}

template <class T>
void BinarySearchTree<T>::pre_order(Node<T> *t_node_ptr) const
{
	if (t_node_ptr) // same as if (t_node_ptr != nullptr)
	{
		cout << t_node_ptr->data << "   ";
		pre_order(t_node_ptr->left);
		pre_order(t_node_ptr->right);
	}
}

template <class T>
void BinarySearchTree<T>::post_order(Node<T> *t_node_ptr) const
{
	if (t_node_ptr)
	{
		post_order(t_node_ptr->left);
		post_order(t_node_ptr->right);
		cout << t_node_ptr->data << "   ";
	}
}

// Deletes a node using right child promotion
template <class T>
void BinarySearchTree<T>::remove_node(Node<T> *&t_node_ptr)
{
	Node<T> *delPtr = t_node_ptr;
	Node<T> *attach;
	if (t_node_ptr->left == nullptr && t_node_ptr->right == nullptr) // no children
		t_node_ptr = nullptr;
	else if (t_node_ptr->right == nullptr) // only left child
		t_node_ptr = t_node_ptr->left;
	else if (t_node_ptr->left == nullptr) // only right child
		t_node_ptr = t_node_ptr->right;
	else // two children
	{
		attach = t_node_ptr->right;
		while (attach->left != nullptr)
			attach = attach->left;
		attach->left = t_node_ptr->left;
		t_node_ptr = t_node_ptr->right;
	}
	delete delPtr;
	m_size -= 1;
}

// Recursive function that searches for node to be deleted and then
// passes the appropriate pointer to method remove_node
template <class T>
void BinarySearchTree<T>::remove_node(Node<T> *&t_node_ptr, T t_data)
{
	if (t_node_ptr)
	{
		if (t_node_ptr->data == t_data)
			remove_node(t_node_ptr);
		else if (t_data < t_node_ptr->data)
			remove_node(t_node_ptr->left, t_data);
		else
			remove_node(t_node_ptr->right, t_data);
	}
}

template <class T>
bool BinarySearchTree<T>::search_value(Node<T> *t_node_ptr, T t_data)
{
	if (t_node_ptr)
	{
		if (t_data == t_node_ptr->data)
			return true;
		else if (t_data < t_node_ptr->data)
			return search_value(t_node_ptr->left, t_data);
		else
			return search_value(t_node_ptr->right, t_data);
	}
	return false;
}

template <class T>
void BinarySearchTree<T>::graph_viz_ids(Node<T> *t_node_ptr, ofstream &VizOut)
{
	if (t_node_ptr)
	{
		graph_viz_ids(t_node_ptr->left, VizOut);
		VizOut << " node" << t_node_ptr->data << " [label=\"" << t_node_ptr->data << "\"];" << '\n';
		graph_viz_ids(t_node_ptr->right, VizOut);
	}
}

template <class T>
void BinarySearchTree<T>::graph_viz_connections(Node<T> *t_node_ptr, ofstream &VizOut)
{
	if (t_node_ptr)
	{
		if (t_node_ptr->left)
			VizOut << "  node" << t_node_ptr->data << "->"
				   << " node" << t_node_ptr->left->data << '\n';
		if (t_node_ptr->right)
			VizOut << "  node" << t_node_ptr->data << "->"
				   << " node" << t_node_ptr->right->data << '\n';
		graph_viz_connections(t_node_ptr->left, VizOut);
		graph_viz_connections(t_node_ptr->right, VizOut);
	}
}

template <class T>
void BinarySearchTree<T>::graph_viz(string file_path)
{
	ofstream VizOut;
	VizOut.open(file_path);
	VizOut << "digraph g { \n";
	graph_viz_ids(m_root, VizOut);
	graph_viz_connections(m_root, VizOut);
	VizOut << "} \n";
	VizOut.close();
}

template <class T>
size_t BinarySearchTree<T>::size()
{
	return m_size;
}

#endif