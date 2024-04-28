/// Header file for AVL Tree class
#ifndef AVL_TEMPLATE
#define AVL_TEMPLATE
#include <iostream>
#include <fstream>
#include <cstddef>
#include <algorithm>

using namespace std;

/// @brief A class template for creating AVL trees for any given
/// data type.
/// @tparam T The type for the data to be stored in the tree.
template <class T>
class AVLTree
{
private:
    /// @brief A class template for nodes of a specified data type.
    /// @tparam U The data type to be stored in the node.
    template <class U>
    struct Node
    {
        U data{};
        size_t count{0};        // Count of duplicate values
        long balance_factor{0}; // AVL balance factor
        Node *left{nullptr};
        Node *right{nullptr};

        // Constructor for creating a new node
        Node() {}

        /// @brief Constructor for creating a new node.
        /// @param t_data Data for node to store.
        /// @param t_left Node pointer to left child.
        /// @param t_right Node pointer to right child.
        /// @param t_count Number of occurrence of the value.
        /// @param t_balance_factor Balance factor.
        Node(U t_data, Node *t_left = nullptr, Node *t_right = nullptr, size_t t_count = 1, long t_balance_factor = 0) : data(t_data), left(t_left), right(t_right), count(t_count), balance_factor(t_balance_factor) {}
    };

    Node<T> *m_root{nullptr};
    size_t m_size{0};

    /// @brief Calculates the sum of the heights of each node of a subtree.
    /// @param t_node_ptr Pointer to root of subtree.
    /// @return Sum of the heights of the tree.
    void sum_heights(Node<T> *t_node_ptr, size_t &total_height);

    /// @brief Inserts a node into the tree.
    /// @param t_node_ptr Pointer to the root of the subtree.
    /// @param t_data Data for node to store.
    void insert_node(Node<T> *&t_node_ptr, T t_data);

    /// @brief Destroys a subtree.
    /// @param t_node_ptr Pointer to root of subtree.
    void destroy_subtree(Node<T> *&t_node_ptr);

    /// @brief Inorder print of values.
    /// @param t_node_ptr
    void in_order(Node<T> *t_node_ptr);

    /// @brief Preorder print of values.
    /// @param t_node_ptr
    void pre_order(Node<T> *t_node_ptr);

    /// @brief Postorder print of values.
    /// @param t_node_ptr
    void post_order(Node<T> *t_node_ptr);

    /// @brief Remove a node with the specified value.
    /// @param t_data Value of node to be removed.
    /// @param t_node_ptr Pointer to root of subtree.
    void remove_node(T t_data, Node<T> *&t_node_ptr);

    /// @brief Deletes a node.
    /// @param t_node_ptr Pointer to node.
    void delete_node(Node<T> *&t_node_ptr);

    /// @brief Calculates height of the subtree.
    /// @param t_node_ptr Pointer to root of the subtree.
    /// @return Height of the subtree.
    size_t sub_tree_height(Node<T> *t_node_ptr);

    /// @brief Computes the avl values.
    /// @param t_node_ptr Pointer to root of subtree.
    void compute_avl_values(Node<T> *&t_node_ptr);

    /// @brief Checks if subtree is left heavy.
    /// @param t_node_ptr Pointer to root of subtree.
    /// @return true if left heavy, false otherwise.
    bool left_heavy(Node<T> *t_node_ptr);

    /// @brief Checks if subtree is right heavy.
    /// @param t_node_ptr Pointer to root of subtree.
    /// @return true if right heavy, false otherwise.
    bool right_heavy(Node<T> *t_node_ptr);

    /// @brief Writes GraphViz IDs to an output stream.
    /// @param t_node_ptr Pointer to root of subtree.
    /// @param VizOut Output stream.
    void graph_viz_ids(Node<T> *t_node_ptr, ofstream &VizOut);

    /// @brief Writes GraphViz connections to an output stream.
    /// @param t_node_ptr Pointer to root of subtree.
    /// @param VizOut Output stream.
    void graph_viz_connections(Node<T> *t_node_ptr, ofstream &VizOut);

    /// @brief Performs left rotation on the subtree.
    /// @param node Pointer to root of subtree.
    void rotate_left(Node<T> *&t_node_ptr);

    /// @brief Performs right rotation on the subtree.
    /// @param t_node_ptr Pointer to root of subtree.
    void rotate_right(Node<T> *&t_node_ptr);

public:
    /// @brief Computes the averahe node height of the tree.
    /// @return Average node height.
    double average_height();

    /// @brief Computes the balance factor of a specific node.
    /// @param t_node_ptr Pointer to node.
    /// @return Balance factor.
    long balance_factor(Node<T> *t_node_ptr);

    /// @brief Create a default AVLTree object.
    AVLTree() {}

