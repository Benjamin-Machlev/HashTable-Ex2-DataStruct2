#pragma once
#include <iostream>
using namespace std;

template <typename T, typename K>
class HashTable {
protected:
	enum state { empty, full, deleted };
	template <typename U, typename V>
	class Item {
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
	void add(K& key);
	bool remove(K key);
	int search(K key);
};

/// <summary>
/// calculate if prime number or not
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="n"></param>
/// <returns></returns>
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

/// <summary>
/// Generates an array with the size of a prime number close to the received parameter
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="m"></param>
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

/// <summary>
/// Generates the index to the array
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="key"></param>
/// <param name="i"></param>
/// <returns></returns>
template<typename T, typename K>
inline int HashTable<T, K>::hash(K key, int i)
{
	return (h1(key) + i * h2(key)) % size;
}


/// <summary>
/// add the key to array
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="key"></param>
template<typename T, typename K>
void HashTable<T, K>::add(K& key)
{
	for (int i = 0; i < size; i++) {
		int index = hash(key, i);
		if (arr[index].flag != full) {
			arr[index].key = key;
			arr[index].flag = full;
			return;
		}
	}
}

/// <summary>
/// search the key in the table
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="key"></param>
/// <returns></returns>
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

/// <summary>
/// remove the key from the table
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="K"></typeparam>
/// <param name="key"></param>
/// <returns>return if the delete success</returns>
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