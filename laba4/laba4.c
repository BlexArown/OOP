#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // sort, find_if
using namespace std;

class EducationInstitut {
private:
    string type;
    string subord;

public:
    EducationInstitut() = default;
    EducationInstitut(string t, string s) : type(t), subord(s) {}

    string getType() const { return type; }
    string getSubord() const { return subord; }

    void setType(string t) { type = t; }
    void setSubord(string s) { subord = s; }

    void outputInfo() const {
        cout << "Учеб. заведение: " << type << " | Подчинение: " << subord << endl;
    }

    // для сорт по типу
    bool operator<(const EducationInstitut &other) const {
        return type < other.type;
    }
};

// вставка с сохранением сорт
void insertSorted(vector<EducationInstitut> &vec, const EducationInstitut &inst) {
    auto pos = lower_bound(vec.begin(), vec.end(), inst);
    vec.insert(pos, inst);
}

int main() {
    setlocale(LC_ALL, "ru");

    int n;
    cout << "Введите количество учебных заведений: ";
    cin >> n;
    cin.ignore();

    vector<EducationInstitut> institutes;
    institutes.reserve(n); // без лишних реаллокаций

    // заполн вектора
    for (int i = 0; i < n; i++) {
        string t, s;
        cout << "\n[" << i + 1 << "] Введите тип заведения: ";
        getline(cin, t);
        cout << "\n\nВведите подчинение: ";
        getline(cin, s);
        institutes.push_back(EducationInstitut(t, s));
    }

    cout << "\n=== исходн вектор ===" << endl;
    for (const auto &inst : institutes) {
        inst.outputInfo();
    }

    // создание нового вектора
    vector<EducationInstitut> universities;
    for (const auto &inst : institutes) {
        if (inst.getType().find("Университет") != string::npos) {
            universities.push_back(inst);
        }
    }

    // проверка на пустоту
    if (universities.empty()) {
        cout << "\nВ новом векторе нет элементов, соответствующих критерию." << endl;
        return 0;
    } else {
        cout << "\nНовый вектор не пуст. Элементы:" << endl;
        for (const auto &u : universities) u.outputInfo();
    }

    // Сорт нового вектора
    sort(universities.begin(), universities.end());

    cout << "\n=== После сортировки (по типу) ===" << endl;
    for (const auto &u : universities) u.outputInfo();

    // вставка нью элемента с сохранением сорт
    string t, s;
    cout << "\nВведите тип заведения для вставки: ";
    getline(cin, t);
    cout << "Введите подчинение: ";
    getline(cin, s);

    EducationInstitut newInst(t, s);
    insertSorted(universities, newInst);

    cout << "\n=== После вставки нового элемента ===" << endl;
    for (const auto &u : universities) u.outputInfo();

    return 0;
}
