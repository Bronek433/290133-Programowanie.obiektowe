#include <iostream>
#include <string>
using namespace std;

class Osoba {
    private:
    string imie;
    string nazwisko;
    string indeks;
    bool obecnosc;

    public:
    //zastosowac metody zabezpieczające (setter, getter) bez obecnosci w class bo nie pasuje do przepisu na osobe 
    // obecnosci w osobnej tablicy 
    // list obecnosci w programie moze byc wiecej niz jedna ! przygotowac sie do tego w domu !

};

void dodaj_osoby(Osoba *tab, int liczba_osob) {
    if (liczba_osob >= 10) {
        return;
    }

    cin >> tab[liczba_osob].imie;

 
    cin >> tab[liczba_osob].nazwisko;


    cin >> tab[liczba_osob].indeks;

    tab[liczba_osob].obecnosc = false; 
}

void usun_osoby(Osoba *tab, int liczba_osob){
    string szukany_indeks;

    cin >> szukany_indeks;

    for (int i; i<10; i++){

        if (tab[i].indeks == szukany_indeks){

            for (int j=i; j<liczba_osob-1; j++){
                tab[j] = tab[j+1];
            }
            return;
        }
    }
}

void ustaw_obecnosc(Osoba *tab, int liczba_osob) {
    string indeks;

    cin >> indeks;

    for (int i = 0; i < liczba_osob; i++) {
        if (tab[i].indeks == indeks) {
            int czy_jest;
            cin >> czy_jest;

            tab[i].obecnosc = czy_jest;
            return;
        }
    }

}

void wyswietl_liste(Osoba *tab, int liczba_osob) {
    if (liczba_osob == 0) {
        cout << "lista jest pusta\n";
        return;
    }

    for (int i = 0; i < liczba_osob; i++) {
        cout << tab[i].imie << " "
             << tab[i].nazwisko << " "
             << tab[i].indeks << " - ";

        if (tab[i].obecnosc == true) {
            cout << "obecny";
        } else {
            cout << "nieobecny";
        }

        cout << endl;
    }
}

int main() {
    Osoba lista[10];
    int liczba_osob = 0;
    int wybor;

    do {
        cout << "\nco chcesz zrobic?\n";
        cout << "0 - usun osobe\n";
        cout << "1 - dodaj osobe\n";
        cout << "2 - ustaw obecnosc\n";
        cout << "3 - wyswietl liste\n";
        cout << "4 - zakoncz dzialania\n";

        cin >> wybor;

        switch (wybor) {
            case 0:
                cout << "wybrales usuwanie osoby\n";
                cout << "podaj numer indeksu ktory chcesz usunac\n";
                usun_osoby(lista,liczba_osob);
                liczba_osob--;
                break;



            case 1:
                cout << "wybrales dodawanie osoby\n";
                cout << "podaj imie, naziwsko, numer indeksu\n";
                dodaj_osoby(lista, liczba_osob);
                liczba_osob++;
                break;

            case 2:
                cout << "wybrales ustawianie obecnosci\n";
                cout << "podaj numer indeksu a potem obecnosc (0/1)\n";
                ustaw_obecnosc(lista, liczba_osob);
                break;

            case 3:
                cout << "wybrales wyswietlanie listy\n";
                wyswietl_liste(lista, liczba_osob);
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