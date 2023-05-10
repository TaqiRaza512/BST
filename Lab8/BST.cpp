#include "BST.h"
#include<iostream>
#include<fstream>
#include<list>
#include<queue>
#include<vector>
using namespace std;

BST::BST(Node*R)
{
	Root = R;
}

void BST::InsertValue(int value)
{
	InsertValue(value, Root,nullptr);
}
void BST::InsertValue(int value, Node*& Root, Node* Parent)
{
	Node* temp = new Node(value);

	if (Root == nullptr)
	{
		Root = temp;
		Root->Parent = nullptr;
		return;
	}

	Node* temp2 = Root;
	LNR_iterator itr(temp);
	do
	{
		temp2->size++;
		if (temp2->Data > value)
		{
			if (temp2->Left == nullptr)
			{
				temp2->Left = temp;
				temp->Parent = temp2;


				temp->Next = itr.Successor(temp);
				temp->Previous = itr.Predecessor(temp);

				if (temp->Next != nullptr)
					temp->Next->Previous = temp;
				if (temp->Previous != nullptr)
					temp->Previous->Next = temp;
				break;

			}
			temp2 = temp2->Left;
		}
		else
		{
			if (temp2->Right == nullptr)
			{
				temp2->Right = temp;
				temp->Parent = temp2;

				temp->Next = itr.Successor(temp);
				temp->Previous = itr.Predecessor(temp);

				if (temp->Next != nullptr)
					temp->Next->Previous = temp;
				if (temp->Previous != nullptr)
					temp->Previous->Next = temp;
				break;
			}
			temp2 = temp2->Right;
		}
	} while (true);

	while (temp2 != nullptr)
	{
		temp2->Height = Height(temp2);
		temp2 = temp2->Parent;
	}
}

void BST::PrintLNR()
{
	PrintLNR(Root);
}
void BST::PrintLNR(Node * Root)
{

	if (!Root)
		return;

	PrintLNR(Root->Left);
	cout << Root->Data << "  ";
	PrintLNR(Root->Right);
}

void BST::PrintNLR()
{
	PrintNLR(Root);
}
void BST::PrintNLR(Node* Root)
{

	if (!Root)
		return;

	cout << Root->Data << "  ";
	PrintNLR(Root->Left);
	PrintNLR(Root->Right);
}

void BST::PrintLRN()
{
	PrintLRN(Root);
}
void BST::PrintLRN(Node* Root)
{

	if (!Root)
		return;

	PrintLRN(Root->Left);
	PrintLRN(Root->Right);
	cout << Root->Data << "  ";
}

void BST::PrintRLN()
{
	PrintRLN(Root);
}
void BST::PrintRLN(Node* Root)
{

	if (!Root)
		return;

	PrintRLN(Root->Right);
	PrintRLN(Root->Left);
	cout << Root->Data << "  ";
}

void BST::PrintLeaves()
{
	PrintLeaves(Root);
}
void BST::PrintLeaves(Node*Root)
{

	if (!Root)
		return;

	PrintLeaves(Root->Left);
	if (!Root->Left and !Root->Right)
		cout << Root->Data<<"  ";
	PrintLeaves(Root->Right);

}

void BST::NodesAtDistanceK(int K)
{

	NodesAtDistanceK(Root, K);

}
void  BST::NodesAtDistanceK(Node* Root, int K)
{
	queue<Node*>StoringNodes;
	Node* Temp=nullptr;
	StoringNodes.push(Root);
	StoringNodes.push(nullptr);
	int Distance = 0;
	while (true)
	{
		if (Distance==K)
			break;
		else
		{
			bool IsInsert;
			while (StoringNodes.front())
			{
				Temp = StoringNodes.front();
				if (Temp->Left)
				{
					IsInsert = true;
					StoringNodes.push(Temp->Left);

				}
				if (Temp->Right)
				{
					IsInsert = true;
					StoringNodes.push(Temp->Right);
				}
				StoringNodes.pop();

				if (StoringNodes.size() == 0)
				{
					break;
				}
			}
			if (IsInsert)
			{
				StoringNodes.push(nullptr);
				IsInsert = false;
			}
			if(!StoringNodes.empty())
				StoringNodes.pop();
		}
		Distance++;
	}
	if (!StoringNodes.empty())
	{
		while (StoringNodes.front())
		{
			cout << StoringNodes.front()->Data;
			cout << "  ";
			StoringNodes.pop();
			if (StoringNodes.empty())
				break;
		}
	}
}

