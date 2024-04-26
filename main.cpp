#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

int sharedData = 0; // Общая переменная для чтения и записи

void writerFunction()// Функция для записи данных в общую переменную 
{
    for (int i = 0; i < 5; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Блокировка мьютекса
        sharedData = i;
        std::cout << "Записал: " << i << std::endl;
    }
}

void readerFunction()// Функция для чтения данных из общей переменной 
{
    for (int i = 0; i < 5; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Блокировка мьютекса
        std::cout << "Прочитал: " << sharedData << std::endl;
    }
}

int main() {
    std::thread writerThread(writerFunction); // Поток для записи данных
    std::thread readerThread(readerFunction); // Поток для чтения данных

    writerThread.join();
    readerThread.join();

    return 0;
}