    /// @brief Delete the AVLTree object.
    ~AVLTree() { clear(); }

    /// @brief Clears the tree.
    void clear() { destroy_subtree(m_root); }

    /// @brief Insert a value into the tree.
    /// @param t_data Value to be inserted.
    void insert(T t_data)
    {
        insert_node(m_root, t_data);
        compute_avl_values(m_root);
    }

    /// @brief Print the values in the tree inorder.
    void in_order_print() { in_order(m_root); };

    /// @brief Print the values in the tree in preorder.
    void pre_order_print() { pre_order(m_root); };

    /// @brief Print the values in the tree in postorder.
    void post_order_print() { post_order(m_root); };

    /// @brief Check if a value exists in the tree.
    /// @param t_data Value to be checked.
    /// @return true if value exists, false otherwise.
    bool search_value(T t_data);

    /// @brief Remove a value from the tree.
    /// @param t_data Value to be removed.
    void remove(T t_data) { remove_node(t_data, m_root); };

    /// @brief Calculates the height of the tree.
    /// @return Height of the tree.
    size_t height() { return sub_tree_height(m_root); }

    /// @brief Writes GraphViz code for a graph of the tree to a file.
    /// @param file_path File path.
    void graph_viz(string file_path);

    /// @brief Size of the tree, meaning number of nodes.
    /// @return Size of the tree.
    size_t size();
};

template <class T>
double AVLTree<T>::average_height()
{
    size_t total = 0;
    sum_heights(this->m_root, total);

    double avg_height = (double)total / (double)(this->size());

    return avg_height;
}

template <class T>
void AVLTree<T>::sum_heights(Node<T> *t_node_ptr, size_t &total_height)
{
    if (!t_node_ptr)
    {
        return;
    }

    sum_heights(t_node_ptr->left, total_height);
    total_height += sub_tree_height(t_node_ptr);
    sum_heights(t_node_ptr->right, total_height);
}

template <class T>
void AVLTree<T>::destroy_subtree(Node<T> *&t_node_ptr)
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

// The insert_node method is a recursive private method that will be passed
// a pointer (m_root initially) and an integer to be added to the tree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void AVLTree<T>::insert_node(Node<T> *&t_node_ptr, T t_data)
{
    if (!t_node_ptr) // Insertion position found
    {
        t_node_ptr = new Node<T>(t_data);
        m_size += 1;
    }
    else if (t_data == t_node_ptr->data)
        t_node_ptr->count++;            // Update count of duplicate t_data
    else if (t_data < t_node_ptr->data) // insert in the left subtree
        insert_node(t_node_ptr->left, t_data);
    else // insert in the right subtree
        insert_node(t_node_ptr->right, t_data);
}

// Prints the in_order traversal of the tree.
template <class T>
void AVLTree<T>::in_order(Node<T> *t_node_ptr)
{
    if (t_node_ptr)
    {
        in_order(t_node_ptr->left);
        cout << t_node_ptr->data << " "
             << "(" << t_node_ptr->balance_factor << "/" << t_node_ptr->count << ")\n";
        in_order(t_node_ptr->right);
    }
}

// Prints the post_order traversal of the tree.
template <class T>
void AVLTree<T>::post_order(Node<T> *t_node_ptr)
{
    if (t_node_ptr)
    {
        post_order(t_node_ptr->left);
        post_order(t_node_ptr->right);
        cout << t_node_ptr->data << " "
             << "(" << t_node_ptr->balance_factor << "/" << t_node_ptr->count << ")\n";
    }
}

// Prints the post_order traversal of the tree.
template <class T>
void AVLTree<T>::pre_order(Node<T> *t_node_ptr)
{
    if (t_node_ptr)
    {
        cout << t_node_ptr->data << " "
             << "(" << t_node_ptr->balance_factor << "/" << t_node_ptr->count << ")\n";
        pre_order(t_node_ptr->left);
        pre_order(t_node_ptr->right);
    }
}

template <class T>
bool AVLTree<T>::search_value(T t_data)
{
    Node<T> *t_node_ptr = m_root;
    while (t_node_ptr)
    {
        if (t_node_ptr->data == t_data)
            return true;
        else if (t_data < t_node_ptr->data)
            t_node_ptr = t_node_ptr->left;
        else
            t_node_ptr = t_node_ptr->right;
    }
    return false;
}

template <class T>
void AVLTree<T>::remove_node(T t_data, Node<T> *&t_node_ptr)
{
    if (t_data < t_node_ptr->data)
        remove_node(t_data, t_node_ptr->left);
    else if (t_data > t_node_ptr->data)
        remove_node(t_data, t_node_ptr->right);
    else
        delete_node(t_node_ptr);
}

