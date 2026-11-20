#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib> 
#include <ctime>   
#include <windows.h> 
#include <string> 

using namespace std;

//базовый класс
class Number {
protected:
    int value; //число

public:
    Number(int v) : value(v) {}

    virtual void show() const {
        cout << "  -> Обычное число: " << value << "\n";
    }

    virtual ~Number() {}
};
//класс:четное
class EvenNumber : public Number {
public:
    EvenNumber(int v) : Number(v) {
        cout << "  Создан объект: Четное число " << value << "\n";
    }

    void show() const override {
        cout << "  -> Проверка: Число " << value << " является ЧЕТНЫМ.\n";
    }
};
//класс:нечетное
class OddNumber : public Number {
public:
    OddNumber(int v) : Number(v) {
        cout << "  Создан объект: Нечетное число " << value << "\n";
    }

    void show() const override {
        cout << "  -> Проверка: Число " << value << " является НЕЧЕТНЫМ.\n";
    }
};
//добавление в хранилище
void add(vector<shared_ptr<Number>>& storage, shared_ptr<Number> obj) {
    storage.push_back(obj);
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(static_cast<unsigned int>(time(0)));

    vector<shared_ptr<Number>> storage;
    int count = 6; // сколько чисел сгенерируем

    cout << "--- генерация случайных чисел ---\n\n";

    for (int i = 0; i < count; i++) {
        int randomNum = rand() % 100;
        cout << "Шаг " << i + 1 << " (выпало " << randomNum << "):\n";

        if (randomNum % 2 == 0) {
            //четное
            auto obj = make_shared<EvenNumber>(randomNum);
            add(storage, obj);
        }
        else {
            //нечетное
            auto obj = make_shared<OddNumber>(randomNum);
            add(storage, obj);
        }
        cout << "\n";
    }

    cout << "--- результат проверки чисел ---\n\n";

    for (size_t i = 0; i < storage.size(); i++) {
        cout << "Объект №" << i + 1 << ":\n";
        storage[i]->show();
    }

    cout << "\n--- освобождение ресурсов ---\n";
    storage.clear();
    cout << "Все объекты удалены. Программа завершена.\n";

    return 0;
}
