#include <iostream>
#include "match.h"
#include "dlclist.hpp"

using namespace std;



class Championship{
    private:
    DLCList* karatekaList;
    DLCList* topHalf;
    DLCList* bottomHalf;
    DLCList* finals;

    int contestants;
    int weight;


    public:
    Championship() : karatekaList(new DLCList) {
        cout<<"Championship Started!"<<endl;



    }  // Initialize during object creation


    void signUpKarateka(Karateka* karateka) {
    // Add the karateka to the list
    karatekaList->push(*karateka);  // Assuming karatekaList is a DLCList object
    }


    void printKaratekaList(){
        cout<<"print karateka list"<<endl;
        this->karatekaList->printList();
    }

    void topHalfRun(){
        
    }

    void bottomHalfRun(){

    }

    void finalsRun(){

    }


    

};


