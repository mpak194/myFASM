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
    // �������� ������ ��� ������.
    if(watered.find(flower) -> second == 0)
    {
        watered.insert(make_pair(flower, true));
        cout << "[" << watered.size() << "] �������� 1 ����� ������ " << flower << "\n";
    }
    sem_post(&mySemafore);
}

void watering_by_2(int flower)
{
    sem_wait(&mySemafore);
    this_thread::sleep_for(chrono::milliseconds(100));
    // �������� ������ ��� ������.
    if(watered.find(flower) -> second == 0)
    {
        watered.insert(make_pair(flower, true));
        cout << "[" << watered.size() << "] �������� 2 ����� ������ " << flower << "\n";
    }
    sem_post(&mySemafore);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    // ����� ������.
    int flower1, flower2;
    sem_init(&mySemafore, 0, 1);

    while(watered.size() != 40)
    {
        // ��������� ������ ��� ������.
        flower1 = rand() % 40 + 1;
        flower2 = rand() % 40 + 1;
        if (flower1 != flower2)
        {
            // ������ 2 �������.
            thread gardener1(&watering_by_1, flower1);
            thread gardener2(&watering_by_2, flower2);
            gardener1.join();
            gardener2.join();
        }
    }
    return 0;
}
