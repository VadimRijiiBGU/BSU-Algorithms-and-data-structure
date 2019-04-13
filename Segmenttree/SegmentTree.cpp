/*Имеется последовательность s0, …, sn − 1, состоящая из нулей. На этой последовательности могут выполняться запросы следующих типов:

	1. Установить значение si равным v.
	2. Прибавить к каждому элементу с индексом из отрезка [a, b] число v.
	3. Найти сумму элементов с индексами из отрезка [a, b].
	4. Найти минимум среди элементов с индексами из отрезка [a, b].
	5. Найти максимум среди элементов с индексами из отрезка [a, b].

Требуется написать программу, которая будет обрабатывать указанные запросы.*/


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <climits>
#include <Windows.h>

using namespace std;

struct List {
	long long summ;
	long long min;
	long long max;
};

long long *arr;
long long *add;
List *mass;

long long Min(long long a, long long b) {
	if (a < b)
		return a;
	else
		return b;
}
long long Max(long long a, long long b) {
	if (a > b)
		return a;
	else
		return b;
}

void build(int u, int l, int r) {
	if (l == r) {
		mass[u].summ = arr[l];
		mass[u].min = arr[l];
		mass[u].max = arr[l];
		return;
	}
	int medium = (l + r) / 2;
	build(u * 2 + 1, l, medium);
	build(u * 2 + 2, medium + 1, r);
	mass[u].summ = mass[2 * u + 1].summ + mass[2 * u + 2].summ;
	mass[u].min = Min(mass[2 * u + 1].min, mass[2 * u + 2].min);
	mass[u].max = Max(mass[2 * u + 1].max, mass[2 * u + 2].max);
}

void push(int u, int l, int r) {
	if (add[u] != 0) {
		mass[u].summ += add[u] * (r - l + 1);
		mass[u].min += add[u];
		mass[u].max += add[u];
		if (l != r) {
			add[u * 2 + 1] += add[u];
			add[u * 2 + 2] += add[u];
		}
		add[u] = 0;
	}
}

void modify(int u, int l, int r, int left, int right, int temp) { 
	push(u, l, r);
	if (left > r || right < l)
		return;
	if (left <= l && right >= r) {
		add[u] += temp;
		push(u, l, r);
		return;
	}
	int medium = (l + r) / 2;
	modify(u * 2 + 1, l, medium, left, right, temp);
	modify(u * 2 + 2, medium + 1, r, left, right, temp);
	mass[u].summ = mass[2 * u + 1].summ + mass[2 * u + 2].summ;
	mass[u].min = Min(mass[2 * u + 1].min, mass[2 * u + 2].min);
	mass[u].max = Max(mass[2 * u + 1].max, mass[2 * u + 2].max);
}

void update(int u, int l, int r, int left, int right, int temp) {
	push(u, l, r);
	if (left > r || right < l)
		return;
	if (left == l && right == r) {
		mass[u].summ = temp;
		mass[u].min = temp;
		mass[u].max = temp;
		add[u] = 0;
		return;
	}
	int medium = (l + r) / 2;
	update(u * 2 + 1, l, medium, left, right, temp);
	update(u * 2 + 2, medium + 1, r, left, right, temp);
	mass[u].summ = mass[2 * u + 1].summ + mass[2 * u + 2].summ;
	mass[u].min = Min(mass[2 * u + 1].min, mass[2 * u + 2].min);
	mass[u].max = Max(mass[2 * u + 1].max, mass[2 * u + 2].max);
}

long long Summ(int u, int l, int r, int left, int right) {
	push(u, l, r);
	if (left <= l && right >= r)
		return mass[u].summ;
	if (right < l || left > r)
		return 0;
	int medium = (l + r) / 2;
	return Summ(u * 2 + 1, l, medium, left, right) + Summ(u * 2 + 2, medium + 1, r, left, right);
}

long long GetMin(int u, int l, int r, int left, int right) {
	push(u, l, r);
	if (left <= l && right >= r)
		return mass[u].min;
	if (right < l || left > r)
		return MAXINT;
	int medium = (l + r) / 2;
	return Min(GetMin(u * 2 + 1, l, medium, left, right), GetMin(u * 2 + 2, medium + 1, r, left, right));
}

long long GetMax(int u, int l, int r, int left, int right) {
	push(u, l, r);
	if (left <= l && right >= r)
		return mass[u].max;
	if (right < l || left > r)
		return MININT;
	int medium = (l + r) / 2;
	return Max(GetMax(u * 2 + 1, l, medium, left, right), GetMax(u * 2 + 2, medium + 1, r, left, right));
}

int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n = 0;
	fin >> n;
	arr = new long long[n];
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
	mass = new List[4 * n];
	for (int i = 0; i < 4 * n; i++) {
		mass[i].summ = 0;
		mass[i].min = MAXINT;
		mass[i].max = MININT;
	}
	add = new long long[4 * n];
	for (int i = 0; i < 4 * n; i++) {
		add[i] = 0;
	}

	build(0, 0, n - 1);
	int tmp = 10;
	while (tmp != 0) {
		fin >> tmp;
		switch (tmp) {
		case 1: {
			int i, v;
			fin >> i >> v;
			update(0, 0, n - 1, i, i, v);
			break;
		}
		case 2: {
			int a, b, v;
			fin >> a >> b >> v;
			modify(0, 0, n - 1, a, b, v);
			break;
		}
		case 3: {
			int a, b;
			fin >> a >> b;
			fout << Summ(0, 0, n - 1, a, b) << endl;
			break;
		}
		case 4: {
			int a, b;
			fin >> a >> b;
			fout << GetMin(0, 0, n - 1, a, b) << endl;
			break;
		}
		case 5: {
			int a, b;
			fin >> a >> b;
			fout << GetMax(0, 0, n - 1, a, b) << endl;
			break;
		}
		}
	}
	return 0;
}