template <class T>
void AVLTree<T>::delete_node(Node<T> *&t_node_ptr)
{
    Node<T> *temp_node_ptr;
    if (t_node_ptr == nullptr)
        cout << "Cannot delete empty node.\n";
    else if (t_node_ptr->right == nullptr)
    {
        temp_node_ptr = t_node_ptr;
        t_node_ptr = t_node_ptr->left;
        delete temp_node_ptr;
        m_size -= 1;
    }
    else if (t_node_ptr->left == nullptr)
    {
        temp_node_ptr = t_node_ptr;
        t_node_ptr = t_node_ptr->right;
        delete temp_node_ptr;
        m_size -= 1;
    }
    else
    {
        temp_node_ptr = t_node_ptr->right;
        while (temp_node_ptr->left)
            temp_node_ptr = temp_node_ptr->left;
        temp_node_ptr->left = t_node_ptr->left;
        temp_node_ptr = t_node_ptr;
        t_node_ptr = t_node_ptr->right;
        delete temp_node_ptr;
        m_size -= 1;
    }
    compute_avl_values(t_node_ptr);
}

template <class T>
size_t AVLTree<T>::sub_tree_height(Node<T> *t_node_ptr)
{
	if(!t_node_ptr)
	return 0;

	if(!t_node_ptr->left && !t_node_ptr->right)
	return 0;

	size_t left_height = sub_tree_height(t_node_ptr->left);
	size_t right_height = sub_tree_height(t_node_ptr->right);

	return max(left_height, right_height) + 1;
}

// Credit to:  Terry Griffin
// Method to help create GraphViz code so the expression tree can
// be visualized. This method prints out all the unique node id's
// by traversing the tree.
// Recivies a node pointer to m_root and performs a simple recursive
// tree traversal.
//////////////////////////////////////////////////////////////////////
template <class T>
void AVLTree<T>::graph_viz_ids(Node<T> *t_node_ptr, ofstream &VizOut)
{
    if (t_node_ptr)
    {
        graph_viz_ids(t_node_ptr->left, VizOut);
        VizOut << " node" << t_node_ptr->data << " [label=\"" << t_node_ptr->data << "\\nBF| " << t_node_ptr->balance_factor << "\\nC|" << t_node_ptr->count << "\"]" << '\n';
        graph_viz_ids(t_node_ptr->right, VizOut);
    }
}

template <class T>
void AVLTree<T>::graph_viz_connections(Node<T> *t_node_ptr, ofstream &VizOut)
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
void AVLTree<T>::graph_viz(string file_path)
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
bool AVLTree<T>::left_heavy(Node<T> *t_node_ptr)
{
    return (sub_tree_height(t_node_ptr->left) > sub_tree_height(t_node_ptr->right));
}

template <class T>
bool AVLTree<T>::right_heavy(Node<T> *t_node_ptr)
{
    return (sub_tree_height(t_node_ptr->right) > sub_tree_height(t_node_ptr->left));
}

template <class T>
void AVLTree<T>::rotate_left(Node<T> *&t_node_ptr)
{
    if (t_node_ptr->right != nullptr && left_heavy(t_node_ptr->right))
    {
        rotate_right(t_node_ptr->right);
    }

    Node<T> *Temp;
    Temp = t_node_ptr->right;
    t_node_ptr->right = Temp->left;
    Temp->left = t_node_ptr;
    t_node_ptr = Temp;

    compute_avl_values(t_node_ptr);
}

template <class T>
void AVLTree<T>::rotate_right(Node<T> *&t_node_ptr)
{
    if (t_node_ptr->left != nullptr && right_heavy(t_node_ptr->left))
    {
        rotate_left(t_node_ptr->left);
    }
    Node<T> *Temp;
    Temp = t_node_ptr->left;
    t_node_ptr->left = Temp->right;
    Temp->right = t_node_ptr;
    t_node_ptr = Temp;
    compute_avl_values(t_node_ptr);
}

template <class T>
long AVLTree<T>::balance_factor(Node<T> *t_node_ptr)
{
    size_t leftheight = sub_tree_height(t_node_ptr->left);
    size_t rightheight = sub_tree_height(t_node_ptr->right);
    return leftheight - rightheight;
}

template <class T>
void AVLTree<T>::compute_avl_values(Node<T> *&t_node_ptr)
{
    if (t_node_ptr)
    {
        compute_avl_values(t_node_ptr->left);
        compute_avl_values(t_node_ptr->right);
        t_node_ptr->balance_factor = balance_factor(t_node_ptr);
        if (t_node_ptr->balance_factor > 1)
            rotate_right(t_node_ptr);
        else if (t_node_ptr->balance_factor < -1)
            rotate_left(t_node_ptr);
    }
}

template <class T>
size_t AVLTree<T>::size()
{
    return m_size;
}

#endif