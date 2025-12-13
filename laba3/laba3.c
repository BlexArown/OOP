#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class TourInfo {
private:
    string country;
    double price;
    int sales[6];
    double total;

public:
    TourInfo() : price(0), total(0) {
        for (int i = 0; i < 6; i++) sales[i] = 0;
    }

    void readFromText(ifstream &fin) {
        getline(fin, country);
        fin >> price;
        for (int i = 0; i < 6; i++) {
            fin >> sales[i];
        }
        fin.ignore();

        int sumSales = 0;
        for (int i = 0; i < 6; i++) sumSales += sales[i];
        total = sumSales * price;
    }

    void writeToBinary(ofstream &fout) const {
        size_t len = country.size();
        fout.write((char*)&len, sizeof(len));
        fout.write(country.c_str(), len);
        fout.write((char*)&price, sizeof(price));
        fout.write((char*)sales, sizeof(sales));
        fout.write((char*)&total, sizeof(total));
    }
};

int main() {
    ifstream fin("data.txt");
    if (!fin) {
        cerr << "Не удалось открыть data.txt\n";
        return 1;
    }

    ofstream fout("data.bin", ios::binary);
    if (!fout) {
        cerr << "Не удалось создать data.bin\n";
        return 1;
    }

    int n;
    fin >> n;
    fin.ignore();

    const int MAX_TOURS = 100;
    TourInfo tours[MAX_TOURS];

    for (int i = 0; i < n && i < MAX_TOURS; i++) {
        tours[i].readFromText(fin);
        tours[i].writeToBinary(fout);
    }

    fin.close();
    fout.close();

    cout << "Файл data.bin успешно создан!\n";
    return 0;
}
