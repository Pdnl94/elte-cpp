#include <iostream>
#include "List.h"

int main() {
    auto *a = new List<int>(1);
    //auto *b = new List<int>;
    //b->data = 2;
    //a->next = b;
    a->add(3);

    a->add(2);
    a->add(3);
    a->add(4);

    std::cout << "a.size: " << a->size() << std::endl;
    std::cout << "a.get(3): " << a->getNext()->get(3) << std::endl;

    std::cout << "a.size: " << a->size() << std::endl;


    std::cout << "Hello, World!" << std::endl;
    return 0;
}