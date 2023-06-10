#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <time.h> // Added to seed the random number generator
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

void generateRandomLevel(char polje[n][n])
{
    // Seed the random number generator
    srand(time(0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Generate random obstacles and treasures
            int randomNum = rand() % 30; // Generates a random number between 0 and 9
            if (randomNum < 3)
                polje[i][j] = 'X'; // Obstacle
            else if (randomNum == 9)
                polje[i][j] = '*'; // Treasure
            else
                polje[i][j] = '-'; // Empty space

        }
    }
}

void savePoljeToFile(char polje[n][n])
{
    ofstream outputFile("polje.txt"); // Create an output file stream

    if (outputFile.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                outputFile << polje[i][j] << " ";
            }
            outputFile << endl;
        }

        outputFile.close();
        cout << "Polje je uspješno spremljeno u datoteku polje.txt" << endl;
    }
    else
    {
        cout << "Nije moguæe otvoriti datoteku za spremanje polja." << endl;
    }
}

void savePoljeToBinary(char polje[n][n])
{
    ofstream outputFile("polje.bin", ios::binary | ios::out); // Create an output file stream in binary mode

    if (outputFile.is_open())
    {
        for (int i = 0; i < n; i++)
        {
            outputFile.write(reinterpret_cast<char*>(polje[i]), n); // Write each row as a binary block
        }

        outputFile.close();
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
    ofstream datotekaIzlaz(datoteka, ios::app); // Otvori datoteku u naèinu dodavanja (append mode)

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

    // Generate a random level
    generateRandomLevel(polje);

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

    savePoljeToFile(polje); // Save the field to a file
    savePoljeToBinary(polje); //Save the field to a binary file

    return 0;
} 