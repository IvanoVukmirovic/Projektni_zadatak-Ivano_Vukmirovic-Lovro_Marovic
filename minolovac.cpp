#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;
struct Statistika
{
    int brojPobjeda;
    int brojPoraza;
    int brojPobjeda10;
    int brojPoraza10;
    int brojPobjeda20;
    int brojPoraza20;
    int brojPobjeda30;
    int brojPoraza30;
    int brojPobjeda50;
    int brojPoraza50;
    int brojPobjeda70;
    int brojPoraza70;
    int brojPobjeda100;
    int brojPoraza100;
};
Statistika statistika;                       // Instanca statistike
const char *statDatoteka = "statistika.dat"; // Put do datoteke za statistiku
void cls() { printf("\033[2J"
                    "\033[1;1H"); }
void resetirajStatistiku(Statistika &stat)
{
    stat.brojPobjeda = 0;
    stat.brojPoraza = 0;
    stat.brojPobjeda10 = 0;
    stat.brojPoraza10 = 0;
    stat.brojPobjeda20 = 0;
    stat.brojPoraza20 = 0;
    stat.brojPobjeda30 = 0;
    stat.brojPoraza30 = 0;
    stat.brojPobjeda50 = 0;
    stat.brojPoraza50 = 0;
    stat.brojPobjeda70 = 0;
    stat.brojPoraza70 = 0;
    stat.brojPobjeda100 = 0;
    stat.brojPoraza100 = 0;
}
void spremiStatistiku(const Statistika &stat, const char *datoteka)
{
    std::ofstream out(datoteka, std::ios::binary);
    if (out.is_open())
    {
        out.write(reinterpret_cast<const char *>(&stat), sizeof(stat));
        out.close();
    }
}

