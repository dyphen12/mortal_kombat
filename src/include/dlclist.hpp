#include <iostream>
#include "karateka.h"

// Node structure for the doubly linked circular list
struct Node {
    Node(Karateka karateka) : karateka(karateka), prev(nullptr), next(nullptr) {}

    Karateka karateka;
    Node* prev;
    Node* next;
};


class DLCList {
private:
    Node* head;

public:
    DLCList() : head(nullptr) {}  // Initialize head to nullptr

    void push(Karateka karateka) {
        Node* fresh = new Node(karateka);

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

        Node* current = head;
        Node* todelete = current->prev;

        if (current == current->next) {  // Handle single-node case
            delete head;
            head = nullptr;
        } else {
            current->prev = current->prev->prev;
            current->prev->next = current;
        }

        delete todelete; // Delete last node
    }

    // Implement sorting logic within the do-while loop in sort
    // ... (Replace the comment with your sorting implementation)

     void sort(bool reverse){
        if (head == NULL){
            cout<<"The list is empty!"<<endl;

        }else{ 

            if(!reverse){ // Sort in ascending order
                Node* current = head;
                Node* majorNode = current;
                //cout<<"Sorting airplanes in ascending order by ID!"<<endl;

                do{
                    //Node* majorNode = current;

                    
                    if (current->karateka.getID() > majorNode->karateka.getID())
                    majorNode = current;
                    current = current->next;


                } while (current != head);

                //cout<<"Major ID Node is: "<< majorNode->airplane1.getPilot();

            } 
            
        }
 
    }


    void printList() {
        Node* current = head;

        if (current == nullptr) {
            cout << "List is empty" << endl;
        } else {
            do {
                // Access details of the Karateka object using methods from match.hpp
                cout << "Karateka details: ";
                // Replace the following line with appropriate method calls from match.hpp
                cout << "ID: " << current->karateka.getID() << ", Points: " << current->karateka.getPoints() << endl;
                current = current->next;
            } while (current != head); // Continue until you reach the head again
        }
    }
};
