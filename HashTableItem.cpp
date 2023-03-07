#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class HashTableItem {
private:
	long int key;
	string value;

	void set_key(long int key) {
		if (key >= 0) {
			this->key = key;
		}
	}

	void set_value(string value) {
		this->value = value;
	}

public:
	HashTableItem(): key(-1), value("") {}

	HashTableItem(long int key, string item) {
		this->create(key, item);
	}

	void create(long int key, string item) {
		this->set_key(key);
		this->set_value(item);
	}

	bool is() {
		return this->key == -1 ? false : true;
	}

	long int get_key() {
		return this->key;
	}

	string get_value() {
		return this->value;
	}

	friend ostream& operator<<(ostream& out, HashTableItem& hti) {
		out << hti.get_key() << " " << hti.get_value();

		return out;
	}

	friend ofstream& operator<<(ofstream& out, HashTableItem& hti) {
		out << hti.get_key() << " " << hti.get_value();

		return out;
	}
};