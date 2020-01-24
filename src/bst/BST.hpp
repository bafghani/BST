/**
 * Name: Joseph Mattingly
 * Name: Bijan Afghani
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
 * Binary Search Tree: A data Structure composed of Nodes containing
 * some arbitrary datatype. Each Node may have up to 2 children Nodes.
 * The left child being of lesser value than the parent, and the right
 * child being of greater value than the parent. This organization allows
 * for more efficient search algorithms that run in O(log(n)) time.
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

    /** Copy constructor */
    BST(const BST<Data>& bst) : root(0), isize(0), iheight(-1) {
        auto orderedVector = bst.inorder();
        root = buildSubtree(orderedVector, 0, orderedVector.size(), -1);
    }

    /** BST destructor to properly deallocate memory of BST
     * to avoid memory leaks
     */
    ~BST() { deleteAll(root); }

    /**
     * Inserts a BSTnode into the BST.
     *
     * Takes in reference to a data item and sets inserted
     * BSTnode's data equal to the data item's value. If
     * the data item value already exists in the BST, no BSTnode
     * will be inserted.
     *
     * @param item value of data for inserted BSTNode.
     * @return true if BSTNode inserted, false otherwise.
     */
    bool insert(const Data& item) {  // Creates root node if tree doesn't exist

        if (root == nullptr) {
            root = new BSTNode<Data>(item);
            isize++;
            iheight = 0;
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
                    iheight = height();
                    return true;
                } else if (curr->left != nullptr) {
                    curr = curr->left;
                }
            } else if (curr->getData() < item) {
                if (curr->right == nullptr) {
                    curr->right = new BSTNode<Data>(item);
                    curr->right->parent = curr;  // Reassigns pointer
                    isize++;
                    iheight = height();
                    return true;
                } else if (curr->right != nullptr) {
                    curr = curr->right;
                }
            }
        }

        // Returns false if node with data == item exists

        return false;
    }

    /** searches for a node containing data equivalent to item
     * and returns an iterator pointing to that node if it exists
     * otherwise it returns an iterator pointing to a nullptr
     */
    iterator find(const Data& item) const {
        BSTNode<Data>* curr = root;
        if (root == nullptr) {
            return end();
        }
        while (curr != nullptr) {
            if (item < curr->getData()) {
                if (curr->left == nullptr) {
                    return BST<Data>::iterator(0);
                }
                curr = curr->left;
            } else if (curr->getData() < item) {
                if (curr->right == nullptr) {
                    BST<Data>::iterator(0);
                }
                curr = curr->right;
            } else {
                return BST<Data>::iterator(curr);
            }
        }
    }

    /** This function searches for a node containing data
     * equivalent to item. If it exists, that node is removed from the tree.
     * This function returns true if a node is successfully deleted,
     * false otherwise
     */
    bool deleteNode(const Data& item) {
        if (root == nullptr) {
            return false;
        }
        BSTNode<Data>* curr = root;

        // while curr->getData() != item

        BSTIterator<Data> iter = find(item);
        BSTIterator<Data> none = BSTIterator<Data>(nullptr);
        if (iter.operator==(none)) {
            return false;
        }
        curr = iter.getNode();

        // if curr->getData() == item then this code will execute
        // case 1 (no children)
        if (curr->left == nullptr && curr->right == nullptr) {
            // remove edge from curr->parent to curr
            if (curr->parent != nullptr) {
                if (curr == curr->parent->left) {
                    curr->parent->left = nullptr;
                } else {
                    curr->parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }
            isize--;
            delete curr;
        }

        // case 2 (1 child)
        else if (curr->left == nullptr || curr->right == nullptr) {
            // curr->parent point to curr->child instead of to curr
            if (curr == root) {
                // root has right child
                if (curr->left == nullptr) {
                    root = curr->right;
                    curr->right->parent = nullptr;
                }
                // root has left child
                else {
                    root = curr->left;
                    curr->left->parent = nullptr;
                }
            }
            // curr has a right child
            else if (curr->left == nullptr) {
                // curr is its parents left child
                if (curr == curr->parent->left) {
                    curr->parent->left = curr->right;
                    curr->right->parent = curr->parent;
                }
                // curr is its parents right child
                else {
                    curr->parent->right = curr->right;
                    curr->right->parent = curr->parent;
                }
            }
            // curr has a left child
            else if (curr->right == nullptr) {
                // curr is its parents left child
                if (curr == curr->parent->left) {
                    curr->parent->left = curr->left;
                    curr->left->parent = curr->parent;
                }
                // curr is its parents right child
                else {
                    curr->parent->right = curr->left;
                    curr->left->parent = curr->parent;
                }
            }
            iheight = height();
            isize--;
            delete curr;

        }

        // case 3 (2 children)
        else {
            BSTNode<Data>* s = curr->successor();

            if (s == s->parent->right) {
                // case 1 s is right child with right child
                if (s->right != nullptr) {
                    s->right->parent = curr;
                    curr->right = curr->right->right;

                }
                // case 2 s is right child with no children
                else if (s->right == nullptr && s->left == nullptr) {
                    curr->right = nullptr;
                }
            }

            // left child
            else {
                // case 3 s is left child with no children
                if (s->right == nullptr && s->right == nullptr) {
                    s->parent->left = nullptr;
                }
                // left child with right child
                if (s->right != nullptr) {
                    s->right->parent = s->parent;
                    s->parent->left = s->right;
                }
            }
            curr->setData(s->getData());
            delete s;
            isize--;
        }

        iheight = height();
        return true;
    }

    /** returns the number of nodes in the BST*/
    unsigned int size() const { return isize; }

    /** returns the maximum depth of the BST */
    int height() const { return getHeight(root); }

    /** returns true if there are no nodes in the BST, false otherwise */
    bool empty() const {
        if (isize == 0) {
            return true;
        } else {
            return false;
        }
    }

    /** returns an iterator pointing to the root of the BST */
    iterator begin() const { return BST<Data>::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST. */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Returns a vector containing the elements of our BST
     * in the order of the inorder traversal. (Left, Root, Right)
     */
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

    /** Recursively deletes all Nodes of the BST
     *  Helper method for BST destructor
     */
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
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        BSTNode<Data>* root = new BSTNode<Data>(data[mid]);
        isize++;

        root->left = buildSubtree(data, start, mid - 1, depth);
        root->left->parent = root;
        depth++;
        root->right = buildSubtree(data, mid + 1, end, depth);
        root->right->parent = root;

        return root;
    }

    // Add more helper functions below
    // Helper Method to determine maximum Depth of BST
    int getHeight(BSTNode<Data>* n) const {
        if (n == nullptr) {
            return -1;
        }
        if (n->left == nullptr && n->right == nullptr) {
            return 0;
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
