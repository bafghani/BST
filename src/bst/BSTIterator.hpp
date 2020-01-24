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
 * TODO: add class header
 */
template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /**
     * Constructor that initialize the current BSTNode
     * in this BSTIterator.
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

    /** TODO */
    bool operator==(BSTIterator<Data> const& other) const {
        return this->curr == other.curr;
    }

    /** TODO */
    bool operator!=(BSTIterator<Data> const& other) const {
        return this->curr != other.curr;
    }
};

#endif  // BSTITERATOR_HPP
