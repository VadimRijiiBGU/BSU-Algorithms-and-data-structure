/*Given the total number n of vertices in the binomial heap. Determine which binomial trees this heap can consist of.
For each binomial tree Bk in the heap, print in a separate line one integer - height k.
Trees should be derived in ascending order of height. All trees must have different orders, and the sum of orders must be n.
If there are several solutions, output any. If there are no solutions and a binomial heap 
with a given number of vertices cannot be built, output −1.*/


#include <iostream>	
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

long long dva(int j) {
	long long x = 1;
	for (int i = 0; i < j; i++)
		x *= 2;
	return x;
}

void Step(long long n, vector<long long> &vect) {
	if (n == 0)
		return;
	long long x = 1;
	int i = 0;
	while (x <= n) {
		x *= 2;
		i++;
	}
	vect.push_back(i - 1);
	n -= dva(i - 1);
	
	Step(n, vect);
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	vector <long long> Myvect;
	long long n;
	fin >> n;
	Step(n, Myvect);
	vector <long long>::reverse_iterator it;
	int i = Myvect.size();
	
	for (it = Myvect.rbegin(); it != Myvect.rend(); it++)
			fout << *it << endl;
	
	return 0;
}