int BST::PrimeCounts()
{
	int count=0;
	PrimeCounts(Root,count);
	return count;
}
bool IsPrime(int val)
{
	int count = 0;
		
	for (int ri=1;ri<=val;ri++)
	{
		if (val % ri == 0)
			count++;

	}
	if (count==2)
	{
		return true;
	}
	return false;
}
void BST::PrimeCounts(Node*Root,int& count)
{
	if (!Root)
		return;
	PrimeCounts(Root->Left,count);
	if (IsPrime(Root->Data))
	{
		count++;
	}
	PrimeCounts(Root->Right,count);

}

int BST::EvenCounts()
{
	int count = 0;
	EvenCounts(Root, count);
	return count;

}
void BST::EvenCounts(Node* Root, int& count)
{

	if (!Root)
		return;
	EvenCounts(Root->Left, count);
	if (Root->Data%2==0)
	{
		count++;
	}
	EvenCounts(Root->Right, count);
}

int Max(int a,int b)
{
	if (a > b)
		return a;
	return b;
}
int BST::Height(Node* Root)
{
	if (!Root)
		return 0;

	return 1+Max(Height(Root->Left),Height(Root->Right));
}
int  BST::Height()
{
	return Height(Root);
}

bool BST::PictoriallyWise(BST Tree)
{
	return PictoriallyWise(Root,Tree.Root);
}
bool BST::PictoriallyWise(Node* Root, Node* BRoot)
{
	if (Root->Left and BRoot->Left)
	{
		return true;
	}
	else if(!(!Root->Left and !BRoot->Left))
	{
		return false;
	}
	if (Root->Right and BRoot->Right)
	{
		return true;
	}
	else if (!(!Root->Right and !BRoot->Right))
	{
		return false;
	}

	return PictoriallyWise(Root->Right, Root->Right)&& PictoriallyWise(Root->Left, Root->Left);
}

void BST::InsertValuesInAscOrder(BST::Node* Root, vector<int>&VS)
{
	if (!Root)
		return;

	InsertValuesInAscOrder(Root->Left, VS);
	VS.push_back(Root->Data);
	InsertValuesInAscOrder(Root->Right, VS);

}

bool BST::ValueWise(BST Tree)
{
	vector<int>FirstTree;
	vector<int>SecondTree;
	InsertValuesInAscOrder(this->Root,FirstTree);
	InsertValuesInAscOrder(Tree.Root,SecondTree);
	if (FirstTree == SecondTree)
	{
		return true;
	}
	return false;
}

int BST::TreeMinimum(Node*Root)
{
	if (!Root->Left)
		return Root->Data;

	TreeMinimum(Root->Left);
}
int BST::TreeMaximum(Node* Root)
{
	if (!Root->Right)
		return Root->Data;
	TreeMaximum(Root->Right);
}

int BST::TreeMinimum()
{
	return TreeMinimum(Root);
}
int BST::TreeMaximum()
{
	return TreeMaximum(Root);
}

bool BST::IsBalancedTree()
{
	return IsBalancedTree(Root);
}
bool BST::IsBalancedTree(Node* Root)
{
	int Hl = 0,Hr=0;

	if (!Root)
	{
		return true;
	}
	Hl = Height(Root->Left);
	Hr = Height(Root->Right);

	if (abs(Hl - Hr) > 1)
		return false;

	return IsBalancedTree(Root->Left) && IsBalancedTree(Root->Right);
}



