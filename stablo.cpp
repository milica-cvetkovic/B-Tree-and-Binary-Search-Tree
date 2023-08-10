#include "stablo.h"

Stablo::Stablo(int n) {
	m = n;
	string k = "koren";
	koren = new Bstablo(n, k);
}

Stablo::~Stablo() {
	Bstablo* temp = koren;
	stack<Bstablo*> stek;
	stek.push(temp);
	while (!stek.empty()) {
		temp = stek.top();
		stek.pop();
		if (temp->list) {
			delete[] temp->niz;
			delete[] temp->sinovi;
			continue;
		}
		else {
			for (int i = temp->broj - 1; i >= 0; i--) {
				stek.push(temp->sinovi[i]);
			}
		}
		delete[] temp->niz;
	}
}

void Stablo::prelivanjeDesni(Bstablo* temp, int flag, string k) {
	int l = temp->broj + temp->parent->sinovi[flag + 1]->broj + 2;
	int flg = 0;
	string* str = new string[l];
	for (int i = 0, j = 0; i < temp->broj + 1; i++) {
		if (temp->niz[j].compare(k) > 0 && !flg) {
			str[i] = k;
			flg++;
		}
		else if (flg == 2) {
			str[i] = k;
		}
		else {
			str[i] = temp->niz[j];
			if (j < temp->max) j++;
			if (j == temp->max) flg = 2, j--;
		}
	}
	str[m] = temp->parent->niz[flag];
	for (int i = m + 1, j = 0; i < l;i++, j++) {
		str[i] = temp->parent->sinovi[flag + 1]->niz[j];
	}
	int poz = (int)ceil((double)l / 2) - 1;
	delete[] temp->niz;
	delete[] temp->parent->sinovi[flag + 1]->niz;
	int str1 = floor((m + temp->parent->sinovi[flag + 1]->broj) / 2);
	temp->niz = new string[str1];
	temp->parent->sinovi[flag + 1]->niz = new string[l - str1 - 1];
	for (int i = 0; i < str1; i++) {
		temp->niz[i] = str[i];
	}
	temp->parent->niz[flag] = str[poz];
	for (int i = poz + 1, j = 0; i < l;i++, j++) {
		temp->parent->sinovi[flag + 1]->niz[j] = str[i];
	}
	temp->broj = str1;
	temp->parent->sinovi[flag + 1]->broj = l - str1 - 1;
}

void Stablo::prelivanjeLevi(Bstablo* temp, int flag, string k) {
	int l = temp->broj + temp->parent->sinovi[flag - 1]->broj + 2;
	int flg = 0;
	string* str = new string[l];
	for (int i = 0, j = 0; i < temp->parent->sinovi[flag - 1]->broj;i++, j++) {
		str[i] = temp->parent->sinovi[flag - 1]->niz[j];
	}
	str[temp->parent->sinovi[flag - 1]->broj] = temp->parent->niz[flag - 1];
	for (int i = temp->parent->sinovi[flag - 1]->broj + 1, j = 0; i < l; i++) {
		if (temp->niz[j].compare(k) > 0 && !flg) {
			str[i] = k;
			flg++;
		}
		else if (flg == 2) {
			str[i] = k;
		}
		else {
			str[i] = temp->niz[j];
			if (j < temp->max) j++;
			if (j == temp->max) flg = 2, j--;
		}
	}
	int poz = (int)ceil((double)l / 2) - 1;
	delete[] temp->niz;
	delete[] temp->parent->sinovi[flag - 1]->niz;
	int str1 = floor((m + temp->parent->sinovi[flag - 1]->broj) / 2);
	temp->niz = new string[m - 1];
	temp->parent->sinovi[flag - 1]->niz = new string[m - 1];
	for (int i = 0; i < str1; i++) {
		temp->parent->sinovi[flag - 1]->niz[i] = str[i];
	}
	temp->parent->niz[flag - 1] = str[poz];
	for (int i = poz + 1, j = 0; i < l;i++, j++) {
		temp->niz[j] = str[i];
	}
	temp->parent->sinovi[flag - 1]->broj = str1;
	temp->broj = l - str1 - 1;
}

