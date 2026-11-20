#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

//klass public.
class Publication {
protected:
    string nazvanie;
    float cena = 0;

public:
    virtual void getdata() {
        do {
            cout << "Введите название: ";
            getline(cin, nazvanie);
            if (nazvanie.empty()) {
                cout << "Ошибка: название не может быть пустым!\n";
            }
        } while (nazvanie.empty());

        while (true) {
            cout << "Введите цену: ";
            cin >> cena;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ошибка: введите число!\n";
                continue;
            }
            if (cena <= 0) {
                cout << "Ошибка: цена должна быть больше нуля!\n";
                continue;
            }
            break;
        }
    }

    virtual void putdata() {
        cout << "Название: " << nazvanie << "\n";
        cout << "Цена: " << cena << "\n";
    }

    virtual ~Publication() {}
};

//klass prodaz.
class sales {
protected:
    float prodazhi[3] = { 0, 0, 0 };   //3 месяца

public:
    virtual void getdata() {
        cout << "Введите продажи за 3 месяца (3 числа через пробел): ";

        for (int i = 0; i < 3; i++) {
            while (true) {
                cin >> prodazhi[i];

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Ошибка: введите 3 числа через пробел. Повторите: ";
                    i = -1;   // начать цикл сначала
                    break;
                }
                if (prodazhi[i] < 0) {
                    cout << "Ошибка: продажи не могут быть отрицательными. Повторите все 3 числа: ";
                    i = -1;
                    break;
                }
                break;
            }
        }
    }

    virtual void putdata() {
        cout << "Продажи за 3 месяца: ";
        for (int i = 0; i < 3; i++) {
            cout << prodazhi[i];
            if (i < 2) cout << " | ";
        }
        cout << "\n";
    }

    virtual ~sales() {}
};

//klass kniaga
class book : public Publication, public sales {
private:
    int stranicy = 0;   // количество страниц

public:
    void getdata() override {
        Publication::getdata();
        sales::getdata();

        while (true) {
            cout << "Введите количество страниц: ";
            cin >> stranicy;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ошибка: введите число!\n";
                continue;
            }
            if (stranicy <= 0) {
                cout << "Ошибка: количество страниц должно быть больше нуля!\n";
                continue;
            }
            break;
        }
    }

    void putdata() override {
        Publication::putdata();
        sales::putdata();
        cout << "Страниц: " << stranicy << "\n";
    }
};

//klass audio
class type : public Publication, public sales {
private:
    int minuty = 0;   // время записи в минутах

public:
    void getdata() override {
        Publication::getdata();
        sales::getdata();

        while (true) {
            cout << "Введите время записи (в минутах): ";
            cin >> minuty;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Ошибка: введите число!\n";
                continue;
            }
            if (minuty <= 0) {
                cout << "Ошибка: время записи должно быть больше нуля!\n";
                continue;
            }
            break;
        }
    }

    void putdata() override {
        Publication::putdata();
        sales::putdata();
        cout << "Минут записи: " << minuty << "\n";
    }
};

//main
int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Добавляем книгу.\n";
    book kniga;
    kniga.getdata();

    cout << "\nДобавляем аудиокнигу.\n";
    cin.ignore();
    type audio;
    audio.getdata();

    cout << "\nКнига:\n";
    kniga.putdata();

    cout << "\nАудиокнига:\n";
    audio.putdata();

    return 0;
}
