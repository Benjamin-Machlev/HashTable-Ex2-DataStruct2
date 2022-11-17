#pragma once
#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <math.h>
using namespace std;



template <typename T, typename K>
class HashTable
{
protected:

	enum state { empty, full, deleted };
	template <typename U, typename V>
	class Item
	{
	public:
		U data;
		V key;
		state flag;
		Item() { flag = empty; }
		Item(U d, V  k, state f) { data = d; key = k; flag = f; }
	};

	int size;
	Item<T, K>* arr;
	bool prime(int n);
	int hash(K key, int i);
	virtual int h1(K key) = 0;
	virtual int h2(K key) = 0;
public:
	HashTable(int m = 10);
	~HashTable() { delete[] arr; }
	void add(K& key, T& dat);
	bool remove(K key);
	int search(K key);
	T* entryData(K i)
	{
		int ind = search(i);
		if (ind == -1)
			return NULL;
		else
			return &(arr[ind].data);
	}
	void print();
};

template<typename T, typename K>
inline bool HashTable<T, K>::prime(int n)
{
	for (int i = 2; i < n; i++) {
		if ((n % i) == 0) {
			return false;
		}
	}
	return true;
}

template<typename T, typename K>
inline HashTable<T, K>::HashTable(int m)
{
	if (prime(m)) {
		arr = new Item<T, K>[m];
	}
	else {
		do {
			m += 1;
		} while (!prime(m));
		arr = new Item<T, K>[m];
	}
	size = m;
}

template<typename T, typename K>
inline int HashTable<T, K>::hash(K key, int i)
{
	return (h1(key) + i * h2(key)) % size;
}

template<typename T, typename K>
inline void HashTable<T, K>::add(K& key, T& dat)
{
	for (int i = 0; i < size; i++) {
		int index = hash(key, i);
		if (arr[index].flag != full) {
			arr[index].data = dat;
			arr[index].key = key;
			arr[index].flag = full;
			return;
		}
	}
	throw "arr overflow";
}

template<typename T, typename K>
inline int HashTable<T, K>::search(K key)
{
	for (int i = 0; i < size; i++) {
		int index = hash(key, i);
		if (arr[index].key == key && arr[index].flag == full) {
			return index;
		}
		if (arr[index].flag == empty) {
			return -1;
		}
	}
	return -1;
}

template<typename T, typename K>
inline bool HashTable<T, K>::remove(K key)
{
	int index = search(key);
	if (index == -1) {
		return false;
	}
	else {
		arr[index].flag = deleted;
		return true;
	}
}

template <class T, class K>
void HashTable<T, K>::print()
{

	for (int i = 0; i < size; i++)
		if (arr[i].flag == full)
			cout << i << ": " << arr[i].data << endl;
		else
			cout << i << ": " << (arr[i].flag == empty ? "empty" : "deleted") << endl;
	//Item<T, K>* arr1 = new Item<T, K>[size];
	//list<int> toList;
	//for (int i = 0; i < size; i++)
	//{
	//	toList.push_front((int)(arr[i].data));
	//}
	//toList.sort();

	
	//for (int i = 0; i < toList.size(); i++)
	//{
	//	cout << toList.pop_front();
	//}
	//list<int>::iterator it;
	////for_each(toList.begin(), toList.end(), [](T) {
	////	cout << T;
	////	});
	//for (it = toList.begin(); it != toList.end(); it++)
	//{
	//	cout << (*it);
	//}
	//for each (auto var in toList)
	//{
	//	cout << var;
	//}
	//int *arr = new int[8];
}



class intHash :public HashTable<int,int>
{
public:
	intHash(int size) :HashTable(size) {}
	int h1(int key)
	{
		return key % size;
	}
	int h2(int key)
	{
		return key % (size - 1) + 1;
	}
};
