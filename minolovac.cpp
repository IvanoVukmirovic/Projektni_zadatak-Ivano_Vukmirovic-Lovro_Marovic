#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;
struct str_account
{
    char username[20];
    int ID;
    char lozinka[20];
};
void cls() { printf("\033[2J"
                    "\033[1;1H"); }
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
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (polje[i][j] == 10 && polje[i][j] < 100)
            {
                continue;
            }
            int mineCount = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0)
                        continue;
                    int ni = i + x;
                    int nj = j + y;
                    if (ni >= 0 && ni < 10 && nj >= 0 && nj < 10 && polje[ni][nj] == 10)
                    {
                        mineCount++;
                    }
                }
            }
            polje[i][j] = mineCount;
        }
    }
}
void prikaziPolje(int **polje, int Vpolja)
{
    cls();
    cout << endl;
    for (int i = 0; i < Vpolja; i++)
    {
        for (int j = 0; j < Vpolja; j++)
        {
            if (polje[i][j] == 100)
            {
                cout << "⬛";
            }
            else if (polje[i][j] == 69)
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
void spremiPoljeUDatoteku(int **polje, int Vpolja, const char *dat, int ID)
{
    ofstream ofs;
    ofs.open(dat, ofstream::out | ofstream::trunc);
    ofs.close();
    ofstream file(dat, ios::app);
    if (!file.is_open())
    {
        cerr << "Unable to open file " << dat << endl;
        return;
    }
    for (int i = 0; i < Vpolja; ++i)
    {
        for (int j = 0; j < Vpolja; ++j)
        {
            file << polje[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}
void igrapocinje(int **polje, int Vpolja, int ID)
{
    while (true)
    {
        cout << "ukoliko želiute piknut polje unesite 1, a ako želite postaviti zastavicu unesite 2." << endl;
    start2:
        int zilip;
        cin >> zilip;
        if (zilip == 505)
        {
            cout << "odaberite želite li lpristiti save spot 1(unesite 1), 2(unesite 2), 3(unesite 3)";
            int save = 0;
            cin >> save;
            if (save == 1)
            {
                const char *spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja.txt";
                spremiPoljeUDatoteku(polje, Vpolja, spremljena_polja, ID);
            }
            if (save == 2)
            {
                const char *spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja2.txt";
                spremiPoljeUDatoteku(polje, Vpolja, spremljena_polja, ID);
            }
            if (save == 3)
            {
                const char *spremljena_polja = "C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja3.txt";
                spremiPoljeUDatoteku(polje, Vpolja, spremljena_polja, ID);
            }
            break;
        }
        if (zilip != 1 && zilip != 2)
        {
            cout << "unos nije valjan pokušajte ponovo" << endl;
            goto start2;
        }
        int x = 0, y = 0;
    start1:
        cout << "Unesite kordinate polja koje želite odabrati (1-" << Vpolja << "): " << endl;
        cin >> x >> y;

        if (x < 1 || x > Vpolja || y < 1 || y > Vpolja)
        {
            cout << "Neispravne koordinate. Pokušajte ponovo." << endl;
            goto start1;
        }

        x--;
        y--;
        if (zilip == 1)
        {
            if (polje[x][y] == 0)
            {
                rekurzija(polje, x, y, Vpolja, Vpolja);
            }
            else if (polje[x][y] >= 100)
            {
                cout << "Polje je već odabrano, pokušajte ponovo." << endl;
                goto start1;
            }
            else if (polje[x][y] == 10)
            {
                cout << "Pogodili ste minu, igra je gotova." << endl;
                break;
            }
            else if (polje[x][y] == 69)
            {
                polje[x][y] -= 69;
                if (polje[x][y] == 10)
                {
                    cout << "Pogodili ste minu, igra je gotova." << endl;
                    break;
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
        if (zilip == 2)
        {
            polje[x][y] += 69;
        }
        prikaziPolje(polje, Vpolja);
        int figragotova=1;
        for(int ij=0; ij<Vpolja; ij++){
            for(int j=0; j<Vpolja; j++){
                if(polje[ij][j]<100||polje[ij][j]==10){
                }
                else{
                    figragotova=0;
                }
            }
        }
        if(figragotova==0){
            break;
        }
    }
}

int main()
{
    vector<vector<int>> poljasce;
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
        cout << "DOBRODOŠLI U MINESWEEPER" << endl
             << "Ukoliko želite li kreirati novi račun unesite 1,ako se želite ulogirati u več postojeći račun unesite 2.";
        int acc;
        cin >> acc;
        char username[50], lozinka[50];
        int ID;
        if (acc == 1)
        {
            str_account racun;

            memset(&racun, 0, sizeof(racun));

            ofstream account;
            account.open("C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/account.dat", ios::binary | ios::app);

            if (!account)
            {
                cerr << "Error opening file for writing." << endl;
                return 1;
            }

            cout << "Unesite korisničko ime." << endl;
            cin >> racun.username;
            strcpy(username, racun.username);

            cout << "Unesite ID (niz 5 brojeva od 0 do 9)" << endl;
            cin >> racun.ID;
            ID = racun.ID;

            cout << "Unesite lozinku." << endl;
            cin >> racun.lozinka;
            strcpy(username, racun.username);

            account.write((char *)&racun, sizeof(racun));
            if (!account)
            {
                cerr << "Error writing to file." << endl;
                return 1;
            }

            account.close();
            cout << "Račun je uspješno kreiran!" << endl;
        }

        else if (acc == 2)
        {
            ifstream account("C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/account.dat", ios::binary);
            if (!account)
            {
                cerr << "Error opening file for reading." << endl;
                return 1;
            }

            cout << "Unesite korisničko ime:" << endl;
            cin >> username;

            cout << "Unesite ID (niz 5 brojeva od 0 do 9):" << endl;
            cin >> ID;

            cout << "Unesite lozinku:" << endl;
            cin >> lozinka;

            str_account racun;
            bool found = false;
            while (account.read(reinterpret_cast<char *>(&racun), sizeof(racun)))
            {
                if (strcmp(username, racun.username) == 0 && ID == racun.ID && strcmp(lozinka, racun.lozinka) == 0)
                {
                    found = true;
                    cout << "Uspješno ste prijavljeni!" << endl;
                    cout << "Korisničko ime: " << racun.username << endl;
                    cout << "ID: " << racun.ID << endl;
                    cout << "Lozinka: " << racun.lozinka << endl;
                    break;
                }
            }

            if (!found)
            {
                cout << "Pogrešno korisničko ime, ID ili lozinka." << endl;
            }

            account.close();
            cout << "želite li nastaviti već postojeću igru (unesiste 1) ili ne (unesite 2)" << endl;
            cin >> p;
            if (p == 1)
            {
                cout << "želite li učitati save1(unesite 1) save2(unesite 2) ili save3(unesite 3)" << endl;
                cin >> kojsave;
                if (kojsave == 1)
                {
                    ifstream ulaznaDatoteka("C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja.txt");
                    if (!ulaznaDatoteka.is_open())
                    {
                        cerr << "Nije moguće otvoriti datoteku!" << endl;
                        return 1;
                    }

                    string linija;
                    while (getline(ulaznaDatoteka, linija))
                    {
                        vector<int> red;
                        stringstream ss(linija);
                        int broj;
                        while (ss >> broj)
                        {
                            red.push_back(broj);
                        }
                        poljasce.push_back(red);
                    }
                    ulaznaDatoteka.close();
                }
                if (kojsave == 2)
                {
                    ifstream ulaznaDatoteka("C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja2.txt");
                    if (!ulaznaDatoteka.is_open())
                
                    {
                        cerr << "Nije moguće otvoriti datoteku!" << endl;
                        return 1;
                    }

                    string linija;
                    while (getline(ulaznaDatoteka, linija))
                    {
                        vector<int> red;
                        stringstream ss(linija);
                        int broj;
                        while (ss >> broj)
                        {
                            red.push_back(broj);
                        }
                        poljasce.push_back(red);
                    }
                    ulaznaDatoteka.close();
                }
                if (kojsave == 3)
                {
                    ifstream ulaznaDatoteka("C:\\Users/Ivano/Documents/GitHub/Projektni_zadatak-Ivano_Vukmirovic-Lovro_Marovic/spremljena_polja3.txt");
                    if (!ulaznaDatoteka.is_open())
                    {
                        cerr << "Nije moguće otvoriti datoteku!" << endl;
                        return 1;
                    }

                    string linija;
                    while (getline(ulaznaDatoteka, linija))
                    {
                        vector<int> red;
                        stringstream ss(linija);
                        int broj;
                        while (ss >> broj)
                        {
                            red.push_back(broj);
                        }
                        poljasce.push_back(red);
                    }
                    ulaznaDatoteka.close();
                }
            }
        }
        else if (acc == 3)
        {
        }
        int izbor = 0;
    start3:
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
                 << "6. 100x100" << endl
                 << "7. Prilagođena veličina" << endl;

            int izbor;
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
            case 7:
                cout << "Unesite prilagođenu veličinu: ";
                cin >> Vpolja;
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

            for (int i = 0; i < Vpolja; i++)
            {
                for (int j = 0; j < Vpolja; j++)
                {
                    polje[i][j] = poljasce[i][j];
                }
            }
            int prvix=0, prviy=0;
            int numMines = Vpolja * Vpolja / 7; // Broj mina je 1/7 polja
            if (p != 1)
            {
                cout << "Unesite koordinate (x y) polja koje želite označiti da na njima sigurno neće biti mina pri kreirajnu polja: ";
                cin >> prvix >> prviy;
                prvix--;
                prviy--;
                if (prvix < 0 || prvix > Vpolja || prviy < 0 || prviy > Vpolja)
                {
                    cout << "Nevažeće koordinate. Izlazim." << endl;
                    return 1;
                }
            }
                IspuniPolje(polje, Vpolja, numMines, prvix, prviy);
            
            for (int i = 0; i < Vpolja; i++)
            {
                for (int j = 0; j < Vpolja; j++)
                {
                    cout << polje[i][j] << "\t";
                }
                cout << endl;
            }
            igrapocinje(polje, Vpolja, ID);
            prikaziPolje(polje, Vpolja);
            // Očisti dinamički alociranu memoriju
            for (int i = 0; i < Vpolja; i++)
            {
                delete[] polje[i];
            }
            delete[] polje;
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
            break;
        }
        else
        {
            cout << "upisali ste nevaljani unos pokušajte ponovi" << endl;
        }
    }
    return 0;
}
