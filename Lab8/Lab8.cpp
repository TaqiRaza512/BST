#include<iostream>
#include"BST.h"
#include<queue>
using namespace std;
int main()
{
	BST B;
	B.InsertValue(23);
	B.InsertValue(45);
	B.InsertValue(12);
	B.InsertValue(1);
	B.InsertValue(2);
	cout << endl;
	BST A;
	A.InsertValue(45);
	A.InsertValue(1);
	A.InsertValue(2);
	A.InsertValue(23);
	A.InsertValue(12);
	cout << endl;
	cout << endl;
	A.OutputTree();
}