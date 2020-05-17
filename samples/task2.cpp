#include "stack.h"
#include <ctime>
#include <locale>
#include <string>
int main() {
	AVL_Tree<char> a;
	a.insert(3, 'A');
	a.insert(5, 'B');
	a.insert(6, 'C');
	a.insert(7, 'D');
	a.Print(a.GetRoot());
	return 0;
}