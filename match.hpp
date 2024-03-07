#include <iostream>
#include "karateka.hpp"

using namespace std;

class Match {

    protected:
    Karateka *k1;
    Karateka *k2;
    Karateka *winner;
    int k1R;
    int k2R;

    public:
    Match(Karateka *k1, Karateka *k2){
        this->k1 = k1;
        this->k2 = k2;

        this->k1->initialize(k2);
        this->k2->initialize(k1);
    }

    void simulateMatch(){

        cout<<"Simulating Match"<<endl;
        cout<<k1->getName()<<" VS "<<k2->getName()<<endl;
    }

    void printMatchNames(){
        cout<<k1->getName()<<endl;
        cout<<k2->getName()<<endl;
    }


};