void Stablo::prelamanjeKoren(Bstablo* temp, Bstablo* temp1, int flag, string* str) {
	int m1 = (int)floor((double)(2 * m - 2) / 3);
	int m2 = (int)floor((double)(2 * m - 1) / 3);
	int m3 = (int)floor((double)(2 * m) / 3);
	int poz = (int)ceil((double)temp->parent->broj / 2) - 1;
	Bstablo* novi1 = new Bstablo(m);
	Bstablo* novi2 = new Bstablo(m);
	string* pom = new string[temp->parent->broj];
	for (int i = 0; i < flag;i++) {
		pom[i] = temp->parent->niz[i];
	}
	pom[flag] = str[m1];
	pom[flag + 1] = str[m1 + 1 + m2];
	for (int i = flag + 1, j = flag + 2; i < temp->parent->broj - 1;i++, j++) {
		pom[j] = temp->parent->niz[i];
	}
	for (int i = 0; i < poz;i++) {
		novi1->niz[i] = pom[i];
	}
	novi1->broj = poz;
	for (int i = poz + 1, j = 0; i < temp->parent->broj; i++, j++) {
		novi2->niz[j] = pom[i];
	}
	novi2->broj = temp->parent->broj - poz - 1;
	int f = 0, p = 0, prvi = 0, drugi = 0, treci = 0;
	for (int i = 0, j = 0; j <= poz;j++) {
		if (i == flag + 2 && !f) {
			novi1->sinovi[i] = temp1;
			f++;
		}
		else {
			if (i == poz) p++;
			novi1->sinovi[j] = temp->parent->sinovi[i];
			i++;
		}
	}
	int f1 = 0;
	for (int i = (p ? poz + 1 : poz), j = 0; j < novi2->broj + 1; j++) {
		if (i == flag + 2 && !f && !f1) {
			novi2->sinovi[j] = temp1;
			f1++;
		}
		else {
			novi2->sinovi[j] = temp->parent->sinovi[i];
			i++;
		}
	}
	delete[] temp->parent->niz;
	//DELETE SINOVI
	for (int i = 0; i < temp->parent->max + 1;i++) {
		temp->parent->sinovi[i] = nullptr;
	}
	temp->parent->niz = new string[temp->parent->max];
	temp->parent->list = false;
	temp->parent->sinovi[0] = novi1;
	temp->parent->sinovi[1] = novi2;
	novi1->parent = temp->parent;
	novi2->parent = temp->parent;
	novi1->list = false;
	novi2->list = false;
	temp->parent->niz[0] = pom[poz];
	temp->parent->broj = 1;
	if (p) {
		temp->parent = novi1;
		temp->parent->sinovi[flag + 1]->parent = novi1;
		temp1->parent = novi1;
	}
	else {
		temp->parent = novi2;
		temp->parent->sinovi[flag + 1]->parent = novi2;
		temp1->parent = novi2;
	}
}

string* Stablo::prelamanjeDesniString(Bstablo* temp, int flag, string k) {
	int l = temp->broj + temp->parent->sinovi[flag + 1]->broj + 2;
	int flg = 0;
	int m1 = (int)floor((double)(2 * m - 2) / 3);
	int m2 = (int)floor((double)(2 * m - 1) / 3);
	int m3 = (int)floor((double)(2 * m) / 3);
	string* str = new string[l];
	for (int i = 0, j = 0; i < temp->broj + 1; i++) {
		if (temp->niz[j].compare(k) > 0 && !flg) {
			str[i] = k;
			flg++;
		}
		else if (flg == 2) {
			str[i] = k;
		}
		else {
			str[i] = temp->niz[j];
			if (j < temp->max) j++;
			if (j == temp->max) flg = 2, j--;
		}
	}
	str[m] = temp->parent->niz[flag];
	for (int i = m + 1, j = 0; i < l;i++, j++) {
		str[i] = temp->parent->sinovi[flag + 1]->niz[j];
	}
	return str;
}

string* Stablo::prelamanjeLeviString(Bstablo* temp, int flag, string k) {
	int l = temp->broj + temp->parent->sinovi[flag - 1]->broj + 2;
	int flg = 0;
	int m1 = (int)floor((double)(2 * m - 2) / 3);
	int m2 = (int)floor((double)(2 * m - 1) / 3);
	int m3 = (int)floor((double)(2 * m) / 3);
	string* str = new string[l];
	for (int i = 0, j = 0; i < temp->parent->sinovi[flag - 1]->broj;i++, j++) {
		str[i] = temp->parent->sinovi[flag - 1]->niz[j];
	}
	str[temp->parent->sinovi[flag - 1]->broj] = temp->parent->niz[flag - 1];
	for (int i = temp->parent->sinovi[flag - 1]->broj + 1, j = 0; i < l; i++) {
		if (temp->niz[j].compare(k) > 0 && !flg) {
			str[i] = k;
			flg++;
		}
		else if (flg == 2) {
			str[i] = k;
		}
		else {
			str[i] = temp->niz[j];
			if (j < temp->max) j++;
			if (j == temp->max) flg = 2, j--;
		}
	}
	return str;
}

Stablo::Bstablo* Stablo::prelamanjeDesni(Bstablo* temp, int flag, string k) {
	int l = temp->broj + temp->parent->sinovi[flag + 1]->broj + 2;
	int m1 = (int)floor((double)(2 * m - 2) / 3);
	int m2 = (int)floor((double)(2 * m - 1) / 3);
	int m3 = (int)floor((double)(2 * m) / 3);
	string* str = prelamanjeDesniString(temp, flag, k);
	delete[] temp->niz;
	delete[] temp->parent->sinovi[flag + 1]->niz;
	temp->niz = new string[m];
	temp->parent->sinovi[flag + 1]->niz = new string[m];
	Bstablo* temp1 = new Bstablo(m);
	temp1->parent = temp->parent;
	temp1->list = true;
	temp->parent->broj++;
	int warn = 0;
	if (temp->parent->broj > temp->parent->max) {
		warn++;
	}
	for (int i = 0; i < m1;i++) {
		temp->niz[i] = str[i];
	}
	if (!warn) {
		temp->parent->niz[flag] = str[m1];
	}
	for (int i = m1 + 1, j = 0; i < m1 + 1 + m2;i++, j++) {
		temp->parent->sinovi[flag + 1]->niz[j] = str[i];
	}
	if (!warn) {
		for (int i = temp->parent->max - 1; i >= flag + 1; i--) {
			temp->parent->niz[i] = temp->parent->niz[i - 1];
		}
		temp->parent->niz[flag + 1] = str[m1 + 1 + m2];
	}
	for (int i = m1 + m2 + 2, j = 0; i < l; i++, j++) {
		temp1->niz[j] = str[i];
	}
	temp->broj = m1;
	temp->parent->sinovi[flag + 1]->broj = m2;
	temp1->broj = m3;
	if (warn) return temp1;
	else {
		for (int i = temp->parent->broj + 1; i > flag + 2; i--) {
			temp->parent->sinovi[i] = temp->parent->sinovi[i - 1];
		}
		temp->parent->sinovi[flag + 2] = temp1;
		return nullptr;
	}
}

