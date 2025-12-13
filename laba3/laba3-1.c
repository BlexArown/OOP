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

    bool readFromBinary(ifstream &fin) {
        size_t len;
        if (!fin.read((char*)&len, sizeof(len))) return false;

        country.resize(len);
        fin.read(&country[0], len);
        fin.read((char*)&price, sizeof(price));
        fin.read((char*)sales, sizeof(sales));
        fin.read((char*)&total, sizeof(total));

        return true;
    }

    int totalSales() const {
        int sum = 0;
        for (int i = 0; i < 6; i++) sum += sales[i];
        return sum;
    }

    double getTotalAmount() const { return total; }
    string getCountry() const { return country; }

    void print() const {
        cout << country << " (продано " << totalSales() << " путёвок, сумма: " << total << " $)\n";
    }
};

int main() {
    ifstream fin("data.bin", ios::binary);
    if (!fin) {
        cerr << "Не удалось открыть data.bin\n";
        return 1;
    }

    const int MAX_TOURS = 100;
    TourInfo tours[MAX_TOURS];
    int count = 0;

    // чтение даныых
    while (count < MAX_TOURS && tours[count].readFromBinary(fin)) {
        count++;
    }
    fin.close();

    if (count == 0) {
        cerr << "Нет данных для обработки.\n";
        return 1;
    }

    // ищем страну с макс кол путевок
    int maxIndex = 0;
    int maxSales = tours[0].totalSales();

    for (int i = 1; i < count; i++) {
        int sales = tours[i].totalSales();
        if (sales > maxSales) {
            maxSales = sales;
            maxIndex = i;
        }
    }

    cout << "Страна, в которую продано больше всего путёвок:\n";
    tours[maxIndex].print();

    return 0;
}
