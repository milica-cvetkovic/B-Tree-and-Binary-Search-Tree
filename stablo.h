#ifndef _stablo_h_
#define _stablo_h_

#include <iostream>
#include <string>
#include <cmath>
#include <queue>
#include <stack>

using namespace std;

class Stablo {

	int m;
	struct Bstablo {
		string* niz;
		Bstablo** sinovi;
		Bstablo* parent;
		int broj;
		int max;
		int min;
		bool list;
		Bstablo(int n, string k) {
			broj = 0;
			list = true;
			int len = 2 * (int)floor((double)(2 * n - 2) / 3);
			niz = new string[len];
			for (int i = 0; i < len;i++) {
				niz[i] = "";
			}
			sinovi = new Bstablo * [len + 1];
			for (int i = 0;i < len;i++) {
				sinovi[i] = nullptr;
			}
			parent = nullptr;
			max = len;
			min = 1;
		}
		Bstablo(int n) {
			broj = 0;
			list = true;
			niz = new string[n - 1];
			for (int i = 0; i < n - 1;i++) {
				niz[i] = "";
			}
			sinovi = new Bstablo * [n];
			for (int i = 0;i < n;i++) {
				sinovi[i] = nullptr;
			}
			parent = nullptr;
			max = n - 1;
			min = (int)ceil((double)(2 * n - 1) / 3) - 1;
		}
	};
	Bstablo* koren = nullptr;

public:

	Stablo() = default;
	Stablo(int m);
	~Stablo();

	void prelamanjeKoren(Bstablo* temp, Bstablo* temp1, int flag, string* str);

	bool pronadjiKljuc(string k);

	friend ostream& operator<<(ostream& os, const Stablo& s);

	bool umetniKljuc(string k);

	bool obrisiKljuc(string k);

	int leksikografski(string k);

	void prelivanjeDesni(Bstablo* temp, int flag, string k);

	void prelivanjeLevi(Bstablo* temp, int flag, string k);

	string* prelamanjeDesniString(Bstablo* temp, int flag, string k);

	string* prelamanjeLeviString(Bstablo* temp, int flag, string k);

	Bstablo* prelamanjeDesni(Bstablo* temp, int flag, string k);

	Bstablo* prelamanjeLevi(Bstablo* temp, int flag, string k);

};

#endif