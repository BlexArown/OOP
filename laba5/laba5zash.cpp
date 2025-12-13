#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class Car {
private:
    string number;
public:
    Car(string num) : number(num) {}

    string getNumber() const { return number; }

    void showInfo() const {
        cout << "Машина №" << number << endl;
    }

    bool operator==(const Car& other) const {
        return number == other.number;
    }
};

void showCars(const list<Car>& cars) {
    if (cars.empty()) {
        cout << "Стоянка пуста.\n";
        return;
    }
    cout << "На стоянке сейчас:\n";
    for (const auto& c : cars)
        c.showInfo();
}

int main() {
    setlocale(LC_ALL, "ru");
    list<Car> parking;

    int choice;
    do {
        cout << "\n=== ГАРАЖНАЯ СТОЯНКА ===\n";
        cout << "1. Прибытие машины\n";
        cout << "2. Отъезд машины\n";
        cout << "3. Показать машины на стоянке\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string num;
            cout << "Введите номер прибывшей машины: ";
            getline(cin, num);

            auto it = find_if(parking.begin(), parking.end(), [&](const Car& c) { return c.getNumber() == num; });
            if (it == parking.end()) {
                parking.push_back(Car(num));
                cout << "Машина №" << num << " прибыла и поставлена на стоянку.\n";
            } else {
                cout << "Машина с номером " << num << " уже на стоянке!\n";
            }
        }
        else if (choice == 2) {
            string num;
            cout << "Введите номер машины, которая уезжает: ";
            getline(cin, num);

            auto it = find_if(parking.begin(), parking.end(), [&](const Car& c) { return c.getNumber() == num; });
            if (it != parking.end()) {
                parking.erase(it);
                cout << "Машина №" << num << " покинула стоянку.\n";
            } else {
                cout << "Машины с таким номером нет на стоянке.\n";
            }
        }
        else if (choice == 3) {
            showCars(parking);
        }

    } while (choice != 0);

    cout << "Выход из программы.\n";
    return 0;
}

