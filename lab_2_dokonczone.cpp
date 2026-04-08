#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool czy_same_cyfry(string tekst)
{
    for (int i = 0; i < tekst.length(); i++) {
        if (!isdigit(tekst[i])) {
            return false;
        }
    }
    return true;
}

bool czy_same_litery(string tekst)
{
    for (int i = 0; i < tekst.length(); i++) {
        if (!isalpha(tekst[i])) {
            return false;
        }
    }
    return true;
}

class Osoba {
private:
    string imie;
    string nazwisko;
    string indeks;

public:
    bool ustaw_imie(string nowe_imie)
    {
        if (nowe_imie.length() < 3) {
            cout << "imie za krotkie\n";
            return false;
        }

        if (!czy_same_litery(nowe_imie)) {
            cout << "imie musi zawierac same litery\n";
            return false;
        }

        imie = nowe_imie;
        return true;
    }

    bool ustaw_nazwisko(string nowe_nazwisko)
    {
        if (nowe_nazwisko.length() < 3) {
            cout << "nazwisko za krotkie\n";
            return false;
        }

        if (!czy_same_litery(nowe_nazwisko)) {
            cout << "nazwisko musi zawierac same litery\n";
            return false;
        }

        nazwisko = nowe_nazwisko;
        return true;
    }

    bool ustaw_indeks(string nowy_indeks)
    {
        if (nowy_indeks.length() != 7) {
            cout << "indeks musi miec 7 cyfr\n";
            return false;
        }

        if (!czy_same_cyfry(nowy_indeks)) {
            cout << "indeks musi zawierac same cyfry\n";
            return false;
        }

        indeks = nowy_indeks;
        return true;
    }

    string pobierz_imie() {
        return imie;
    }

    string pobierz_nazwisko() {
        return nazwisko;
    }

    string pobierz_indeks() {
        return indeks;
    }

};

void dodaj_osoby(Osoba *tab, int liczba_osob, int *lista_o) {
    if (liczba_osob >= 10) {
        return;
    }
    string imie, nazwisko, indeks;

    cin >> imie >> nazwisko >> indeks;
    if (!tab[liczba_osob].ustaw_imie(imie)) return;
    if (!tab[liczba_osob].ustaw_nazwisko(nazwisko)) return;
    if (!tab[liczba_osob].ustaw_indeks(indeks)) return;

    lista_o[liczba_osob] = false; 
}

void usun_osoby(Osoba *tab, int liczba_osob,int *lista_o){
    string szukany_indeks;

    cin >> szukany_indeks;

    for (int i=0; i<liczba_osob; i++){

        if (tab[i].pobierz_indeks() == szukany_indeks){

            for (int j=i; j<liczba_osob-1; j++){
                tab[j] = tab[j+1];
            }
            for (int j=i; j<liczba_osob-1; j++){
                lista_o[j] = lista_o[j+1];
            }           
            return;
        }
    }
}

void ustaw_obecnosc(Osoba *tab, int liczba_osob, int *lista_o) {
    string indeks;

    cin >> indeks;

    for (int i = 0; i < liczba_osob; i++) {
        if (tab[i].pobierz_indeks() == indeks) {
            int czy_jest;
            cin >> czy_jest;

            lista_o[i] = czy_jest;
            return;
        }
    }

}

void wyswietl_liste(Osoba *tab, int liczba_osob, int *lista_o) {
    if (liczba_osob == 0) {
        cout << "lista jest pusta\n";
        return;
    }

    for (int i = 0; i < liczba_osob; i++) {
        cout << tab[i].pobierz_imie() << " "
             << tab[i].pobierz_nazwisko() << " "
             << tab[i].pobierz_indeks() << " - ";

        if (lista_o[i] == true) {
            cout << "obecny";
        } else {
            cout << "nieobecny";
        }

        cout << endl;
    }
}

int main() {
    Osoba lista[10];
    int lista_obecnosci[10];
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
                usun_osoby(lista,liczba_osob,lista_obecnosci);
                liczba_osob--;
                break;



            case 1:
                cout << "wybrales dodawanie osoby\n";
                cout << "podaj imie, naziwsko, numer indeksu\n";
                dodaj_osoby(lista, liczba_osob,lista_obecnosci);
                liczba_osob++;
                break;

            case 2:
                cout << "wybrales ustawianie obecnosci\n";
                cout << "podaj numer indeksu a potem obecnosc (0/1)\n";
                ustaw_obecnosc(lista, liczba_osob,lista_obecnosci);
                break;

            case 3:
                cout << "wybrales wyswietlanie listy\n";
                wyswietl_liste(lista, liczba_osob,lista_obecnosci);
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