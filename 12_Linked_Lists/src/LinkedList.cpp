#include "LinkedList.h"
#include <stdexcept>
#include <iostream>

LinkedList::LinkedList() : head(nullptr) {}

int LinkedList::get(int index) {
    Node* temp = head;
    int count = 0;

    while (temp != nullptr) {
        if (count == index) {
            return temp->data;
        }
        temp = temp->next;
        count++;
    }
    throw std::out_of_range("Index out of range");
}

void LinkedList::addAtHead(int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode; 
}

void LinkedList::addAtTail(int data) {
    
}

void LinkedList::addAtIndex(int index, int val) {

}

void LinkedList::display() const {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << "--->";
        temp = temp->next;
    }
    std::cout << "nullptr";
    std::cout << std::endl;
}

void LinkedList::deleteValue(int val) {
    Node* temp = head;
    Node* prev = nullptr;

    // If head node itself holds the value
    if (temp != nullptr && temp->data == val) {
        head = temp->next;
        delete temp;
        return;
    }

    // Search for the value to be deleted
    while (temp != nullptr && temp->data != val) {
        prev = temp;
        temp = temp->next;
    }

    // If value was not found
    if (temp == nullptr) return;

    // Unlink the node from the linked list
    prev->next = temp->next;
    delete temp;
}

void LinkedList::deleteAtIndex(int index) {

}

void LinkedList::search(int data) {

}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}
