/**
 * TODO: add file header
 */
#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <queue>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

/**
 * TODO: add class header
 */
template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /**
     * Default constructor.
     * Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {}

    /** TODO */
    ~BST() { deleteAll(root); }

    /** TODO */
    bool insert(const Data& item) {  // Creates root node if tree doesn't exist
        std::cout << item;
        if (root == nullptr) {
            root = new BSTNode<Data>(item);
            isize++;
            return true;
        }

        BSTNode<Data>* curr;
        curr = root;

        // while curr->data != item
        while (!(!(curr->getData() < item) && !(item < curr->getData()))) {
            if (item < curr->getData()) {
                if (curr->left == nullptr) {
                    curr->left = new BSTNode<Data>(item);
                    curr->left->parent = curr;  // Reassigns pointer
                    isize++;
                    return true;
                } else if (curr->left != nullptr) {
                    curr = curr->left;
                }
            } else if (curr->getData() < item) {
                if (curr->right == nullptr) {
                    curr->right = new BSTNode<Data>(item);
                    curr->right->parent = curr;  // Reassigns pointer
                    isize++;
                    return true;
                } else if (curr->right != nullptr) {
                    curr = curr->right;
                }
            }
        }

        // Returns false if node with data == item exists
        return false;
    }

    /** TODO */
    iterator find(const Data& item) const {
        if (root == nullptr) {
            return end();
        }

        BSTNode<Data>* curr = root;

        while (!(!(curr->getData() < item) && !(item < curr->getData()))) {
            if (item < curr->getData()) {
                curr = curr->left;
            } else if (curr->getData() < item) {
                curr = curr->right;
            }

            if (curr == nullptr) {
                return BST<Data>::iterator(0);
            }
        }
        return BST<Data>::iterator(curr);
    }

    /** TODO */
    bool deleteNode(const Data& item) { return false; }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return getHeight(root); }

    /** TODO */
    bool empty() const {
        if (isize == 0) {
            return true;
        } else {
            return false;
        }
    }

    /** TODO */
    iterator begin() const { return BST<Data>::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO */
    vector<Data> inorder() const {
        vector<Data> list;
        if (root == nullptr) {
            return list;
        }
        inOrderHelper(root, list);
        return list;
    }

    /**
     * DO NOT CHANGE THIS METHOD
     * Prints a tree, including its structure to an
     * output stream to help with grading and debugging.
     */
    void print(ostream* out) {
        if (empty()) {
            *out << "(Empty tree)" << endl;
            return;
        }

        // Using a queue to traverse a tree is otherwise
        // known as a breadth first traversal of the tree.
        // It's useful here to show which nodes are on which
        // level.
        queue<BSTNode<Data>*> toVisit;
        toVisit.push(root);
        int nodesPerLevel = 1;
        int totalSpacing = 1 << iheight;

        for (int i = 0; i <= iheight; i++) {
            for (int j = 0; j < nodesPerLevel; j++) {
                BSTNode<Data>* curr = toVisit.front();
                toVisit.pop();
                if (curr == nullptr) {
                    *out << "X";
                    // If we have an entire missing subtree, we
                    // would like to print X's in place of all
                    // nodes because it avoids ambiguity
                    toVisit.push(nullptr);
                    toVisit.push(nullptr);
                } else {
                    *out << curr->getData();
                    toVisit.push(curr->left);
                    toVisit.push(curr->right);
                }
                for (int k = 0; k < totalSpacing / nodesPerLevel; k++) {
                    *out << "\t";
                }
            }
            *out << endl;
            nodesPerLevel *= 2;
        }
    }

  private:
    /** TODO Helper function for begin() */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* curr = root;
        if (curr == nullptr) {
            return nullptr;
        }

        while (curr->left != nullptr) {
            curr = curr->left;
        }

        return curr;
    }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        // if current node is null: return;
        if (n == nullptr) {
            return;
        }
        deleteAll(n->left);   // recursively delete left sub-tree
        deleteAll(n->right);  // recursively delete right sub-tree

        // delete current node
        delete n;
    }

    /** TODO */
    BSTNode<Data>* buildSubtree(vector<Data>& data, int start, int end,
                                int depth) {
        return 0;
    }

    // Add more helper functions below
    int getHeight(BSTNode<Data>* n) const {
        if (n == nullptr) {
            return -1;
        }
        int leftSize = getHeight(n->left);
        int rightSize = getHeight(n->right);

        if (rightSize < leftSize) {
            return leftSize + 1;
        } else {
            return rightSize + 1;
        }
    }
    // inOrderHelper
    static void inOrderHelper(BSTNode<Data>* n, vector<Data>& addList) {
        if (n == nullptr) {
            return;
        }
        inOrderHelper(n->left, addList);
        addList.push_back(n->getData());
        inOrderHelper(n->right, addList);
    }
};

#endif  // BST_HPP