Stablo::Bstablo* Stablo::prelamanjeLevi(Bstablo* temp, int flag, string k) {
	int l = temp->broj + temp->parent->sinovi[flag - 1]->broj + 2;
	int flg = 0;
	int m1 = (int)floor((double)(2 * m - 2) / 3);
	int m2 = (int)floor((double)(2 * m - 1) / 3);
	int m3 = (int)floor((double)(2 * m) / 3);
	string* str = prelamanjeLeviString(temp, flag, k);
	delete[] temp->niz;
	delete[] temp->parent->sinovi[flag - 1]->niz;
	temp->niz = new string[m];
	temp->parent->sinovi[flag - 1]->niz = new string[m];
	Bstablo* temp1 = new Bstablo(m);
	temp1->parent = temp->parent;
	temp1->list = true;
	temp->parent->broj++;
	int warn = 0;
	if (temp->parent->broj > temp->parent->max) {
		warn++;
	}
	for (int i = 0; i < m1;i++) {
		temp->parent->sinovi[flag - 1]->niz[i] = str[i];
	}
	if (!warn) temp->parent->niz[flag - 1] = str[m1];
	for (int i = m1 + 1, j = 0; i < m1 + 1 + m2;i++, j++) {
		temp->niz[j] = str[i];
	}
	if (!warn) {
		for (int i = temp->parent->max - 1; i >= flag; i--) {
			temp->parent->niz[i] = temp->parent->niz[i - 1];
		}
		temp->parent->niz[flag] = str[m1 + 1 + m2];
	}
	for (int i = m1 + m2 + 2, j = 0; i < l; i++, j++) {
		temp1->niz[j] = str[i];
	}
	temp->parent->sinovi[flag - 1]->broj = m1;
	temp->broj = m2;
	temp1->broj = m3;
	if (warn) return temp1;
	else {
		for (int i = temp->parent->broj + 1; i > flag + 1; i--) {
			temp->parent->sinovi[i] = temp->parent->sinovi[i - 1];
		}
		temp->parent->sinovi[flag + 1] = temp1;
		return nullptr;
	}
}

bool Stablo::pronadjiKljuc(string k) {
	Bstablo* temp = koren;
	while (true) {
		if (temp->niz[0].compare(k) > 0) {
			temp = temp->sinovi[0];
		}
		else if (temp->niz[temp->broj - 1].compare(k) < 0) {
			temp = temp->sinovi[temp->broj];
		}
		else {
			for (int i = 0; i < temp->max - 1; i++) {
				if (temp->niz[i].compare(k) < 0 && temp->niz[i + 1].compare(k) > 0) {
					temp = temp->sinovi[i + 1];
				}
				if (temp == nullptr) return false;
			}
		}
		if (temp == nullptr) return false;
		for (int i = 0; i < temp->max; i++) {
			if (temp->niz[i] == k) return true;
		}
	}
	return false;
}


