/*In one feudal state of medieval Europe there were n cities and m roads,
each of which connected some two cities. Each road belonged to the ruler 
of one of the cities (not necessarily one of those that she connected). 
Once the ruler of the city s decided to declare war on the ruler of the city t.
Immediately he faced a difficult task: how to bring the army to the city t.

The ruler of each city requires payment for the passage of troops through his city.
In addition, the ruler of the city s can move troops only on the roads that belong to him.
At the same time, he can buy any road from its owner for a certain fee (even if the owner 
is the ruler of the city t). Unfortunately, all the money from the city s treasury was 
spent on a previous unsuccessful military campaign, so first the ruler will have to sell 
some of his roads (of course, after that he will not be able to conduct troops on them).

Help the ruler to find out which roads should be sold and which ones to buy in order to
bring troops from city s to city t and pay for passage through all intermediate cities. 
All operations for the sale and purchase of roads should be carried out before the campaign,
while the rulers of other cities did not guess about the belligerent intentions of the ruler of the city s.


In the first line print the list of roads that need to be sold in the following format: 
first the number of roads, and then their numbers. Roads are numbered from one in the order
in which they are given at the entrance. In the second line print the list of roads that need
to be bought in the same format. In the third line print the route of the hike - numbers of 
cities in the order of the troops. If there are several solutions, output any. If there is no solution, output only −1.*/


#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <fstream>
#include <algorithm>
#include <Windows.h>

using namespace std;

struct Road {
	int a;
	int b;
	int owner;
	int coast;
	int number;
};

struct Myway {
	int top;
	int cost;
	int num;
};

struct Comp {
	bool operator() (pair<int, int> p1, pair<int, int> p2) {
		return p1.first > p2.first;
	}
};

int main() {
	ifstream fin("campaign.in");
	ofstream fout("campaign.out");
	int n, m;
	fin >> n >> m;
	int *mass = new int[n + 1];
	for (int i = 1; i < n + 1; i++)
		fin >> mass[i];

	vector<pair<int, int>> path;
	path.push_back(make_pair(0, 0));
	//int *path = new int[n + 1];
	int *met = new int[n + 1];
	bool *visit = new bool[n + 1];
	for (int i = 1; i < n + 1; i++) {
		path.push_back(make_pair(0, 0));
		met[i] = MAXINT;
		visit[i] = false;
	}

	int kash = 0;
	vector<int> Myroad;
	vector<vector<Myway>> massiv(n + 1);
	Road* arr = new Road[m + 1];
	for (int i = 1; i < m + 1; i++) {
		Road r;
		fin >> r.a >> r.b >> r.owner >> r.coast;
		Myway w1, w2;
		w1.top = r.b;
		w1.num = i;
		w1.cost = r.coast + mass[r.b];
		w2.top = r.a;
		w2.num = i;
		w2.cost = r.coast + mass[r.a];
		massiv[r.a].push_back(w1);
		massiv[r.b].push_back(w2);
		r.number = i;
		if (r.owner == 1) {
			Myroad.push_back(r.number);
			kash += r.coast;
		}
		arr[i] = r;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, Comp> q;
	met[1] = 0;
	q.push(make_pair(met[1], 1));
	while (!q.empty()) {
		pair<int, int> p = q.top();
		q.pop();
		visit[p.second] = true;
		for (int i = 0; i < massiv[p.second].size(); i++) {
			if (visit[massiv[p.second][i].top] == false) {
				if (met[massiv[p.second][i].top] > met[p.second] + massiv[p.second][i].cost) {
					met[massiv[p.second][i].top] = met[p.second] + massiv[p.second][i].cost;
					q.push(make_pair(met[massiv[p.second][i].top], massiv[p.second][i].top));
					path[massiv[p.second][i].top] = (make_pair(p.second, massiv[p.second][i].num));
				}
			}
		}
	}

	if (met[n] == MAXINT) {
		fout << -1;
	}
	else {
		int j = n;
		vector<int> buy;
		vector<int> Myvect;
		Myvect.push_back(j);
		while (j != 1) {
			if (arr[path[j].second].owner != 1)
				buy.push_back(arr[path[j].second].number);
			else {
				Myroad.erase(find(Myroad.begin(), Myroad.end(), arr[path[j].second].number));
			}

			j = path[j].first;
			Myvect.push_back(j);
		}

		int sellSize = Myroad.size();
		int buySize = buy.size();
		int MyvectSize = Myvect.size();
		if (kash < met[n])
			fout << -1;
		else {
			fout << sellSize << " ";
			for (int i = 0; i < sellSize; i++)
				fout << Myroad[i] << " ";
			fout << endl;
			fout << buySize << " ";
			for (int i = buySize - 1; i >= 0; i--)
				fout << buy[i] << " ";
			fout << endl;
			int j = n;
			for (int i = MyvectSize - 1; i >= 0; i--) {
				fout << Myvect[i] << " ";
			}
		}
	}
	return 0;
}