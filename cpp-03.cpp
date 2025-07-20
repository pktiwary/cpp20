#include <iostream>
#include <thread>
#include <future>

// Function that will run in a separate thread
void calculateSquare(std::promise<int> prom, int value) {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int result = value * value;
    // Set the result in the promise
    prom.set_value(result);
}

int main() {
    // Create a promise object
    std::promise<int> prom;

    // Get the future associated with the promise
    std::future<int> fut = prom.get_future();

    int number = 7;

    // Launch a thread and pass the promise and value
    std::thread t(calculateSquare, std::move(prom), number);

    // Do other work here if needed...

    // Wait for the result from the thread
    int square = fut.get(); // This will block until set_value is called

    std::cout << "Square of " << number << " is " << square << std::endl;

    t.join(); // Wait for the thread to finish

    return 0;
}