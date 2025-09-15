#include <iostream>
#include <string>
using namespace std;

// superclass
class EducationInstitut {
private:
    string type;        // тип заведения
    string subord; // подчинение

public:
    //  конструктор
    EducationInstitut(string t, string s) {
        type = t;
        subord = s;
    }

    // изменение значений
    void setType(string t) {
        type = t;
    }

    void setSubord(string s) {
        subord = s;
    }

    // получение значений
    string getType() {
        return type;
    }

    string getSubord() {
        return subord;
    }

    // вывод информации
    void outputInfo() {
        cout << "Учеб.заведение: " << type << endl;
        cout << "Подчинение: " << subord << endl;
    }
};

int main() {
    EducationInstitut sibguti("Университет", "МО РФ");

    cout << "=== До изменений ===" << endl;
    sibguti.outputInfo();

    // замена
    sibguti.setType("СибГУТИ");
    sibguti.setSubord("Департамент образования НО");

    cout << "\n=== После изменений ===" << endl;
    sibguti.outputInfo();

    return 0;
}

