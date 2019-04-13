/*Find the average value of the tree tops, in which the subtree heights are equal,
and the number of descendants in the right and left subtrees is different. 
Delete it (right delete), if such a vertex exists.

The output file must contain a sequence of vertex keys obtained by a direct left traversal of the resulting tree.*/


#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct List
{
	int info;
	int H;
	int NC;
	List *rSon;
	List *lSon;
};

void Add(int x, List *&Tree)
{
	if (Tree == NULL)
	{
		Tree = new List;
		Tree->info = x;
		Tree->lSon = Tree->rSon = NULL;
	}
	else
	{
		if (x < Tree->info)
		{
			if (Tree->lSon != NULL)
			{
				Add(x, Tree->lSon);
			}
			else
			{
				Tree->lSon = new List;
				Tree->lSon->info = x;
				Tree->lSon->lSon = Tree->lSon->rSon = NULL;
			}
		}
		else if (x > Tree->info)
		{
			if (Tree->rSon != NULL)
			{
				Add(x, Tree->rSon);
			}
			else
			{
				Tree->rSon = new List;
				Tree->rSon->info = x;
				Tree->rSon->lSon = Tree->rSon->rSon = NULL;
			}
		}
	}
}

void Height(List *&Tree)
{
	if (Tree->rSon == NULL && Tree->lSon == NULL)
		Tree->H = 0;
	else if (Tree->rSon != NULL && Tree->lSon == NULL)
		Tree->H = Tree->rSon->H + 1;
	else if (Tree->lSon != NULL && Tree->rSon == NULL)
		Tree->H = Tree->lSon->H + 1;
	else
	{
		if (Tree->lSon->H > Tree->rSon->H)
			Tree->H = Tree->lSon->H + 1;
		else
			Tree->H = Tree->rSon->H + 1;
	}
}

void RShow(List *&Tree, vector <int> &sset)
{
	if (Tree == NULL)
		return;
	RShow(Tree->lSon, sset);
	RShow(Tree->rSon, sset);
	Height(Tree);
	if (Tree->lSon != NULL && Tree->rSon != NULL)
		Tree->NC = Tree->lSon->NC + Tree->rSon->NC + 1;
	if (Tree->lSon != NULL && Tree->rSon == NULL)
		Tree->NC = Tree->lSon->NC + 1;
	if (Tree->lSon == NULL && Tree->rSon != NULL)
		Tree->NC = Tree->rSon->NC + 1;
	if (Tree->lSon == NULL && Tree->rSon == NULL)
		Tree->NC = 1;
	if (Tree->lSon != NULL && Tree->rSon != NULL)
		if (Tree->rSon->H == Tree->lSon->H && Tree->lSon->NC != Tree->rSon->NC)
			sset.push_back(Tree->info);
}

void Delete(List *&Tree, int temp)
{
	List* Root = Tree;
	List* Parent = NULL;
	while (Root != NULL && Root->info != temp)
	{
		Parent = Root;
		if (Root->info > temp)
			Root = Root->lSon;
		else
			Root = Root->rSon;
	}

	if (Root == NULL)
		return;

	List *Rem = NULL;

	if (Root->rSon == NULL || Root->lSon == NULL)
	{
		List *Child = NULL;
		Rem = Root;
		if (Root->lSon != NULL)
			Child = Root->lSon;
		else if (Root->rSon != NULL)
			Child = Root->rSon;

		if (Parent == NULL)
			Tree = Child;
		else
		{
			if (Parent->rSon == Root)
				Parent->rSon = Child;
			else
				Parent->lSon = Child;
		}
	}
	else
	{
		List *Node = Root->rSon;
		List *Unit = Root;
		while (Node->lSon != NULL)
		{
			Unit = Node;
			Node = Node->lSon;
		}

		Root->info = Node->info;
		Rem = Node;

		List* Child = NULL;
		if (Unit->lSon == Node)
		{
			if (Node->rSon)
			{
				Child = Node->rSon;
				Unit->lSon = Child;
			}
			else
				Unit->lSon = NULL;
		}
		else
		{
			if (Node->rSon == NULL)
				Unit->rSon = NULL;
			else
				Unit->rSon = Node->rSon;
		}
	}

	delete[] Rem;
}

void Show(List *&Tree, ofstream &Fout)
{
	if (Tree == NULL)
		return;
	Fout << Tree->info << endl;
	Show(Tree->lSon, Fout);
	Show(Tree->rSon, Fout);
}

int main()
{
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	vector <int> Myvect;
	int temp;
	List *MyTree = NULL;
	while (!fin.eof())
	{
		fin >> temp;
		Add(temp, MyTree);
	}
	RShow(MyTree, Myvect);
	if (Myvect.size() % 2 != 0)
	{
		sort(Myvect.begin(), Myvect.end());
		int tmp = Myvect[Myvect.size() / 2];
		Delete(MyTree, tmp);
	}
	Show(MyTree, fout);
	
	return 0;
}
