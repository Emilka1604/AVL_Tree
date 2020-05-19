#include "stack.h"//
#include <gtest.h>
TEST(AVL_Tree, can_insert_in_tree)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 3, 'A');
	a.insert(a.GetRoot(), 5, 'B');
	a.insert(a.GetRoot(), 6, 'C');
	a.insert(a.GetRoot(), 7, 'D');
	EXPECT_TRUE(a.GetRoot()->GetRight()->GetKey() == 6);
}
TEST(AVL_Tree, can_not_insert_in_tree_nods_with_equal_keys)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 10, 'A');
	ASSERT_ANY_THROW(a.insert(a.GetRoot(), 10, 'B'));
}
TEST(AVL_Tree, can_remove_node)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 100, 'D');
	a.remove(100);
	ASSERT_ANY_THROW(a.search(a.GetRoot(), 100));
}
TEST(AVL_Tree, can_not_remove_node_which_does_not_exist_in_tree)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 1, 'H');
	ASSERT_ANY_THROW(a.remove(4));
}
TEST(AVL_Tree, can_search)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 5, 'K');
	a.insert(a.GetRoot(), 12, 'Y');
	a.insert(a.GetRoot(), 76, 'W');
	a.insert(a.GetRoot(), 32, 'Q');
	a.insert(a.GetRoot(), 54, 'J');
	a.insert(a.GetRoot(), 11, 'Z');
	EXPECT_TRUE(a.search(a.GetRoot(), 76)->GetKey() == 76);
}
TEST(AVL_Tree, can_not_search_node_which_does_not_exist_in_tree)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 2, 'U');
	a.insert(a.GetRoot(), 1, 'P');
	a.insert(a.GetRoot(), 9, 'R');
	ASSERT_ANY_THROW(a.search(a.GetRoot(), 38));
}
TEST(AVL_Tree, can_find_min_in_tree)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 76, 'X');
	a.insert(a.GetRoot(), 64, 'E');
	a.insert(a.GetRoot(), 23, '%');
	a.insert(a.GetRoot(), 55, 'I');
	a.insert(a.GetRoot(), 12, 'O');
	EXPECT_EQ(a.t_min()->GetKey(), 12);
}
TEST(AVL_Tree, can_find_max_in_tree)
{
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 76, 'X');
	a.insert(a.GetRoot(), 64, 'E');
	a.insert(a.GetRoot(), 23, '%');
	a.insert(a.GetRoot(), 55, 'I');
	a.insert(a.GetRoot(), 98, 'O');
	EXPECT_EQ(a.t_max()->GetKey(), 98);
}


