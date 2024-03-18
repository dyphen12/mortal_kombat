#include <iostream>
#include <cmath>
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
    if (matchState->getIsColliding()) {
        return "none"; // No movement if colliding
    } else {
        int opponentX = matchState->getOpponentPosition()->x;
        int opponentY = matchState->getOpponentPosition()->y;
        int myX = matchState->getKaratekaPosition()->x;
        int myY = matchState->getKaratekaPosition()->y;

        // Calculate difference in x and y coordinates
        int deltaX = myX - opponentX;
        int deltaY = myY - opponentY;

        cout<<"Delta X = "<<deltaX<<endl;
        cout<<"Delta Y = "<<deltaY<<endl;

        /*
        // Determine movement direction based on relative positions
        if (deltaX < 0) {
            return "right";
        } else if (deltaX > 0) {
            return "left";
        } else if (deltaY < 0) {
            return "down";
        } else if (deltaY > 0) {
            return "up";
        } else {
            // No movement required
            return "none";
        }
        */

       if (deltaX > 0) {
            return "forward";
        } else if (deltaX <= 45) {
            return "backward";
        } else {
            // No movement required
            return "none";
        }

       //return "none";

        
    }
}

string getXMovement(State* matchState) {
    if (matchState->getIsColliding()) {
        return "none"; // No movement if colliding
    } else {
        int opponentX = matchState->getOpponentPosition()->x;
        int opponentY = matchState->getOpponentPosition()->y;
        int myX = matchState->getKaratekaPosition()->x;
        int myY = matchState->getKaratekaPosition()->y;

        // Calculate difference in x and y coordinates
        int deltaX = myX - opponentX;
        int deltaY = myY - opponentY;

        cout<<"Delta X = "<<deltaX<<endl;
        cout<<"Delta Y = "<<deltaY<<endl;

        /*
        // Determine movement direction based on relative positions
        if (deltaX < 0) {
            return "right";
        } else if (deltaX > 0) {
            return "left";
        } else if (deltaY < 0) {
            return "down";
        } else if (deltaY > 0) {
            return "up";
        } else {
            // No movement required
            return "none";
        }
        */

       if (deltaX > 0) {
            return "forward";
        } else if (deltaX <= 45) {
            return "backward";
        } else {
            // No movement required
            return "none";
        }

       //return "none";

        
    }
}

string getYMovement(State* matchState) {
    if (matchState->getIsColliding()) {
        return "none"; // No movement if colliding
    } else {
        int opponentX = matchState->getOpponentPosition()->x;
        int opponentY = matchState->getOpponentPosition()->y;
        int myX = matchState->getKaratekaPosition()->x;
        int myY = matchState->getKaratekaPosition()->y;

        // Calculate difference in x and y coordinates
        int deltaX = myX - opponentX;
        int deltaY = myY - opponentY;

        //cout<<"Delta X = "<<deltaX<<endl;
        //cout<<"Delta Y = "<<deltaY<<endl;

        /*
        // Determine movement direction based on relative positions
        if (deltaX < 0) {
            return "right";
        } else if (deltaX > 0) {
            return "left";
        } else if (deltaY < 0) {
            return "down";
        } else if (deltaY > 0) {
            return "up";
        } else {
            // No movement required
            return "none";
        }
        */

       if (deltaY < 0) {
            return "left";
        } else if (deltaY > 0) {
            return "right";
        } else {
            // No movement required
            return "none";
        }

       //return "none";

        
    }
}


};





