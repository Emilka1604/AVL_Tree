#include "stack.h"//
#include <ctime>
#include <locale>
#include <string>
int main() {
	AVL_Tree<char> a;
	a.insert(a.GetRoot(), 3, 'A');
	a.insert(a.GetRoot(), 5, 'B');
	a.insert(a.GetRoot(), 6, 'C');
	a.insert(a.GetRoot(), 7, 'D');
	a.insert(a.GetRoot(), 10, 'Q');
	a.insert(a.GetRoot(), 1, 'L');
	a.remove(7);
	a.remove(5);
	a.remove(3);
	a.remove(6);
	a.Print(a.GetRoot());
	//(a.GetRoot())->Print();
	return 0;
}