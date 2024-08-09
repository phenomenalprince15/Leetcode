#include <iostream>

#include "LinkedList.h"

int main() {
    LinkedList list;
    list.addAtHead(1);
    list.addAtHead(2);
    list.addAtHead(3);

    std::cout << "Linked list: ";
    list.display();

    list.deleteValue(2);

    std::cout << "Linked list after deletion: ";
    list.display();

    return 0;
}