int  BST::ClosestLeaf()
{

	queue<Node*>Vs;
	Vs.push(Root);
	Vs.push(nullptr);
	Node*Temp= ClosestLeaf(Vs);
	return Temp->Data;
}
BST::Node*&  BST::ClosestLeafForPath()
{

	queue<Node*>Vs;
	Vs.push(Root);
	Vs.push(nullptr);
	return ClosestLeaf(Vs);
}
BST::Node*& BST::ClosestLeaf(queue<Node*>&Vs)
{
	if (!Vs.front())
	{
		Vs.pop();
	}
	else if(!Vs.front() and Vs.size() == 1)
	{
		return Vs.front();
	}
	else if(Vs.front())
	{
		while (Vs.front())
		{
			if (Vs.front()->Left)
			{
				Vs.push(Vs.front()->Left);

				if (!Vs.front()->Left->Left and !Vs.front()->Left->Right)
				{
					return Vs.front()->Left;
				}
			}
			if (Vs.front()->Right)
			{
				Vs.push(Vs.front()->Right);

				if (!Vs.front()->Right->Left and !Vs.front()->Right->Right)
				{
					return Vs.front()->Right;
				}
			}
			Vs.pop();
		}
	}
	ClosestLeaf(Vs);
}
void BST::ClosestPathToLeaf()
{
	Node* Temp = ClosestLeafForPath();
	cout << endl;
	while (Temp)
	{
		cout << "==>" << Temp->Data ;
		Temp = Temp->Parent;
	}
}

BST::Node*& BST::FarthestLeaf(queue<Node*>& Vs, Node*& Temp)
{
	if (Vs.size()== 0)
	{
		return Temp;
	}
	if (!Vs.front() and Vs.size() == 1)
	{
		return Temp;
	}
	else if (!Vs.front())
	{
		Vs.pop();
	}
	else if (Vs.front())
	{
		while (Vs.front())
		{
			if (Vs.front()->Left)
			{
				Vs.push(Vs.front()->Left);

				if (!Vs.front()->Left->Left and !Vs.front()->Left->Right)
				{
					Temp = Vs.front()->Left;
				}
			}
			if (Vs.front()->Right)
			{
				Vs.push(Vs.front()->Right);

				if (!Vs.front()->Right->Left and !Vs.front()->Right->Right)
				{
					Temp=Vs.front()->Right;
				}
			}
			Vs.pop();
			if (Vs.size()==0)
			{
				return Temp;
			}
		}
	}
	FarthestLeaf(Vs,Temp);
}

BST::Node*& BST::FarthestLeafForPath()
{

	queue<Node*>Vs;
	Node* Temp;
	Vs.push(Root);
	Vs.push(nullptr);
	return FarthestLeaf(Vs, Temp);
}
void BST::FarthestPathToLeaf()
{
	Node* Temp = FarthestLeafForPath();
	cout << endl;
	while (Temp)
	{
		cout << "==>" << Temp->Data;
		Temp = Temp->Parent;
	}
}
int  BST::FarthestLeaf()
{

	queue<Node*>Vs;
	Node* Temp;
	Vs.push(Root);
	Vs.push(nullptr);
	Temp= FarthestLeaf(Vs,Temp);
	return Temp->Data;
}

bool BST::IsLeaf(Node* Temp)
{
	if (!Temp->Left and !Temp->Right)
		return true;
	return false;
}
int BST::CountingInternalNodes()
{
	int count = 0;
	CountingInternalNodes(Root, count);
	return count;
}
void BST::CountingInternalNodes(Node*Root,int&count)
{
	if (!Root)
		return;

	CountingInternalNodes(Root->Left,count);
	if (!IsLeaf(Root))
	{
		count++;
	}
	CountingInternalNodes(Root->Right,count);
}


int BST::CountingLeaves()
{
	int count = 0;
	CountingLeaves(Root, count);
	return count;
}
void BST::CountingLeaves(Node* Root, int& count)
{
	if (!Root)
		return;

	CountingLeaves(Root->Left, count);
	if (IsLeaf(Root))
	{
		count++;
	}
	CountingLeaves(Root->Right, count);
}

