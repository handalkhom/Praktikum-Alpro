#include <iostream>
using namespace std;

struct skill_t
{
    int id;
    string name;
    string sOne;
    string sTwo;
};

int main()
{
    skill_t skill[] = {
        {1, "Quicker", "Lari Super Cepat", "Afterimage"},
        {2, "Killer", "Pembunuh Ahli", "Stealth"},
        {3, "Rage", "Ahli Bela Diri", "Body of Steel"},
        {4, "Priest", "Ceramah", "Hypnotize"}};

cariSkill:
    int idSkillYangDicari;
    int idSkillYangDilewat;

    cout << "Masukkan ID Skill Bundle yang ingin dicari :";
    cin >> idSkillYangDicari;

    cout << "Masukkan ID Skill Bundle yang ingin dilewati :";
    cin >> idSkillYangDilewat;

    for (int i = 0; i < 4; i++)
    {
        if (i + 1 == idSkillYangDilewat)
        {
            continue;
        }
        else
        {
            cout << "Skill Bundle dengan ID '" << skill[i].id << "' Adalah '" << skill[i].name << "' Dengan Skill Aktif '" << skill[i].sOne << "' dan Skill Pasif '" << skill[i].sTwo << "'\n";
            while (i + 1 == idSkillYangDicari)
            {
                cout << "Skill Bundle telah ditemukan\n";
                break;
            }
        }
    }
    string answer;
    do
    {
        cout << "Apakah Anda ingin mencari skill lain? (y/n)\n";
        cin >> answer;
        if (answer == "n")
        {
            break;
        }
        goto cariSkill;
    } while (answer == "y" || answer == "Y");

    return 0;
}