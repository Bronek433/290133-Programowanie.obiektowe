#include <iostream>
#include <string>
#include <cctype>

using namespace std;


bool czy_same_cyfry(string tekst) {
    for (char c : tekst) if (!isdigit(c)) return false;
    return (tekst.length() > 0);
}

bool czy_same_litery(string tekst) {
    for (char c : tekst) if (!isalpha(c)) return false;
    return (tekst.length() > 0);
}


class Osoba {
protected:
    string imie;
    string nazwisko;
public:
    virtual ~Osoba() {}
    

    virtual int pobierz_id() = 0;
    virtual bool ustaw_dane(string i, string n, int id) = 0;
    virtual void drukuj() = 0;
    
    string pobierz_imie() { return imie; }
    string pobierz_nazwisko() { return nazwisko; }
};


class Student : public Osoba {
private:
    int nr_indeksu;
public:
    int pobierz_id() override { return nr_indeksu; }
    
    bool ustaw_dane(string i, string n, int id) override {
        if (i.length() < 3 || !czy_same_litery(i)) return false;
        if (n.length() < 3 || !czy_same_litery(n)) return false;
        if (id < 1000000 || id > 9999999) return false;
        imie = i; nazwisko = n; nr_indeksu = id;
        return true;
    }

    void drukuj() override {
        cout << "[STUDENT] " << imie << " " << nazwisko << " (Index: " << nr_indeksu << ")";
    }
};


class Stazysta : public Osoba {
private:
    int id_pracownika;
public:
    int pobierz_id() override { return id_pracownika; }
    
    bool ustaw_dane(string i, string n, int id) override {
        if (i.length() < 3 || !czy_same_litery(i)) return false;
        if (n.length() < 3 || !czy_same_litery(n)) return false;
        if (id < 1000 || id > 9999) return false; 
        imie = i; nazwisko = n; id_pracownika = id;
        return true;
    }

    void drukuj() override {
        cout << "[STAZYSTA] " << imie << " " << nazwisko << " (ID: " << id_pracownika << ")";
    }
};

class ListaObecnosci {
private:
    Osoba **tabOsob;
    bool *czyObecny;
    int iloscOsob;
    int maxOsob;

public:
    ListaObecnosci() : iloscOsob(0), maxOsob(10) {
        tabOsob = new Osoba*[maxOsob];
        czyObecny = new bool[maxOsob];
    }

    void dodajOsobe(Osoba *os) {
        if (iloscOsob < maxOsob) {
            tabOsob[iloscOsob] = os;
            czyObecny[iloscOsob] = false;
            iloscOsob++;
        }
    }

    void ustawObecnosc(int id, bool stan) {
        for (int i = 0; i < iloscOsob; i++) {
            if (tabOsob[i]->pobierz_id() == id) {
                czyObecny[i] = stan;
                return;
            }
        }
    }

    void drukujListe() {
        if (iloscOsob == 0) { cout << "Lista pusta.\n"; return; }
        for (int i = 0; i < iloscOsob; i++) {
            tabOsob[i]->drukuj();
            cout << " - " << (czyObecny[i] ? "OBECNY" : "nieobecny") << endl;
        }
    }
};


class InterfejsUzytkownika {
private:
    Osoba **bazaOsob;
    int &licznikOsob;
    ListaObecnosci *tablicaList;

    void dodajOsobeDoBazy() {
        int typ;
        cout << "1. Student | 2. Stazysta: "; cin >> typ;
        string i, n; int id;
        cout << "Podaj imie, nazwisko i ID (Student=7cyfr, Stazysta=4cyfry): ";
        cin >> i >> n >> id;

        if (typ == 1) bazaOsob[licznikOsob] = new Student();
        else bazaOsob[licznikOsob] = new Stazysta();

        if (bazaOsob[licznikOsob]->ustaw_dane(i, n, id)) {
            licznikOsob++;
            cout << "Dodano do bazy.\n";
        } else {
            cout << "Bledne dane!\n";
            delete bazaOsob[licznikOsob];
        }
    }

    void dodajOsobeDoListy() {
        int nrId, nrListy;
        cout << "Nr listy (0-1) i ID osoby: "; cin >> nrListy >> nrId;
        for (int i = 0; i < licznikOsob; i++) {
            if (bazaOsob[i]->pobierz_id() == nrId) {
                tablicaList[nrListy].dodajOsobe(bazaOsob[i]);
                cout << "Dodano.\n";
                return;
            }
        }
        cout << "Nie znaleziono osoby o takim ID!\n";
    }

public:
    InterfejsUzytkownika(Osoba **tO, int &lO, ListaObecnosci *tL)
        : bazaOsob(tO), licznikOsob(lO), tablicaList(tL) {}

    void loop() {
        int wybor;
        do {
            cout << "\n--- MENU ---\n1.Dodaj osobe do bazy\n2.Wyswietl liste\n3.Dodaj osobe do listy\n4.Ustaw obecnosc\n5.Koniec\nWybor: ";
            cin >> wybor;
            switch (wybor) {
                case 1: dodajOsobeDoBazy(); break;
                case 2: {
                    int n; cout << "Nr listy (0-1): "; cin >> n;
                    tablicaList[n].drukujListe(); break;
                }
                case 3: dodajOsobeDoListy(); break;
                case 4: {
                    int n, id, st; cout << "Nr listy, ID osoby i stan (1/0): "; cin >> n >> id >> st;
                    tablicaList[n].ustawObecnosc(id, st); break;
                }
            }
        } while (wybor != 5);
    }
};

int main() {
    Osoba *tablicaOsob[10];
    int aktualnaIloscOsob = 0;
    ListaObecnosci tablicaList[2];

    InterfejsUzytkownika ui(tablicaOsob, aktualnaIloscOsob, tablicaList);
    ui.loop();

    for(int i=0; i<aktualnaIloscOsob; i++) delete tablicaOsob[i];
    
    return 0;
}