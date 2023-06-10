#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h> // dodano za rand funkciju
using namespace std;

const int n = 10;
int iPozicijaIgraca = 0;
int jPozicijaIgraca = 0;

int provjeraPoteza(int igracevPotez, char polje[n][n], int iPozicija, int jPozicija)
{
    if (polje[iPozicija][jPozicija] == 'X')
    {
        cout << "Nije se moguce pomaknuti na unesenu poziciju\n";
        return -1;
    }
    if (polje[iPozicija][jPozicija] == '*')
    {
        cout << "Izgubio si, hvala na igranju" << endl;
        return 0;
    }
    if (polje[iPozicija][jPozicija] == 'B')
    {
        cout << "Pobijedio si, hvala na igranju!" << endl;
        return 2;
    }
    return 1;
}

int provjeraPolja(int igracevPotez, char polje[n][n], int iPozicija, int jPozicija)
{
    if (iPozicija < 0 || iPozicija >= n || jPozicija < 0 || jPozicija >= n)
    {
        cout << "Nije se moguce pomaknuti na unesenu poziciju\n";
        return 0;
    }
    else if (polje[iPozicija][jPozicija] == 'X')
    {
        cout << "Nije se moguce pomaknuti na unesenu poziciju\n";
        return 0;
    }
    else if (polje[iPozicija][jPozicija] == '*')
    {
        cout << "Nije se moguce pomaknuti na unesenu poziciju\n";
        return 0;
    }
    else
    {
        return 1;
    }
}

void prikaziPolje(char polje[n][n])
{
    system("cls");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << polje[i][j] << " ";
        }
        cout << endl;
    }
}

int pomakniIgraca(int igracevPotez, char polje[n][n], int iPozicija, int jPozicija)
{
    int tempi = iPozicija;
    int tempj = jPozicija;
    int TRUE;

    if (igracevPotez == 8)
    {
        iPozicijaIgraca -= 1;
    }
    else if (igracevPotez == 2)
    {
        iPozicijaIgraca += 1;
    }
    else if (igracevPotez == 6)
    {
        jPozicijaIgraca += 1;
    }
    else if (igracevPotez == 4)
    {
        jPozicijaIgraca -= 1;
    }





    TRUE = provjeraPoteza(igracevPotez, polje, iPozicijaIgraca, jPozicijaIgraca);
    if (TRUE == 1 && provjeraPolja(igracevPotez, polje, iPozicijaIgraca, jPozicijaIgraca) == 1)
    {
        char temp = polje[tempi][tempj];
        polje[tempi][tempj] = polje[iPozicijaIgraca][jPozicijaIgraca];
        polje[iPozicijaIgraca][jPozicijaIgraca] = temp;

        return TRUE;
    }
    else
    {
        iPozicijaIgraca = iPozicija;
        jPozicijaIgraca = jPozicija;

        return TRUE;
    }
}

void Nasumicnarazina(char polje[n][n])
{
    // Funkcija za generiranje nasumicne razine
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Generiranje nasumicnih prepreka i blaga
            int randomNum = rand() % 30; // Generira nasumican broj izmedu 0 i 29
            if (randomNum < 3)
                polje[i][j] = 'X'; // Prepreka
            else if (randomNum == 9)
                polje[i][j] = '*'; // Blago
            else
                polje[i][j] = '-'; // Prazan prostor

        }
    }
}

void Tekstualnadatoteka(char polje[n][n])
{
    ofstream datoteka("polje.txt"); // Kreira tekstualnu datoteku

    if (datoteka.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                datoteka << polje[i][j] << " ";
            }
            datoteka << endl;
        }

        datoteka.close();
        cout << "Polje je uspješno spremljeno u datoteku polje.txt" << endl;
    }
    else
    {
        cout << "Nije moguæe otvoriti datoteku za spremanje polja." << endl;
    }
}

void Binarnadatoteka(char polje[n][n])
{
    ofstream datoteka1("polje.bin", ios::binary | ios::out); // Kreiraj binarnu datoteku

    if (datoteka1.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            datoteka1.write(reinterpret_cast<char*>(polje[i]), n); // Zapisuje svaki red binarno
        }

        datoteka1.close();
        cout << "Polje je uspješno spremljeno u datoteku polje.bin" << endl;
    }
    else
    {
        cout << "Nije moguæe otvoriti datoteku za spremanje polja." << endl;
    }
}

int main()
{
    cout << "Unesite svoje ime: ";
    string ime;
    getline(cin, ime);

    cout << "Unesite svoje prezime: ";
    string prezime;
    getline(cin, prezime);

    string datoteka = "ime_prezime.txt";
    ofstream datotekaIzlaz(datoteka, ios::app); // Otvori datoteku u naèinu dodavanja 

    if (datotekaIzlaz.is_open()) {
        datotekaIzlaz << "Ime: " << ime << endl;
        datotekaIzlaz << "Prezime: " << prezime << endl;

        datotekaIzlaz.close();
        cout << "Podaci su spremljeni u datoteku." << endl;
    }
    else {
        cout << "Nije moguæe otvoriti datoteku." << endl;
    }
    char polje[n][n];

    // Generira nasumicnu razinu
    Nasumicnarazina(polje);

    polje[iPozicijaIgraca][jPozicijaIgraca] = 'P';
    polje[9][9] = 'B';

    int igracevPotez;
    int ispravanPotez = 1;

    while (ispravanPotez != 0 && ispravanPotez != 2)
    {
        prikaziPolje(polje);
        cout << "Dobrodosli u nasu igru - Potraga za blagom" << endl;
        cout << "X-bomba, *-prepreka, B-blago, P-igrac" << endl;
        cout << "Cilj igre je doci do blaga" << endl;
        cout << "Unesite svoj potez (8 - gore, 2 - dolje, 4 - lijevo, 6 - desno): ";
        cin >> igracevPotez;

        ispravanPotez = pomakniIgraca(igracevPotez, polje, iPozicijaIgraca, jPozicijaIgraca);
    }

    Tekstualnadatoteka(polje); // Spremi polje u tekstualnu datoteku
    Binarnadatoteka(polje); //Spremi polje u binarnu datoteku

    return 0;
} 