#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList {
    private:
        Node* head;
    
    public:
        LinkedList();
        
        int get(int index);

        void addAtHead(int data);
        void addAtTail(int data);
        void addAtIndex(int index, int val);

        void display() const;
        
        void deleteValue(int val);
        void deleteAtIndex(int index);

        void search(int data);

        ~LinkedList();
};

#endif
