/**
 * Name: Joseph Mattingly
 * Name: Bijan Afghani
 */
#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"

using namespace std;

/**
 * This file creates the BST Iterator object to traverse from node to node
 * Contains getter for getting the node from iterator along with
 * overloaded operators
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
     * @param node we would like to initialize Iterator with
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}
    // getter method to get node from iterator
    BSTNode<Data>* getNode() { return curr; }
    /** Dereference operator. */
    Data operator*() const { return curr->getData(); }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /** equality operator */
    bool operator==(BSTIterator<Data> const& other) const {
        return curr == other.curr;
    }

    /** non equality operator */
    bool operator!=(BSTIterator<Data> const& other) const {
        return this->curr != other.curr;
    }
};

#endif  // BSTITERATOR_HPP
