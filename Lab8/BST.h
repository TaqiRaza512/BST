#pragma once
#include<queue>
#include<list>
#include<fstream>
#include<vector>
using namespace std;
class BST
{
	friend class Node;
private:
	class Node
	{
		friend class BST;
	private:
		int Data;
		Node* Right;
		Node* Left;
		Node* Parent;
		Node* Next;
		Node* Previous;
		int size;
		int Height;
	public:
		Node(int d=0, Node* R= nullptr,Node* L= nullptr,Node* P=nullptr, Node* prev = nullptr, Node* n = nullptr)
		{
			Height = 1;
			size = 1;
			Data = d;
			Right = R;
			Left = L;
			Parent = P;
			Previous = prev;
			Next = n;
		}
	};
	Node* Root;
	void InsertValue(int value, Node*& Root, Node* Parent);
	void PrintLNR(Node* Root);
	void PrintNLR(Node* Root);
	void PrintLRN(Node* Root);
	void PrintRLN(Node* Root);
	void PrintLeaves(Node*Root);
	void NodesAtDistanceK(Node* Root, int K);
	void PrimeCounts(Node* Root,int &count);
	void EvenCounts(Node* Root, int& count);
	int Height(Node* Root);
	bool PictoriallyWise(Node* Root, Node* BRoot);
	void InsertValuesInAscOrder(Node* Root, vector<int>&VS);
	int TreeMinimum(Node*Root);
	int TreeMaximum(Node* Root);
	bool IsBalancedTree(Node*Root);
	Node*& ClosestLeaf(queue<Node*>& Vs);
	Node*& FarthestLeaf(queue<Node*>& Vs,Node*& Temp);
	void CountingInternalNodes(Node* Root, int& count);
	void CountingLeaves(Node* Root, int& count);
	void CountingOneBranchOut(Node* Root, int& count);
	bool IsValidBST(Node*Root,int max,int min);


	Node* LCA_recursion(Node* r, Node* n1, Node* n2)
	{
		if (r == n1 || r == n2)														
			return r;
		if (r == nullptr)
			return nullptr;

		Node* left = LCA_recursion(r->Left, n1, n2);							
		Node* right = LCA_recursion(r->Right, n1, n2);							
		if (left == nullptr && right == nullptr)								
			return nullptr;
		if (left != nullptr && right != nullptr)								
			return r;
		if (left != nullptr)													
			return left;
		if (right != nullptr)													
			return right;
	}
	//Section 2
	void Delete_Case1(Node*& temp);
	void Delete_Case2(Node*& temp);
	void Delete_Case3(Node*& temp);
	void OutputTree_recursion(Node* temp, int pos);
	//Section 3
	void SaveTree_Rec(ofstream& fout, Node* r);

	BST BST_SortedArray_Rec(BST& BST, vector<int> data, int index, int size);

	void RangeSearch_RecAscending(Node* r, int v1, int v2);
	void RangeSearch_RecDescending(Node* r, int v1, int v2);
	bool IsSubtree_Rec(Node* r, Node* r2);
 


public:
	class Iterator
	{
		friend class BSTree;
	public:
		Node* i;

		Iterator(Node* n)
		{
			i = n;
		}

		int operator*()
		{
			return i->Data;
		}

		bool operator==(Iterator n)
		{
			return i == n.i;
		}

		bool operator!=(Iterator n)
		{
			return i != n.i;
		}
	};
	class LNR_iterator
	{
		friend class BSTree;
	public:
		Node* i;
		LNR_iterator(Node* n)
		{
			i = n;
		}

		int operator*()
		{
			return i->Data;
		}

		Node* Min(Node* temp)
		{
			while (temp->Left!= nullptr)
				temp = temp->Left;
			return temp;
		}

		Node* Max(Node* temp)
		{
			while (temp->Right != nullptr)
				temp = temp->Right;
			return temp;
		}

		Node* Successor(Node* r)
		{
			if (r->Right != nullptr)
			{
				return Min(r->Right);
			}
			while (r->Parent != nullptr && r->Parent->Right== r)
				r = r->Parent;
			return r->Parent;
		}

		Node* Predecessor(Node* r)
		{
			if (r->Left != nullptr)
			{
				return Max(r->Left);
			}
			while (r->Parent != nullptr && r->Parent->Left== r)
				r = r->Parent;
			return r->Parent;
		}

		LNR_iterator operator++()
		{
			i = Successor(i);
			return *this;
		}

		LNR_iterator operator--()
		{

			i = Predecessor(i);
			return *this;
		}

		bool operator==(LNR_iterator n)
		{
			return i == n.i;
		}

		bool operator!=(LNR_iterator n)
		{
			return i != n.i;
		}
	};
	Iterator Start()
	{
		return Iterator(Root);
	}
	Iterator End()
	{
		return Iterator(nullptr);
	}
	Iterator Search(int val)
	{
		Node* temp = Root;
		if (val == Root->Data)
		{
			return Iterator(temp);
		}

		while (temp != nullptr)
		{
			if (temp->Data == val)
				return temp;
			else if (temp->Data > val)
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		return Iterator(temp);
	}
	LNR_iterator LNR_Start()
	{
		LNR_iterator temp(Root);
		return temp.Min(temp.i);
	}
	LNR_iterator LNR_End()
	{
		LNR_iterator temp(Root);
		return temp.Max(temp.i);
	}
	LNR_iterator LCA(LNR_iterator i1, LNR_iterator i2)
	{
		return LCA_recursion(Root, i1.i, i2.i);
	}

	BST(Node* R = nullptr);
	void InsertValue(int value);
	void PrintLNR();
	void PrintNLR();
	void PrintLRN();
	void PrintRLN();
	void PrintLeaves();
	void NodesAtDistanceK(int K);
	int PrimeCounts();
	int EvenCounts();
	int Height();
	bool PictoriallyWise(BST Tree);
	bool ValueWise(BST Tree);
	int TreeMinimum();
	int TreeMaximum();
	bool IsBalancedTree();
	int  ClosestLeaf();
	int  FarthestLeaf();
	void ClosestPathToLeaf();
	Node*& ClosestLeafForPath();
	Node*& FarthestLeafForPath();
	void FarthestPathToLeaf();
	bool IsLeaf(Node* Temp);
	int CountingInternalNodes();
	int CountingLeaves();
	int CountingOneBranchOut();
	bool IsValidBST();
	void LNR_Alternative_Print();

	//Section 2
	
	void Deletion(int value);
	void OutputTree();


	//Section 3 
	void Load_Tree();
	void Save_Tree();
	void RangeSearch(int v1, int v2);
	BST BST_SortedArray(vector<int> data);
	vector<list<Node*>> Linked_List();
	bool IsSubtree(BST T2);


};

