#include <iostream>
#include <string>
#include "HashTableItem.cpp"

using namespace std;

class HashTable {
private:
	HashTableItem* A;
	int N;
	int count;

	int H(long int k, int i = 0) {
		return (k + i) % this->N;
	}

public:
	HashTable(int size): N(size), A(new HashTableItem[size]()), count(0) {

	}

	~HashTable() {
		delete[] this->A;
	}


	void add(long int key, string value) {
		if (this->N > this->count) {
			this->set_item(this->free_index(key), key, value);
		}
	}

	void del(long int key) {
		int shift = find_shift(key);
		this->clear_item(key, shift);
		this->refresh_claster(key, shift);
	}

	void refresh_claster(long int key, int shift) {
		int free_index, index = this->H(key, ++shift);
		HashTableItem item = this->index(index);

		while(item.is()){
			free_index = this->free_index(item.get_key());

			if (index != free_index) {
				this->set_item(free_index, item.get_key(), item.get_value());
				this->clear_index(index);
			}

			index = this->H(key, ++shift);
			item = this->index(index);
		}
	}

	void clear_item(long int key) {
		this->clear_index(this->find_index(key));
		this->count--;
	}

	void clear_item(long int key, int shift) {
		this->clear_index(this->H(key, shift));
		this->count--;
	}

	void clear_index(int index) {
		this->A[index] = HashTableItem();
		this->count--;
	}

	int size() {
		return this->N;
	}

	void set_item(int index, long int key, string value) {
		this->A[index] = HashTableItem(key, value);
		this->count++;
	}

	int free_index(long int key) {
		int collisions = 0, index = this->H(key);
		HashTableItem item = this->index(index);

		while (item.is()) {
			index = this->H(key, ++collisions);
			item = this->index(index);
		}

		return index;
	}

	int find_index(long int key) {
		return this->H(key, this->find_shift(key));
	}

	int find_shift(long int key) {
		int shift = 0, index = this->H(key);
		HashTableItem item = this->index(index);

		do {
			if (item.get_key() == key) { 
				break; 
			}

			index = this->H(key, ++shift);
			item = this->index(index);
		} 
		while (true);

		return shift;
	}

	string get(long int key) {
		return this->item(key).get_value();
	}

	HashTableItem& index(int index) {
		return this->A[index];
	}

	HashTableItem& item(long int key) {
		return this->A[this->find_index(key)];
	}

	friend ostream& operator<<(ostream& out, HashTable& ht) {
		for (int i = 0; i < ht.size(); i++) {
			out << i << " " << ht.index(i) << endl;
		}

		return out;
	}

	friend ofstream& operator<<(ofstream& out, HashTable& ht) {
		for (int i = 0; i < ht.size(); i++) {
			if (ht.index(i).is()) {
				out << i << " " << ht.index(i) << endl;
			}
		}

		return out;
	}

	HashTableItem* begin() { return &this->A[0]; }

	HashTableItem* end() { return &this->A[N]; }
};