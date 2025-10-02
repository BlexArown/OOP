#include <iostream>
#include <string>
using namespace std;

class University {
protected:
    string name;
    string phone;
    string address;
public:
    University() {
        name = "";
        phone = "";
        address = "";
    }

    University(string n, string p, string a) {
        name = n;
        phone = p;
        address = a;
    }

    void setName(const string& n) { name = n; }
    void setPhone(const string& p) { phone = p; }
    void setAddress(const string& a) { address = a; }

    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }

    virtual void printInfo() const {
        cout << "Университет: " << name << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
    }
};

class TechnicalUniversity : public University {
private:
    string subordinationStatus;
public:
    TechnicalUniversity() : University() {
        subordinationStatus = "";
    }

    TechnicalUniversity(string n, string p, string a, string s) : University(n, p, a) {
        subordinationStatus = s;
    }

    void setSubordinationStatus(const string& s) { subordinationStatus = s; }
    string getSubordinationStatus() const { return subordinationStatus; }

    void printInfo() const override {
        cout << "Технический университет: " << name << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Адрес: " << address << endl;
        cout << "Статус подчинения: " << subordinationStatus << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=   Базовый университет   =" << endl;
    University u1("НГУ", "+7(383)363-41-52", "г. Новосибирск, ул. Пирогова, 1");
    u1.printInfo();

    cout << "\n=  Технический университет   =" << endl;
    TechnicalUniversity tu("НГТУ", "+7(383)987-65-43", "г. Новосибирск, пр. К. Маркса, 20", "Федеральный");
    tu.printInfo();

    cout << "\n=   Редактирование данных   =" << endl;
    tu.setName("НГГТУУ (обновлённое название)");
    tu.setSubordinationStatus("Региональный");
    tu.printInfo();

    return 0;
}
