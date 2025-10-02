#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
};

class Quadrilateral {
protected:
    Point A, B, C, D;
public:
    Quadrilateral(Point p1, Point p2, Point p3, Point p4) {
        A = p1; B = p2; C = p3; D = p4;
    }

    virtual ~Quadrilateral() {}

    double length(Point p1, Point p2) const {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }

    double sideAB() const { return length(A, B); }
    double sideBC() const { return length(B, C); }
    double sideCD() const { return length(C, D); }
    double sideDA() const { return length(D, A); }

    double diagAC() const { return length(A, C); }
    double diagBD() const { return length(B, D); }

    double perimeter() const {
        return sideAB() + sideBC() + sideCD() + sideDA();
    }

    double area() const {
        return fabs((A.x*B.y + B.x*C.y + C.x*D.y + D.x*A.y
                   - A.y*B.x - B.y*C.x - C.y*D.x - D.y*A.x) / 2.0);
    }

    // Перегрузка
    int areaInt() const {
        return round(area());
    }

    virtual void outputTo() const {
        cout << "Четырёхугольник:" << endl;
        cout << "Стороны: AB=" << sideAB() << ", BC=" << sideBC() << ", CD=" << sideCD() << ", DA=" << sideDA() << endl;
        cout << "Диагонали: AC=" << diagAC() << ", BD=" << diagBD() << endl;
        cout << "Периметр = " << perimeter() << endl;
        cout << "Площадь (double) = " << area() << ", (int) = " << areaInt() << endl;
    }
};

class IsoscelesTrapezoid : public Quadrilateral {
private:
    bool isIsoscelesTrapezoid;
public:
    IsoscelesTrapezoid(Point p1, Point p2, Point p3, Point p4)
        : Quadrilateral(p1, p2, p3, p4) 
    {
        isIsoscelesTrapezoid = checkIsoscelesTrapezoid();
    }

    bool checkIsoscelesTrapezoid() {
        double dx1 = B.x - A.x, dy1 = B.y - A.y;
        double dx2 = D.x - C.x, dy2 = D.y - C.y;

        bool parallel = fabs(dx1 * dy2 - dy1 * dx2) < 1e-6;
        bool equalSides = fabs(sideBC() - sideDA()) < 1e-6;

        return parallel && equalSides;
    }

    void outputTo() const override {
        cout << "Фигура: ";
        if (isIsoscelesTrapezoid) cout << "Равнобочная трапеция" << endl;
        else cout << "Не является равнобочной трапецией" << endl;
        cout << "Стороны: AB=" << sideAB() << ", BC=" << sideBC() << ", CD=" << sideCD() << ", DA=" << sideDA() << endl;
        cout << "Диагонали: AC=" << diagAC() << ", BD=" << diagBD() << endl;
        cout << "Периметр = " << perimeter() << endl;
        cout << "Площадь (double) = " << this->area() << ", (int) = " << const_cast<IsoscelesTrapezoid*>(this)->area() << endl;
    }

    double getMinDiagonal() const {
        return min(diagAC(), diagBD());
    }
};

class MainApp {
public:
    void run() {
        setlocale(LC_ALL, "Russian");

        const int size = 3;
        Quadrilateral* figures[size];

        figures[0] = new IsoscelesTrapezoid({0,4}, {4,0}, {3,3}, {1,3});
        figures[1] = new IsoscelesTrapezoid({0,0}, {6,0}, {5,2}, {1,2});
        figures[2] = new IsoscelesTrapezoid({0,6}, {8,0}, {6,4}, {2,4});

        cout << "Вывод информации о фигурах (полиморфизм):" << endl << endl;
        for (int i = 0; i < size; i++) {
            figures[i]->outputTo();
            cout << "-----------------------------" << endl;
        }

        double minDiag = 1e9;
        int index = -1;
        for (int i = 0; i < size; i++) {
            IsoscelesTrapezoid* trap = dynamic_cast<IsoscelesTrapezoid*>(figures[i]);
            if (trap) {
                double d = trap->getMinDiagonal();
                if (d < minDiag) {
                    minDiag = d;
                    index = i;
                }
            }
        }

        cout << "Трапеция с наименьшей диагональю имеет индекс: " 
             << index << " (минимальная диагональ = " << minDiag << ")" << endl;

        for (int i = 0; i < size; i++) delete figures[i];
    }
};

int main() {
    MainApp app;
    app.run();
    return 0;
}
