#include <iostream>
#include <semaphore.h>
#include <ctime>
#include <map>
#include <thread>
#include <vector>
#include <random>

using namespace std;

sem_t mySemafore;
map<int, bool> watered;

void watering_by_1(int flower)
{
    sem_wait(&mySemafore);
    this_thread::sleep_for(chrono::milliseconds(100));
    // Проверка цветка для полива.
    if(watered.find(flower) -> second == 0)
    {
        watered.insert(make_pair(flower, true));
        cout << "[" << watered.size() << "] Садовник 1 полил цветок " << flower << "\n";
    }
    sem_post(&mySemafore);
}

void watering_by_2(int flower)
{
    sem_wait(&mySemafore);
    this_thread::sleep_for(chrono::milliseconds(100));
    // Проверка цветка для полива.
    if(watered.find(flower) -> second == 0)
    {
        watered.insert(make_pair(flower, true));
        cout << "[" << watered.size() << "] Садовник 2 полил цветок " << flower << "\n";
    }
    sem_post(&mySemafore);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    // Номер цветка.
    int flower1, flower2;
    sem_init(&mySemafore, 0, 1);

    while(watered.size() != 40)
    {
        // Генерация цветка для полива.
        flower1 = rand() % 40 + 1;
        flower2 = rand() % 40 + 1;
        if (flower1 != flower2)
        {
            // Запуск 2 потоков.
            thread gardener1(&watering_by_1, flower1);
            thread gardener2(&watering_by_2, flower2);
            gardener1.join();
            gardener2.join();
        }
    }
    return 0;
}
