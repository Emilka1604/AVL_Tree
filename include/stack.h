#pragma once//
#include <exception>
#include <iostream>
#include <locale>
#include <string>
#include <stack>

template<class T>
	class Node
	{
	private:
		int key;
		T data;
		Node<T>* left;
		Node<T>* right;
		int height;
		Node(int key = 0, T data = T())
		{
			this->data = data;
			this->key = key;
			left = right = nullptr;
			height = 1;
		}
	public:
		int GetKey()
		{
			return key;
		}
		Node<T>* GetLeft()
		{
			return left;
		}
		Node<T>* GetRight()
		{
			return right;
		}
		template<typename T> friend class AVL_Tree;
	};
template <class T>
class AVL_Tree
{
private:
	Node<T>* root;
	int Height(Node<T>*);
	void refreshHeight(Node<T>*);
	int GetBalance(Node<T>*);
	Node<T>* rotateLeft(Node<T>*);
	Node<T>* rotateRight(Node<T>*);
	Node<T>* Balance(Node<T>*);
	Node<T>* ins(Node<T>*, int, T);
	Node<T>* rem(Node<T>*, int);
	Node<T>* search_min(Node<T>*);
	Node<T>* remove_min(Node<T>*);
public:
	AVL_Tree();
	void remove(Node<T>*, int);
	void insert(Node<T>*, int, T);
	Node<T>* search(Node<T>*, int);
	Node<T>* GetRoot();
	Node<T>* t_min(Node<T>*);
	Node<T>* t_max(Node<T>*);
};
template<class T>
AVL_Tree<T>::AVL_Tree()
{
	root = nullptr;
}
template<class T>
void AVL_Tree<T>::remove(Node<T>* a, int key)
{
	root = rem(a, key);
}
template<class T>
Node<T>* AVL_Tree<T>::GetRoot()
{
	return root;
}
template<class T>
Node<T>* AVL_Tree<T>::t_min(Node<T>* a)
{
	if (a->left != nullptr)
		return t_min(a->left);
	return a;
}
template<class T>
inline Node<T>* AVL_Tree<T>::t_max(Node<T>* a)
{
	if (a->right != nullptr)
		return t_max(a->right);
	return a;
}
template<class T>
int AVL_Tree<T>::Height(Node<T>* a)
{
	if (a != nullptr)
		return a->height;
	else
		return 0;
}
template<class T>
void AVL_Tree<T>::refreshHeight(Node<T>* a)
{
	if (Height(a->left) > Height(a->right))
		a->height = Height(a->left) + 1;
	else
		a->height = Height(a->right) + 1;
}
template<class T>
int AVL_Tree<T>::GetBalance(Node<T>* a)
{
	return Height(a->left) - Height(a->right);
}
template<class T>
Node<T>* AVL_Tree<T>::rotateLeft(Node<T>* a)
{
	Node<T>* tmp = a->right;
	a->right = tmp->left;
    tmp->left = a;
	refreshHeight(a);
	refreshHeight(tmp);
	return tmp;
}
template<class T>
Node<T>* AVL_Tree<T>::rotateRight(Node<T>* a)
{
	Node<T>* tmp = a->left;
	a->left = tmp->right;
	tmp->right = a;
	refreshHeight(a);
	refreshHeight(tmp);
	return tmp;
}
template<class T>
Node<T>* AVL_Tree<T>::Balance(Node<T>* a)
{
	if (a != nullptr)
	{
		refreshHeight(a);
		if (GetBalance(a) == -2)
		{
			if (GetBalance(a->right) == 1)
				a->right = rotateRight(a->right);
			return rotateLeft(a);
		}
		else
			if (GetBalance(a) == 2)
			{
				if (GetBalance(a->left) == -1)
					a->left = rotateLeft(a->left);
				return rotateRight(a);
			}
	}
	return a;
}
template<class T>
Node<T>* AVL_Tree<T>::ins(Node<T>* a, int key, T data)
{
		if (a == nullptr)
		{
			return new Node<T>(key, data);
		}
		else
			if (key < a->key)
				a->left = ins(a->left, key, data);
			else
				if (key > a->key)
					a->right = ins(a->right, key, data);
				else
				{
					std::exception ex("Элемент с данным ключом уже есть в дереве");
					throw ex;
				}
	return Balance(a);
}
template<class T>
void AVL_Tree<T>::insert(Node<T>* a, int key, T data)
{
	root = ins(a, key, data);
}
template<class T>
Node<T>* AVL_Tree<T>::search(Node<T>* a, int key)
{
	if (a == nullptr)
	{
		std::exception ex("В дереве нет элемента с таким ключом");
		throw ex;
	}
	if (key < a->key)
		return search(a->left, key);
	else
		if (key > a->key)
			return search(a->right, key);
		else
			return a;
}
template<class T>
Node<T>* AVL_Tree<T>::search_min(Node<T>* a)
{
	if (a->left != nullptr)
		return search_min(a->left);
	else
		return a;
}
template<class T>
Node<T>* AVL_Tree<T>::remove_min(Node<T>* a)
{
	if (a->left == nullptr)
		return a->right;
	a->left = remove_min(a->right);
	return Balance(a);
}
template<class T>
Node<T>* AVL_Tree<T>::rem(Node<T>* a, int key)
{
	if (a == nullptr)
	{
		std::exception ex("В дереве нет элемента с таким ключом");
		throw ex;
	}
	if (key < a->key)
		a->left = rem(a->left, key);
	else
		if (key > a->key)
			a->right = rem(a->right, key);
		else
		{
			Node<T>* tmp_1 = a->left;
			Node<T>* tmp_2 = a->right;
			delete[] a;
			if (tmp_2 == nullptr)
				return tmp_1;
			Node<T>* min = search_min(tmp_2);
			min->right = remove_min(tmp_2);
			min->left = tmp_1;
			return Balance(min);
		}
	return Balance(a);
}





