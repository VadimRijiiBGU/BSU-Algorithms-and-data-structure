/*There are n rectangular envelopes and n rectangular cards of various sizes.
It is necessary to determine whether all the cards can be expanded in envelopes 
so that there is one card in each envelope. Postcards can not be folded, 
folded, etc., but can be placed in an envelope at an angle. For example, a
postcard with sides of 5: 1 is placed in envelopes with sizes of 5: 1, 6: 3, 4.3: 4.3, 
but not included in envelopes with sizes of 4: 1, 10: 0.5, 4.2 : 4.2.

If all the cards can be expanded, then a single line should contain the message YES.
If all postcards cannot be expanded, the first line should contain the message NO, 
and the second line should contain the maximum number of postcards that can be expanded in envelopes.*/


#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

int Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

struct Postcard {
	long long A;
	long long B;
	int number;
};

struct Path {
	int a;
	int b;
	int weight;
	bool isReverse;
};

int **mass;
int **arr;
int n;
bool *visit;
int *path;
queue <int> q;
vector <Path> vect;
bool BFS() {
	q.push(0);
	visit[0] = true;
	while (!q.empty() && visit[2 * n + 1] == false) {
		int A = q.front();
		q.pop();
		for (int i = 0; i < 2 * n + 2; i++) {
			if (visit[i] == false) {
				if (mass[A][i] > 0) {
					q.push(i);
					path[i] = A;
					visit[i] = true;
				}
			}
		}
		if (visit[2 * n + 1] == true)
			break;
		for (int j = 0; j < 2 * n + 2; j++) {
			if (visit[j] == false) {
				if (arr[A][j] > 0) {
					q.push(j);
					path[j] = A;
					visit[j] = true;
				}
			}
		}
	}
	if (visit[2 * n + 1] == true) {
		int k = 2 * n + 1;
		while (k != 0) {
			Path pa;
			pa.b = k;
			k = path[k];
			pa.a = k;
			if (mass[pa.a][pa.b] > 0) {
				pa.weight = mass[pa.a][pa.b];
				pa.isReverse = false;
			}
			else if (arr[pa.a][pa.b] > 0) {
				pa.weight = arr[pa.a][pa.b];
				pa.a = pa.b;
				pa.b = k;
				pa.isReverse = true;
			}
			vect.push_back(pa);
		}
		return true;
	}
	else
		return false;
}

bool enter(Postcard e, Postcard p)
{
	if (e.A >= p.A && e.B >= p.B)
		return true;
	if (p.A * p.A + p.B * p.B > e.A * e.A + e.B * e.B)
		return false;
	if (e.A * e.A >= p.A * p.A + p.B * p.B)
		return e.B >= p.A;
	return (e.A * e.B > 2 * p.A * p.B) && ((p.A * p.A + p.B * p.B - e.B * e.B) * (p.A * p.A + p.B * p.B - e.A * e.A) <= e.A * e.A * e.B * e.B - 4 * e.A*e.B*p.A*p.B + 4 * p.A*p.A*p.B*p.B);
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> n;
	Postcard *pc = new Postcard[n];
	Postcard *envelope = new Postcard[n];

	mass = new int*[2 * n + 2];
	arr = new int*[2 * n + 2];
	for (int i = 0; i < 2 * n + 2; i++) {
		mass[i] = new int[2 * n + 2];
		arr[i] = new int[2 * n + 2];
	}

	for (int i = 0; i < 2 * n + 2; i++) {
		for (int j = 0; j < 2 * n + 2; j++) {
			mass[i][j] = 0;
			arr[i][j] = 0;
		}
	}

	long long a, b;
	for (int i = 0; i < n; i++) {
		Postcard p1;
		fin >> a >> b;
		if (b > a) {
			swap(a, b);
		}
		p1.A = a;
		p1.B = b;
		p1.number = i + n + 1;
		pc[i] = p1;
	}

	for (int i = 0; i < n; i++) {
		Postcard e1;
		fin >> a >> b;
		if (b > a) {
			swap(a, b);
		}
		e1.A = a;
		e1.B = b;
		e1.number = i + 1;
		envelope[i] = e1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (enter(envelope[i], pc[j])) {
				mass[envelope[i].number][pc[j].number] = 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		mass[0][envelope[i].number] = 1;
		mass[pc[i].number][2 * n + 1] = 1;
	}
	
	visit = new bool[2 * n + 2];
	path = new int[2 * n + 2];
	for (int i = 0; i < 2 * n + 2; i++) {
		visit[i] = false;
		path[i] = 0;
	}

	int F = 0;
	while (BFS()) {
		int C = MAXINT;
		for (int i = 0; i < vect.size(); i++) {
			C = Min(C, vect[i].weight);
		}
		for (int i = 0; i < vect.size(); i++) {
			if (vect[i].isReverse == false) {
				mass[vect[i].a][vect[i].b] -= C;
				arr[vect[i].b][vect[i].a] += C;
			}
			else {
				mass[vect[i].a][vect[i].b] += C;
				arr[vect[i].b][vect[i].a] -= C;
			}
		}
		
		for (int i = 0; i < 2 * n + 2; i++) {
			visit[i] = false;
		}
		while (!q.empty())
			q.pop();
		vect.clear();
		F += C;
	}

	if (F == n)
		fout << "YES";
	else
		fout << "NO\n" << F;
	return 0;
}