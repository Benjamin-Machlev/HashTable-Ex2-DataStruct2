#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;
#include "HashTable.h"

const int MAX = 1000;



class HSubject :public HashTable<list<string>, string> {
private:
	int key(string s) { return (int)s[0] + (int)s[1] + (int)s[s.length() - 1]; }

public:
	HSubject(int n) :HashTable <list<string>, string>(n) {}
	int h1(string s) { return key(s) % size; }
	int h2(string s) { return (key(s) % (size - 1) + 1) % size; }
	void printS(string ky);
	void printN(string ky, int N);
	void print();
	void startNewTable();
	void addSubjectAndTitle(string s, string t);
};

void HSubject::printS(string ky)
{

	for (int i = 0; i < size; i++) {
		if (ky == arr[i].key) {
			cout << arr[i].data.size() << endl;
			for_each(arr[i].data.begin(), arr[i].data.end(), [](string a) {
				cout << a;
				});
			return;
		}
	}

}


void HSubject::printN(string ky, int N)
{
	int index = search(ky);
	if (index == -1) {
		cout << "the object not found\n";
	}
	else {
		for_each(arr[index].data.begin(), arr[index].data.end(), [](int N, string a) {
			if (N == 0) {
				return;
			}
			cout << a;
			N--;
			});
	}

}

void HSubject::print()
{
	list<string> a;
	for (int i = 0; i < size; i++) {
		a.push_back(arr[i].key);
	}
	a.sort();
	for_each(a.begin(), a.end(), [](string a) {cout << a; });
}

void HSubject::startNewTable()
{
	delete[] arr;
}

void HSubject::addSubjectAndTitle(string s, string t)
{
	int index = search(s);
	if (index == -1) {
		add(s, t);
	}
	else {
		arr[index].data.push_front(t);
	}
}