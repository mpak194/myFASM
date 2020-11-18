#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <chrono>
#include <mutex>

using namespace std;

string library[100][100][100];
string common_catalog[100][100][100];
mutex mtx;

// Метод ввода целочисленного значения.
int GetIntValue(string str, int min_value, int max_value)
{
    cout << str << "[" << min_value << ", "
         << max_value << "]" << endl;
    int n; cin >> n;
    if (n >= min_value && n <= max_value)
        return n;
    else
    {
        cout << "Введено неверное значение!" << endl;
        exit(1);
    }
}

// Метод генерации названия книги.
string CreateBookName()
{
    int length_name = 5 + rand() % 11;
    string name;
    for (int i = 0; i < length_name; i++)
    {
        if (i == 0)
            name += (char)(65 + rand() % 25);
        name += (char)(97 + rand() % 25);
    }
    return name;
}

// Создание библиотеки и заполнение имен книг.
void CreateLibrary(int count_rows, int count_bookcase, int count_book)
{
    for (int i = 0; i < count_rows; i++)
    {
        for (int j = 0; j < count_bookcase; j++)
        {
            for (int k = 0; k < count_book; k++)
            {
                library[i][j][k] = CreateBookName();
            }
        }
    }
}

// Метод заполнения каталога по одному ряду.
void GetCatalog(int row, int count_bookcase, int count_book)
{
    mtx.lock();
    for (int i = 0; i < count_bookcase; i++)
    {
        for (int j = 0; j < count_book; j++)
        {
            this_thread::sleep_for(chrono::milliseconds(500));
            common_catalog[row][i][j] = library[row][i][j];
        }
    }
    mtx.unlock();
}

// Метод вывода каталога на экран.
void DisplayCatalog(int count_rows, int count_bookcase, int count_book)
{
    for (int i = 0; i < count_rows; i++)
    {
        cout << "Ряд " << i + 1 << endl;
        for (int j = 0; j < count_bookcase; j++)
        {
            cout << "\tШкаф " << j + 1 << endl;
            for (int k = 0; k < count_book; k++)
            {
                cout << "\t\tКнига " << library[i][j][k] << endl;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    int count_rows = GetIntValue("Введите число рядов: ", 1, 20);
    int count_bookcase = GetIntValue("Введите число книжных шкафов: ", 1, 10);
    int count_book = GetIntValue("Введите число книг в шкафу: ", 1, 20);

    CreateLibrary(count_rows, count_bookcase, count_book);

    cout << "Для составления каталога необходимо студентов: " << count_rows << endl;

    vector<thread> ths;
    for (int i = 0; i < count_rows; i++)
    {
        ths.push_back(std::thread(GetCatalog, i, count_bookcase, count_book));
    }
    for (int i = 0; i < ths.size(); i++)
        ths[i].join();

    DisplayCatalog(count_rows, count_bookcase, count_book);
    return 0;
}
