#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Kinoteatr {
private:
	string name;
	string phone;
	string address;
	string TimeJob;
	int countzal;
public:
	Kinoteatr() {
		name = "";
		phone = "";
		address = "";
		TimeJob = "";
		countzal = 0;
	}

	Kinoteatr(string n, string p, string a, string t, int z) {
		name = n;
		phone = t;
		address = a;
		TimeJob = t;
		countzal = z;
	}

	void setname(string n) { name = n; }
	void setphone(string p) { phone = p; }
	void setaddress(string a) { address = a; }
	void setTimeJob(string t) { TimeJob = t; }
	void setcountzal(int z) { countzal = z; }

	string getname() { return name; }
	string getphone() { return phone; }
	string getaddress() { return address; }
	string getTimeJob() { return TimeJob; }
	int getcountzal() { return countzal; }

	virtual void printInfo() {
		cout << "Название: " << name << endl;
		cout << "Телефон: " << phone << endl;
		cout << "Адрес: " << address << endl;
		cout << "Время работы: " << TimeJob << endl;
		cout << "Количество кинозалов: " << countzal << endl;
	}
};

class KinoZal : public Kinoteatr {
private:
	int mesta;
public:
	KinoZal() : Kinoteatr() {
		mesta = 0;
	}

	KinoZal(string n, string p, string a, string t, int z, int m) : Kinoteatr(n,p,a,t,z) {
		mesta = m;
	}

	void setmesta(int m) { mesta = m; }
	int getmesta() { return mesta; }

	void printInfo() override {
		Kinoteatr::printInfo();
		cout << "Вместимость зала: " << mesta << " человек" << endl;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	int N;
	cout << "Введите количество кинотеатров и залов: ";
	cin >> N;
	cin.ignore();

	Kinoteatr kino[100];
	KinoZal zal[100];

	ifstream fileKino("Kino.txt");
	ifstream fileZal("Zal.txt");

	if (!fileKino.is_open() || !fileZal.is_open()) {
		cout << "Ошибка открытия файла." << endl;
		return 1;
	}

	cout << "\n Читаем данные о кинотеатрах \n";
	for (int i = 0; i < N; i++) {
		string n, p, a, t;
		int z, m;

		getline(fileZal >> ws, n);
		getline(fileZal, p);
		getline(fileZal, a);
		getline(fileZal, t);
		fileZal >> z >> m;
		fileZal.ignore();

		zal[i] = KinoZal(n, p, a, t, z, m);

		cout << "\nКинозал #" << i + 1 << " (из файла):\n";
		zal[i].printInfo();
	}

	fileKino.close();
	fileZal.close();

	return 0;
}
