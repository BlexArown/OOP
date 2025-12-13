#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Request {
private:
    string destination;
    string flightNumber;
    string passenger;
    string date;
public:
    Request(string dest, string flight, string pass, string dt) : destination(dest), flightNumber(flight), passenger(pass), date(dt) {}

    string getDestination() const { return destination; }
    string getFlightNumber() const { return flightNumber; }
    string getPassenger() const { return passenger; }
    string getDate() const { return date; }

    void print() const {
        cout << "Пункт: " << destination << " | Рейс: " << flightNumber << " | Пассажир: " << passenger << " | Дата: " << date << endl;
    }
};

class RequestQueue {
private:
    queue<Request> q;
public:
    void addRequest(const Request& r) { q.push(r); }

    void removeRequest() {
        if (q.empty()) {
            cout << "Очередь пуста, удалять нечего.\n";
            return;
        }
        cout << "Удалена заявка:\n";
        q.front().print();
        q.pop();
    }

    void printAll() const {
        if (q.empty()) {
            cout << "Очередь пуста.\n";
            return;
        }
        queue<Request> temp = q;
        int i = 1;
        while (!temp.empty()) {
            cout << i++ << ". ";
            temp.front().print();
            temp.pop();
        }
    }

    void printFirst() const {
        if (q.empty()) {
            cout << "Очередь пуста.\n";
            return;
        }
        cout << "Первая заявка:\n";
        q.front().print();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    RequestQueue rq;

    while (true) {
        cout << "\nМеню:\n"
             << "1. Добавить заявку\n"
             << "2. Удалить первую заявку\n"
             << "3. Показать все заявки\n"
             << "4. Показать первую заявку\n"
             << "0. Выход\n"
             << "Ваш выбор: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        if (choice == 1) {
            string dest, flight, pass, date;

            cout << "Пункт назначения: ";
            getline(cin, dest);

            cout << "Номер рейса: ";
            getline(cin, flight);

            cout << "Фамилия и инициалы: ";
            getline(cin, pass);

            cout << "Дата вылета: ";
            getline(cin, date);

            rq.addRequest(Request(dest, flight, pass, date));
            cout << "Заявка добавлена.\n";
        }
        else if (choice == 2) {
            rq.removeRequest();
        }
        else if (choice == 3) {
            rq.printAll();
        }
        else if (choice == 4) {
            rq.printFirst();
        }
        else {
            cout << "Неверный выбор.\n";
        }
    }

    cout << "Выход из программы.\n";
    return 0;
}

