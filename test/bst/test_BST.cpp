/**
 * Name: Joseph Mattingly
 * Name: Bijan Afghani
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

// TODO: add more BST tests here
TEST_F(SmallBSTFixture, HEIGHT_TEST) {
    // assert height is 2
    ASSERT_EQ(bst.height(), 2);
}

TEST_F(SmallBSTFixture, INSERT_TEST) {
    // assert successful insertion
    ASSERT_TRUE(bst.insert(50));
}

TEST_F(SmallBSTFixture, EMPTY_TEST) {
    // assert tree is not empty
    ASSERT_FALSE(bst.empty());
}

TEST_F(SmallBSTFixture, INORDER_TEST) {
    // assert correct inorder traversal
    vector<int> vect;
    vect.push_back(-33);
    vect.push_back(1);
    vect.push_back(3);
    vect.push_back(4);
    vect.push_back(100);
    ASSERT_EQ(bst.inorder(), vect);
<<<<<<< HEAD
}
=======
}

TEST_F(SmallBSTFixture, DELETE_ALL) {
    bst.~BST();
    ASSERT_TRUE(bst.insert(3));
}
>>>>>>> 91a384cff71631d4eb4fdd794e187b1bee5eed0f
