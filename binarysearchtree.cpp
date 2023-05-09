#include "binarysearchtree.h"

Position::Position(Node* v) : v(v) {} // constructor

Elem& BinarySearchTree::Position::operator*() // get element
{
    return v->elt;
}

bool BinarySearchTree::Position::operator==(const Position p) const /* Not implemented */
{
    return this->v == p.v;
}

bool BinarySearchTree::Position::operator!=(const Position p)  const /* Not implemented */
{
    return this->v != p.v;

}

BinarySearchTree::Position::operator bool()  const /* Not implemented */
{
    return v != NULL;

}

Position Position::left() const // get left child
{
    return Position(v->left);
}

Position Position::right() const // get right child
{
    return Position(v->right);
}

Position Position::parent() const // get parent
{
    return Position(v->par);
}

bool Position::isRoot() const // root of the tree?
{
    return v->par == NULL;
}

bool Position::isExternal() const // an external node?
{
    return v->left == NULL && v->right == NULL;
}

bool Position::hasLeftChild() const // has a left child?
{
    return v->left != NULL;
}

bool Position::hasRightChild() const // has a right child?
{
    return v->right != NULL;
}

BinarySearchTree::BinarySearchTree() // constructor
    : _root(NULL), n(0) { }

int BinarySearchTree::size() const // number of nodes
{
    return n;
}

bool BinarySearchTree::empty() const // is tree empty?
{
    return size() == 0;
}

Position BinarySearchTree::root() const // get the root
{
    return Position(_root);
}

void BinarySearchTree::addRoot() // add root to empty tree
{
    _root = new Node;
    n = 1;
}

void BinarySearchTree::expandExternal(const Position& p)
{
    Node* v = p.v; // p’s node
    v->left = new Node; // add a new left child
    v->left->par = v; // v is its parent
    v->right = new Node; // and a new right child
    v->right->par = v; // v is its parent
    n += 2; // two more nodes
}

// remove p and parent
Position BinarySearchTree::removeAboveExternal(const Position& p)
{
    Node* w = p.v;
    Node* v = w->par; // get p’s node and parent
    Node* sib = (w == v->left ? v->right : v->left);
    if (v == _root)   // child of root?
    {
        _root = sib; // . . .make sibling root
        sib->par = NULL;
    }
    else
    {
        Node* gpar = v->par; // w’s grandparent
        if (v == gpar->left) gpar->left = sib; // replace parent by sib
        else gpar->right = sib;
        sib->par = gpar;
    }
    delete w;
    delete v; // delete removed nodes
    n -= 2; // two fewer nodes
    return Position(sib);
}

PositionList BinarySearchTree::positions() const
{
    PositionList pl;
    inorder(_root, pl); // inorder traversal
    return PositionList(pl); // return resulting list
}


// inorder traversal
void BinarySearchTree::inorder(Position p, PositionList& pl) const
{
    // traverse left subtree
    if(p.hasLeftChild())
        inorder(p.left(), pl);
    // Push inorder / external
    // add this node
    pl.push_back(p);
    // traverse right subtree
    if(p.hasRightChild())
        inorder(p.right(), pl);
}
/* ########################################### */
/*          Implement methods below            */
/* ########################################### */

/* [01]A add node to tree */
void BinarySearchTree::add(Elem data)
{
    Node* newNode = new Node;
    newNode->elt = data;
    newNode->left = NULL;
    newNode->right = NULL;
    if (empty())
    {
        _root = newNode;
        n = 1;
        return;
    }
    // if not empty then get pos and search
    Position p = root();

    while (true)
    {
        if (data < *p)
        {
            if (!p.hasLeftChild())
            {

                newNode->par = p.v;
                p.v->left = newNode;
                n++;
                return;
            }
            p = p.left(); //p.v->left

        }

        else  if (data >= *p)
        {
            if (!p.hasRightChild())
            {

                newNode->par = p.v;
                p.v->right = newNode;
                n++;
                return;
            }
            p = p.right();
        }
    }





}

