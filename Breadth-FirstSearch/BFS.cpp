/*For a directed graph specified by the adjacency matrix,
a wide search was performed. When the choice of the next vertex 
is ambiguous, a vertex with a lower number is always selected. 
In the search process, at the time of visiting the top, a label
was assigned to it (the numbering of the tags starts from one).
Determine which label each of the graph vertices received 
(a wide search was performed until all vertices received a label).

Print n numbers, the i-th of which is the label that vertex i received.*/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <queue>

using namespace std;

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	queue <int> fifo;
	int n;
	fin >> n;
	int **mass = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		mass[i] = new int[n + 1];

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
			fin >> mass[i][j];

	int *met = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
		met[i] = 0;
	bool *visit = new bool[n + 1];
	for (int i = 0; i < n + 1; i++)
		visit[i] = false;

	int count = 1;
	for (int i = 1; i < n + 1; i++) {
		if (visit[i] == false) {
			fifo.push(i);
			visit[i] = true;
			met[i] = count;
			count++;
			while (!fifo.empty()) {
				int A = fifo.front();
				fifo.pop();
				for (int j = 1; j < n + 1; j++) {
					if (mass[A][j] == 1 && visit[j] == false) {
						fifo.push(j);
						visit[j] = true;
						met[j] = count;
						count++;
					}
				}
			}
		}
	}

	for (int i = 1; i < n + 1; i++)
		fout << met[i] << " ";

	delete[] mass;
	delete[] met;
	delete[] visit;

	return 0;
}