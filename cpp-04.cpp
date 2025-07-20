#include <iostream>
#include <utility>
#include <cstring>

class SmartClass {
private:
    char* data;
public:
    // Constructor
    SmartClass(const char* str) {
        data = new char[std::strlen(str) + 1];
        std::strcpy(data, str);
        std::cout << "Constructed: " << data << std::endl;
    }

    // Copy Constructor
    SmartClass(const SmartClass& other) {
        data = new char[std::strlen(other.data) + 1];
        std::strcpy(data, other.data);
        std::cout << "Copied: " << data << std::endl;
    }

    // Move Constructor
    SmartClass(SmartClass&& other) noexcept : data(other.data) {
        other.data = nullptr;
        std::cout << "Moved (ctor): " << (data ? data : "null") << std::endl;
    }

    // Copy Assignment
    SmartClass& operator=(const SmartClass& other) {
        if (this != &other) {
            delete[] data;
            char* newData = new char[std::strlen(other.data) + 1];
            std::strcpy(newData, other.data);
            std::swap(data, newData);
        }
        std::cout << "Copy assigned: " << data << std::endl;
        return *this;
    }

    // Move Assignment
    SmartClass& operator=(SmartClass&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            other.data = nullptr;
        }
        std::cout << "Move assigned: " << (data ? data : "null") << std::endl;
        return *this;
    }

    // Destructor
    ~SmartClass() {
        std::cout << "Destroyed: " << (data ? data : "null") << std::endl;
        delete[] data;
    }

    void print() const {
        std::cout << "Data: " << (data ? data : "null") << std::endl;
    }
};

int main() {
    SmartClass a("Hello");
    SmartClass b = a; // Copy
    SmartClass c = std::move(a); // Move

    SmartClass d("World");
    d = b; // Copy assignment
    d = std::move(c); // Move assignment

    d.print();
    b.print();
    a.print();
    c.print();

    return 0;
}