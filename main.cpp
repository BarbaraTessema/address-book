#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <limits>

using namespace std;

struct Adresat {
	int id = 0;
	string imie = "";
	string nazwisko = "";
	string numerTelefonu = "";
	string email = "";
	string adres = "";
};

string wczytajLinie();
int dodajAdresata(vector<Adresat>&, int);
int wczytajAdresatowZPliku(vector<Adresat>&);
void rozdzielLinieNaPojedynczeDane(vector<Adresat>&, string);
void wyswietlWszystkichAdresatow(vector<Adresat>&);
void wyszukajPoImieniu(vector<Adresat>&);
void wyszukajPoNazwisku(vector<Adresat>&);
void usunAdresata(vector<Adresat>&);
bool sprawdzCzyIstniejeAdresatOPodanymID (vector <Adresat>&, int);
void zapiszDoPliku(vector<Adresat>&);
void edytujAdresata(vector<Adresat>&);
void zmienImie(vector<Adresat>&, int);
void zmienNazwisko(vector<Adresat>&, int);
void zmienNumerTelefonu(vector<Adresat>&, int);
void zmienEmail(vector<Adresat>&, int);
void zmienAdres(vector<Adresat>&, int);

int main() {
	vector <Adresat> adresaci;
	int iloscAdresatow = 0; 
	char wybor;

	iloscAdresatow = wczytajAdresatowZPliku(adresaci);
	cout << "Ilosc adresatow: " << iloscAdresatow << "\n";
	system("pause");

	while (true) {
		system("cls");
		cout << "KSIAZKA ADRESOWA";
		cout << "\n1. Dodaj adresata";
		cout << "\n2. Wyszukaj po imieniu";
		cout << "\n3. Wyszukaj po nazwisku";
		cout << "\n4. Wyswietl wszystkich adresatow";
		cout << "\n5. Usun adresata";
		cout << "\n6. Edytuj adresata";
		cout << "\n9. Zakoncz program";
		cout << "\nTwoj wybor: ";
		cin >> wybor;

		switch (wybor) {
		case '1':
			iloscAdresatow = dodajAdresata(adresaci, iloscAdresatow);
			break;
		case '2':
			wyszukajPoImieniu(adresaci);
			break;
		case '3':
			wyszukajPoNazwisku(adresaci);
			break;
		case '4':
			wyswietlWszystkichAdresatow(adresaci);
			break;
		case '5':
			usunAdresata(adresaci);
			break;
		case '6':
			edytujAdresata(adresaci);
			break;
		case '9':
			exit(0);
			break;
		}	
	}
	return 0;
}

string wczytajLinie() {
	string linia = "";
	getline(cin, linia);
	return linia;
}

int dodajAdresata(vector<Adresat>& adresaci, int iloscAdresatow) {
	string imie, nazwisko, numerTelefonu, email, adres;
	Adresat adresat;
	cin.ignore();
	cout << "Podaj imie: ";
	imie = wczytajLinie();
	cout << "Podaj nazwisko: ";
	nazwisko = wczytajLinie();
	cout << "Podaj numer telefonu: ";
	numerTelefonu = wczytajLinie();
	cout << "Podaj email: ";
	email = wczytajLinie();
	cout << "Podaj adres: ";
	adres = wczytajLinie();

	adresat.id = iloscAdresatow + 1;
	adresat.imie = imie;
	adresat.nazwisko = nazwisko;
	adresat.numerTelefonu = numerTelefonu;
	adresat.email = email;
	adresat.adres = adres;

	adresaci.push_back(adresat);

	fstream plik;
	plik.open("Ksiazka Adresowa v 4.0.txt", ios::out | ios::app);

	if (plik.good() == true) {
		plik << adresat.id << "|";
		plik << adresat.imie << "|";
		plik << adresat.nazwisko << "|";
		plik << adresat.numerTelefonu << "|";
		plik << adresat.email << "|";
		plik << adresat.adres << "|" << "\n";
		plik.close();
	}
	else {
		cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych" << endl;
		system("pause");
	}
	cout << "\nAdresat zostal dodany\n";
	system("pause");
	return iloscAdresatow++;
}

void rozdzielLinieNaPojedynczeDane(vector <Adresat>& adresaci, string linia) {
	Adresat adresat;
	int nrLinii = 1;
	stringstream ss(linia);
	string pojedynczeDane = "";

	while (getline(ss, pojedynczeDane, '|')) {
		switch (nrLinii) {
		case 1:
			adresat.id = atoi(pojedynczeDane.c_str());
			break;
		case 2:
			adresat.imie = pojedynczeDane;
			break;
		case 3:
			adresat.nazwisko = pojedynczeDane;
			break;
		case 4:
			adresat.numerTelefonu = pojedynczeDane;
			break;
		case 5:
			adresat.email = pojedynczeDane;
			break;
		case 6:
			adresat.adres = pojedynczeDane;
			break;
		}
		nrLinii++;
	}
	adresaci.push_back(adresat);
}

