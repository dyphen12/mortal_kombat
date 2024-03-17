#include <iostream>
#include "state.h"

using namespace std;

class DecisionMaker {
    private:
    string style;

    public:
    DecisionMaker(string style){
        this->style = style;
    }

    string getDecision(State* matchState){
        return "none";
    }

    string getMovement(State* matchState) {
        return "none";
    }

};