void ucitajStatistiku(Statistika &stat, const char *datoteka)
{
    std::ifstream in(datoteka, std::ios::binary);
    if (in.is_open())
    {
        in.read(reinterpret_cast<char *>(&stat), sizeof(stat));
        in.close();
    }
}
void ispisiStatistiku(const Statistika &stat, const char *datoteka)
{
    std::ofstream out(datoteka); // Otvaramo datoteku za pisanje

    if (!out.is_open())
    {
        std::cerr << "Nije moguće otvoriti datoteku za pisanje: " << datoteka << std::endl;
        return;
    }

    cout << "Statistika igre Minesweeper:" << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Broj pobjeda: " << stat.brojPobjeda << std::endl;
    cout << "Broj poraza: " << stat.brojPoraza << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Veličina polja 10x10:" << std::endl;
    cout << "Pobjede: " << stat.brojPobjeda10 << std::endl;
    cout << "Porazi: " << stat.brojPoraza10 << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Veličina polja 20x20:" << std::endl;
    cout << "Pobjede: " << stat.brojPobjeda20 << std::endl;
    cout << "Porazi: " << stat.brojPoraza20 << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Veličina polja 30x30:" << std::endl;
    cout << "Pobjede: " << stat.brojPobjeda30 << std::endl;
    cout << "Porazi: " << stat.brojPoraza30 << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Veličina polja 50x50:" << std::endl;
    cout << "Pobjede: " << stat.brojPobjeda50 << std::endl;
    cout << "Porazi: " << stat.brojPoraza50 << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Veličina polja 70x70:" << std::endl;
    cout << "Pobjede: " << stat.brojPobjeda70 << std::endl;
    cout << "Porazi: " << stat.brojPoraza70 << std::endl;
    cout << "---------------------------" << std::endl;
    cout << "Veličina polja 100x100:" << std::endl;
    cout << "Pobjede: " << stat.brojPobjeda100 << std::endl;
    cout << "Porazi: " << stat.brojPoraza100 << std::endl;

    out.close(); // Zatvaramo datoteku
}
void ucitajPoljeIzDatoteke(int **polje, int Vpolja, const char *dat)
{
    ifstream file(dat, ios::binary);
    if (!file.is_open())
    {
        cerr << "Unable to open file " << dat << endl;
        return;
    }

    for (int i = 0; i < Vpolja; ++i)
    {
        for (int j = 0; j < Vpolja; ++j)
        {
            file.read(reinterpret_cast<char *>(&polje[i][j]), sizeof(int));
        }
    }

    file.close();
}
// Funkcija za brojanje mina oko danog polja
int broj(int **polje, int i1, int j1, int Vpolja)
{
    int BrMina = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;
            int ni = i1 + x;
            int nj = j1 + y;
            if (ni >= 0 && ni < Vpolja && nj >= 0 && nj < Vpolja && polje[ni][nj] == 10)
            {
                BrMina++;
            }
        }
    }
    return BrMina;
}
void IspuniPolje(int **polje, int Vpolja, int numMines, int prvix, int prviy)
{
    // Inicijalizacija polja na 0
    for (int i = 0; i < Vpolja; i++)
    {
        for (int j = 0; j < Vpolja; j++)
        {
            polje[i][j] = 0;
        }
    }

    srand(time(0));
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            int ni = prvix + x;
            int nj = prviy + y;
            if (ni >= 0 && ni < Vpolja && nj >= 0 && nj < Vpolja)
            {
                polje[ni][nj] = 100;
            }
        }
    }
    for (int i = 0; i < numMines; i++)
    {
        int a = rand() % Vpolja;
        int b = rand() % Vpolja;
        if (polje[a][b] != 0)
        {
            i--;
        }
        else
        {
            polje[a][b] = 10;
        }
    }
    // Izračunavanje broja susjednih mina
    for (int i = 0; i < Vpolja; i++)
    {
        for (int j = 0; j < Vpolja; j++)
        {
            if (polje[i][j] == 10) // Ako je polje mina, preskočimo ga
                continue;

            int mineCount = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0)
                        continue;
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < Vpolja && nj >= 0 && nj < Vpolja && polje[ni][nj] == 10)
                    {
                        mineCount++;
                    }
                }
            }
            polje[i][j] = mineCount; // Postavljamo broj susjednih mina
        }
    }
}
void prikaziPolje(int **polje, int Vpolja)
{
    cls();
    cout << endl;
    /*for (int i = 0; i < Vpolja; i++)
    {
        cout << i << "\t";
    }*/
    cout << endl;
    for (int i = 0; i < Vpolja; i++)
    {
        for (int j = 0; j < Vpolja; j++)
        {
            if (polje[i][j] == 100)
            {
                cout << "⬛";
            }
            else if (polje[i][j] == 79)
            {
                cout << "🚩";
            }
            else if (polje[i][j] < 100)
            {
                cout << "⬜";
            }

            else if (polje[i][j] == 101)
            {
                cout << " 1";
            }
            else if (polje[i][j] == 102)
            {
                cout << " 2";
            }
            else if (polje[i][j] == 103)
            {
                cout << " 3";
            }
            else if (polje[i][j] == 104)
            {
                cout << " 4";
            }
            else if (polje[i][j] == 105)
            {
                cout << " 5";
            }
            else if (polje[i][j] == 106)
            {
                cout << " 6";
            }
            else if (polje[i][j] == 107)
            {
                cout << " 7";
            }
            else if (polje[i][j] == 108)
            {
                cout << " 8";
            }
            else if (polje[i][j] == 110)
            {
                cout << "💣";
            }
        }
        cout << endl;
    }
}
void rekurzija(int **polje, int x, int y, int rows, int cols)
{

    for (int p = x - 1; p <= x + 1; p++)
    {
        for (int l = y - 1; l <= y + 1; l++)
        {

            if (p >= 0 && p < rows && l >= 0 && l < cols && polje[p][l] == 0)
            {
                polje[p][l] += 100;
                if (p - 1 >= 0 && p - 1 < rows && l - 1 >= 0 && l - 1 < cols && (polje[p - 1][l - 1] > 0 && polje[p - 1][l - 1] < 10))
                {
                    polje[p - 1][l - 1] += 100;
                }
                if (p - 1 >= 0 && p - 1 < rows && l >= 0 && l < cols && (polje[p - 1][l] > 0 && polje[p - 1][l] < 10))
                {
                    polje[p - 1][l] += 100;
                }
                if (p - 1 >= 0 && p - 1 < rows && l + 1 >= 0 && l + 1 < cols && (polje[p - 1][l + 1] > 0 && polje[p - 1][l + 1] < 10))
                {
                    polje[p - 1][l + 1] += 100;
                }
                if (p >= 0 && p < rows && l - 1 >= 0 && l - 1 < cols && (polje[p][l - 1] > 0 && polje[p][l - 1] < 10))
                {
                    polje[p][l - 1] += 100;
                }
                if (p >= 0 && p < rows && l + 1 >= 0 && l + 1 < cols && (polje[p][l + 1] > 0 && polje[p][l + 1] < 10))
                {
                    polje[p][l + 1] += 100;
                }
                if (p + 1 >= 0 && p + 1 < rows && l - 1 >= 0 && l - 1 < cols && (polje[p + 1][l - 1] > 0 && polje[p + 1][l - 1] < 10))
                {
                    polje[p + 1][l - 1] += 100;
                }
                if (p + 1 >= 0 && p + 1 < rows && l >= 0 && l < cols && (polje[p + 1][l] > 0 && polje[p + 1][l] < 10))
                {
                    polje[p + 1][l] += 100;
                }
                if (p + 1 >= 0 && p + 1 < rows && l + 1 >= 0 && l + 1 < cols && (polje[p + 1][l + 1] > 0 && polje[p + 1][l + 1] < 10))
                {
                    polje[p + 1][l + 1] += 100;
                }
                rekurzija(polje, p, l, rows, cols);
            }
        }
    }
}
void spremiPoljeUDatoteku(int **polje, int Vpolja, const char *dat)
{
    ofstream file(dat, ios::out | ios::binary | ios::trunc);
    if (!file.is_open())
    {
        cerr << "Unable to open file " << dat << endl;
        return;
    }
    for (int i = 0; i < Vpolja; ++i)
    {
        file.write(reinterpret_cast<const char *>(polje[i]), Vpolja * sizeof(int));
    }
    file.close();
}

