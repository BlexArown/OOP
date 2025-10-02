#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// Точка
struct Point {
    double x, y;
};

// ========================
// Суперкласс Четырёхугольник
// ========================
class Quadrilateral {
protected:
    double a, b, c, d; // стороны: a,b - основания, c,d - боковые
    Point A, B, C, D;  // координаты вершин
public:
    Quadrilateral(double A_, double B_, double C_, double D_) {
        a = A_; b = B_; c = C_; d = D_;
        buildCoordinates();
    }

    virtual ~Quadrilateral() {}

    // Построение координат трапеции (основание AB на оси X)
    void buildCoordinates() {
        A = {0, 0};
        B = {a, 0};

        // Высота из условия равнобокости (сначала считаем через c)
        double dx = (a - b) / 2.0;
        double h = sqrt(max(0.0, c*c - dx*dx));

        C = {dx, h};
        D = {dx + b, h};
    }

    // Длина отрезка
    double length(Point p1, Point p2) const {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }

    // Периметр
    double perimeter() const {
        return a + b + c + d;
    }

    // Высота (по формуле площади)
    double height() const {
        double h = 2.0 * area() / (a + b);
        return h;
    }

    // Площадь
    double area() const {
        double dx = (a - b) / 2.0;
        double h = sqrt(max(0.0, c*c - dx*dx));
        return (a + b) / 2.0 * h;
    }

    // Диагонали
    double diagAC() const { return length(A, C); }
    double diagBD() const { return length(B, D); }

    virtual void outputTo() const {
        cout << "Четырёхугольник:" << endl;
        cout << "Стороны: a=" << a << ", b=" << b
             << ", c=" << c << ", d=" << d << endl;
        cout << "Периметр = " << perimeter() << endl;
        cout << "Площадь = " << area() << endl;
        cout << "Диагонали: AC=" << diagAC() << ", BD=" << diagBD() << endl;
    }
};

// ========================
// Подкласс Равнобочная трапеция
// ========================
class IsoscelesTrapezoid : public Quadrilateral {
private:
    bool isIsoscelesTrapezoid;
public:
    IsoscelesTrapezoid(double A_, double B_, double C_, double D_)
        : Quadrilateral(A_, B_, C_, D_) 
    {
        isIsoscelesTrapezoid = checkIsoscelesTrapezoid();
    }

    bool checkIsoscelesTrapezoid() {
        return fabs(c - d) < 1e-6; // боковые стороны равны
    }

    void outputTo() const override {
        cout << "Фигура: ";
        if (isIsoscelesTrapezoid) cout << "Равнобочная трапеция" << endl;
        else cout << "Не является равнобочной трапецией" << endl;

        cout << "Стороны: a=" << a << ", b=" << b
             << ", c=" << c << ", d=" << d << endl;
        cout << "Периметр = " << perimeter() << endl;
        cout << "Площадь = " << area() << endl;
        cout << "Диагонали: AC=" << diagAC() << ", BD=" << diagBD() << endl;
    }

    double getMinDiagonal() const {
        return min(diagAC(), diagBD());
    }
};

// ========================
// Main
// ========================
int main() {
    setlocale(LC_ALL, "Russian");

    int M;
    cout << "Введите количество трапеций: ";
    cin >> M;

    vector<Quadrilateral*> figures;

    for (int i = 0; i < M; i++) {
        cout << "\nТрапеция №" << i+1 << endl;
        double a, b, c, d;
        cout << "Введите основание a: "; cin >> a;
        cout << "Введите основание b: "; cin >> b;
        cout << "Введите боковую сторону c: "; cin >> c;
        cout << "Введите боковую сторону d: "; cin >> d;

        IsoscelesTrapezoid* trap = new IsoscelesTrapezoid(a, b, c, d);
        figures.push_back(trap);
    }

    cout << "\nВывод информации о фигурах:" << endl << endl;
    for (int i = 0; i < figures.size(); i++) {
        cout << "Трапеция №" << i+1 << ":" << endl;
        figures[i]->outputTo();
        cout << "-----------------------------" << endl;
    }

    double minDiag = 1e9;
    int index = -1;
    for (int i = 0; i < figures.size(); i++) {
        IsoscelesTrapezoid* trap = dynamic_cast<IsoscelesTrapezoid*>(figures[i]);
        if (trap) {
            double d = trap->getMinDiagonal();
            if (d < minDiag) {
                minDiag = d;
                index = i;
            }
        }
    }

    cout << "\nТрапеция с наименьшей диагональю: №" << index+1
         << " (минимальная диагональ = " << minDiag << ")" << endl;

    for (auto f : figures) delete f;

    return 0;
}