int wczytajAdresatowZPliku(vector<Adresat>& adresaci) {
	string linia;
	//int nrLinii =1;
	int iloscAdresatow = 0;
	Adresat adresat;

	adresaci.clear();

	fstream plik;
	plik.open("Ksiazka Adresowa v 4.0.txt", ios::in);
	if (plik.good() == false) {
		cout << "Ksiazka adresowa jest pusta!\n";
		system("pause");
	}
	else{
		while (getline(plik, linia)) {
			rozdzielLinieNaPojedynczeDane(adresaci, linia);
			//nrLinii++;
			iloscAdresatow++;
		}
		plik.close();
	}
	return iloscAdresatow;
}

void wyswietlWszystkichAdresatow(vector <Adresat>& adresaci) {
	vector <Adresat> ::iterator itr = adresaci.begin();
	vector <Adresat> ::iterator itrEnd = adresaci.end();
	for (itr; itr != itrEnd; ++itr) {
		cout << "\nID: " << itr->id << "\n";
		cout << itr->imie << " " << itr->nazwisko << "\n";
		cout << "Numer telefonu: " << itr->numerTelefonu << "\n";
		cout << "Email: " << itr->email << "\n";
		cout << "Adres: " << itr->adres << "\n\n";
	}
	system("pause");
}

void wyszukajPoImieniu(vector<Adresat>& adresaci) {
	vector <Adresat> ::iterator itr = adresaci.begin();
	vector <Adresat> ::iterator itrEnd = adresaci.end();
	string imie;
	int liczbaZnalezionychAdresatow = 0;
	cout << "Podaj imie wyszukiwanego adresata: ";
	cin.ignore();
	imie = wczytajLinie();
	for (itr; itr != itrEnd; itr++) {
		if (itr->imie == imie) {
			cout << "\nID: " << itr->id << "\n";
			cout << itr->imie << " " << itr->nazwisko << "\n";
			cout << "Numer telefonu: " << itr->numerTelefonu << "\n";
			cout << "Email: " << itr->email << "\n";
			cout << "Adres: " << itr->adres << "\n\n";
			liczbaZnalezionychAdresatow++;
		}
	}
	if (liczbaZnalezionychAdresatow == 0) {
		cout << "Nie znaleziono adresata o takim imieniu w ksiazce adresowej.\n";
	}
	system("pause");
}

void wyszukajPoNazwisku(vector<Adresat>& adresaci) {
	vector <Adresat> ::iterator itr = adresaci.begin();
	vector <Adresat> ::iterator itrEnd = adresaci.end();

	string nazwisko;
	int liczbaZnalezionychAdresatow = 0;
	cout << "Podaj nazwisko wyszukiwanego adresata: ";
	cin.ignore();
	nazwisko = wczytajLinie();
	for (itr; itr != itrEnd; ++itr) {
		if (itr->nazwisko == nazwisko) {
			cout << "\nID: " << itr->id << "\n";
			cout << itr->imie << " " << itr->nazwisko<< "\n";
			cout << "Numer telefonu: " << itr->numerTelefonu << "\n";
			cout << "Email: " << itr->email << "\n";
			cout << "Adres: " << itr->adres << "\n\n";
			liczbaZnalezionychAdresatow++;
		}
	}
	if (liczbaZnalezionychAdresatow == 0) {
		cout << "Nie znaleziono adresata o takim nazwisku w ksiazce adresowej.\n";
	}
	system("pause");
}

bool sprawdzCzyIstniejeAdresatOPodanymID(vector<Adresat>& adresaci, int numerId) {
	int liczbaZnalezionychAdresatow = 0;
	vector <Adresat> ::iterator itr = adresaci.begin();
	vector <Adresat> ::iterator itrEnd = adresaci.end();
	for (itr; itr != itrEnd; ++itr) {
		if (itr->id == numerId) {
			cout << "\nID: " << itr->id << "\n";
			cout << itr->imie << " " << itr->nazwisko << "\n";
			cout << "Numer telefonu: " << itr->numerTelefonu << "\n";
			cout << "Email: " << itr->email << "\n";
			cout << "Adres: " << itr->adres << "\n\n";
			liczbaZnalezionychAdresatow++;
			system("pause");
			return true;
		}
	}
	if (liczbaZnalezionychAdresatow == 0) {
		cout << "Nie znaleziono adresata o podanym numerze identyfikacyjnym.\n";
		system("pause");
		return false;
	}
}

void zapiszDoPliku(vector <Adresat>& adresaci) {

	ofstream plik;
	plik.open("Ksiazka Adresowa v 4.0.txt");
	cout << adresaci.size();
	if (plik.is_open()) {
		for (size_t i = 0; i < adresaci.size(); i++) {
			plik << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|" << endl;
		}
	}
	plik.close();
}

