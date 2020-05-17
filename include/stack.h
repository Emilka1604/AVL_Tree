#pragma once
#include <exception>
#include <iostream>
#include <locale>
#include <string>

template<class T>
	class Node
	{
	private:
		int key;
		int h_def;
		T data;
		Node<T>* p;
		Node<T>* left;
		Node<T>* right;
		Node(int key = 0, T data = T())
		{
			this->key = key;
			this->data = data;
			h_def = 0;
			p = left = right = 0;
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
		Node<T>* GetParrent()
		{
			return p;
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
			std::cout << "(" << key << ", " << data << ")";
		}
		
		template<typename T> friend class AVL_Tree;
	};
template <class T>
class AVL_Tree
{
private:
	Node<T>* root;
	int size;
	void rotateLeft(Node<T>*);
	void rotateRight(Node<T>*);
	void bigRotateLeft(Node<T>*);
	void bigRotateRight(Node<T>*);
	Node<T>* UnderTheTreeMin(Node<T>*);
	Node<T>* UnderTheTreeMax(Node<T>*);
	void Distruct(Node<T>*);
public:
	Node<T>* t_max();
	Node<T>* t_min();
	Node<T>* search(int);
	void remove(int);
	AVL_Tree();
	void insert(int, T);
	void Print(Node<T>*);
	Node<T>* GetRoot()
	{
		return root;
	}
	~AVL_Tree();


};
template<class T>
AVL_Tree<T>::AVL_Tree()
{
	size = 0;
	root = nullptr;
}
template<class T>
void AVL_Tree<T>::rotateLeft(Node<T>* a)
{
	Node<T>* b = a->right;
	Node<T>* tmp_1 = b->left;
	b->left = a;
	Node<T>* tmp_2 = a->p;
	a->p = b;
	a->right = tmp_1;
	if (tmp_1 != nullptr)
	{
		tmp_1->p = a;
	}
	b->p = tmp_2;
	if (tmp_2 == nullptr)
	{
		root = b;
	}
	else
		if (a == tmp_2->left)
		{
			tmp_2->left = b;
		}
		else
		{
			tmp_2->right = b;
		}
	if (b->h_def == -1)
	{
		a->h_def = 0;
		b->h_def = 0;
	}
	else
		if (b->h_def == 0)
		{
			a->h_def = -1;
			b->h_def = 1;
		}
}
template<class T>
void AVL_Tree<T>::rotateRight(Node<T>* a)
{
	Node<T>* b = a->left;
	Node<T>* tmp_1 = b->right;
	b->right = a;
	Node<T>* tmp_2 = a->p;
	a->p = b;
	a->left = tmp_1;
	if (tmp_1 != nullptr)
	{
		tmp_1->p = a;
	}
	b->p = tmp_2;
	if (tmp_2 == nullptr)
	{
		root = b;
	}
	else
		if (a == tmp_2->left)
		{
			tmp_2->left = b;
		}
		else
		{
			tmp_2->right = b;
		}
	if (b->h_def == 1)
	{
		a->h_def = 0;
		b->h_def = 0;
	}
	else
		if (b->h_def == 0)
		{
			a->h_def = 1;
			b->h_def = -1;
		}
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
void AVL_Tree<T>::insert(int key, T data)
{
	Node<T>* new_Node = new Node<T>(key, data);
	Node<T>* a = root;
	if (a == nullptr)
	{
		root = new_Node;
	}
	else
	{
		Node<T>* b;
		while (a != nullptr)
		{
			b = a;
			if (new_Node->key < a->key)
			{
				a = a->left;
			}
			else
				if (new_Node->key > a->key)
				{
					a = a->right;
				}
				else
				{
					std::exception ex("Ключ с таким значением уже есть в дереве!");
					throw ex;
				}
		}
		if (new_Node->key < b->key)
		{
			b->left = new_Node;
		}
		else
		{
			b->right = new_Node;
		}
		new_Node->p = b;
		a = new_Node;
		size++;
		if (a == b->right)
		{
			b->h_def--;
		}
		else
		{
			b->h_def++;
		}
		a = b;
		b = b->p;
		if (a->h_def != 0)
		{
			while (b != nullptr)
			{
				if (a == b->right)
				{
					b->h_def--;
					if (b->h_def == 0)
					{
						break;
					}
					else
						if (b->h_def == -1)
						{
							a = a->p;
							b = b->p;
						}
						else
						{
							if (a->h_def == 1)
							{
								a = a->p;
								b = b->p;
								bigRotateLeft(a);
							}
							else
							{
								a = a->p;
								b = b->p;
								rotateLeft(a);
							}
						}
				}
				else
				{
					b->h_def++;
					if (b->h_def == 0)
					{
						break;
					}
					else
						if (b->h_def == 1)
						{
							a = a->p;
							b = b->p;
						}
						else
						{
							if (a->h_def == -1)
							{
								a = a->p;
								b = b->p;
								bigRotateRight(a);
							}
							else
							{
								a = a->p;
								b = b->p;
								rotateRight(a);
							}
						}
				}
				if (b != a->p)
				{
					if (b == nullptr)
					{
						break;
					}
					else
						if (a->key > b->key)
						{
							a = b->right;
						}
						else
							if (a->key < b->key)
							{
								a = b->left;
							}

				}
				if (a->h_def == 0)
				{
					break;
				}
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
Node<T>* AVL_Tree<T>::search(int key)
{
	if (root == nullptr)
	{
		std::exception ex("Дерево пустое");
		throw ex;
	}
	Node<T>* a = root;
	while (a != nullptr)
	{
		if (a->key > key)
		{
			a = a->left;
		}
		else
			if (a->key < key)
			{
				a = a->right;
			}
			else
			{
				return a;
			}
	}
	std::exception ex1("Элемента с данным ключом нет в дереве");
	throw ex1;
}

template<class T>
void AVL_Tree<T>::remove(int key)
{
	Node<T>* del_node = search(key);
	Node<T>* a;
	Node<T>* b;
	if (del_node->left == nullptr && del_node->right == nullptr)
	{
		a = del_node;
		b = a->p;
		if (del_node == root)
		{
			root = nullptr;
		}
	}
	else
	{
		if (del_node->h_def > 0)
		{
			a = UnderTheTreeMax(del_node->left);
		}
		else
		{
			a = UnderTheTreeMin(del_node->right);
		}
		del_node->key = a->key;
		del_node->data = a->data;
		b = a->p;
		
			if (a == UnderTheTreeMax(del_node->left))
			{
				if (del_node->left == a && a->left != nullptr)
				{
					b->left = a->left;
					a->left->p = b;
					del_node = a;
					a = b->left;
				}
				if (a->left != nullptr)
				{
					b->right = a->left;
					a->left->p = b;
					del_node = a;
					a = b->right;
				}
				else
				{
					del_node = a;
				}
			}
			else
				if (a == UnderTheTreeMin(del_node->right))
				{
					if (del_node->right == a && a->right != nullptr)
					{
						b->right = a->right;
						a->right->p = b;
						del_node = a;
						a = b->right;
					}
					else
					     if (a->right != nullptr)
					     {
						  b->left = a->right;
						  a->right->p = b;
						  del_node = a;
						  a = b->left;
					      }
					        else
					        {
						        del_node = a;
					        }
				}
		
	}
		while (b != nullptr)
		{
			if (a == b->right)
			{
				b->h_def++;
				if (b->h_def == 0)
				{
					a = a->p;
					b = b->p;
				}
				else
					if (b->h_def == 2)
					{
						if (b->left->h_def == -1)
						{
							b = b->p;
							a = a->p;
							bigRotateRight(a);
						}
						else
						{
							b = b->p;
							a = a->p;
							rotateRight(a);
						}
					}
					else
					{
						break;
					}

			}
			else
			{
				b->h_def--;
				if (b->h_def == 0)
				{
					a = a->p;
					b = b->p;
				}
				else
					if (b->h_def == -2)
					{
						if (b->right->h_def == 1)
						{
							b = b->p;
							a = a->p;
							bigRotateLeft(a);
						}
						else
						{
							b = b->p;
							a = a->p;
							rotateLeft(a);
						}
					}
					else
					{
						break;
					}
			}
			if (b != a->p)
			{
				if (b == nullptr)
				{
					break;
				}
				else
					if (a->key > b->key)
					{
						a = b->right;
					}
					else
						if (a->key < b->key)
						{
							a = b->left;
						}
			}
			if (a->h_def == -1 || a->h_def == 1)
			{
				break;
			}

		}
		if (del_node != nullptr && del_node->p != nullptr)
		{
			if (del_node->p->left == del_node)
			{
				del_node->p->left = nullptr;
			}
			else
				if (del_node->p->right == del_node)
				{
					del_node->p->right = nullptr;
				}
		}
		delete[] del_node;
	size--;
}


