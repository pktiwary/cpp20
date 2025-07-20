#include <iostream>

#include <thread>

void printHello() {
    std::cout << "Hello, World from thread!" << std::endl;
}

int main() {
    std::thread t(printHello);
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some work in main
    t.join();
    std::cout << "Hello, World from main!" << std::endl;
    return 0;
}