/* [01]B remove node from tree */
void BinarySearchTree::remove(Elem data) {
    Node* node = _root;     // start at the root
    // traverse the tree until the node with the element to be removed is found
    while (!node->elt == data) {
        if (data < node->elt)
            node = node->left;      // move left if the data is less than the current node's element
        else
            node = node->right;     // move right if the data is greater than the current node's element
    }
    // if the node has no left child, replace it with its right child
    if (node->left == NULL) {
        Node* node_to_delete = node; // save a reference to the node to be deleted
        node = node->right; // replace the node with its right child
        if (node != NULL) node->par = node_to_delete->par; // update the parent pointer of the child node
        if (node_to_delete == _root) _root = node; // update the root if necessary
        else if (node_to_delete == node_to_delete->par->left) node_to_delete->par->left = node; // update the parent node's child pointer
        else node_to_delete->par->right = node; // update the parent node's child pointer
        delete node_to_delete; // delete the node
    }
    // if the node has no right child, replace it with its left child
    else if (node->right == NULL) {
        Node* node_to_delete = node; // save a reference to the node to be deleted
        node = node->left; // replace the node with its left child
        if (node != NULL) node->par = node_to_delete->par; // update the parent pointer of the child node
        if (node_to_delete == _root) _root = node; // update the root if necessary
        else if (node_to_delete == node_to_delete->par->left) node_to_delete->par->left = node; // update the parent node's child pointer
        else node_to_delete->par->right = node; // update the parent node's child pointer
        delete node_to_delete; // delete the node
    }
    // if the node has both left and right children, find the minimum node in the right subtree and replace the current node with it
    else {
        Node* min_node = node->right; // find the minimum node in the right subtree
        while (min_node->left != NULL) min_node = min_node->left;
        node->elt = min_node->elt; // replace the current node's element with that of the minimum node


        Node* parent_of_min_node = min_node->par; // save a reference to the parent node of the minimum node

         if (parent_of_min_node->left == min_node )
            parent_of_min_node->left = min_node->right; // update the parent node's child pointer عشان وصل ل اخر الشمال ف هيوصل   باليمين
         else
            parent_of_min_node->right = min_node->right; // update the parent node's child pointer

        if (min_node->right != NULL) min_node->right->par = parent_of_min_node; // update the parent pointer of the child node
        delete min_node; // delete the minimum node
    }
}
//
///* [02] returns position of the maximum element in the tree */
//Position BinarySearchTree::max() const
//{ }
//
///* [03] returns position of the minimum element in the tree */
//Position BinarySearchTree::min() const
//{ }
//
///* [04] returns true if value is in the tree */
//bool BinarySearchTree::exist(Elem val) const
//{ }
//
///* [05] returns position of the (inorder predecessor) largest element less than the value in p */
//Position BinarySearchTree::inorder_predecessor(Position p) const
//{ }
//
///* [06] returns position of the (inorder successor) smallest element larger than the value in p */
//Position BinarySearchTree::inorder_successor(Position p) const
//{ }
//
///* [07] count: returns the number of stored elements/nodes (traverse the tree). */
//unsigned int BinarySearchTree::count() const
//{ }
//
///* [08]/[09] opereator [] positive/negative index */
//Elem BinarySearchTree::operator [](int index) const
//{ }
//
///* [10] mean of all elements */
//double BinarySearchTree::mean() const
//{ }
/* [02] returns position of the maximum element in the tree */

// [02] returns position of the maximum element in the tree
Position BinarySearchTree::max() const {
    if (empty()) {
        return Position(NULL);
    }
    Node* v = _root;
    while (v->right != NULL) {
        v = v->right;
    }
    return Position(v);
}

// [03] returns position of the minimum element in the tree
Position BinarySearchTree::min() const {
    if (empty()) {
        return Position(NULL);
    }
    Node* v = _root;
    while (v->left != NULL) {
        v = v->left;
    }
    return Position(v);
}

// [04] returns true if value is in the tree
bool BinarySearchTree::exist(Elem val) const {
    if (empty()) {
        return false;
    }
    Node* v = _root;
    while (v != NULL) {
        if (val < v->elt) {
            v = v->left;
        }
        else if (val > v->elt) {
            v = v->right;
        }
        else { // val == v->elt
            return true;
        }
    }
    return false;
}

// [05] returns position of the (inorder predecessor) largest element less than the value in p
Position BinarySearchTree::inorder_predecessor(Position p) const {
    if (p.hasLeftChild()) {
        p = p.left();
        while (p.hasRightChild()) {
            p = p.right();
        }
        return p;
    }
    else {
        while (p.hasLeftChild() ) {
            p = p.parent();
        }
        return p.parent();
    }
}
/* [06] returns position of the (inorder successor) smallest element larger than the value in p */
BinarySearchTree::Position BinarySearchTree::inorder_successor(Position p) const
{
    // If the right subtree of p exists, then the inorder successor
    // is the leftmost node of the right subtree
    if (p.hasRightChild()) {
        p = p.right();
        while (p.hasLeftChild()) {
            p = p.left();
        }
        return p;
    }

    // If the right subtree of p does not exist, then the inorder successor
    // is the lowest ancestor of p whose left child is also an ancestor of p
    while (p.hasRightChild() ) {
        p = p.parent();
    }
    return p.parent();
}

/* [07] count: returns the number of stored elements/nodes (traverse the tree). */
unsigned int BinarySearchTree::count() const
{
    // Traverse the tree and count the number of nodes
    unsigned int count = 0;
    for (auto it = positions().begin(); it != positions().end(); ++it) {
        ++count;
    }
    return count;
}

/* [08]/[09] opereator [] positive/negative index */
Elem BinarySearchTree::operator [](int index) const
{
    // Convert negative index to positive index
    if (index < 0) {
        index += count();
    }

    // Traverse the tree to find the node at the specified index
    int i = 0;
    for (auto it = positions().begin(); it != positions().end(); ++it) {
        if (i == index) {
            return *it;
        }
        ++i;
    }

    // If the index is out of bounds, throw an exception
    throw std::out_of_range("Index out of bounds.");
}

/* [10] mean of all elements */
double BinarySearchTree::mean() const
{
    // Traverse the tree and compute the sum of all elements
    double sum = 0.0;
    for (auto it = positions().begin(); it != positions().end(); ++it) {
        sum += *it;
    }

    // Compute the mean and return it
    return sum / count();
}
