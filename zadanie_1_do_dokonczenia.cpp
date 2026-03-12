#include <iostream>
#include <string>
using namespace std;

void dodaj_osoby(string *tab1, int &liczba_osob) {
    if (liczba_osob >= 10) {
        return;
    }

    cout << "podaj nazwisko\n";
    cin >> tab1[liczba_osob];
    liczba_osob++;
}

void ustaw_obecnosc(string *tab1, bool *tab2, string nazwisko, bool obecnosc, int liczba_osob) {
    for (int i = 0; i < liczba_osob; i++) {
        if (tab1[i] == nazwisko) {
            tab2[i] = obecnosc;
            return;
        }
    }
    for (int i = 0; i < liczba_osob; i++){
        cout<<tab1[i]<<tab2[i];
    }
}

void wyswietl_liste(string *tab1, bool *tab2, int liczba_osob) {
    for (int i = 0; i < liczba_osob; i++) {
        cout << tab1[i] << " ";

        if (tab2[i] == true) {
            cout << "obecny";
        } else {
            cout << "nieobecny";
        }

        cout << endl;
    }
}

int main() {
    string tabNazwiska[10];
    int liczba_osob = 0;
    bool tabobecnosc[10] = {false};   
    string second_name;
    bool czy_jest;
    int wybor;

    do {
        cout << "\nco chcesz zrobic?\n";
        cout << "1 - dodaj osoby\n";
        cout << "2 - ustaw obecnosc\n";
        cout << "3 - wyswietl liste\n";
        cout << "4 - zakoncz dzialania\n";

        cin >> wybor;

        switch (wybor) {
            case 1:
                cout << "wybrales dodawanie osob\n";
                dodaj_osoby(tabNazwiska, liczba_osob);
                break;

            case 2:
                cout << "wybrales ustawianie obecnosci\n";
                cout << "podaj nazwisko\n";
                cin >> second_name;

                cout << "podaj obecnosc (0/1): ";
                cin >> czy_jest;

                ustaw_obecnosc(tabNazwiska, tabobecnosc, second_name, czy_jest, liczba_osob);
                break;

            case 3:
                cout << "wybrales wyswietlanie listy\n";
                wyswietl_liste(tabNazwiska, tabobecnosc, liczba_osob);
                break;

            case 4:
                cout << "koniec programu\n";
                break;

            default:
                cout << "niepoprawny wybor\n";
        }

    } while (wybor != 4);

    return 0;
}