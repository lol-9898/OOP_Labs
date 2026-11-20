#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    const int n = 10;
    short* arr = new short[n];

    cout << "Введите 10 чисел массива (через enter):\n";
    for (int i = 0; i < n; i++) {
        cout << "Элемент " << i << ": ";
        cin >> arr[i];

        if (cin.fail()) {
            cin.clear();               // сбросить состояние ошибки
            cin.ignore(10000, '\n');   // выбросить плохой ввод из буфера
            cout << "Ошибка: введите число!\n";
            i--;                       // повторить ввод этого же элемента
        }
    }
    // Вывод 
    cout << "\nСодержимое массива:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";

    // Адрес начала массива
    cout << "\nАдрес начала массива: " << (void*)arr << "\n";
    cout << "Размер одного элемента (short): " << sizeof(short) << " байт\n";

    cout << "\nРасстояние элементов от начала массива:\n";
    for (int i = 0; i < n; i++) {
        long long offset = (char*)&arr[i] - (char*)arr;
        cout << "Элемент " << i << ": смещение " << offset
            << " байт, адрес " << (void*)&arr[i] << "\n";
    }

    delete[] arr;  //защита от утечки
    return 0;
}
