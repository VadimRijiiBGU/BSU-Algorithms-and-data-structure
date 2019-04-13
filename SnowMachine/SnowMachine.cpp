/*The main street of the city is a rectangle with vertices 
at the points (0, 0), (0, 2), (n, 2), (n, 0). At night there 
was heavy snowfall in the city and now there is snow on some single
squares of the street. A snowblower is a segment of length 1, which 
is initially located so that its ends have coordinates (k, 0) and (k, 1).
The snowplow can move in the horizontal direction by 1 in 1 second, 
while its segment “sweeps up” the cage.

In the first line print the minimum possible number of seconds it takes to remove the snow.*/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <Windows.h>

using namespace std;

int Min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;	
}

int main() {
	ifstream fin("in.txt");
	ofstream fout("out.txt");
	int n = 0;
	int k = 0;
	fin >> n >> k;
	k++;
	int **mass = new int*[2];
	for (int i = 0; i < 2; i++)
		mass[i] = new int[n + 1];

	for (int i = 1; i < n + 1; i++) {
		fin >> mass[1][i] >> mass[0][i];
	}
	
	int a = 1;
	while (mass[1][a] == 0 && mass[0][a] == 0 && a != k)
		a++;
	int b = n;
	while (mass[1][b] == 0 && mass[0][b] == 0 && b != k)
		b--;

	int count = 0;
	int X = k;
	int min = MAXINT;
	for (int i = k; i < b + 1; i++) {
		if (mass[1][i] == 1 && mass[0][i] == 1) {
			mass[1][i] = mass[0][i] = 0;
			if (i - 1 >= k)
				mass[1][i] = mass[1][i - 1] + 3;
			else
				mass[1][i] = 3;
			X++;
		}
		else {
			mass[1][i] = mass[0][i] = 0;
			if (i - 1 >= k)
				mass[1][i] = mass[1][i - 1] + 1;
			else
				mass[1][i] = 1;
			X++;
		}
	}
	for (int i = k; i < b; i++) {
		if (i + 1 < b + 1) {
			mass[0][i + 1] = mass[1][i] + 2 * (b + 1 - (i + 1));
			min = Min(min, mass[0][i + 1]);
		}
	}
	//if(b != 0)
	min = Min(min, mass[1][b]);
	int RIGHT = 0;
	if (k < b + 1) {
		if (b != k)
			RIGHT = 2 * (b - k);
		else
			RIGHT = 2;
	}
	min = Min(min, RIGHT);

	X = k - 1;
	int min1 = MAXINT;
	for (int j = k - 1; j >= a; j--) {
		if (mass[1][j] == 1 && mass[0][j] == 1) {
			mass[1][j] = mass[0][j] = 0;
			if (j + 1 < k)
				mass[1][j] = mass[1][j + 1] + 3;
			else
				mass[1][j] = 3;
			X--;
		}
		else {
			mass[1][j] = mass[0][j] = 0;
			if (j + 1 < k)
				mass[1][j] = mass[1][j + 1] + 1;
			else
				mass[1][j] = 1;
			X--;
		}
	}

	for (int j = k - 1; j > a; j--) {
		if (j - 1 >= a) {
			mass[0][j - 1] = mass[1][j] + 2 * (j - a);
			min1 = Min(min1, mass[0][j - 1]);
		}
	}
	//if(a != b + 1)
	min1 = Min(min1, mass[1][a]);
	int LEFT = 0;
	if (k > a) {
		if (a != k)
			LEFT = 2 * (k - a);
		else
			LEFT = 2;
	}
	min1 = Min(min1, LEFT);

	if (a == b && mass[1][a] == 0 && mass[0][a] == 0)
		count = 0;
	else {
		if (LEFT < RIGHT) {
			count = LEFT + min;
		}
		else if (LEFT > RIGHT)
			count = RIGHT + min1;
		else
			count = LEFT + Min(min, min1);
	}

	fout << count;
	return 0;
}