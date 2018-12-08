#include <iostream>


int main() {
    char array[6] = "hello";
    char* pointer = array;
    std::cout << sizeof(array);
    std::cout << sizeof(pointer);
}