bool Stablo::umetniKljuc(string k) {
	Bstablo* temp = koren;
	if (temp->list == 1) {
		//PROVERA DA LI JE KOREN LIST
		if (temp->broj < temp->max) {
			//AKO IMA MESTA U KORENU
			for (int i = 0; i < temp->max; i++) {
				if (temp->niz[i].compare(k) > 0) {
					for (int j = temp->max; j > i;j--) {
						temp->niz[j] = temp->niz[j - 1];
					}
					temp->niz[i] = k;
					temp->broj++;
					return true;
				}
				else if (temp->niz[i] == "") {
					temp->niz[i] = k;
					temp->broj++;
					return true;
				}
			}
		}
		else {
			//PRELAMANJE KORENA
			int poz = (int)ceil((double)temp->broj / 2);
			int flag = 0;
			Bstablo* novi1 = new Bstablo(m);
			Bstablo* novi2 = new Bstablo(m);
			string* str = new string[temp->max + 1];
			for (int i = 0, j = 0; i < temp->max + 1; i++) {
				if (temp->niz[j].compare(k) > 0 && !flag) {
					str[i] = k;
				}
				else if (flag) {
					str[i] = k;
				}
				else {
					str[i] = temp->niz[j];
					if (j < temp->max - 1) j++;
					else flag++;
				}
			}
			for (int i = 0; i < poz; i++) {
				novi1->niz[i] = str[i];
			}
			for (int i = poz + 1, j = 0; i < temp->max + 1; i++, j++) {
				novi2->niz[j] = str[i];
			}
			delete[] temp->niz;
			temp->niz = new string[m];
			temp->niz[0] = str[poz];
			temp->sinovi[0] = novi1;
			temp->sinovi[1] = novi2;
			temp->list = false;
			temp->broj = 1;
			novi1->parent = novi2->parent = temp;
			novi1->list = true;
			novi2->list = true;
			novi1->broj += poz;
			novi2->broj += temp->max - poz;
			delete[] str;
			return true;
		}
	}
	else {
		//AKO KOREN NIJE LIST
		int flag = 0;
		//TRAZI SE LIST SA MESTOM ZA KLJUC
		while (!temp->list) {
			if (temp->niz[0].compare(k) > 0) {
				temp = temp->sinovi[0];
				flag = 0;
			}
			else if (temp->niz[temp->broj - 1].compare(k) < 0) {
				flag = temp->broj;
				temp = temp->sinovi[temp->broj];
			}
			else {
				for (int i = 0; i < temp->broj; i++) {
					if (temp->niz[i].compare(k) < 0 && temp->niz[i + 1].compare(k) > 0) {
						temp = temp->sinovi[i + 1];
						flag = i + 1;
						break;
					}
				}
			}
			for (int i = 0; i < temp->max; i++) {
				if (temp->niz[i] == k) return false;
			}
		}
		if (temp->broj < temp->max&& temp->broj >= temp->min) {
			//PROVERA DA LI IMA MESTA U PRONADJENOM LISTU
			for (int i = 0; i < temp->max; i++) {
				if (temp->niz[i].compare(k) > 0) {
					for (int j = temp->max; j > i;j--) {
						temp->niz[j] = temp->niz[j - 1];
					}
					temp->niz[i] = k;
					temp->broj++;
					return true;
				}
				else if (temp->niz[i] == "") {
					temp->niz[i] = k;
					temp->broj++;
					return true;
				}
			}
		}
		else if (temp->broj == (m - 1) && flag < temp->parent->broj && temp->parent->sinovi[flag + 1]->broj != temp->parent->sinovi[flag + 1]->max) {
			//PROVERA DESNOG BRATA LISTA
			prelivanjeDesni(temp, flag, k);
		}
		else if (temp->broj == (m - 1) && flag != 0 && temp->parent->sinovi[flag - 1]->broj != temp->parent->sinovi[flag - 1]->max) {
			//PRELIVANJE SA LEVIM BRATOM
			prelivanjeLevi(temp, flag, k);
		}
		else if (temp->broj == (m - 1) && flag < temp->parent->broj && temp->parent->sinovi[flag + 1]->broj == temp->parent->sinovi[flag + 1]->max) {
			//PRELAMANJE SA DESNIM BRATOM
			string* str = prelamanjeDesniString(temp, !flag ? 0 : flag - 1, k);
			Bstablo* temp1 = prelamanjeDesni(temp, !flag ? 0 : flag - 1, k);
			if (temp1) {
				if (temp->parent == koren) {
					prelamanjeKoren(temp, temp1, !flag ? 0 : flag - 1, str);
				}
				else {
					int prelamanje = 1;
					Bstablo* priv = temp->parent;
					while (prelamanje) {
						for (int i = 0; i < priv->parent->broj + 1; i++) {
							if (priv->parent->sinovi[i] == priv) {
								flag = i;
								break;
							}
						}
						if (flag < priv->parent->broj && priv->parent->sinovi[flag + 1]->broj != priv->parent->sinovi[flag + 1]->max) {
							prelivanjeDesni(priv, flag, k);
							prelamanje = 0;
						}
						else if (flag != 0 && priv->parent->sinovi[flag - 1]->broj != priv->parent->sinovi[flag - 1]->max) {
							prelivanjeLevi(priv, flag, k);
							prelamanje = 0;
						}
						else if (flag < priv->parent->broj && priv->parent->sinovi[flag + 1]->broj == priv->parent->sinovi[flag + 1]->max) {
							str = prelamanjeDesniString(priv, !flag ? 0 : flag - 1, k);
							temp1 = prelamanjeDesni(priv, !flag ? 0 : flag - 1, k);
							if (temp->parent == koren) {
								prelamanjeKoren(temp, temp1, !flag ? 0 : flag - 1, str);
								prelamanje = 0;
							}
							else priv = priv->parent;
						}
					}
				}
			}
		}
		else if (temp->broj == (m - 1) && flag != 0 && temp->parent->sinovi[flag - 1]->broj == temp->parent->sinovi[flag - 1]->max) {
			//PRELAMANJE SA LEVIM BRATOM
			string* str = prelamanjeLeviString(temp, flag, k);
			Bstablo* temp1 = prelamanjeLevi(temp, flag, k);
			//SUKCESIVNO PRELAMANJE
			if (temp1) {
				if (temp->parent == koren) {
					prelamanjeKoren(temp, temp1, flag, str);
				}
				else {
					int prelamanje = 1;
					Bstablo* priv = temp->parent;
					while (prelamanje) {
						for (int i = 0; i < priv->parent->broj + 1; i++) {
							if (priv->parent->sinovi[i] == priv) {
								flag = i;
								break;
							}
						}
						if (flag < priv->parent->broj && priv->parent->sinovi[flag + 1]->broj != priv->parent->sinovi[flag + 1]->max) {
							prelivanjeDesni(priv, flag, k);
						}
						else if (flag != 0 && priv->parent->sinovi[flag - 1]->broj != priv->parent->sinovi[flag - 1]->max) {
							prelivanjeLevi(priv, flag, k);
						}
						else if (flag < priv->parent->broj && priv->parent->sinovi[flag + 1]->broj == priv->parent->sinovi[flag + 1]->max) {
							str = prelamanjeDesniString(priv, !flag ? 0 : flag - 1, k);
							temp1 = prelamanjeDesni(priv, !flag ? 0 : flag - 1, k);
							if (temp->parent == koren) {
								prelamanjeKoren(temp, temp1, !flag ? 0 : flag - 1, str);
								prelamanje = 0;
							}
							else priv = priv->parent;
						}
					}
				}
			}
		}
	}
	return true;
}

