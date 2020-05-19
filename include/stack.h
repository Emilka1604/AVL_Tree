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
		int h_def;
		T data;
		Node<T>* left;
		Node<T>* right;
		Node(int key = 0, T data = T())
		{
			this->key = key;
			this->data = data;
			h_def = 0;
            left = right = 0;
		}
	public:
		int GetKey()
		{
			return key;
		}
		int GetH_def()
		{
			return h_def;
		}
		T GetData()
		{
			return data;
		}
		Node<T>* GetLeft()
		{
			return left;
		}
		Node<T>* GetRight()
		{
			return right;
		}
		void Print()
		{
			std::cout << "(" << key << ", " << data << ", "<< h_def<< ")";
		}
		
		template<typename T> friend class AVL_Tree;
	};
template <class T>
class AVL_Tree
{
private:
	Node<T>* root;
	Node<T>* tmp;
	int count;
	void rotateLeft(Node<T>*);
	void rotateRight(Node<T>*);
	void bigRotateLeft(Node<T>*);
	void bigRotateRight(Node<T>*);
	Node<T>* UnderTheTreeMin(Node<T>*);
	Node<T>* UnderTheTreeMax(Node<T>*);
	void Distruct(Node<T>*);
	Node<T>* GetParrent(Node<T>*);
	void Balance(Node<T>*);
public:
	Node<T>* t_max();
	Node<T>* t_min();
	Node<T>* search(Node<T>*, int);
	void remove(int);
	AVL_Tree();
	void insert(Node<T>*,int, T);
	void Print(Node<T>*);
	Node<T>* GetRoot()
	{
		return root;
	}
	~AVL_Tree();

};
template<class T>
Node<T>* AVL_Tree<T>::GetParrent(Node<T>* a)
{
	Node<T>* tmp = root;
	if (tmp == a)
		return nullptr;
	else
	{
		Node<T>* tmp1;
		while (tmp->key != a->key)
		{
			if (a->key < tmp->key)
			{
				tmp1 = tmp;
				tmp = tmp->left;
			}
			else
		    {
					tmp1 = tmp;
					tmp = tmp->right;
	        }
		}
		return tmp1;
	}
}
template<class T>
void AVL_Tree<T>::Balance(Node<T>* a)
{
	if (a->h_def == -2)
	{
		if (a->right->h_def == 1)
			bigRotateLeft(a);
		else
			rotateLeft(a);
	}
	else
		if (a->h_def == 2)
		{
			if (a->left->h_def == -1)
				bigRotateRight(a);
			else
				rotateRight(a);
		}
}
template<class T>
AVL_Tree<T>::AVL_Tree()
{
	count = 0;
	tmp = nullptr;
	root = nullptr;
}
template<class T>
void AVL_Tree<T>::rotateLeft(Node<T>* a)
{
	Node<T>* b = a->right;
	Node<T>* tmp = b->left;
	b->left = a;
	a->right = tmp;
	if (b->h_def == -1)
		a->h_def = b->h_def = 0;
	else
	{
		a->h_def = -1;
		b->h_def = 1;
	}
	Node<T>* p = GetParrent(a);
	if (p == nullptr)
		root = b;
	else
		if (a == p->left)
			p->left = b;
		else
			p->right = b;
}
template<class T>
void AVL_Tree<T>::rotateRight(Node<T>* a)
{
	Node<T>* b = a->left;
	Node<T>* tmp = b->right;
	b->right = a;
	a->left = tmp;
	if (b->h_def == 1)
		a->h_def = b->h_def = 0;
	else
	{
		a->h_def = 1;
		b->h_def = -1;
	}
	Node<T>* p = GetParrent(a);
	if (p == nullptr)
		root = b;
	else
		if (a == p->left)
			p->left = b;
		else
			p->right = b;

}
template<class T>
void AVL_Tree<T>::bigRotateLeft(Node<T>* a)
{
	rotateRight(a->right);
	rotateLeft(a);
}
template<class T>
void AVL_Tree<T>::bigRotateRight(Node<T>* a)
{
	rotateLeft(a->left);
	rotateRight(a);
}
template<class T>
Node<T>* AVL_Tree<T>::UnderTheTreeMin(Node<T>* a)
{
	while (a->left != nullptr)
	{
		a = a->left;
	}
	return a;
}
template<class T>
Node<T>* AVL_Tree<T>::UnderTheTreeMax(Node<T>* a)
{
	while (a->right != nullptr)
	{
		a = a->right;
	}
	return a;
}