int BST::CountingOneBranchOut()
{

	int count = 0;
	CountingOneBranchOut(Root, count);
	return count;
}
void BST::CountingOneBranchOut(Node* Root, int& count)
{
	if (!Root)
		return;

	CountingOneBranchOut(Root->Left, count);
	if (!IsLeaf(Root) and (Root->Left or Root->Right))
	{
		count++;
	}
	CountingOneBranchOut(Root->Right, count);
}

bool BST::IsValidBST()
{
	return IsValidBST(Root, INT_MAX, INT_MIN);

}
bool BST::IsValidBST(Node* Root,int max,int min)
{
	if (Root== nullptr)																														//right node needs to be greater than parent and less than its child 
		return true;
	if (Root->Data> min && Root->Data< max)																										//max determines upper bound and min lower bound
		return (IsValidBST(Root->Left, Root->Data, min) && IsValidBST(Root->Right, max, Root->Data));
	else
		return false;
}

void BST::LNR_Alternative_Print()
{
	LNR_iterator itr(Root);
	Node* r = itr.Min(Root);
	while (r != nullptr)
	{
		cout << r->Data << " ";
		r = itr.Successor(r);
	}
}


//Section 2

void BST::Delete_Case1(Node*& temp)
{
	auto del = temp;
	if (temp == temp->Parent->Left)
	{
		temp->Parent->Left= nullptr;
		delete del;
	}
	else if (temp == temp->Parent->Right)
	{
		temp->Parent->Right = nullptr;
		delete del;
	}
}

void BST::Delete_Case2(Node*& temp)
{

	auto del = temp;
	if (temp->Right== nullptr)										//Case 2: left child
	{
		if (temp == temp->Parent->Left)
		{
			temp->Parent->Left = temp->Left;
			temp->Left->Parent = temp->Parent;
			delete del;
		}
		else if (temp == temp->Parent->Right)
		{
			temp->Parent->Right= temp->Left;
			temp->Left->Parent = temp->Parent;
			delete del;
		}
		return;
	}

	if (temp->Left == nullptr)										//Case 2: right child
	{
		if (temp == temp->Parent->Left)
		{
			temp->Parent->Left = temp->Left;
			temp->Right->Parent = temp->Parent;
			delete del;
		}
		else if (temp == temp->Parent->Right)
		{
			temp->Parent->Right = temp->Right;
			temp->Right->Parent = temp->Parent;
			delete del;
		}
		return;
	}
}

void BST::Delete_Case3(Node*& temp)
{
	LNR_iterator it(temp);							//Both left and right child exist
	auto pre = it.Predecessor(it.i);

	if (pre->Right != nullptr && pre->Left!= nullptr)
	{
		swap(temp->Data, pre->Data);
		if (pre == pre->Parent->Right)
		{
			pre->Parent->Right = nullptr;
			delete pre;
		}
		else if (pre == pre->Parent->Left)
		{
			pre->Parent->Left= nullptr;
			delete pre;
		}
		return;
	}

	if (temp == temp->Parent->Left)
	{
		pre->Right = temp->Right;
		pre->Parent = temp->Parent;

		temp->Parent->Left = pre;
		temp->Right->Parent = pre;
	}

	else if (temp == temp->Parent->Right)
	{
		pre->Right = temp->Right;
		pre->Parent = temp->Parent;

		temp->Parent->Right = pre;
		temp->Right->Parent = pre;
	}
}

