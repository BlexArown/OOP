#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class CoffeeShop {
private:
    string name;
    string address;
    string workTime;
    double income;

public:
    CoffeeShop() = default;

    CoffeeShop(string n, string a, string w, double inc) : name(n), address(a), workTime(w), income(inc) {}

    string getName() const    { return name; }
    string getAddress() const { return address; }
    string getWorkTime() const { return workTime; }
    double getIncome() const  { return income; }

    void print() const {
        cout << "Название: " << name << " | Адрес: " << address << " | Время работы: " << workTime << " | Доход: " << income << " руб." << endl;
    }
};

void insertSorted(vector<CoffeeShop>& v, const CoffeeShop& shop) {
    auto it = lower_bound(v.begin(), v.end(), shop, [](const CoffeeShop& a, const CoffeeShop& b) {
            return a.getIncome() < b.getIncome();
        }
    );
    v.insert(it, shop);
}

int main() {
    setlocale(LC_ALL, "ru");

    int N;
    cout << "Введите количество объектов N (сколько читать из файла): ";
    cin >> N;
    cin >> ws;

    ifstream fin("kofe.txt");
    if (!fin) {
        cout << "Не удалось открыть файл kofe.txt" << endl;
        return 0;
    }

    vector<CoffeeShop> rich;

    for (int i = 0; i < N; ++i) {
        string name, addr, time;
        double inc;

        if (!getline(fin, name)) break;
        if (!getline(fin, addr)) break;
        if (!getline(fin, time)) break;
        if (!(fin >> inc)) break;
        fin >> ws;

        CoffeeShop c(name, addr, time, inc);

        if (inc > 500000.0) {
            rich.push_back(c);
        }
    }

    cout << "\nКофейни с доходом > 500000:\n";
    for (size_t i = 0; i < rich.size(); ++i) {
        rich[i].print();
    }

    sort(rich.begin(), rich.end(), [](const CoffeeShop& a, const CoffeeShop& b) {
             return a.getIncome() < b.getIncome(); });

    cout << "\nПосле сортировки по доходу:\n";
    for (size_t i = 0; i < rich.size(); ++i) {
        rich[i].print();
    }

    cout << "\nВведите данные новой кофейни:\n";

    string name, addr, time;
    double inc;

    cout << "Название: ";
    getline(cin, name);
    cout << "Адрес: ";
    getline(cin, addr);
    cout << "Время работы: ";
    getline(cin, time);
    cout << "Среднесуточный доход: ";
    cin >> inc;

    CoffeeShop newCafe(name, addr, time, inc);
    insertSorted(rich, newCafe);

    cout << "\nПосле вставки новой кофейни:\n";
    for (size_t i = 0; i < rich.size(); ++i) {
        rich[i].print();
    }

    ofstream fout("kofe.txt", ios::app);
    if (!fout) {
        cout << "Не удалось открыть kofe.txt для дозаписи\n";
        return 0;
    }

    fout << '\n' << name << '\n' << addr << '\n' << time << '\n' << inc;

    cout << "\nНовая кофейня дозаписана в файл kofe.txt\n";

    return 0;
}
