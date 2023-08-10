#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

class BST {

	struct node {
		string key, info;
		struct node* left;
		struct node* right;
		struct node* parent;
	};

public:

	node* root;

	BST() {
		root = nullptr;
	}

	int height() {
		int height = 0, num;
		queue<node*> red;
		node* temp = root;
		red.push(temp);

		while (!red.empty()) {
			num = red.size();
			while (num--) {
				temp = red.front();
				red.pop();
				if (temp->left != nullptr) red.push(temp->left);
				if (temp->right != nullptr) red.push(temp->right);
			}
			height++;
		}
		return height;
	}


	void insert(string k, string n) {
		node* inserting = new node;
		inserting->key = k;
		inserting->info = n;
		inserting->left = nullptr;
		inserting->right = nullptr;
		inserting->parent = nullptr;
		node* temp = root;
		node* temp1 = nullptr;
		while (temp != nullptr) {
			temp1 = temp;
			if (temp->key == inserting->key) {
				node* prom;
				if (temp->left) {
					prom = temp->left;
					while (prom->right) prom = prom->right;
					prom->right = inserting;
					inserting->parent = prom;
				}
				else {
					temp->left = inserting;
					inserting->parent = temp;
				}
				return;
			}
			else if ((inserting->key.compare(temp->key)) < 0) temp = temp->left;
			else temp = temp->right;
		}
		if (temp1 == nullptr) {
			root = inserting;
		}
		else {
			if ((inserting->key.compare(temp1->key)) < 0) {
				temp1->left = inserting;
				inserting->parent = temp1;
			}
			else {
				temp1->right = inserting;
				inserting->parent = temp1;
			}
		}
	}

	void search(string k) {
		node* temp = root;
		while ((temp != nullptr) && (temp->key != k)) {
			if (k < temp->key) temp = temp->left;
			else temp = temp->right;
		}
		if (temp == nullptr) {
			cout << "Kljuc nije nadjen\n";
			return;
		}
		cout << temp->info << endl;

		if (temp->left) {
			temp = temp->left;
			while (temp != nullptr) {
				while ((temp->right) && (temp->key.compare(k))) {
					temp = temp->right;
				}
				if ((temp != nullptr) && (temp->key == k)) {
					cout << temp->info << endl;
					temp = temp->right;
				}
				else return;
			}
		}
	}

	// po ugledu na kod sa sajta predmeta
	void printing() {
		if (root == nullptr) return;
		queue<node*> row;
		int length = 62;
		int first = length, middle;
		int h = height();
		node* temp;

		row.push(root);
		for (int i = 0; i <= h;i++) {
			int j = 1 << i, k;
			middle = first;
			first = (first - 2) / 2;
			for (k = 0;k < first;k++) putchar(' ');
			for (k = 0; k < j;k++) {
				temp = row.front();
				row.pop();
				if (temp) {
					row.push(temp->left);
					row.push(temp->right);
				}
				else {
					row.push(nullptr);
					row.push(nullptr);
				}
				if (temp) cout << temp->key;
				else cout << "  ";
				for (int l = 0; l < middle;l++) putchar(' ');
			}
			cout << endl << endl;
		}
	}


	void printing_inorder() {
		stack<node*> stek;
		node* temp = root;
		while (true) {
			while (temp != nullptr) {
				stek.push(temp);
				temp = temp->left;
			}
			if (!stek.empty()) {
				temp = stek.top();
				stek.pop();
				cout << temp->key << " " << temp->info << endl;
				temp = temp->right;
			}
			else return;
		}
	}

	void delete_node(string k) {
		node* temp = root;
		node* temp1 = nullptr;
		node* sin, * par, * pom;
		while (true) {
			while ((temp != nullptr) && (temp->key != k)) {
				if (k < temp->key) temp = temp->left;
				else temp = temp->right;
			}
			if (temp == nullptr) return;
			if (temp->left == nullptr) sin = temp->right;
			else if (temp->right == nullptr) sin = temp->left;
			else {
				sin = temp;
				if (sin->right) {
					sin = sin->right;
					while (sin->left) {
						sin = sin->left;
					}
				}
				else {
					pom = sin->parent;
					while (pom && (sin == pom->right)) {
						sin = pom;
						pom = pom->parent;
					}
					sin = pom;
				}
				if (sin->parent != temp) {
					sin->parent->left = sin->right;
					sin->right = temp->right;
				}
				sin->left = temp->left;
			}
			if (temp->parent == nullptr) root = sin;
			else if (temp == temp->parent->left) {
				temp->parent->left = sin;
				if (sin != nullptr) sin->parent = temp->parent;
			}
			else {
				temp->parent->right = sin;
				if (sin != nullptr) sin->parent = temp->parent;
			}
			delete temp;
			temp = sin;
		}
	}

