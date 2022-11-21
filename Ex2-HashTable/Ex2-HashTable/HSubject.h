#pragma once
#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include "HashTable.h"
using namespace std;

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

/// <summary>
/// print the sub subject
/// </summary>
/// <param name="ky"></param>
void HSubject::printS(string ky)
{
	for (int i = 0; i < size; i++) {
		if (ky == arr[i].key && arr[i].flag == full) {
			cout << "Subject " << arr[i].key << " " << arr[i].data.size() << " topics:" << endl;
			for_each(arr[i].data.begin(), arr[i].data.end(), [](string a) {
				cout << a << " ";
				});
			return;
		}
	}
	cout << "ERROR\n";
}

/// <summary>
/// print the N subject
/// </summary>
/// <param name="ky"></param>
/// <param name="N"></param>
void HSubject::printN(string ky, int N)
{
	int index = search(ky);
	if (index == -1) {
		cout << "ERROR\n";
	}
	else {
		for_each(arr[index].data.begin(), arr[index].data.end(), [&](string a) {
			if (N == 0) {
				return;
			}
			cout << a << " ";
			N--;
			});
	}
}

/// <summary>
/// print the all subject and topics
/// </summary>
void HSubject::print()
{
	int index;
	list<string> a;
	for (int i = 0; i < size; i++) {

		if (arr[i].flag == full) {
			a.push_back(arr[i].key);
		}
	}
	a.sort();
	cout << "All subjects and titles:\n";
	for_each(a.begin(), a.end(), [&](string a) {
		cout << a << ":";
		index = search(a);
		for_each(arr[index].data.begin(), arr[index].data.end(), [](string b) {cout << b << " "; });
		cout << "\n";
		});
}

/// <summary>
/// start a new table
/// </summary>
void HSubject::startNewTable()
{
	for (int i = 0; i < size; i++) {
		arr[i].flag = empty;
	}
}

/// <summary>
/// adds a tile to subject
/// </summary>
/// <param name="s"></param>
/// <param name="t"></param>
void HSubject::addSubjectAndTitle(string s, string t)
{
	int index = search(s);
	if (index == -1) {
		add(s);
		index = search(s);
	}
	arr[index].data.push_front(t);
}