bool Stablo::obrisiKljuc(string k) {
	Bstablo* temp = koren;
	int flag = 0;
	if (temp->list) {
		//KOREN JE LIST
		for (int i = 0; i < temp->max; i++) {
			if (temp->niz[i] == k) {
				for (int j = i; j < temp->max - 1;j++) {
					temp->niz[j] = temp->niz[j + 1];
				}
				temp->niz[temp->max - 1] = "";
				temp->broj--;
				if (temp->broj == 0) {
					// OBRISI TEMP
				}
			}
		}
	}
	else {
		//PRETRAGA NA LIST SA KLJUCEM
		int flagovi = 0, pozicija = 0;
		while (true) {
			if (temp->niz[0].compare(k) > 0) {
				temp = temp->sinovi[0];
				flag = 0;
			}
			else if (temp->niz[temp->broj - 1].compare(k) < 0) {
				flag = temp->broj;
				temp = temp->sinovi[temp->broj];
			}
			else {
				for (int i = 0; i < temp->broj; i++) {
					if (temp->niz[i].compare(k) < 0 && temp->niz[i + 1].compare(k) > 0) {
						temp = temp->sinovi[i + 1];
						flag = i + 1;
						break;
					}
				}
			}
			for (int i = 0; i < temp->max;i++) {
				if (temp->niz[i] == k) {
					flagovi++;
					pozicija = i;
					break;
				}
			}
			if (flagovi) break;
		}
		if (!temp->list) {
			Bstablo* priv = temp;
			priv = priv->sinovi[pozicija + 1];
			while (!priv->list) {
				priv = priv->sinovi[0];
			}
			string privremen = priv->niz[0];
			priv->niz[0] = temp->niz[pozicija];
			temp->niz[pozicija] = privremen;
			temp = priv;
			for (int i = 0; i < temp->max + 1; i++) {
				if (temp->parent->sinovi[i] == temp) {
					flag = i;
					break;
				}
			}
		}
		for (int i = 0; i < temp->max; i++) {
			if (temp->niz[i] == k) {
				for (int j = i; j < temp->max - 1;j++) {
					temp->niz[j] = temp->niz[j + 1];
				}
				temp->niz[temp->max - 1] = "";
				temp->broj--;
			}
		}
		if (temp->broj >= temp->min) {
			//LIST IMA DOVOLJNO DA SME DA SE OBRISE IZ NJEGA
		}
		else if (temp->broj < temp->min && flag < temp->parent->broj && temp->parent->sinovi[flag + 1]->broj > temp->parent->sinovi[flag + 1]->min) {
			//PRVI DESNI BRAT IMA DOVOLJNO
			temp->broj = temp->min;
			for (int i = 0; i < temp->max; i++) {
				if (temp->niz[i] == "") {
					temp->niz[i] = temp->parent->niz[!flag ? 0 : flag - 1];
					temp->broj++;
					break;
				}
			}
			temp->parent->niz[!flag ? 0 : flag - 1] = temp->parent->sinovi[flag + 1]->niz[0];
			for (int i = 0; i < temp->parent->sinovi[flag + 1]->broj - 1; i++) {
				temp->parent->sinovi[flag + 1]->niz[i] = temp->parent->sinovi[flag + 1]->niz[i + 1];
			}
			temp->parent->sinovi[flag + 1]->niz[temp->parent->sinovi[flag + 1]->broj - 1] = "";
			temp->parent->sinovi[flag + 1]->broj--;
			return true;
		}
		else if (temp->broj < temp->min && flag != 0 && temp->parent->sinovi[flag - 1]->broj > temp->parent->sinovi[flag - 1]->min) {
			//PRVI LEVI BRAT IMA DOVOLJNO
			temp->broj = temp->min;
			for (int i = temp->broj; i > 0; i--) {
				temp->niz[i] = temp->niz[i - 1];
			}
			temp->niz[0] = temp->parent->niz[flag - 1];
			temp->parent->niz[flag - 1] = temp->parent->sinovi[flag - 1]->niz[temp->parent->sinovi[flag - 1]->broj - 1];
			temp->parent->sinovi[flag - 1]->niz[temp->parent->sinovi[flag - 1]->broj - 1] = "";
			temp->parent->sinovi[flag - 1]->broj--;
			return true;
		}
		else if (temp->broj < temp->min && flag < temp->parent->broj - 1 && temp->parent->sinovi[flag + 2]->broj > temp->parent->sinovi[flag + 2]->min) {
			//DRUGI DESNI BRAT IMA DOVOLJNO
			temp->broj = temp->min;
			string pom1 = temp->parent->niz[flag + 1];
			temp->parent->niz[flag + 1] = temp->parent->sinovi[flag + 2]->niz[0];
			for (int i = 0; i < temp->parent->sinovi[flag + 2]->max - 1; i++) {
				temp->parent->sinovi[flag + 2]->niz[i] = temp->parent->sinovi[flag + 2]->niz[i + 1];
			}
			temp->parent->sinovi[flag + 2]->niz[temp->parent->sinovi[flag + 2]->max - 1] = "";
			string pom2 = temp->parent->niz[flag];
			temp->parent->niz[flag] = temp->parent->sinovi[flag + 1]->niz[0];
			for (int i = 0; i < temp->parent->sinovi[flag + 1]->max - 1; i++) {
				temp->parent->sinovi[flag + 1]->niz[i] = temp->parent->sinovi[flag + 1]->niz[i + 1];
			}
			temp->parent->sinovi[flag + 1]->niz[temp->parent->sinovi[flag + 1]->broj - 1] = pom1;
			temp->niz[temp->broj - 1] = pom2;
			temp->parent->sinovi[flag + 2]->broj--;
			return true;
		}
		else if (temp->broj < temp->min && flag > 1 && temp->parent->sinovi[flag - 2]->broj > temp->parent->sinovi[flag - 2]->min) {
			//DRUGI LEVI BRAT IMA DOVOLJNO
			temp->broj = temp->min;
			string pom1 = temp->parent->niz[flag - 2];
			temp->parent->niz[flag - 2] = temp->parent->sinovi[flag - 2]->niz[temp->parent->sinovi[flag - 2]->broj - 1];
			temp->parent->sinovi[flag - 2]->niz[temp->parent->sinovi[flag - 2]->broj - 1] = "";
			temp->parent->sinovi[flag - 2]->broj--;
			string pom2 = temp->parent->niz[flag - 1];
			temp->parent->niz[flag - 1] = temp->parent->sinovi[flag - 1]->niz[temp->parent->sinovi[flag - 1]->broj - 1];
			for (int i = temp->parent->sinovi[flag - 1]->max - 1; i > 0;i--) {
				temp->parent->sinovi[flag - 1]->niz[i] = temp->parent->sinovi[flag - 1]->niz[i - 1];
			}
			temp->parent->sinovi[flag - 1]->niz[0] = pom1;
			for (int i = temp->max - 1; i > 0;i--) {
				temp->niz[i] = temp->niz[i - 1];
			}
			temp->niz[0] = pom2;
			return true;
		}
		else if (temp->broj < temp->min && flag != 0 && flag < temp->parent->broj - 1 && temp->parent->sinovi[flag - 1]->broj == temp->parent->sinovi[flag - 1]->min && temp->parent->sinovi[flag + 1]->broj == temp->parent->sinovi[flag + 1]->min) {
			//SPAJANJE 3 U 2 SA LEVIM I DESNIM BRATOM
			string* str = new string[temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag + 1]->broj + 2];
			for (int i = 0; i < temp->parent->sinovi[flag - 1]->broj;i++) {
				str[i] = temp->parent->sinovi[flag - 1]->niz[i];
			}
			str[temp->parent->sinovi[flag - 1]->broj] = temp->parent->niz[flag - 1];
			for (int i = temp->parent->sinovi[flag - 1]->broj + 1, j = 0; i < temp->parent->sinovi[flag - 1]->broj + temp->broj + 1;i++, j++) {
				str[i] = temp->niz[j];
			}
			str[temp->parent->sinovi[flag - 1]->broj + temp->broj + 1] = temp->parent->niz[flag];
			for (int i = temp->parent->sinovi[flag - 1]->broj + temp->broj + 2, j = 0; j < temp->parent->sinovi[flag + 1]->broj;i++, j++) {
				str[i] = temp->parent->sinovi[flag + 1]->niz[j];
			}
			int poz = (int)ceil((double)(temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag + 1]->broj + 2) / 2) - 1;
			for (int i = flag - 1; i < temp->parent->max - 1; i++) {
				temp->parent->niz[i] = temp->parent->niz[i + 1];
			}
			temp->parent->niz[flag - 1] = str[poz];
			temp->parent->broj--;
			temp->parent->niz[temp->parent->broj] = "";
			delete[] temp->parent->sinovi[flag - 1]->niz;
			delete[] temp->niz;
			delete[] temp->parent->sinovi[flag + 1]->niz;
			temp->parent->sinovi[flag + 1]->parent = nullptr;
			for (int i = flag + 1; i < temp->parent->max;i++) {
				temp->parent->sinovi[i] = temp->parent->sinovi[i + 1];
			}
			temp->parent->sinovi[temp->parent->max] = nullptr;
			temp->parent->sinovi[flag - 1]->niz = new string[temp->parent->sinovi[flag - 1]->max];
			temp->niz = new string[temp->max];
			for (int i = 0; i < poz; i++) {
				temp->parent->sinovi[flag - 1]->niz[i] = str[i];
			}
			for (int i = poz + 1, j = 0; j < temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag + 1]->broj + 2 - poz - 1; i++, j++) {
				temp->niz[j] = str[i];
			}
			int brojevi = temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag + 1]->broj + 2 - poz - 1;
			temp->parent->sinovi[flag - 1]->broj = poz;
			temp->broj = brojevi;
		}
		else if (temp->broj < temp->min && flag < temp->parent->broj - 1 && temp->parent->sinovi[flag + 2]->broj == temp->parent->sinovi[flag + 2]->min && temp->parent->sinovi[flag + 1]->broj == temp->parent->sinovi[flag + 1]->min) {
			//3 U 2 SA DESNA DVA BRATA
			string* str = new string[temp->broj + temp->parent->sinovi[flag + 1]->broj + temp->parent->sinovi[flag + 2]->broj + 2];
			for (int i = 0; i < temp->broj;i++) {
				str[i] = temp->niz[i];
			}
			str[temp->broj] = temp->parent->niz[flag];
			for (int i = temp->broj + 1, j = 0; i < temp->broj + temp->parent->sinovi[flag + 1]->broj + 1;i++, j++) {
				str[i] = temp->parent->sinovi[flag + 1]->niz[j];
			}
			str[temp->broj + temp->parent->sinovi[flag + 1]->broj + 1] = temp->parent->niz[flag + 1];
			for (int i = temp->broj + temp->parent->sinovi[flag + 1]->broj + 2, j = 0; j < temp->parent->sinovi[flag + 2]->broj;i++, j++) {
				str[i] = temp->parent->sinovi[flag + 2]->niz[j];
			}
			int poz = (int)ceil((double)(temp->broj + temp->parent->sinovi[flag + 1]->broj + temp->parent->sinovi[flag + 2]->broj + 2) / 2) - 1;
			for (int i = flag; i < temp->parent->max - 1; i++) {
				temp->parent->niz[i] = temp->parent->niz[i + 1];
			}
			temp->parent->niz[flag] = str[poz];
			temp->parent->broj--;
			temp->parent->niz[temp->parent->broj] = "";
			delete[] temp->niz;
			delete[] temp->parent->sinovi[flag + 1]->niz;
			delete[] temp->parent->sinovi[flag + 2]->niz;
			temp->parent->sinovi[flag + 2]->parent = nullptr;
			for (int i = flag + 1;i < temp->parent->max;i++) {
				temp->parent->sinovi[i] = temp->parent->sinovi[i + 1];
			}
			temp->parent->sinovi[temp->parent->max] = nullptr;
			temp->niz = new string[temp->max];
			for (int i = 0; i < poz;i++) {
				temp->niz[i] = str[i];
			}
			temp->parent->sinovi[flag + 1]->niz = new string[temp->parent->sinovi[flag + 1]->max];
			for (int i = poz + 1, j = 0; j < temp->broj + temp->parent->sinovi[flag + 1]->broj + temp->parent->sinovi[flag + 2]->broj + 2 - 1 - poz;i++, j++) {
				temp->parent->sinovi[flag + 1]->niz[j] = str[i];
			}
			int brojevi = temp->broj + temp->parent->sinovi[flag + 1]->broj + temp->parent->sinovi[flag + 2]->broj + 2 - 1 - poz;
			temp->broj = poz;
			temp->parent->sinovi[flag + 1]->broj = brojevi;
		}
		else if (temp->broj < temp->min && flag>1 && temp->parent->sinovi[flag - 2]->broj == temp->parent->sinovi[flag - 2]->min && temp->parent->sinovi[flag - 1]->broj == temp->parent->sinovi[flag - 1]->min) {
			// 3 U 2 SA LEVA DVA BRATA
			string* str = new string[temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag - 2]->broj + 2];
			for (int i = 0; i < temp->parent->sinovi[flag - 2]->broj; i++) {
				str[i] = temp->parent->sinovi[flag - 2]->niz[i];
			}
			str[temp->parent->sinovi[flag - 2]->broj] = temp->parent->niz[flag - 2];
			for (int i = temp->parent->sinovi[flag - 2]->broj + 1, j = 0; i < temp->parent->sinovi[flag - 2]->broj + temp->parent->sinovi[flag - 1]->broj + 1;i++, j++) {
				str[i] = temp->parent->sinovi[flag - 1]->niz[j];
			}
			str[temp->parent->sinovi[flag - 2]->broj + temp->parent->sinovi[flag - 1]->broj + 1] = temp->parent->niz[flag - 1];
			for (int i = temp->parent->sinovi[flag - 2]->broj + temp->parent->sinovi[flag - 1]->broj + 2, j = 0; j < temp->broj;i++, j++) {
				str[i] = temp->niz[j];
			}
			int poz = (int)ceil((double)(temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag - 2]->broj + 2) / 2) - 1;
			for (int i = flag - 2; i < temp->parent->max - 1; i++) {
				temp->parent->niz[i] = temp->parent->niz[i + 1];
			}
			temp->parent->niz[flag - 2] = str[poz];
			temp->parent->broj--;
			temp->parent->niz[temp->parent->broj] = "";
			delete[] temp->parent->sinovi[flag - 2]->niz;
			delete[] temp->parent->sinovi[flag - 1]->niz;
			delete[] temp->niz;
			for (int i = flag; i < temp->parent->max;i++) {
				temp->parent->sinovi[i] = temp->parent->sinovi[i + 1];
			}
			temp->parent->sinovi[temp->parent->max] = nullptr;
			temp->parent->sinovi[flag - 2]->niz = new string[poz];
			for (int i = 0; i < poz; i++) {
				temp->parent->sinovi[flag - 2]->niz[i] = str[i];
			}
			temp->parent->sinovi[flag - 1]->niz = new string[temp->parent->sinovi[flag - 1]->max];
			for (int i = poz + 1, j = 0; j < temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag - 2]->broj + 2 - poz - 1;i++, j++) {
				temp->parent->sinovi[flag - 1]->niz[j] = str[i];
			}
			int brojevi = temp->broj + temp->parent->sinovi[flag - 1]->broj + temp->parent->sinovi[flag - 2]->broj + 2 - poz - 1;
			temp->parent->sinovi[flag - 2]->broj = poz;
			temp->parent->sinovi[flag - 1]->broj = brojevi;
			temp->parent = nullptr;
		}
	}
	return true;
}

