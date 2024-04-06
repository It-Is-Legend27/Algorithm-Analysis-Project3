#ifndef AVL_TEMPLATE
#define AVL_TEMPLATE
#include <iostream>
#include <fstream>
#include <cstddef>

using namespace std;

template <class T>
class avl_tree
{
private:
    template <class U>
    struct node
    {
        U data{};
        size_t count{0};        // Count of duplicate values
        long balance_factor{0}; // AVL balance factor
        node *left{nullptr};
        node *right{nullptr};

        // Constructor for creating a new node
        node() {}

        node(U t_data, node *t_left = nullptr, node *t_right = nullptr, size_t t_count = 1, long t_balance_factor = 0) : data(t_data), left(t_left), right(t_right), count(t_count), balance_factor(t_balance_factor) {}
    };

    node<T> *m_root{nullptr};

    void insert_node(node<T> *&t_node_ptr, T t_data);
    void destroy_subtree(node<T> *&t_node_ptr);
    void in_order(node<T> *t_node_ptr);
    void pre_order(node<T> *t_node_ptr);
    void post_order(node<T> *t_node_ptr);
    void remove_node(T, node<T> *&);
    void delete_node(node<T> *&t_node_ptr);
    size_t sub_tree_height(node<T> *t_node_ptr);
    void compute_avl_values(node<T> *&t_node_ptr);
    bool left_heavy(node<T> *t_node_ptr);
    bool right_heavy(node<T> *t_node_ptr);
    void graph_viz_ids(node<T> *t_node_ptr, ofstream &VizOut);
    void graph_viz_connections(node<T> *t_node_ptr, ofstream &VizOut);

public:
    long balance_factor(node<T> *t_node_ptr);
    avl_tree() {}
    ~avl_tree() { clear(); }

    void clear() { destroy_subtree(m_root); }

    void insert(T t_data)
    {
        insert_node(m_root, t_data);
        compute_avl_values(m_root);
    }
    void in_order_print() { in_order(m_root); };

    void pre_order_print() { pre_order(m_root); };

    void post_order_print() { post_order(m_root); };

    bool search_value(T t_data);

    void remove(T t_data) { remove_node(t_data, m_root); };

    size_t height() { return sub_tree_height(m_root); }

    void graph_viz(string file_path);

private:
    void rotate_left(node<T> *&node);
    void rotate_right(node<T> *&t_node_ptr);
};

template <class T>
void avl_tree<T>::destroy_subtree(node<T> *&t_node_ptr)
{
    if (t_node_ptr)
    {
        destroy_subtree(t_node_ptr->left);
        destroy_subtree(t_node_ptr->right);
        delete t_node_ptr;
        t_node_ptr = nullptr;
    }
}

// The insert_node method is a recursive private method that will be passed
// a pointer (m_root initially) and an integer to be added to the tree.
///////////////////////////////////////////////////////////////////////////////
template <class T>
void avl_tree<T>::insert_node(node<T> *&t_node_ptr, T t_data)
{
    if (!t_node_ptr) // Insertion position found
        t_node_ptr = new node<T>(t_data);
    else if (t_data == t_node_ptr->data)
        t_node_ptr->count++;            // Update count of duplicate t_data
    else if (t_data < t_node_ptr->data) // insert in the left subtree
        insert_node(t_node_ptr->left, t_data);
    else // insert in the right subtree
        insert_node(t_node_ptr->right, t_data);
}

// Prints the in_order traversal of the tree.
template <class T>
void avl_tree<T>::in_order(node<T> *t_node_ptr)
{
    if (t_node_ptr)
    {
        in_order(t_node_ptr->left);
        cout << t_node_ptr->data << " " << "(" << t_node_ptr->balance_factor << "/" << t_node_ptr->count << ")\n";
        in_order(t_node_ptr->right);
    }
}

// Prints the post_order traversal of the tree.
template <class T>
void avl_tree<T>::post_order(node<T> *t_node_ptr)
{
    if (t_node_ptr)
    {
        post_order(t_node_ptr->left);
        post_order(t_node_ptr->right);
        cout << t_node_ptr->data << " " << "(" << t_node_ptr->balance_factor << "/" << t_node_ptr->count << ")\n";
    }
}

// Prints the post_order traversal of the tree.
template <class T>
void avl_tree<T>::pre_order(node<T> *t_node_ptr)
{
    if (t_node_ptr)
    {
        cout << t_node_ptr->data << " " << "(" << t_node_ptr->balance_factor << "/" << t_node_ptr->count << ")\n";
        pre_order(t_node_ptr->left);
        pre_order(t_node_ptr->right);
    }
}

