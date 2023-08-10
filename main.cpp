#include "stablo.h"

int main() {
	int izbor;
	int pretraga;
	string x; int m;
	cout << "Red stabla: ";
	cin >> m;
	Stablo stablo(m);
	cout << "Objekat je stvoren!\n";
	while (true) {
		cout << "MENI:\n1.Brisanje objekta stabla\n2.Pronalazenje kljuca\n3.Ispis stabla\n4.Umetanje kljuca\n5.Brisanje kljuca\n6.Broj leksikografski manjih kljuceva\n7.Kraj\n";
		cin >> izbor;
		switch (izbor) {
		case 1:
			cout << "Objekat je izbrisan!\n";
			return 0;
			break;
		case 2:
			cout << "Unesite kljuc za pretragu: ";
			cin >> x;
			pretraga = stablo.pronadjiKljuc(x);
			if (pretraga) cout << "Kljuc postoji!" << endl;
			else cout << "Kljuc ne postoji!" << endl;
			break;
		case 3:
			cout << stablo;
			break;
		case 4:
			cout << "Unesite kljuc: ";
			cin >> x;
			stablo.umetniKljuc(x);
			cout << "Kljuc je umetnut!\n";
			break;
		case 5:
			cout << "Unesite kljuc: ";
			cin >> x;
			stablo.obrisiKljuc(x);
			cout << "Kljuc je izbrisan!\n";
			break;
		case 6:
			cout << "Unesite kljuc na pretragu: ";
			cin >> x;
			cout << "Broj kljuceva koji su leksikografski manji od unesenog kljuca: ";
			cout << stablo.leksikografski(x);
			cout << endl;
			break;
		case 7:
			return 0;
			break;
		default:
			cout << "Neispravan unos!\n";
			break;
		}
	}
}