template<class T>
void AVL_Tree<T>::insert(Node<T>* a, int key, T data)
{
	if (root == nullptr)
		root = new Node<T>(key, data);
	else
	{
		count = 0;
		if (key < a->key)
			if (a->left == nullptr)
			{
				a->left = new Node<T>(key, data);
				tmp = a->left;
			}
			else
				insert(a->left, key, data);
		else
			if (key > a->key)
				if (a->right == nullptr)
				{
					a->right = new Node<T>(key, data);
					tmp = a->right;
				}
				else
					insert(a->right, key, data);
			else
			{
				std::exception ex("Такой ключ уже есть в дереве");
				throw ex;
			}
		if (count == 0)
		{
			if (tmp == a->left)
				a->h_def++;
			else
				a->h_def--;
			tmp = GetParrent(a);
			Balance(a);
			if (tmp != nullptr)
			{
				if (a->key < tmp->key)
					tmp = tmp->left;
				else
					tmp = tmp->right;
				if (tmp->h_def == 0)
					count = 1;
			}
		}
	}
}

template<class T>
void AVL_Tree<T>::Print(Node<T>* a)
{
	if (a != nullptr)
	{
		Print(a->left);
		a->Print();
		Print(a->right);
	}
}

template<class T>
void AVL_Tree<T>::Distruct(Node<T>* a)
{
	if (a != nullptr)
	{
		Distruct(a->left);
		Distruct(a->right);
		delete[] a;
	}
}

template<class T>
AVL_Tree<T>::~AVL_Tree()
{
	Distruct(root);
}


template<class T>
Node<T>* AVL_Tree<T>::t_max()
{
	if (root == nullptr)
	{
		std::exception ex("Дерево пустое");
		throw ex;
	}
	Node<T>* a = root;
	while (a->right != nullptr)
	{
		a = a->right;
	}
	return a;
}
template<class T>
Node<T>* AVL_Tree<T>::t_min()
{
	if (root == nullptr)
	{
		std::exception ex("Дерево пустое");
		throw ex;
	}
	Node<T>* a = root;
	while (a->left != nullptr)
	{
		a = a->left;
	}
	return a;
}

template<class T>
Node<T>* AVL_Tree<T>::search(Node<T>* a, int key)
{
	if (a == nullptr)
	{
		std::exception ex("В дереве нет элемента с данным ключом");
		throw ex;
	}
	else
	{
		if (key < a->key)
			search(a->left, key);
		else
			if (key > a->key)
				search(a->right, key);
			else
				return a;
	}
}

template<class T>
void AVL_Tree<T>::remove(int key)
{
	if (root == nullptr)
	{
		std::exception ex("Дерево пустое");
		throw ex;
	}
	else
	{
		Node<T>* p = nullptr;
		Node<T>* a = root;
		std::stack<Node<T>*> stack;
		while (a->key != key)
		{
			stack.push(a);
			if (key < a->key)
				a = a->left;
			else
				if (key > a->key)
					a = a->right;
			if (a == nullptr)
			{
				std::exception ex("Элемента с данным ключом нет в дереве");
				throw ex;
			}
		}
		Node<T>* del_elem;
		del_elem = a;
		if (a->left == nullptr && a->right == nullptr)
		{
			if (!stack.empty())
			{
				tmp = del_elem;
				p = stack.top();
			}
		}
		else
		{
			stack.push(a);
			if (a->h_def > 0)
			{
				a = a->left;
				while (a->right != nullptr)
				{
					stack.push(a);
					a = a->right;
				}
				del_elem->key = a->key;
				del_elem->data = a->data;
				del_elem = a;
				if (del_elem == stack.top()->left)
				{
					stack.top()->left = del_elem->left;
					tmp = stack.top()->left;
				}
				else
				{
					stack.top()->right = del_elem->left;
					tmp = stack.top()->right;
				}
			}
			else
			{
				a = a->right;
				while (a->left != nullptr)
				{
					stack.push(a);
					a = a->left;
				}
				del_elem->key = a->key;
				del_elem->data = a->data;
				del_elem = a;
				if (del_elem == stack.top()->left)
				{
					stack.top()->left = del_elem->right;
					tmp = stack.top()->left;
				}
				else
				{
					stack.top()->right = del_elem->right;
					tmp = stack.top()->right;
				}
			}

		}
		while (!stack.empty())
		{
			if (tmp == stack.top()->left)
				stack.top()->h_def--;
			else
				stack.top()->h_def++;
			tmp = stack.top();
			stack.pop();
			if (tmp->h_def == -1 || tmp->h_def == 1)
				break;
			Balance(tmp);
		}
		if (p != nullptr)
		{
			if (del_elem == p->left)
				p->left = nullptr;
			else
				p->right = nullptr;
		}
		else
			root = nullptr;
		delete[] del_elem;
	}
}


