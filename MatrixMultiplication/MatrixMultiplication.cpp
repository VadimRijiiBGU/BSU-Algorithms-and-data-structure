/*Given a sequence of s matrices A1, A2, ..., As. It is required to determine the order 
in which they should be multiplied so that the number of atomic multiplication operations is minimal.
Matrices are assumed to be compatible with matrix multiplication.
Print the minimum number of atomic multiplication operations required to multiply s matrices.*/


#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <climits>
#include <Windows.h>

using namespace std;

struct Matr {
	int n;
	int m;
};

int Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

int Matrix(vector <Matr> v) {
	int n = v.size();
	int **mass = new int*[n + 1];
	for (int i = 0; i <= n; i++)
		mass[i] = new int[n + 1];
	for (int i = 1; i <= n; i++)
		mass[i][i] = 0;
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			mass[i][j] = MAXINT;
			for (int k = i; k < j; k++) {
				mass[i][j] = Min(mass[i][j], (mass[i][k] + mass[k + 1][j] + v[i - 1].n * v[k - 1].m * v[j -1].m));
			}
		}
	}
	return mass[1][n];
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	vector <Matr> vect;
	int X;
	fin >> X;
	Matr M;
	for(int i = 0; i < X; i++) {
		fin >> M.n >> M.m;
		vect.push_back(M);
	}

	fout << Matrix(vect);
	return 0;
}