#include <iostream>
#include <cmath>
using namespace std;

class Circle {
	private:
    		double x0;
    		double y0;
    		double R;

	public:
    		Circle() {
        	x0 = 0;
        	y0 = 0;
        	R = 1;
    	}

    	Circle(double x, double y, double r) {
        	x0 = x;
        	y0 = y;
        	R = (r > 0) ? r : 1; // радиус не отриц
    	}

   	// вычисл длины
    	double length() {
        	return 2 * M_PI * R;
    	}

    	// пересечения с OX
    	bool intersectsOX() {
        	return (y0 - R <= 0 && y0 + R >= 0); // нижняя ≤ 0 и верхняя ≥ 0, иначе пересекает
    	}

    	// пересечения с OY
    	bool intersectsOY() {
        	return (x0 - R <= 0 && x0 + R >= 0); // аналогично, проверка содержит ли значение 0
    	}

    	// вывод
    	void outputInfo() {
        	cout << "Окружность: центр(" << x0 << ", " << y0 << "), радиус = " << R << endl;
        	cout << "Длина окружности = " << length() << endl;
        	cout << "Пересекает OX: " << (intersectsOX() ? "Да" : "Нет") << endl;
        	cout << "Пересекает OY: " << (intersectsOY() ? "Да" : "Нет") << endl;
        	cout << "=================================" << endl;
    	}
};


int main() {
    	int N;
    	cout << "Введите количество окружностей: ";
    	cin >> N;

    	Circle* circles = new Circle[N];

    	for (int i = 0; i < N; i++) {
        	double x, y, r;
        	cout << "\nВведите данные для окружности " << i + 1 << " (x0 y0 R): ";
        	cin >> x >> y >> r;
        	circles[i] = Circle(x, y, r); // окр через конструктор
    	}

    	cout << "\n=== Резы ===\n";
    	for (int i = 0; i < N; i++) {
        	cout << "Окружность #" << i + 1 << endl;
        	circles[i].outputInfo();
    	}

    	delete[] circles; // освобождение памяти
    	return 0;
}

