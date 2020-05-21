#include "stack.h"//
#include <gtest.h>
TEST(AVL_Tree, can_insert_in_tree)
{
	AVL_Tree<char> a;
	a.insert(3, 'A');
	a.insert(5, 'B');
	a.insert(6, 'C');
	a.insert(7, 'D');
	EXPECT_TRUE(a.GetRoot()->GetRight()->GetKey() == 6);
}
TEST(AVL_Tree, can_not_insert_in_tree_nods_with_equal_keys)
{
	AVL_Tree<char> a;
	a.insert(10, 'A');
	ASSERT_ANY_THROW(a.insert(10, 'B'));
}
TEST(AVL_Tree, can_remove_node)
{
	AVL_Tree<char> a;
	a.insert(100, 'D');
	a.remove(100);
	ASSERT_ANY_THROW(a.search(100));
}
TEST(AVL_Tree, can_not_remove_node_which_does_not_exist_in_tree)
{
	AVL_Tree<char> a;
	a.insert(1, 'H');
	ASSERT_ANY_THROW(a.remove(4));
}
TEST(AVL_Tree, can_search)
{
	AVL_Tree<char> a;
	a.insert(5, 'K');
	a.insert(12, 'Y');
	a.insert(76, 'W');
	a.insert(32, 'Q');
	a.insert(54, 'J');
	a.insert(11, 'Z');
	EXPECT_TRUE(a.search(76)->GetKey() == 76);
}
TEST(AVL_Tree, can_not_search_node_which_does_not_exist_in_tree)
{
	AVL_Tree<char> a;
	a.insert(2, 'U');
	a.insert(1, 'P');
	a.insert(9, 'R');
	ASSERT_ANY_THROW(a.search(38));
}
TEST(AVL_Tree, can_find_min_in_tree)
{
	AVL_Tree<char> a;
	a.insert(76, 'X');
	a.insert(64, 'E');
	a.insert(23, '%');
	a.insert(55, 'I');
	a.insert(12, 'O');
	EXPECT_EQ(a.t_min()->GetKey(), 12);
}
TEST(AVL_Tree, can_find_max_in_tree)
{
	AVL_Tree<char> a;
	a.insert(76, 'X');
	a.insert(64, 'E');
	a.insert(23, '%');
	a.insert(55, 'I');
	a.insert(12, 'O');
	EXPECT_EQ(a.t_max()->GetKey(), 76);
}


