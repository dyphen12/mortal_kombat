#include <iostream>
#include "karateka.h"

// Node structure for the doubly linked circular list

template<typename T>
struct Node {
    Node(T* data) : data(data), prev(nullptr), next(nullptr) {}

    T *data;
    Node* prev;
    Node* next;
};


template<typename T>
class DLCList {
private:
    Node<T>* head;

public:
    DLCList() : head(nullptr) {}  // Initialize head to nullptr

    void push(T* data) {
        Node<T>* fresh = new Node(data);

        if (head == nullptr) {
            fresh->next = fresh;  // Set next and prev of the first node to itself
            fresh->prev = fresh;
            head = fresh;
        } else {
            fresh->next = head;
            fresh->prev = head->prev;
            head->prev->next = fresh;
            head->prev = fresh;
        }
    }

    void pop() {
        if (head == nullptr) {
            cout << "The list is empty!" << endl;
            return; // Avoid unnecessary operations if empty
        }

        Node<T>* current = head;
        Node<T>* todelete = current->prev;

        if (current == current->next) {  // Handle single-node case
            delete head;
            head = nullptr;
        } else {
            current->prev = current->prev->prev;
            current->prev->next = current;
        }

        delete todelete; // Delete last node
    }

    T* pop2() {
        if (head == nullptr) {
            cout << "The list is empty!" << endl;
            return nullptr; // Avoid unnecessary operations if empty
        }

        Node<T>* current = head;
        Node<T>* todelete = current->prev;
        T *dummy;

        if (current == current->next) {  // Handle single-node case
            dummy = head->data;
            delete head;
            head = nullptr;
            return dummy;

        } else {
            current->prev = current->prev->prev;
            current->prev->next = current;
        }

        dummy = todelete->data;
        delete todelete; // Delete last node
        return dummy;
    }


    void printList(Karateka* dummy) {
        Node<T>* current = head;

        if (current == nullptr) {
            cout << "List is empty" << endl;
        } else {
            do {
                // Access details of the Karateka object using methods from match.hpp
                cout << "Karateka details: ";
                // Replace the following line with appropriate method calls from match.hpp
                cout << "Name: " << current->data->getName() << ", Points: " << current->data->getPoints() << endl;
                current = current->next;
            } while (current != head); // Continue until you reach the head again
        }
    }

    int getLength(){
        Node<T>* current = head;
        if (current == nullptr) {            
            return 0;
        } else {
            int aux = 0;
            do {
                current = current->next;
                aux++;
            } while (current != head); // Continue until you reach the head again
            return aux;
        }

    }
};
