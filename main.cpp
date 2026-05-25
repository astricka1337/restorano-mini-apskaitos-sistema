#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

void getData(menuItemType menuList[], int& count);
void showMenu(const menuItemType menuList[], int count);
void printCheck(const menuItemType menuList[], int count, const int orderQuantities[]);

int main() {
    setlocale(LC_ALL, "Lithuanian");

    menuItemType menuList[100];
    int n = 0;
    int kiekiai[100] = {0};

    // Jau kviečiame nuskaitymą ir rodymą
    getData(menuList, n);
    if (n == 0) {
        cout << "Klaida: Nerastas meniu!" << endl;
        return 1;
    }

    showMenu(menuList, n);
    return 0;
}

// Įrašom logiką failo nuskaitymui
void getData(menuItemType menuList[], int& count) {
    ifstream failas("menu.txt");
    if (!failas.is_open()) return;

    string eilute;
    count = 0;
    while (getline(failas, eilute) && count < 100) {
        if (eilute.empty()) continue;
        int tarpas = -1;
        for (int i = eilute.length() - 1; i >= 0; i--) {
            if (eilute[i] == ' ') {
                tarpas = i;
                break;
            }
        }
        if (tarpas != -1) {
            menuList[count].menuItem = eilute.substr(0, tarpas);
            menuList[count].menuPrice = stod(eilute.substr(tarpas + 1));
            count++;
        }
    }
    failas.close();
}

// Įrašom logiką meniu rodymui
void showMenu(const menuItemType menuList[], int count) {
    cout << "=== Pusryčių Meniu ===" << endl;
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". "
             << left << setw(38) << menuList[i].menuItem
             << right << setw(6) << fixed << setprecision(2) << menuList[i].menuPrice << "€" << endl;
    }
    cout << "======================" << endl;
}

void printCheck(const menuItemType menuList[], int count, const int orderQuantities[]) {}