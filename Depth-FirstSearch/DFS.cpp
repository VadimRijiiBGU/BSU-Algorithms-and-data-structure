/*For a directed graph specified by the adjacency matrix, 
a depth search was performed. When the choice of the next 
vertex is ambiguous, a vertex with a lower number is always
selected. In the process of searching in depth at the time of
visiting the top, a label was assigned to it 
(the numbering of the tags starts from one).
Determine which label each of the graph vertices received.

Print n numbers, the i-th of which is the label that vertex i received.*/


#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int n;
int *time;
bool *visit;
int **mass;
int fuck = 0;

void DFS(int *time, bool *visit, int **mass, int A) {
	if (visit[A] == false) {
		visit[A] = true;
		fuck++;
		time[A] = fuck;
		for (int j = 1; j < n + 1; j++) {
			if (mass[A][j] == 1)
				if (visit[j] == false)
					DFS(time, visit, mass, j);
		}
	}
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	fin >> n;
	mass = new int*[n + 1];
	for (int i = 0; i < n + 1; i++)
		mass[i] = new int[n + 1];
	time = new int[n + 1];
	for (int i = 1; i < n + 1; i++)
		time[i] = 0;
	visit = new bool[n + 1];
	for (int i = 1; i < n + 1; i++)
		visit[i] = false;

	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
			fin >> mass[i][j];


	int A = 0;
	for (int i = 1; i < n + 1; i++) {
		DFS(time, visit, mass, i);
	}

	for (int i = 1; i < n + 1; i++)
		fout << time[i] << " ";
	return 0;
}