#include <iostream> 
#include <cstring> // Подключение библиотеки для работы с строками

using namespace std; 

class String 
{
private:
    char* data; // Указатель на данные строки

public:
    String(const char* str = "") // Конструктор с параметром по умолчанию
    { 
        data = new char[strlen(str) + 1]; // Выделение памяти для данных строки
        strcpy_s(data, strlen(str) + 1, str); // Копирование строки str в data
    }

    String(const String& other) // Конструктор копирования
    { 
        data = new char[strlen(other.data) + 1]; // Выделение памяти для копии данных
        strcpy_s(data, strlen(other.data) + 1, other.data); // Копирование данных из other.data в data
    }

    String(String&& other) noexcept : data(nullptr) // Конструктор перемещения
    { 
        swap(data, other.data); // Обмен указателей на данные
    }

    String& operator=(const String& other) // Оператор присваивания для копирования
    { 
        if (this != &other) // Проверка на самоприсваивание
        { 
            delete[] data; // Очистка текущих данных
            data = new char[strlen(other.data) + 1]; // Выделение памяти для новых данных
            strcpy_s(data, strlen(other.data) + 1, other.data); // Копирование данных из other.data в data
        }
        return *this; // Возврат ссылки на текущий объект
    }

    String& operator=(String&& other) noexcept // Оператор присваивания для перемещения
    { 
        if (this != &other) // Проверка на самоприсваивание
        { 
            delete[] data; // Очистка текущих данных
            data = nullptr; // Установка указателя на nullptr
            swap(data, other.data); // Обмен указателей на данные
        }
        return *this; // Возврат ссылки на текущий объект
    }

    ~String() // Деструктор
    { 
        delete[] data; // Освобождение памяти
    }

    void print() const // Метод для вывода данных
    { 
        cout << data << endl; // Вывод данных на экран
    }
};

int main() // Точка входа в программу
{ 
    setlocale(LC_ALL, "Russian"); // Установка русской локали

    String str1("ПрЕвЕд"); // Создание объекта str1 с инициализацией строкой "ПрЕвЕд"
    String str2 = str1; // Создание объекта str2 через конструктор копирования
    String str3(std::move(str2)); // Создание объекта str3 через конструктор перемещения

    str1.print(); // Вывод данных объекта str1
    str3.print(); // Вывод данных объекта str3 (так как str2 был перемещен)

    return 0; // Возврат из функции main
}