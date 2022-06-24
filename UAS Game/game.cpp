
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

struct pembunuh
{
    string name;
    int damage;
    int hp;

    void attack(pembunuh *pembunuh)
    {
        if (pembunuh->hp <= 0)
        {
            cout << pembunuh->name << " telah dikalahkan, silahkan lanjutkan permainan!\n";
        }
        else
        {
            int hpFrom = pembunuh->hp;
            cout << "Kamu menyerang " << pembunuh->name << "! \n";
            pembunuh->hp = pembunuh->hp - damage;
            cout << "HP " << pembunuh->name << " berkurang dari " << hpFrom << " menjadi " << pembunuh->hp << "\n";
            cout << "Berhasil menghindar.\n\n";
        }
    }
};

void setcolor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hCon, color);
}

int main()
{
    // Game Kabur dari .............
    /*
    Pemain harus sampai ke titik finish tanpa terbunuh
    * = Karakter (Lokasi Pemain)
    0 = Finish   (Pemain bisa lewat)
    1 = Lantai   (Pemain bisa lewat)
    4 = Puing    (Pemain bisa lewat/daerah rawan)
    8 = Jembatan (Pemain bisa lewat/daerah rawan)
    5 = Batu     (Pemain tidak bisa lewat)
    6 = Lava     (Pemain tidak bisa lewat)
    7 = Dinding  (Pemain tidak bisa lewat)
    */

    pembunuh p1;
    p1.name = "giggity";
    p1.hp = 800;
    p1.damage = 184;

    pembunuh p2;
    p2.name = "sunaga";
    p2.hp = 984;
    p2.damage = 175;

    int panjangPeta = 20; // x
    int lebarPeta = 16;   // y

    int posisiKarakterY = 14;
    int posisiKarakterX = 19;
    int persenRuntuh;

    // Game rules
    cout << "Karakter ada di y:" << posisiKarakterY << ", x:" << posisiKarakterX << "\n";
    cout << "Peraturan permainan:\n";
    cout << "Pemain harus sampai ke titik finish tanpa terbunuh\n";
    cout << "* = Karakter (Lokasi Pemain)\n";
    cout << "0 = Finish   (Pemain bisa lewat)\n";
    cout << "1 = Lantai   (Pemain bisa lewat)\n";
    cout << "4 = Puing    (Pemain bisa lewat/daerah rawan)\n";
    cout << "8 = Jembatan (Pemain bisa lewat/daerah rawan)\n";
    cout << "5 = Batu     (Pemain tidak bisa lewat)\n";
    cout << "6 = Lava     (Pemain tidak bisa lewat)\n";
    cout << "7 = Dinding  (Pemain tidak bisa lewat)\n";

    int peta[lebarPeta][panjangPeta] = {
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {8, 8, 8, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 5, 5, 4, 1, 5, 5, 6},
        {8, 8, 8, 1, 1, 1, 4, 1, 8, 1, 1, 8, 1, 5, 5, 1, 1, 5, 5, 6},
        {5, 8, 8, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5, 5, 6, 6},
        {4, 8, 8, 8, 8, 8, 8, 1, 1, 4, 4, 1, 1, 1, 4, 4, 5, 6, 6, 6},
        {6, 8, 6, 8, 8, 8, 8, 5, 8, 4, 1, 1, 1, 4, 4, 4, 5, 6, 6, 6},
        {4, 4, 4, 4, 4, 1, 1, 1, 1, 8, 1, 1, 1, 4, 4, 5, 5, 5, 6, 6},
        {4, 4, 4, 5, 5, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 5, 5, 6, 6},
        {4, 4, 4, 5, 5, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 6, 6},
        {4, 4, 5, 5, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 5, 4, 6, 6},
        {4, 4, 5, 5, 1, 1, 1, 1, 4, 4, 4, 1, 1, 4, 4, 1, 5, 8, 6, 6},
        {5, 5, 5, 1, 1, 1, 1, 1, 4, 4, 4, 4, 6, 1, 1, 1, 1, 1, 6, 6},
        {5, 5, 4, 1, 1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 6, 1, 6, 6, 6, 6},
        {5, 5, 5, 5, 1, 1, 1, 1, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
    };

    int arrowKey = 0;

    /*
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define KEY_ESC 27
    */

    while (1)
    {
        persenRuntuh = rand() % 10; // mengacak kemungkinan pembunuh

        // Input Keyboard
        cout << "Masukan arrow key untuk bergerak \nESC untuk keluar\n";
        cout << "Masukan arrow key:\n";
        arrowKey = getch();
        cout << "Arrow key yang dimasukan: " << arrowKey << "\n";

        // Aturan menggerakkan karakter ke atas
        if (arrowKey == KEY_UP && (peta[posisiKarakterY - 1][posisiKarakterX] == 1 || peta[posisiKarakterY - 1][posisiKarakterX] == 4 || peta[posisiKarakterY - 1][posisiKarakterX] == 8 || peta[posisiKarakterY - 1][posisiKarakterX] == 0) && posisiKarakterY >= 0)
        {
            // Gerakkan karakter ke atas
            posisiKarakterY = posisiKarakterY - 1;
        }

        // Aturan menggerakkan karakter ke bawah
        else if (arrowKey == KEY_DOWN && (peta[posisiKarakterY + 1][posisiKarakterX] == 1 || peta[posisiKarakterY + 1][posisiKarakterX] == 4 || peta[posisiKarakterY + 1][posisiKarakterX] == 8 || peta[posisiKarakterY + 1][posisiKarakterX] == 0) && posisiKarakterY < lebarPeta)
        {
            // Gerakkan karakter ke bawah
            posisiKarakterY = posisiKarakterY + 1;
        }

        // Aturan menggerakkan karakter ke kiri
        else if (arrowKey == KEY_LEFT && (peta[posisiKarakterY][posisiKarakterX - 1] == 1 || peta[posisiKarakterY][posisiKarakterX - 1] == 4 || peta[posisiKarakterY][posisiKarakterX - 1] == 8 || peta[posisiKarakterY][posisiKarakterX - 1] == 0) && posisiKarakterX >= 0)
        {
            // Gerakkan karakter ke kiri
            posisiKarakterX = posisiKarakterX - 1;
        }

        // Aturan menggerakkan karakter ke kanan
        else if (arrowKey == KEY_RIGHT && (peta[posisiKarakterY][posisiKarakterX + 1] == 1 || peta[posisiKarakterY][posisiKarakterX + 1] == 4 || peta[posisiKarakterY][posisiKarakterX + 1] == 8 || peta[posisiKarakterY][posisiKarakterX + 1] == 0) && posisiKarakterX < panjangPeta)
        {
            // Gerakkan karakter ke kanan
            posisiKarakterX = posisiKarakterX + 1;
        }
        // Tombol Keluar
        else if (arrowKey == KEY_ESC)
        {
            cout << "Kamu telah keluar dari game!\n";
            break;
        }

        system("cls"); // clear screen agar layar tidak spam

        // Render grafik
        for (int y = 0; y < lebarPeta; y++)
        {
            for (int x = 0; x < panjangPeta; x++)
            {
                if (posisiKarakterX == x && posisiKarakterY == y)
                {
                    setcolor(3);
                    cout << '*' << " ";
                    setcolor(7);
                }
                else if (peta[y][x] == 1)
                {
                    setcolor(8);
                    cout << "_ ";
                    setcolor(7);
                }
                else if (peta[y][x] == 4)
                {
                    setcolor(5);
                    cout << "~ ";
                    setcolor(7);
                }
                else if (peta[y][x] == 5)
                {
                    setcolor(6);
                    cout << "^ ";
                    setcolor(7);
                }
                else if (peta[y][x] == 6)
                {
                    setcolor(4);
                    cout << "# ";
                    setcolor(7);
                }
                else if (peta[y][x] == 7)
                {
                    setcolor(9);
                    cout << "==";
                    setcolor(7);
                }
                else if (peta[y][x] == 8)
                {
                    setcolor(10);
                    cout << "| ";
                    setcolor(7);
                }
                else if (peta[y][x] == 0)
                {
                    setcolor(11);
                    cout << "! ";
                    setcolor(7);
                }
                else
                {
                    cout << peta[y][x] << " ";
                }
            }
            cout << "\n";
        }

        // Aturan ketika ada obstacles
        if (arrowKey == KEY_UP && (peta[posisiKarakterY - 1][posisiKarakterX] == 5 || peta[posisiKarakterY - 1][posisiKarakterX] == 6 || peta[posisiKarakterY - 1][posisiKarakterX] == 7) && posisiKarakterY >= 0)
        {
            cout << "Kamu tidak bisa lewat!\n";
        }
        else if (arrowKey == KEY_DOWN && (peta[posisiKarakterY + 1][posisiKarakterX] == 5 || peta[posisiKarakterY + 1][posisiKarakterX] == 6 || peta[posisiKarakterY + 1][posisiKarakterX] == 7) && posisiKarakterY < lebarPeta)
        {
            cout << "Kamu tidak bisa lewat!\n";
        }
        else if (arrowKey == KEY_LEFT && (peta[posisiKarakterY][posisiKarakterX - 1] == 5 || peta[posisiKarakterY][posisiKarakterX - 1] == 6 || peta[posisiKarakterY][posisiKarakterX - 1] == 7) && posisiKarakterX >= 0)
        {
            cout << "Kamu tidak bisa lewat!\n";
        }
        else if (arrowKey == KEY_RIGHT && (peta[posisiKarakterY][posisiKarakterX + 1] == 5 || peta[posisiKarakterY][posisiKarakterX + 1] == 6 || peta[posisiKarakterY][posisiKarakterX + 1] == 7) && posisiKarakterX < panjangPeta)
        {
            cout << "Kamu tidak bisa lewat!\n";
        }

        // Aturan garis finish
        if (peta[posisiKarakterY][posisiKarakterX] == 0)
        {
            cout << "Selamat!! \nKamu telah sampai ke garis Finish.\n"
                 << "Game Selesai\n";
            break;
        }
        // Aturan daerah rawan
        else if (peta[posisiKarakterY][posisiKarakterX] == 4 || peta[posisiKarakterY][posisiKarakterX] == 8)
        {
            cout << "Kamu berada di tempat rawan!\n";
            persenRuntuh = persenRuntuh * rand() % 10;
            if (persenRuntuh == 2) // Aturan Melawan Pembunuh
            {
                cout << "Kamu bertemu dengan Pembunuh!\n"
                     << "Bertarung melawan pembunuh.\n";
                p1.attack(&p1);
            }
            else if (persenRuntuh == 3) // Aturan Melawan Pembunuh
            {
                cout << "Kamu bertemu dengan Pembunuh!\n"
                     << "Bertarung melawan pembunuh.\n";
                p2.attack(&p2);
            }
            else if (persenRuntuh == 1) // Aturan Game Over
            {
                cout << "Kamu bertemu dengan Pembunuh!\n"
                     << "Tidak berhasil melawan pembunuh, kamu meninggal!\n";
                break;
            }
            persenRuntuh = 0;
        }
    }
    cout << "Keluar dari Game.\n";
    return 0;
}
