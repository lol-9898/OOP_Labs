#include <iostream>
#include <vector>
#include <string>
#include <windows.h> 

using namespace std;

//иерархия классов
class ProgramError {
public:
    virtual void showError() const = 0;
    virtual ~ProgramError() {}
};

class NoPrivileges : public ProgramError {
public:
    void showError() const override {
        cout << "Ошибка: Недостаточно привилегий." << endl;
    }
};

class ConversionError : public ProgramError {
public:
    void showError() const override {
        cout << "Ошибка: Ошибка преобразования." << endl;
    }
};

class ValueConversionError : public ProgramError {
public:
    void showError() const override {
        cout << "Ошибка: Невозможно преобразовать значение." << endl;
    }
};

class InterfaceCastError : public ProgramError {
public:
    void showError() const override {
        cout << "Ошибка: Невозможно привести к интерфейсу." << endl;
    }
};

//шаблонный класс(хранилище указателей)
template <typename T>
class MyArray {
private:
    vector<T*> data;

public:
    void add(T* item) {
        data.push_back(item);
    }

    T* operator[](int index) {
        if (index < 0 || index >= data.size()) {
            throw out_of_range("Индекс " + to_string(index) + " вне диапазона массива!");
        }
        return data[index];
    }

    int size() const {
        return data.size();
    }

    ~MyArray() {
        for (T* item : data) {
            delete item;
        }
        data.clear();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MyArray<ProgramError> errorStorage;

    errorStorage.add(new NoPrivileges());
    errorStorage.add(new ConversionError());
    errorStorage.add(new ValueConversionError());
    errorStorage.add(new InterfaceCastError());

    cout << "Содержимое хранилища:" << endl;
    for (int i = 0; i < errorStorage.size(); i++) {
        cout << "[" << i << "] ";
        errorStorage[i]->showError();
    }

    cout << "\nПопытка обратиться к несуществующему элементу (индекс 10):" << endl;
    try {
        errorStorage[10]->showError();
    }
    catch (const out_of_range& e) {
        cout << "Исключение: " << e.what() << endl;
    }

    cout << "\nПрограмма завершена. Память очищена." << endl;
    return 0;
}