	void delete_tree() {
		stack<node*> stek;
		node* temp = root;
		node* temp1;
		while (true) {
			while (temp != nullptr) {
				stek.push(temp);
				temp = temp->left;
			}
			if (!stek.empty()) {
				temp1 = stek.top();
				stek.pop();
				temp = temp1->right;
				delete temp1;
			}
			else {
				root = nullptr;
				return;
			}
		}
	}

	void shortest(string k) {
		stack<node*> stek;
		node* temp = root;
		string shortest;
		int n = k.length();
		int count = 0;
		int len = 0;

		while (true) {
			while (temp != nullptr) {
				stek.push(temp);
				temp = temp->left;
			}
			if (!stek.empty()) {
				temp = stek.top();
				stek.pop();
				int cn = 0, i = 0;
				if (k[0] == temp->key[0]) {
					while ((i < n) && (i < temp->key.length())) {
						if (k[i] == temp->key[i]) cn++;
						else break;
						i++;
					}
					if (count == 0) {
						shortest = temp->key;
						count = cn;
						len = temp->key.length();
					}

					if (len > temp->key.length()) {
						len = temp->key.length();
						shortest = temp->key;
					}
					else if (len == temp->key.length()) {
						if (count <= cn) {
							shortest = temp->key;
						}
					}
				}
				temp = temp->right;
			}
			else {
				cout << shortest << endl;
				return;
			}
		}
	}
};


int main() {

	BST root;
	int choice, n;
	string key, info;

	while (true) {
		cout << "MENI" << endl << "1. Formiranje stabla\n2. Pretraga na kljuc\n3. Unos nove reci\n4. Ispis stabla\n5. Brisanje kljuca\n6. Brisanje stabla\n7. Pronalazenje najkrace reci\n8. Kraj\n";
		cin >> choice;

		switch (choice) {
		case 1:
			int check;
			cout << "1. Standardni ulaz\n2. Datoteka\n";
			cin >> check;
			if (check == 1) {
				cout << "Broj reci koje zelite da unesete: ";
				cin >> n;
				cout << endl << "Unesite reci:" << endl;
				for (int i = 0; i < n;i++) {
					cin >> key >> info;
					root.insert(key, info);
				}
				cout << "Stablo je formirano!\n";
			}
			else if (check == 2) {
				string infile, line;
				int pos;
				cout << "Naziv datoteke: ";
				cin >> infile;
				ifstream file;
				file.open(infile);
				if (!file) cout << "Nepostojeca datoteka\n";
				else {
					while (getline(file, line)) {
						pos = line.find(' ');
						key = line.substr(0, pos);
						info = line.substr(pos + 1);
						root.insert(key, info);
					}
					cout << "Stablo je formirano!\n";
				}
				file.close();
			}
			break;
		case 2:
			cout << "Kljuc za pretragu: ";
			cin >> key;
			cout << endl;
			root.search(key);
			break;
		case 3:
			cout << "Rec koju zelite da unesete: ";
			cin >> key >> info;
			cout << endl;
			root.insert(key, info);
			break;
		case 4:
			root.printing();
			break;
		case 5:
			cout << "Kljuc koji zelite da izbrisete: ";
			cin >> key;
			cout << endl;
			root.delete_node(key);
			break;
		case 6:
			root.delete_tree();
			cout << "Stablo je izbrisano!" << endl;
			break;
		case 7:
			cout << "Rec za pretragu: ";
			cin >> key;
			cout << endl;
			root.shortest(key);
			break;
		case 8:
			return 0;
			break;
		default:
			cout << "Neispravan unos!" << endl;
			break;
		}
	}
}