void usunAdresata(vector<Adresat>& adresaci) {
	vector <Adresat> ::iterator itr = adresaci.begin();
	vector <Adresat> ::iterator itrEnd = adresaci.end();
	int IdAdresata;
	char potwierdzenie;
	cout << "Podaj numer identyfikacyjny adresata, ktorego chcesz usunac: ";
	cin >> IdAdresata;

	sprawdzCzyIstniejeAdresatOPodanymID(adresaci, IdAdresata);

	for (size_t i = 0; i < adresaci.size(); i++) {
		cout << "Potwierdz wciskajac t, jesli na pewno chcesz usunac podanego adresata: ";
		cin >> potwierdzenie;
		if (potwierdzenie == 't' || potwierdzenie == 'T') {
			adresaci.erase(std::remove_if(adresaci.begin(), adresaci.end(), [&](Adresat const& adresaci) {
				return adresaci.id == IdAdresata; }), adresaci.end());
			cout << "Adresat zostal usuniety!\n";
			zapiszDoPliku(adresaci);
			system("pause");
			break;
		}
		else {
			break;
		}
	}
	
}

void zmienImie(vector<Adresat>& adresaci, int numerId) {
	string noweImie;
	cout << "Podaj imie: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, noweImie);

	for (int i = 0; i < adresaci.size(); i++) {
		for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
			if (itr->id == numerId) {
				itr->imie = noweImie;
				break;
			}
		}
	}
	zapiszDoPliku(adresaci);
	cout << "Zmiany zostaly zapisane\n";
	system("pause");
}

void zmienNazwisko(vector<Adresat>& adresaci, int numerId) {
	string noweNazwisko;
	cout << "Podaj nazwisko: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, noweNazwisko);

	for (int i = 0; i < adresaci.size(); i++) {
		for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
			if(itr-> id == numerId) {
				itr->nazwisko = noweNazwisko;
				break;
			}
		}
	}
	zapiszDoPliku(adresaci);
	cout << "Zmany zostaly zapisane\n";
	system("pause");
}

void zmienNumerTelefonu(vector<Adresat>& adresaci, int numerId) {
	string nowyNumerTelefonu;
	cout << "Podaj numer telefonu: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, nowyNumerTelefonu);

	for (int i = 0; i < adresaci.size(); i++) {
		for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
			if (itr->id == numerId) {
				itr->numerTelefonu = nowyNumerTelefonu;
				break;
			}
		}
	}
	zapiszDoPliku(adresaci);
	cout << "Zmiany zostaly zapisane\n";
	system("pause");
}

void zmienEmail(vector<Adresat>& adresaci, int numerId) {
	string nowyEmail;
	cout << "Podaj nowy email: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, nowyEmail);

	for (int i = 0; i < adresaci.size(); i++) {
		for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
			if(itr->id == numerId) {
				itr->email = nowyEmail;
				break;
			}
		}
	}
	zapiszDoPliku(adresaci);
	cout << "Zmiany zostaly zapisane\n";
	system("pause");
}

void zmienAdres(vector<Adresat>& adresaci, int numerId) {
	string nowyAdres;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, nowyAdres);

	for (int i = 0; i < adresaci.size(); i++) {
		for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
			if (itr->id == numerId) {
				itr->adres = nowyAdres;
				break;
			}
		}
	}
	zapiszDoPliku(adresaci);
	cout << "Zmiany zostaly zapisane\n";
	system("pause");
}

void edytujAdresata(vector<Adresat>& adresaci) {
	char wybor;
	int IdAdresata;
	cout << "Podaj numer identyfikacyjny adresata, ktorego dane chcesz edytowac: ";
	cin >> IdAdresata;

	sprawdzCzyIstniejeAdresatOPodanymID(adresaci, IdAdresata);
	while (true) {
		system("cls");
		cout << "Podmenu edycji: \n";
		cout << "1 - imie\n";
		cout << "2 - nazwisko\n";
		cout << "3 - numer telefonu\n";
		cout << "4 - email\n";
		cout << "5 - adres\n";
		cout << "6 - powrot do menu\n";
		cout << "Wybierz pole, ktore chcesz edytowac: ";
		cin >> wybor;

		switch (wybor) {
		case '1':
			zmienImie(adresaci, IdAdresata);
			break;
		case '2':
			zmienNazwisko(adresaci, IdAdresata);
			break;
		case '3':
			zmienNumerTelefonu(adresaci, IdAdresata);
			break;
		case '4':
			zmienEmail(adresaci, IdAdresata);
			break;
		case '5':
			zmienAdres(adresaci, IdAdresata);
			break;
		case '6':
			return;
		}
	}

}