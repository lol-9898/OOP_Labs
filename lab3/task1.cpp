#include <iostream>
#include <string>
#include <vector>
#include <memory> 
#include <utility> 
#include <windows.h> 

using namespace std;

//базовый класс
class Detail {
protected:
    string name;

    Detail(const string& n) : name(n) {}

public:
    string getName() const { return name; }

    virtual void show() const {
        cout << "  - Продукт: " << name << "\n";
    }

    virtual ~Detail() {}

    template <typename T, typename... Args>
    friend shared_ptr<T> create(Args&&... args);
};
//класс:готовое блюдо
class Assembly : public Detail {
private:
    vector<shared_ptr<Detail>> ingredients;

    Assembly(const string& n) : Detail(n) {
        cout << "  СОБРАНО БЛЮДО: " << name << "\n";
    }

public:
    void addIngredient(shared_ptr<Detail> ingr) {
        ingredients.push_back(ingr);
    }

    void show() const override {
        cout << "    БЛЮДО: " << name << " (состоит из " << ingredients.size() << " продуктов)\n";
        cout << "      Состав: ";
        for (size_t i = 0; i < ingredients.size(); i++) {
            cout << ingredients[i]->getName();
            if (i < ingredients.size() - 1) cout << ", ";
        }
        cout << "\n";
    }

    template <typename T, typename... Args>
    friend shared_ptr<T> create(Args&&... args);
};

//друж. функция
template <typename T, typename... Args>
shared_ptr<T> create(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<shared_ptr<Detail>> storage;

    cout << "--- процесс приготовления ---\n\n";

    //бургер
    cout << "1. Готовим бургер:\n";

    auto kotleta = create<Detail>("Котлета");
    cout << "  Создан продукт: Котлета\n";

    auto bulochka = create<Detail>("Булочка");
    cout << "  Создан продукт: Булочка\n";

    auto syr = create<Detail>("Сыр");
    cout << "  Создан продукт: Сыр\n";

    auto ogurec = create<Detail>("Огурец");
    cout << "  Создан продукт: Огурец\n";

    //складываем продукты
    storage.push_back(kotleta);
    storage.push_back(bulochka);
    storage.push_back(syr);
    storage.push_back(ogurec);

    cout << "\n";

    //собираем бургер
    auto burger = create<Assembly>("Бургер Чизбургер");
    burger->addIngredient(kotleta);
    burger->addIngredient(bulochka);
    burger->addIngredient(syr);
    burger->addIngredient(ogurec);
    storage.push_back(burger);

    cout << "\n";

    //картошка
    cout << "2. Готовим картошку фри:\n";

    auto kartoshka = create<Detail>("Картофель");
    cout << "  Создан продукт: Картофель\n";

    auto maslo = create<Detail>("Масло");
    cout << "  Создан продукт: Масло\n";

    auto sous = create<Detail>("Соус");
    cout << "  Создан продукт: Соус\n";

    //складываем продукты
    storage.push_back(kartoshka);
    storage.push_back(maslo);
    storage.push_back(sous);

    cout << "\n";

    //собираем картошку
    auto fries = create<Assembly>("Картошка фри с соусом");
    fries->addIngredient(kartoshka);
    fries->addIngredient(maslo);
    fries->addIngredient(sous);
    storage.push_back(fries);

    //вывод
    cout << "\n--- вывод из хранилища ---\n\n";
    for (const auto& item : storage) {
        item->show();
    }

    return 0;
}