void igrapocinje(int **polje, int Vpolja)
{
    bool igraGotova = false;

    while (!igraGotova)
    {
        int zilip;
        cin >> zilip;

        // Pitanje korisniku da izabere između otkrivanja polja ili postavljanja zastavice
        cout << "Ukoliko želite piknut polje unesite 1, a ako želite postaviti zastavicu unesite 2." << endl;

        if (zilip == 505)
        {
            cout << "Odaberite želite li pristupiti save spot 1(unesite 1), 2(unesite 2), 3(unesite 3): ";
            int save = 0;
            cin >> save;

            const char *spremljena_polja = nullptr;
            if (Vpolja == 10)
            {
                if (save == 1)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja.dat";
                }
                else if (save == 2)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja2.dat";
                }
                else if (save == 3)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja3.dat";
                }
            }
            else if (Vpolja == 20)
            {
                if (save == 1)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja20X20no1.dat";
                }
                else if (save == 2)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja20X20no2.dat";
                }
                else if (save == 3)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja20X20no3.dat";
                }
            }
            else if (Vpolja == 30)
            {
                if (save == 1)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja30X30no1.txt";
                }
                else if (save == 2)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja30X30no2.txt";
                }
                else if (save == 3)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja30X30no3.txt";
                }
            }
            else if (Vpolja == 50)
            {
                if (save == 1)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja50X50no1.txt";
                }
                else if (save == 2)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja50X50no2.txt";
                }
                else if (save == 3)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja50X50no3.txt";
                }
            }
            else if (Vpolja == 70)
            {
                if (save == 1)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja70X70no1.txt";
                }
                else if (save == 2)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja70X70no2.txt";
                }
                else if (save == 3)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja70X70no3.txt";
                }
            }
            else if (Vpolja == 100)
            {
                if (save == 1)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja100X100no1.txt";
                }
                else if (save == 2)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja100X100no2.txt";
                }
                else if (save == 3)
                {
                    spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja100X100no3.txt";
                }
            }
            if (spremljena_polja != nullptr)
            {
                spremiPoljeUDatoteku(polje, Vpolja, spremljena_polja);
            }

            break;
        }

        // Provjera valjanosti unosa za izbor korisnika
        while (zilip != 1 && zilip != 2)
        {
            cout << "Unos nije valjan. Pokušajte ponovo: ";
            cin >> zilip;
        }

        int x = 0, y = 0;

        // Provjera valjanosti unosa za koordinate
        while (true)
        {
            cout << "Unesite koordinate polja koje želite odabrati (1-" << Vpolja << "): " << endl;
            cin >> x >> y;

            if (x >= 1 && x <= Vpolja && y >= 1 && y <= Vpolja)
            {
                break;
            }
            cout << "Neispravne koordinate. Pokušajte ponovo." << endl;
        }

        // Prilagodba koordinata na nulu
        x--;
        y--;

        if (zilip == 1)
        { // Ako je korisnik odabrao otkriti polje
            if (polje[x][y] == 0)
            {
                rekurzija(polje, x, y, Vpolja, Vpolja);
            }
            else if (polje[x][y] >= 100)
            {
                cout << "Polje je već odabrano, pokušajte ponovo." << endl;
            }
            else if (polje[x][y] == 10)
            {
                cout << "Pogodili ste minu, igra je gotova." << endl;
                statistika.brojPoraza++;
                if (Vpolja == 10)
                    statistika.brojPoraza10++;
                else if (Vpolja == 20)
                    statistika.brojPoraza20++;
                else if (Vpolja == 30)
                    statistika.brojPoraza30++;
                else if (Vpolja == 50)
                    statistika.brojPoraza50++;
                else if (Vpolja == 70)
                    statistika.brojPoraza70++;
                else if (Vpolja == 100)
                    statistika.brojPoraza100++;
                spremiStatistiku(statistika, statDatoteka);
                igraGotova = true;
            }
            else if (polje[x][y] == 69)
            {
                polje[x][y] -= 69;
                if (polje[x][y] == 10)
                {
                    cout << "Pogodili ste minu, igra je gotova." << endl;
                    igraGotova = true;
                }
                else
                {
                    polje[x][y] += 100;
                }
            }
            else if (polje[x][y] < 100)
            {
                polje[x][y] += 100;
            }
        }
        else if (zilip == 2)
        { // Ako je korisnik odabrao postaviti zastavicu
            polje[x][y] += 69;
        }

        prikaziPolje(polje, Vpolja);

        // Provjera je li igra dobivena
        bool igraDobivena = true;
        for (int i = 0; i < Vpolja; ++i)
        {
            for (int j = 0; j < Vpolja; ++j)
            {
                if (polje[i][j] < 100 && polje[i][j] == 10)
                {
                    igraDobivena = false;
                    break;
                }
            }
            if (!igraDobivena)
                break;
        }

        if (igraDobivena)
        {
            cout << "Čestitamo, pobijedili ste!" << endl;
            igraGotova = true;
            statistika.brojPobjeda++;
            if (Vpolja == 10)
                statistika.brojPobjeda10++;
            else if (Vpolja == 20)
                statistika.brojPobjeda20++;
            else if (Vpolja == 30)
                statistika.brojPobjeda30++;
            else if (Vpolja == 50)
                statistika.brojPobjeda50++;
            else if (Vpolja == 70)
                statistika.brojPobjeda70++;
            else if (Vpolja == 100)
                statistika.brojPobjeda100++;
            spremiStatistiku(statistika, statDatoteka);
        }
    }
}

