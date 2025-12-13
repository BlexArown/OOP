#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

class Book {
private:
    string udk;
    string author;
    string title;
    int year;
    int count;

public:
    Book(string udk, string author, string title, int year, int count) : udk(udk), author(author), title(title), year(year), count(count) {}

    string getUdk() const { return udk; }
    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    int getYear() const { return year; }
    int getCount() const { return count; }

    void setCount(int newCount) { count = newCount; }

    void outputInfo() const {
        cout << "УДК: " << udk << " | Автор: " << author << " | Название: " << title << " | Год: " << year << " | Кол-во: " << count << endl;
    }

    bool operator<(const Book &other) const {
        return year < other.year;
    }
};

void showBooks(const list<Book> &books) {
    if (books.empty()) {
        cout << "Список пуст.\n";
        return;
    }
    for (const auto &b : books)
        b.outputInfo();
}

string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c); });
    return s;
}

int main() {
    setlocale(LC_ALL, "ru");

    list<Book> books;

    int n;
    cout << "Введите количество книг: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string udk, author, title;
        int year, count;

        cout << "\n[" << i + 1 << "] УДК: ";
        getline(cin, udk);
        cout << "Автор (фамилия и инициалы): ";
        getline(cin, author);
        cout << "Название: ";
        getline(cin, title);
        cout << "Год издания: ";
        cin >> year;
        cout << "Количество экземпляров: ";
        cin >> count;
        cin.ignore();

        books.push_back(Book(udk, author, title, year, count));
    }

    books.sort();

    int choice;
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Показать все книги\n";
        cout << "2. Взять книгу (уменьшить кол-во)\n";
        cout << "3. Вернуть книгу (увеличить кол-во)\n";
        cout << "4. Проверить наличие книги по названию\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            showBooks(books);
        }
        else if (choice == 2) {
            string udk;
            cout << "Введите номер УДК книги: ";
            getline(cin, udk);

            auto it = find_if(books.begin(), books.end(), [&](const Book &b) { return b.getUdk() == udk; });

            if (it != books.end()) {
                if (it->getCount() > 0) {
                    it->setCount(it->getCount() - 1);
                    cout << "Книга \"" << it->getTitle() << "\" выдана читателю.\n";
                } else {
                    cout << "Книги \"" << it->getTitle() << "\" нет в наличии (все на руках).\n";
                }
            } else {
                cout << "Книга с таким УДК не найдена.\n";
            }
        }
        else if (choice == 3) {
            string udk;
            cout << "Введите номер УДК возвращаемой книги: ";
            getline(cin, udk);

            auto it = find_if(books.begin(), books.end(), [&](const Book &b) { return b.getUdk() == udk; });

            if (it != books.end()) {
                it->setCount(it->getCount() + 1);
                cout << "Книга \"" << it->getTitle() << "\" возвращена в библиотеку.\n";
            } else {
                cout << "Книга с таким УДК не найдена.\n";
            }
        }
        else if (choice == 4) {
            string name;
            cout << "Введите название книги: ";
            getline(cin, name);

            auto it = find_if(books.begin(), books.end(), [&](const Book &b) { return toLower(b.getTitle()) == toLower(name); });

            if (it != books.end()) {
                cout << "Найдена книга:\n";
                it->outputInfo();
            } else {
                cout << "Книга не найдена.\n";
            }
        }

    } while (choice != 0);

    cout << "Выход из программы.\n";
    return 0;
}

