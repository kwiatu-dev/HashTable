#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "HashTable.cpp"

using namespace std;

string input = "src/data/input.txt";
string output = "src/data/output.txt";
HashTable* ht;

template <typename T>
void print_vector(vector<T> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}

	cout << endl;
}

vector<string> split(string s, char delimiter = ' ') {
	stringstream ss(s);
	vector<string> tokens;

	string token;

	while (getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

void size(int size) {
	ht = new HashTable(size);
}

void add(long int key, string value) {
	ht->add(key, value);
}

void print() {
	ofstream file(output, ios::app);

	if (file.is_open()) {
		file << *ht << endl;
		file.close();
	}
	else {
		cout << "Wyst¹pi³ b³¹d przy zapisie do pliku.";
	}
}

void del(long int key) {
	ht->del(key);
}

void stop() {
	delete ht;
}

void read_command(vector<string> v) {
	string command = v[0];

	if (command == "size") {
		size(stoi(v[1]));
	}
	else if (command == "add") {
		add(stol(v[1]), v[2]);
	}
	else if (command == "print") {
		print();
	}
	else if (command == "delete") {
		del(stol(v[1]));
	}
	else if (command == "stop") {
		stop();
	}
}

int main() {
	ifstream file(input);
	
	if (file.is_open()) {
		string line;
		int i = 0;

		while (getline(file, line)) {
			read_command(split(line));
		}

		file.close();
	}
	else {
		cout << "Nie uda³o siê otworzyæ pliku.";
	}

	return 0;
}