void BST::Deletion(int value)
{
		if (Root== nullptr)
			return;

		auto itr = Search(value);
		Node* temp = itr.i;
		Node* p = temp->Parent;

		if (temp == nullptr)
			return;

		if (temp->Right== nullptr && temp->Left == nullptr)					// Case 1: No children
		{
			Delete_Case1(temp);
		}
		else if (temp->Right == nullptr || temp->Left == nullptr)
		{
			Delete_Case2(temp);														//Case 2:One child exist
		}
		else if (temp->Right != nullptr && temp->Left!= nullptr)
		{
			Delete_Case3(temp);															//Case 3: Both children exist;
		}

		while (p != nullptr)
		{
			p->size--;
			p->Height = Height(p);
			p = p->Parent;
		}
	
}

void BST::OutputTree_recursion(Node* temp, int pos)
{
	if (temp == nullptr)
	{
		return;
	}
	if (temp != nullptr)
	{
		OutputTree_recursion(temp->Right, pos + 5);
		for (int i = 0; i < pos; i++)
		{
			cout << " ";
		}
		cout << temp->Data << endl;
		OutputTree_recursion(temp->Left, pos + 5);
	}
}

void  BST::OutputTree()
{
	int pos = 5;
	if (Root == nullptr)
		return;
	return OutputTree_recursion(Root, pos);
}

void BST::Load_Tree()
{
	int x;
	ifstream fin("BSTSAVE.txt");
	while (fin >> x)
	{
		InsertValue(x);
	}
}
void BST::SaveTree_Rec(ofstream& fout, Node* r)
{
	if (r == nullptr)
	{
		return;
	}
	fout << r->Data << " ";
	SaveTree_Rec(fout, r->Left);
	SaveTree_Rec(fout, r->Right);
}

BST BST::BST_SortedArray_Rec(BST& BST, vector<int> data, int index, int size)
{
	if (index > size)
		return BST;
	else
	{
		int mid = (index + size) / 2;
		BST.InsertValue(data[mid]);
		BST_SortedArray_Rec(BST, data, index, mid - 1);
		BST_SortedArray_Rec(BST, data, mid + 1, size);
		return BST;
	}
}

BST BST::BST_SortedArray(vector<int> data)
{
	BST BS;
	return BST_SortedArray_Rec(BS, data, 0, data.size() - 1);
}

void BST::Save_Tree()
{
	ofstream fout("BSTSAVE.txt");
	SaveTree_Rec(fout, Root);
}
void BST::RangeSearch_RecAscending(Node* r, int v1, int v2)
{
	if (r == nullptr)
	{
		return;
	}
	RangeSearch_RecAscending(r->Left, v1, v2);
	if (r->Data >= v1 && r->Data<= v2)
	{
		cout << r->Data << " ";
	}
	RangeSearch_RecAscending(r->Right, v1, v2);
}
void BST::RangeSearch_RecDescending(Node* r, int v1, int v2)
{
	if (r == nullptr)
	{
		return;
	}
	RangeSearch_RecDescending(r->Right, v1, v2);
	if (r->Data<= v1 && r->Data >= v2)
	{
		cout << r->Data<< " ";
	}
	RangeSearch_RecDescending(r->Left, v1, v2);
}
void BST::RangeSearch(int v1, int v2)
{
	Iterator itr(Root);
	auto temp1 = Search(v1);
	auto temp2 = Search(v2);
	if (temp1 == nullptr || temp2 == nullptr)
	{
		cout << "Incorrect range";
		return;
	}

	if (v1 < v2)
		RangeSearch_RecAscending(Root, v1, v2);
	else
		RangeSearch_RecDescending(Root, v1, v2);
}
vector<list<BST::Node*>> BST::Linked_List()
{
	vector<list<Node*>> v;
	queue<Node*> Q;
	list<Node*> L;
	Q.push(Root);
	Q.push(nullptr);
	while (!Q.empty())
	{
		auto temp = Q.front();
		Q.pop();
		if (temp != nullptr)
		{

			L.push_back(temp);
			if (temp->Left!= nullptr)
				Q.push(temp->Left);
			if (temp->Right != nullptr)
				Q.push(temp->Right);
		}
		else
		{
			v.push_back(L);
			L.clear();
			if (!Q.empty())
				Q.push(nullptr);
		}
	}
	return v;
}
