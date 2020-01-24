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
#include "BSTNode.hpp"

using namespace std;
using namespace testing;

TEST(BST_NODE_TESTS, TEST_SUCCESSOR) {
    BSTNode<int> node(3);
    ASSERT_EQ(node.successor(), nullptr);
}

TEST(BST_NODE_TESTS, TEST_SUCCESSOR_2) {
    BSTNode<int> node(4);
    ASSERT_EQ(node.successor(), nullptr);
}
TEST(BST_NODE_TESTS, TEST_GETDATA) {
    BSTNode<int> node(4);
    ASSERT_EQ(node.getData(), 4);
}
TEST(BST_NODE_TESTS, TEST_SETDATA) {
    BSTNode<int> node(4);
    node.setData(5);
    ASSERT_EQ(node.getData(), 5);
}