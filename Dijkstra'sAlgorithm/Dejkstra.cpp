/*An undirected weighted pseudograph is set, the vertices of
which are numbers from 1 to n. It is required to find the s
hortest chain between vertices 1 and n. It is guaranteed that (1, n) -chain exists.*/


#include <iostream>
#include <fstream>
#include <queue>
#include <Windows.h>

using namespace std;

struct Comp {
	bool operator() (const pair<long long, int> &p1, const pair<long long, int> &p2) {
		return p1.first > p2.first;
	}
};

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n, m;
	fin >> n >> m;
	vector<vector<pair<int, int>>> mass(n + 1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		fin >> a >> b >> c;
		pair<int, int> p1, p2;
		p1 = make_pair(b, c);
		p2 = make_pair(a, c);
		mass[a].push_back(p1);
		mass[b].push_back(p2);
	}

	int *met = new int[n + 1];
	bool *visit = new bool[n + 1];
	for (int i = 0; i < n + 1; i++)
		visit[i] = false;

	long long rezult = 0;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, Comp> q;
	q.push(make_pair(0, 1));
	while (!q.empty()) {
		pair<long long, int> p = q.top();
		if (p.second == n) {
			rezult = p.first;
			break;
		}
		q.pop();
		if (visit[p.second] == false) {
			visit[p.second] = true;
			for (int i = 0; i < mass[p.second].size(); i++) {
				if (visit[mass[p.second][i].first] == false)
					q.push(make_pair((p.first + mass[p.second][i].second), mass[p.second][i].first));
			}
		}
	}

	fout << rezult;
	return 0;
}