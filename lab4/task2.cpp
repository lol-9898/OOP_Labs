#include <iostream>
#include <vector>
#include <string>
#include <windows.h> 
#include <stdexcept> 

using namespace std;

//иерархия классов
class ProgramError {
public:
    virtual void showError() const = 0;
    virtual ~ProgramError() {}
};

class NoPrivileges : public ProgramError {
public:
    void showError() const override { cout << "Ошибка: Недостаточно привилегий." << endl; }
};

class ConversionError : public ProgramError {
public:
    void showError() const override { cout << "Ошибка: Ошибка преобразования." << endl; }
};

class ValueConversionError : public ProgramError {
public:
    void showError() const override { cout << "Ошибка: Невозможно преобразовать значение." << endl; }
};

class InterfaceCastError : public ProgramError {
public:
    void showError() const override { cout << "Ошибка: Невозможно привести к интерфейсу." << endl; }
};

//шаблонный класс(хранилище указателей)
template <typename T>
class MyArray {
private:
    vector<T*> data;
public:
    void add(T* item) { data.push_back(item); }

    T* operator[](int index) {
        if (index < 0 || index >= data.size()) {
            throw out_of_range("Индекс " + to_string(index) + " вне диапазона массива!");
        }
        return data[index];
    }

    int size() const { return data.size(); }

    ~MyArray() {
        for (T* item : data) { delete item; }
        data.clear();
    }
};

//domain_error
void applyDiscount(double discountPercent) {
    if (discountPercent < 0 || discountPercent > 100) {
        throw domain_error("Недопустимый размер скидки. Скидка может быть только от 0 до 100.");
    }
    cout << "Скидка " << discountPercent << "% успешно применена." << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "Проверка массива ошибок:" << endl;

    MyArray<ProgramError> errors;
    errors.add(new NoPrivileges());
    errors.add(new ConversionError());
    errors.add(new ValueConversionError());
    errors.add(new InterfaceCastError());

    for (int i = 0; i < errors.size(); i++) {
        cout << "[" << i << "] ";
        errors[i]->showError();
    }

    cout << endl;

    cout << "Проверка обработки исключений:" << endl;

    try {
        cout << "Применим скидку 15%:" << endl;
        applyDiscount(15.0);
    }
    catch (const domain_error& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    cout << endl;

    try {
        cout << "Применим скидку 150%:" << endl;
        applyDiscount(150.0);
    }
    catch (const domain_error& e) {
        cout << "ПОЙМАНО ИСКЛЮЧЕНИЕ: " << e.what() << endl;
    }

    return 0;
}