template <class T>
bool avl_tree<T>::search_value(T t_data)
{
    node<T> *t_node_ptr = m_root;
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
void avl_tree<T>::remove_node(T t_data, node<T> *&t_node_ptr)
{
    if (t_data < t_node_ptr->data)
        remove_node(t_data, t_node_ptr->left);
    else if (t_data > t_node_ptr->data)
        remove_node(t_data, t_node_ptr->right);
    else
        delete_node(t_node_ptr);
}

template <class T>
void avl_tree<T>::delete_node(node<T> *&t_node_ptr)
{
    node<T> *temp_node_ptr;
    if (t_node_ptr == nullptr)
        cout << "Cannot delete empty node.\n";
    else if (t_node_ptr->right == nullptr)
    {
        temp_node_ptr = t_node_ptr;
        t_node_ptr = t_node_ptr->left;
        delete temp_node_ptr;
    }
    else if (t_node_ptr->left == nullptr)
    {
        temp_node_ptr = t_node_ptr;
        t_node_ptr = t_node_ptr->right;
        delete temp_node_ptr;
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
    }
    compute_avl_values(t_node_ptr);
}

template <class T>
size_t avl_tree<T>::sub_tree_height(node<T> *t_node_ptr)
{
    int left_height = 0;
    int right_height = 0;
    if (t_node_ptr == nullptr)
        return 0;
    else
    {
        left_height = sub_tree_height(t_node_ptr->left);
        right_height = sub_tree_height(t_node_ptr->right);
    }
    if (left_height > right_height)
        return 1 + left_height;
    else
        return 1 + right_height;
}

// Credit to:  Terry Griffin
// Method to help create GraphViz code so the expression tree can
// be visualized. This method prints out all the unique node id's
// by traversing the tree.
// Recivies a node pointer to m_root and performs a simple recursive
// tree traversal.
//////////////////////////////////////////////////////////////////////
template <class T>
void avl_tree<T>::graph_viz_ids(node<T> *t_node_ptr, ofstream &VizOut)
{
    if (t_node_ptr)
    {
        graph_viz_ids(t_node_ptr->left, VizOut);
        VizOut << " node" << t_node_ptr->data << " [label=\"" << t_node_ptr->data << "\\nBF| " << t_node_ptr->balance_factor << "\\nC|" << t_node_ptr->count << "\"]" << '\n';
        graph_viz_ids(t_node_ptr->right, VizOut);
    }
}

template <class T>
void avl_tree<T>::graph_viz_connections(node<T> *t_node_ptr, ofstream &VizOut)
{
    if (t_node_ptr)
    {
        if (t_node_ptr->left)
            VizOut << "  node" << t_node_ptr->data << "->" << " node" << t_node_ptr->left->data << '\n';
        if (t_node_ptr->right)
            VizOut << "  node" << t_node_ptr->data << "->" << " node" << t_node_ptr->right->data << '\n';
        graph_viz_connections(t_node_ptr->left, VizOut);
        graph_viz_connections(t_node_ptr->right, VizOut);
    }
}

template <class T>
void avl_tree<T>::graph_viz(string file_path)
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
bool avl_tree<T>::left_heavy(node<T> *t_node_ptr)
{
    return (sub_tree_height(t_node_ptr->left) > sub_tree_height(t_node_ptr->right));
}

template <class T>
bool avl_tree<T>::right_heavy(node<T> *t_node_ptr)
{
    return (sub_tree_height(t_node_ptr->right) > sub_tree_height(t_node_ptr->left));
}

template <class T>
void avl_tree<T>::rotate_left(node<T> *&t_node_ptr)
{
    if (t_node_ptr->right != nullptr && left_heavy(t_node_ptr->right))
    {
        rotate_right(t_node_ptr->right);
    }

    node<T> *Temp;
    Temp = t_node_ptr->right;
    t_node_ptr->right = Temp->left;
    Temp->left = t_node_ptr;
    t_node_ptr = Temp;

    compute_avl_values(t_node_ptr);
}

template <class T>
void avl_tree<T>::rotate_right(node<T> *&t_node_ptr)
{
    if (t_node_ptr->left != nullptr && right_heavy(t_node_ptr->left))
    {
        rotate_left(t_node_ptr->left);
    }
    node<T> *Temp;
    Temp = t_node_ptr->left;
    t_node_ptr->left = Temp->right;
    Temp->right = t_node_ptr;
    t_node_ptr = Temp;
    compute_avl_values(t_node_ptr);
}

template <class T>
long avl_tree<T>::balance_factor(node<T> *t_node_ptr)
{
    size_t leftheight = sub_tree_height(t_node_ptr->left);
    size_t rightheight = sub_tree_height(t_node_ptr->right);
    return leftheight - rightheight;
}

template <class T>
void avl_tree<T>::compute_avl_values(node<T> *&t_node_ptr)
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
#endif