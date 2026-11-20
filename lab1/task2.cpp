#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;
//класс: книга
class Book {
protected:
    string author;   // автор
    string title;    // название
    string type;     // "художественная" или "техническая"

public:
    Book(const string& a, const string& t, const string& ty) {
        if (a.empty() || t.empty()) {
            throw invalid_argument("Ошибка: у книги пустой автор или название!");
        }
        author = a;
        title = t;
        type = ty;
    }
    virtual ~Book() {}

    string getAuthor() const { return author; }
    string getTitle()  const { return title; }
    string getType()   const { return type; }

    virtual void print() const {
        cout << "Автор:      " << author << "\n";
        cout << "Название:   " << title << "\n";
        cout << "Тип:        " << type << "\n";
        cout << "\n";
    }
};

//наследник: худ. книга
class FictionBook : public Book {
public:
    FictionBook(const string& a, const string& t)
        : Book(a, t, "художественная") {
    }
};

//наследник: тех. книга
class TechnicalBook : public Book {
public:
    TechnicalBook(const string& a, const string& t)
        : Book(a, t, "техническая") {
    }
};

//класс: библиотека
class Library {
private:
    vector<Book*> books;  // указатели на книги 

public:
    void addBook(Book* book) {
        books.push_back(book);
    }

    void printAll() const {
        cout << "\nКниги в библиотеке:\n\n";
        for (const auto& book : books) {
            book->print();
        }
        cout << "Итог:\n";
        cout << "\n";
    }

    //Пункт Б
    void countWithSwitch() const {
        int fiction = 0;
        int technical = 0;

        for (const auto& book : books) {
            int code;
            if (book->getType() == "художественная")       code = 1;
            else if (book->getType() == "техническая")     code = 2;
            else                                            code = 0;

            switch (code) {
            case 1: fiction++;   break;
            case 2: technical++; break;
            default:             break;
            }
        }

        cout << "[через switch]   Художественных: " << fiction
            << ", технических: " << technical << "\n";
    }

    //Пункт В
    void countWithoutSwitch() const {
        int fiction = 0;
        int technical = 0;

        for (const auto& book : books) {
            if (book->getType() == "художественная")       fiction++;
            else if (book->getType() == "техническая")     technical++;
        }

        cout << "[без switch]     Художественных: " << fiction
            << ", технических: " << technical << "\n";
    }

    //защита от утечки
    ~Library() {
        for (auto& book : books) {
            delete book;
        }
        books.clear();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Library lib;

    try {
        lib.addBook(new FictionBook("Булгаков", "Мастер и Маргарита"));
        lib.addBook(new FictionBook("Оруэлл", "1984"));
        lib.addBook(new FictionBook("Хемингуэй", "Старик и море"));

        lib.addBook(new TechnicalBook("Макконнелл", "Совершенный код"));
        lib.addBook(new TechnicalBook("Бхаргава", "Грокаем алгоритмы"));
        lib.addBook(new TechnicalBook("Дейкстра", "Дисциплина программирования"));
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << "\n";
    }

    lib.printAll();
    lib.countWithSwitch();
    lib.countWithoutSwitch();

    return 0;
}