ostream& operator<<(ostream& os, const Stablo& s) {
	os << endl;
	Stablo::Bstablo* temp = s.koren;
	queue<Stablo::Bstablo*> red;
	red.push(temp);
	red.push(nullptr);
	int flag = 0;
	while (!red.empty()) {
		temp = red.front();
		red.pop();
		if (temp == nullptr && !flag) {
			flag++;
			os << endl;
			red.push(nullptr);
			continue;
		}
		else if (temp == nullptr) break;
		flag = 0;
		for (int i = 0; i < temp->broj;i++) {
			os << temp->niz[i] << "|";
		}
		os << "   ";
		for (int i = 0; i < temp->broj + 1; i++) {
			red.push(temp->sinovi[i]);
		}
	}
	os << endl << endl;
	return os;
}

int Stablo::leksikografski(string k) {
	Bstablo* temp = koren;
	stack<Bstablo*> stek;
	int poz = 0, flag = 0, flg = 0, br = 0;
	int broj = 0;
	while (true) {
		if (temp->niz[0].compare(k) > 0) {
			if (temp->sinovi[0] != nullptr) {
				temp = temp->sinovi[0];
				flg = 0;
			}
			else break;
		}
		else if (temp->niz[temp->broj - 1].compare(k) < 0) {
			if (temp->sinovi[temp->broj] != nullptr) {
				flg = temp->broj;
				temp = temp->sinovi[temp->broj];
			}
			else break;
		}
		else {
			for (int i = 0; i < temp->max - 1; i++) {
				if (temp->niz[i].compare(k) < 0 && temp->niz[i + 1].compare(k) > 0) {
					if (temp->sinovi[i + 1] != nullptr) {
						flg = i + 1;
						temp = temp->sinovi[i + 1];
					}
					else {
						br++;
						break;
					}
				}
			}
		}
		if (br) break;
		for (int i = 0; i < temp->max; i++) {
			if (temp->niz[i] == k) {
				poz = i;
				flag++;
				break;
			}
		}
		if (flag) break;
	}
	if (!flag) {
		temp = koren;
		while (true) {
			if (temp->niz[0].compare(k) > 0) {
				if (temp->sinovi[0] != nullptr) {
					temp = temp->sinovi[0];
					flg = 0;
				}
			}
			else if (temp->niz[temp->broj - 1].compare(k) < 0) {
				if (temp->sinovi[temp->broj] != nullptr) {
					flg = temp->broj;
					temp = temp->sinovi[temp->broj];
				}
			}
			else {
				for (int i = 0; i < temp->max - 1; i++) {
					if (temp->niz[i].compare(k) < 0 && temp->niz[i + 1].compare(k) > 0) {
						if (temp->sinovi[i + 1] != nullptr) {
							temp = temp->sinovi[i + 1];
							flg = i + 1;
						}
						else break;
					}
				}
			}
			for (int i = 0; i < temp->max; i++) {
				if (temp->niz[i].compare(k) > 0) {
					poz = i;
					flag++;
				}
			}
			if (temp->sinovi[0] == nullptr && !flag) {
				poz = temp->broj;
				break;
			}
			if (flag) break;
		}
	}
	broj += poz;

	if (temp->sinovi[0] != nullptr) {
		if (poz == 0) stek.push(temp->sinovi[0]);
		else {
			for (int i = poz; i >= 0; i--) {
				stek.push(temp->sinovi[i]);
			}
		}
	}
	else if (flg == 0)return broj;
	for (int i = flg - 1; i >= 0;i--) {
		stek.push(temp->parent->sinovi[i]);
		broj++;
	}
	while (!stek.empty()) {
		Bstablo* temp = stek.top();
		stek.pop();
		if (temp->list) {
			broj += temp->broj;
			continue;
		}
		else {
			for (int i = temp->broj - 1; i >= 0; i--) {
				stek.push(temp->sinovi[i]);
			}
		}
		broj += temp->broj;
	}
	return broj;
}
