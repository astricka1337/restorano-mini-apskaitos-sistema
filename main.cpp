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

    getData(menuList, n);
    if (n == 0) {
        cout << "Klaida: Tuscias arba nerastas meniu failas!" << endl;
        return 1;
    }

    showMenu(menuList, n);

    int pasirinkimas;
    int porcijos;

    // Pridėtas vartotojo pasirinkimo ciklas
    while (true) {
        cout << "\nIveskite patiekalo numeri (0 - jei baigti): ";
        cin >> pasirinkimas;

        if (pasirinkimas == 0) break;

        if (pasirinkimas < 1 || pasirinkimas > n) {
            cout << "Neteisingas skaicius! Bandykite vel." << endl;
            continue;
        }

        cout << "Kiek porciju uzsakyti? ";
        cin >> porcijos;

        if (porcijos <= 0) {
            cout << "Kiekis turi buti teigiamas skaicius!" << endl;
            continue;
        }

        kiekiai[pasirinkimas - 1] += porcijos;
        cout << "Prideta i krepseli." << endl;
    }

    // Spausdinam čeki
    printCheck(menuList, n, kiekiai);
    return 0;
}

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

void showMenu(const menuItemType menuList[], int count) {
    cout << "=== Pusryčių Meniu ===" << endl;
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". "
             << left << setw(38) << menuList[i].menuItem
             << right << setw(6) << fixed << setprecision(2) << menuList[i].menuPrice << "€" << endl;
    }
    cout << "======================" << endl;
}

// Pilnai užpildyta čekio funkcija
void printCheck(const menuItemType menuList[], int count, const int orderQuantities[]) {
    double tarpineSuma = 0;
    for (int i = 0; i < count; i++) {
        if (orderQuantities[i] > 0) {
            tarpineSuma += menuList[i].menuPrice * orderQuantities[i];
        }
    }

    double pvm = tarpineSuma * 0.21;
    double galutineSuma = tarpineSuma + pvm;

    cout << "\nSveiki atvykę į restoraną „Pavadinimas“\n\n";
    for (int i = 0; i < count; i++) {
        if (orderQuantities[i] > 0) {
            cout << orderQuantities[i] << "  "
                 << left << setw(38) << menuList[i].menuItem
                 << right << setw(6) << fixed << setprecision(2) << menuList[i].menuPrice << "€\n";
        }
    }
    cout << "\nMokesčiai (21%)" << right << setw(32) << fixed << setprecision(2) << pvm << "€\n";
    cout << "Galutinė suma" << right << setw(34) << fixed << setprecision(2) << galutineSuma << "€\n";

    ofstream isvedimas("receipt.txt");
    if (isvedimas.is_open()) {
        isvedimas << "Sveiki atvykę į restoraną „Pavadinimas“\n\n";
        for (int i = 0; i < count; i++) {
            if (orderQuantities[i] > 0) {
                isvedimas << orderQuantities[i] << "  "
                          << left << setw(38) << menuList[i].menuItem
                          << right << setw(6) << fixed << setprecision(2) << menuList[i].menuPrice << "€\n";
            }
        }
        isvedimas << "\nMokesčiai (21%)" << right << setw(32) << fixed << setprecision(2) << pvm << "€\n";
        isvedimas << "Galutinė suma" << right << setw(34) << fixed << setprecision(2) << galutineSuma << "€\n";
        isvedimas.close();
        cout << "\n[Saskaita sėkmingai įrašyta į receipt.txt]" << endl;
    }
}