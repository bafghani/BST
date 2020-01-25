/**
 * Name: Joseph Mattingly
 * Name: Bijan Afghani
 * This file creates the individual Node structures
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

/**
 * This file creates the structure of each BST Node
 * each node contains pointers and a data item
 * There are standard setters and getters to access
 * data along with overloaded operators
 */
template <typename Data>
class BSTNode {
  private:
    Data data;

  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;

    /** initializes a BSTNode with data d
     * @param d the data we would like to initialize our node with
     */
    BSTNode(const Data& d) : data(d) {
        setData(d);
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    /**
     * Sets the data for a BSTnode.
     *
     * @param d The value that BSTnode's data will be set to.
     */
    void setData(const Data& d) { data = d; }

    /** Returns the value of data stored in a BSTnode.
     *
     * @return the data in node.
     */
    Data getData() { return data; }

    /**
     * Returns a BSTNode pointer that points to the successor
     * of the current BSTNode.
     *
     * The successor is the smallest element that is larger
     * than this BSTNode.
     *
     * @return a BSTNode pointer pointing to the successor.
     */
    BSTNode<Data>* successor() {
        BSTNode<Data>* curr = this;  // pointer to current node

        // if right child exists sets curr to right child
        if (this->right != nullptr) {
            curr = this->right;

            // Traverses down to left most node
            while (curr->left != nullptr) {
                curr = curr->left;
            }

            return curr;
        } else {
            curr = this;
            while (curr->parent != nullptr) {
                if (curr == curr->parent->left) {
                    return curr->parent;
                } else {
                    curr = curr->parent;
                }
            }
        }
        return nullptr;
    }
};

/**
 * DO NOT CHANGE THIS METHOD
 * Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
