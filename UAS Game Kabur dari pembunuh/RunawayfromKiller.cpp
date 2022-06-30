/*
UAS Praktikum Algoritma dan Pemrograman
Nama : Handal Khomsyat
NIM  : 1217050061
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <fstream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27
#define ENTER 13

struct player // structure karakter pemain
{
    int attack;
    int hp;
};

struct killer // structure pembunuh
{
    string name;
    int attack;
    int hp;
    void atkKiller(player *player) // fungsi killer attack player
    {
        int hpFrom = player->hp;
        cout << "Kamu diserang! \n";
        player->hp -= attack;
        cout << "HP Kamu berkurang dari " << hpFrom << " menjadi " << player->hp << "\n";
    }
};

// Prototyoe fungsi
void printASCII(string filename);               // print ASCII art
void setcolor(unsigned short color);            // mewarnai map
void renderGrafik();                            // render grafik
void gameRules();                               // menampilkan peraturan game
void obsRules();                                // aturan obstacles
void inputKey();                                // menerima input keyboard
void moveKey();                                 // aturan pergerakan karakter
void gameOver();                                // aturan gameover
void atkPlayer(killer *killer, player *player); // player attack killer
void meet(killer *killer, player *player);      // aturan bertemu killer

// deklarasi map
int arrowKey = 0;
int longMap = 20;  // x
int widthMap = 16; // y
int charPosY = 14;
int charPosX = 19;
int map[16][20] = {
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
    {6, 6, 6, 6, 5, 1, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {6, 6, 6, 5, 5, 8, 1, 1, 1, 1, 1, 1, 1, 5, 5, 4, 1, 5, 5, 6},
    {6, 6, 5, 5, 4, 8, 4, 1, 8, 1, 1, 8, 1, 5, 5, 1, 1, 5, 5, 6},
    {6, 5, 4, 4, 1, 8, 4, 1, 1, 1, 1, 1, 1, 1, 1, 4, 5, 5, 6, 6},
    {4, 8, 8, 8, 8, 8, 8, 1, 1, 4, 4, 1, 1, 1, 4, 4, 5, 6, 6, 6},
    {4, 4, 4, 4, 4, 8, 4, 5, 8, 4, 1, 1, 5, 4, 4, 4, 5, 6, 6, 6},
    {4, 6, 6, 4, 4, 1, 1, 1, 1, 8, 1, 1, 8, 4, 4, 5, 5, 5, 6, 6},
    {6, 6, 4, 5, 4, 1, 1, 1, 1, 1, 4, 4, 8, 4, 4, 4, 5, 5, 6, 6},
    {4, 4, 4, 5, 5, 8, 1, 1, 4, 4, 4, 4, 8, 8, 8, 4, 1, 1, 6, 6},
    {4, 4, 5, 5, 8, 8, 8, 8, 4, 4, 4, 4, 4, 4, 8, 4, 5, 8, 6, 6},
    {4, 4, 5, 5, 1, 8, 1, 1, 4, 4, 4, 1, 1, 4, 8, 1, 5, 8, 6, 6},
    {4, 5, 5, 1, 1, 1, 1, 1, 4, 4, 4, 4, 6, 1, 1, 1, 1, 1, 6, 6},
    {5, 5, 5, 5, 1, 1, 1, 1, 6, 4, 1, 1, 1, 1, 6, 1, 6, 6, 6, 6},
    {5, 5, 5, 5, 5, 1, 1, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
};

// utama
int main()
{
    // define struct player
    player p1;
    p1.hp = 1700;
    p1.attack = 165;

    // define struct killer 1
    killer k1;
    k1.name = "giggity";
    k1.hp = 800;
    k1.attack = 184;

    // define struct killer 2
    killer k2;
    k2.name = "sunaga";
    k2.hp = 984;
    k2.attack = 175;

    int chance; // var peluang

    // print ASCII art
    string fileName = "home.txt";
    printASCII(fileName);
    cout << "Tekan apa saja untuk memulai!\n";
    getch();
    system("cls");

    // Game rules
    cout << "Karakter ada di y:" << charPosY << ", x:" << charPosX << "\n";
    gameRules();

    int choice = 0;

    while (1)
    {
        chance = rand() % 10; // mengacak kemungkinan killer

        // Input Keyboard
        inputKey();

        // Aturan Move
        moveKey();

        // Tombol Keluar
        if (arrowKey == ESC)
        {
            cout << "Kamu telah keluar dari game!\n";
            break;
        }

        system("cls"); // clear screen agar layar tidak spam

        // cek apakah karakter masih hidup
        if (p1.hp <= 0)
        {
            gameOver();
            break;
        }

        // Render grafik
        renderGrafik();

        // Aturan ketika ada obstacles
        obsRules();

        // Aturan garis finish
        if (map[charPosY][charPosX] == 0)
        {
            cout << "Selamat!! \nKamu telah sampai ke garis Finish.\n"
                 << "Game Selesai\n";
            break;
        }
        // Aturan daerah rawan
        else if (map[charPosY][charPosX] == 4 || map[charPosY][charPosX] == 8)
        {
            cout << "Kamu berada di tempat rawan!\n";
            chance *= rand() % 10;
            if (chance == 2) // Aturan Melawan killer
            {
                k1.atkKiller(&p1);
                meet(&k1, &p1);
            }
            else if (chance == 4) // Aturan Melawan killer
            {
                k2.atkKiller(&p1);
                meet(&k2, &p1);
            }
            else if (chance == 1 || chance == 0) // Aturan Game Over
            {
                cout << "Kamu diserang Pembunuh!\n"
                     << "CRITICAL DAMAGE! ";
                gameOver();
                break;
            }
        }
    }
    cout << "Keluar dari Game.\n"; // program ditutup
    return 0;
}

// isian fungsi
void printASCII(string filename)
{
    string line = "";
    ifstream inFile;
    inFile.open("home.txt");
    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "File gagal dibuka \n";
        cout << "Tidak ada ASCII Art yang ditampilkan\n";
    }
    inFile.close();
}

void setcolor(unsigned short color)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hCon, color);
}

void renderGrafik()
{
    for (int y = 0; y < widthMap; y++)
    {
        for (int x = 0; x < longMap; x++)
        {
            if (charPosX == x && charPosY == y)
            {
                setcolor(3);
                cout << '*' << " ";
                setcolor(7);
            }
            else if (map[y][x] == 1)
            {
                setcolor(8);
                cout << "_ ";
                setcolor(7);
            }
            else if (map[y][x] == 4)
            {
                setcolor(5);
                cout << "~ ";
                setcolor(7);
            }
            else if (map[y][x] == 5)
            {
                setcolor(6);
                cout << "^ ";
                setcolor(7);
            }
            else if (map[y][x] == 6)
            {
                setcolor(4);
                cout << "# ";
                setcolor(7);
            }
            else if (map[y][x] == 7)
            {
                setcolor(9);
                cout << "==";
                setcolor(7);
            }
            else if (map[y][x] == 8)
            {
                setcolor(10);
                cout << "| ";
                setcolor(7);
            }
            else if (map[y][x] == 0)
            {
                setcolor(11);
                cout << "! ";
                setcolor(7);
            }
            else
            {
                cout << map[y][x] << " ";
            }
        }
        cout << "\n";
    }
}

void gameRules()
{
    cout << "Kamu tiba tiba terbangun didalam sebuah reruntuhan.\n";
    cout << "Kabur dan carilah jalan keluar!\n";
    cout << "Berhati-hatilah, mungkin ada yang mengincar nyawamu!\n\n";
    cout << "Peraturan permainan:\n";
    cout << "Pemain harus sampai ke titik finish tanpa terbunuh\n";
    cout << "* = Karakter (Lokasi Pemain)\n";
    cout << "! = Finish   (Pemain bisa lewat)\n";
    cout << "_ = Lantai   (Pemain bisa lewat)\n";
    cout << "~ = Puing    (Pemain bisa lewat/daerah rawan)\n";
    cout << "| = Jembatan (Pemain bisa lewat/daerah rawan)\n";
    cout << "^ = Batu     (Pemain tidak bisa lewat)\n";
    cout << "# = Lava     (Pemain tidak bisa lewat)\n";
    cout << "= = Dinding  (Pemain tidak bisa lewat)\n";
}

void obsRules()
{
    if (arrowKey == KEY_UP && (map[charPosY - 1][charPosX] == 5 || map[charPosY - 1][charPosX] == 6 || map[charPosY - 1][charPosX] == 7) && charPosY >= 0)
    {
        cout << "Kamu tidak bisa lewat!\n";
    }
    else if (arrowKey == KEY_DOWN && (map[charPosY + 1][charPosX] == 5 || map[charPosY + 1][charPosX] == 6 || map[charPosY + 1][charPosX] == 7) && charPosY < widthMap)
    {
        cout << "Kamu tidak bisa lewat!\n";
    }
    else if (arrowKey == KEY_LEFT && (map[charPosY][charPosX - 1] == 5 || map[charPosY][charPosX - 1] == 6 || map[charPosY][charPosX - 1] == 7) && charPosX >= 0)
    {
        cout << "Kamu tidak bisa lewat!\n";
    }
    else if (arrowKey == KEY_RIGHT && (map[charPosY][charPosX + 1] == 5 || map[charPosY][charPosX + 1] == 6 || map[charPosY][charPosX + 1] == 7) && charPosX < longMap)
    {
        cout << "Kamu tidak bisa lewat!\n";
    }
}

void inputKey()
{
    cout << "Masukan arrow key untuk bergerak \nESC untuk keluar\n";
    cout << "Masukan arrow key:\n";
    arrowKey = getch();
    cout << "Arrow key yang dimasukan: " << arrowKey << "\n";
}

void moveKey()
{
    // Aturan menggerakkan karakter ke atas
    if (arrowKey == KEY_UP && (map[charPosY - 1][charPosX] == 1 || map[charPosY - 1][charPosX] == 4 || map[charPosY - 1][charPosX] == 8 || map[charPosY - 1][charPosX] == 0) && charPosY >= 0)
    {
        // Gerakkan karakter ke atas
        charPosY = charPosY - 1;
    }
    // Aturan menggerakkan karakter ke bawah
    else if (arrowKey == KEY_DOWN && (map[charPosY + 1][charPosX] == 1 || map[charPosY + 1][charPosX] == 4 || map[charPosY + 1][charPosX] == 8 || map[charPosY + 1][charPosX] == 0) && charPosY < widthMap)
    {
        // Gerakkan karakter ke bawah
        charPosY = charPosY + 1;
    }
    // Aturan menggerakkan karakter ke kiri
    else if (arrowKey == KEY_LEFT && (map[charPosY][charPosX - 1] == 1 || map[charPosY][charPosX - 1] == 4 || map[charPosY][charPosX - 1] == 8 || map[charPosY][charPosX - 1] == 0) && charPosX >= 0)
    {
        // Gerakkan karakter ke kiri
        charPosX = charPosX - 1;
    }
    // Aturan menggerakkan karakter ke kanan
    else if (arrowKey == KEY_RIGHT && (map[charPosY][charPosX + 1] == 1 || map[charPosY][charPosX + 1] == 4 || map[charPosY][charPosX + 1] == 8 || map[charPosY][charPosX + 1] == 0) && charPosX < longMap)
    {
        // Gerakkan karakter ke kanan
        charPosX = charPosX + 1;
    }
}

void gameOver()
{
    cout << "Kamu meninggal. \nGame Over!\n";
}

void atkPlayer(killer *killer, player *player)
{
    if (killer->hp <= 0)
    {
        cout << killer->name << " telah dikalahkan, silahkan lanjutkan permainan!\n";
    }
    else
    {
        int hpFrom = killer->hp;
        cout << "Kamu menyerang " << killer->name << "! \n";
        killer->hp -= player->attack;
        cout << "HP " << killer->name << " berkurang dari " << hpFrom << " menjadi " << killer->hp << "\n";
        cout << "\nBerhasil menghindar.\n\n";
    }
}

void meet(killer *killer, player *player)
{

choice:
    int choice;
    cout << "Tekan ENTER untuk melawan\n"
         << "Tekan ESC untuk kabur\n\n";
    choice = getch();
    if (choice == 13)
    {
        cout << "Bertarung melawan pembunuh.\n";
        atkPlayer(killer, player);
    }
    else if (choice == ESC)
    {
        cout << "Kamu berhasil kabur sementara\n";
    }
    else
    {
        goto choice;
    }
}