int main()
{
    const char *statDatoteka = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/statistika.txt";
    ucitajStatistiku(statistika, statDatoteka);
    int p, kojsave;
    while (1)
    {

        cout << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬛⬛⬜⬛⬛⬜⬜⬛⬜⬜⬛⬛⬜⬛⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬛⬜⬛⬜⬛⬜⬜⬛⬜⬜⬛⬜⬛⬛⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬛⬛⬛⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬛⬛⬜⬜⬛⬛⬛⬜⬜⬛⬛⬛⬜⬜⬜⬛⬛⬛⬜⬜⬛⬛⬛⬜⬜" << endl
             << "⬜⬛⬜⬜⬜⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬜⬜⬜⬜⬛⬜⬜⬜⬜⬛⬜⬜⬛⬜⬜⬛⬜⬜⬜⬜⬛⬜⬜⬛⬜" << endl
             << "⬜⬜⬛⬛⬜⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬛⬜⬜⬜⬛⬛⬜⬜⬜⬛⬛⬛⬜⬜⬜⬛⬛⬜⬜⬜⬛⬛⬛⬜⬜" << endl
             << "⬜⬜⬜⬜⬛⬜⬜⬛⬜⬛⬜⬛⬜⬜⬛⬜⬜⬜⬜⬛⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬛⬜⬛⬜⬜" << endl
             << "⬜⬛⬛⬛⬜⬜⬜⬜⬛⬜⬛⬜⬜⬜⬛⬛⬛⬜⬜⬛⬛⬛⬜⬜⬛⬜⬜⬜⬜⬜⬛⬛⬛⬜⬜⬛⬜⬜⬛⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl
             << "⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜" << endl;
        cout << "DOBRODOŠLI U MINESWEEPER" << endl;
        int izbor = 0;
    start3:
    igragotova:
        cout << "za poretanje igre upišite 1" << endl
             << "za pravila igre upišite 2" << endl
             << "zakontrole upišite 3" << endl
             << "za izlazak upišite 4" << endl;
        cin >> izbor;
        if (izbor == 1)
        {
            int Vpolja;
            cout << "Odaberite veličinu polja koje koristiš:" << endl
                 << "1. 10x10" << endl
                 << "2. 20x20" << endl
                 << "3. 30x30" << endl
                 << "4. 50x50" << endl
                 << "5. 70x70" << endl
                 << "6. 100x100" << endl;
            cin >> izbor;
            switch (izbor)
            {
            case 1:
                Vpolja = 10;
                break;
            case 2:
                Vpolja = 20;
                break;
            case 3:
                Vpolja = 30;
                break;
            case 4:
                Vpolja = 50;
                break;
            case 5:
                Vpolja = 70;
                break;
            case 6:
                Vpolja = 100;
                break;
            default:
                cout << "Nevažeći izbor. Izlazim." << endl;
                return 1;
            }

            // Dinamički alociraj polje
            int **polje = new int *[Vpolja];
            for (int i = 0; i < Vpolja; i++)
            {
                polje[i] = new int[Vpolja];
            }
            cout << "želiš li nastaviti spremljenu igru(unesi 1) ili započeti novu(unesi 2)" << endl;
            cin >> p;
            cls;
            if (p == 1)
            {
                cout << "Koji save želite učitati: ";
                int savec;
                cin >> savec;

                const char *spremljena_polja = nullptr;
                if (Vpolja == 10)
                {
                    if (savec == 1)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja.dat";
                    else if (savec == 2)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja2.dat";
                    else if (savec == 3)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja3.dat";
                }
                else if (Vpolja == 20)
                {
                    if (savec == 1)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja20X20no1.dat";
                    else if (savec == 2)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja20X20no2.dat";
                    else if (savec == 3)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja20X20no3.dat";
                }
                else if (Vpolja == 30)
                {
                    if (savec == 1)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja30X30no1.txt";
                    else if (savec == 2)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja30X30no2.txt";
                    else if (savec == 3)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja30X30no3.txt";
                }
                else if (Vpolja == 50)
                {
                    if (savec == 1)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja50X50no1.txt";
                    else if (savec == 2)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja50X50no2.txt";
                    else if (savec == 3)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja50X50no3.txt";
                }
                else if (Vpolja == 70)
                {
                    if (savec == 1)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja70X70no1.txt";
                    else if (savec == 2)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja70X70no2.txt";
                    else if (savec == 3)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja70X70no3.txt";
                }
                else if (Vpolja == 100)
                {
                    if (savec == 1)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja100X100no1.txt";
                    else if (savec == 2)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja100X100no2.txt";
                    else if (savec == 3)
                        spremljena_polja = "C:\\Users\\Ivano\\Documents\\GitHub\\Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic\\spremljena_polja100X100no3.txt";
                }

                if (spremljena_polja != nullptr)
                {
                    ucitajPoljeIzDatoteke(polje, Vpolja, spremljena_polja);
                }
                else
                {
                    cout << "Neispravan unos za veličinu polja." << endl;
                }
            }
            if (p == 2)
            {
                int numMines = Vpolja * Vpolja / 7; // Broj mina je 1/7 polja
                int prvix = 0, prviy = 0;
                cout << "Unesite koordinate (x y) polja koje želite označiti da na njima sigurno neće biti mina pri kreirajnu polja: ";
                cin >> prvix >> prviy;
                prvix--;
                prviy--;
                if (prvix < 0 || prvix > Vpolja || prviy < 0 || prviy > Vpolja)
                {
                    cout << "Nevažeće koordinate. Izlazim." << endl;
                    return 1;
                }

                IspuniPolje(polje, Vpolja, numMines, prvix, prviy);
            }
            for (int i = 0; i < Vpolja; i++)
            {
                for (int j = 0; j < Vpolja; j++)
                {
                    cout << polje[i][j] << "\t";
                }
                cout << endl;
            }
            igrapocinje(polje, Vpolja);
            prikaziPolje(polje, Vpolja);
            // Očisti dinamički alociranu memoriju
            for (int i = 0; i < Vpolja; i++)
            {
                delete[] polje[i];
            }
            delete[] polje;
            goto igragotova;
        }
        else if (izbor == 2)
        {
            cout << "Minolovac, poznat kao Minesweeper na engleskom, je klasična logička video igra koja testira vašu sposobnost da indeficirate sigurna polja i izbjegnete mine u polju." << endl
                 << " Evo kratkog objašnjenja:" << endl
                 << endl
                 << " Mreža : Igra se odvija na mreži kvadrata, obično veličine 10x10, 20x20 ili većoj, zavisno o postavkama igre." << endl
                 << endl
                 << "Mine: Neki kvadrati u mreži skrivaju mine. Broj mina zavisi o veličini mreže." << endl
                 << endl
                 << "Otkriti polja: Igrač klikne na kvadrat da bi ga otkrio:" << endl
                 << endl
                 << "   2. Ako kvadrat ne sadrži minu, otkriva se broj koji označava koliko susednih kvadrata sadrži mine(može biti od 0 do 8)." << endl
                 << "   1. Ako kvadrat sadrži minu, igra se završava(igrač gubi)." << endl
                 << endl
                 << "Brojevi: Brojevi na otkrivenim kvadratima pomažu igraču da logički zaključi gde se mine nalaze. Na primer, ako kvadrat pokazuje broj  1 ," << endl
                 << " to znači da se jedna mina nalazi u susednih osam kvadrata." << endl
                 << endl
                 << "Označavanje mina: Igrač može desnim klikom miša označiti kvadrat zastavicom ako veruje da se tu nalazi mina. To pomaže da se ne otkriju slučajno ta polja." << endl
                 << endl;
            cout << "za povratak u izbormik unesite 1 a za izlazak unesite 2" << endl;
        start:
            cin >> izbor;
            if (izbor == 1)
            {
                goto start3;
            }
            else if (izbor == 2)
            {
                break;
            }
            else
            {
                cout << "vaš unos je neispravan pokušajte ponovo" << endl;
                goto start;
            }
            cls();
        }
        else if (izbor == 3)
        {
            cout << "prije početka igre označavate polje na kojem ne može biti mina" << endl
                 << "za vrijeme igre unesite 1 ako želite piknuti polje a ako želite postaviti zastavicu unesite 2" << endl
                 << "zatim unesite xy kordinate" << endl
                 << "ako u toku igre želite spremiti igru kad bi inače birali želite li piknuti polje ili postaviti zastavicu unesite 505" << endl;
        }
        else if (izbor == 4)
        {
            int sigotov;
            ispisiStatistiku(statistika, statDatoteka);
            cout << "unesite 1 kad ste završili s pregledom ili unesite 2 da resetirate statistiku." << endl;
            cin >> sigotov;
            if(sigotov==2){
            resetirajStatistiku(statistika);
            }
        }
        else if (izbor == 5)
        {
            break;
        }
        else
        {
            
            cout << "upisali ste nevaljani unos pokušajte ponovi" << endl;
            
        }
    }
    return 0;
}
