#include <iostream>
#include <cmath>
#include "state.h"

using namespace std;

class DecisionMaker {
    private:
    string style;
    bool doMove;

    public:
    DecisionMaker(string style){
        this->style = style;
        doMove = false;
    }

    string getDecision(State* matchState, string arenaSide, int rn){
        int chanceToMove = rn;
        int chanceToHit = rn;
        int chanceToGoAfterOpponent = rn;
        int chanceToCollide = rn;
        int chanceToGoRight = rn;
        int chanceToGoLeft = rn;
        //cout<<rn<<endl;
        //matchState->printState();
        //cout<<matchState->getRotationAngle()<<endl;
        if (matchState->getIsColliding()) 
        {
            if (chanceToHit < 30){
                return "oi-zuki";
            } else {
                return "block";
            }
        
        } else if (chanceToCollide < 2) {

            return goAfterOpponent(matchState, arenaSide);

        } else if (chanceToGoAfterOpponent < 25) {

            if (matchState->calculateDistanceToOpponent() <= 80) {

                if(matchState->getRotationAngle() >= 89 && matchState->getRotationAngle() <=91){

                    if (chanceToGoLeft < 25){
                        return "right";
                    } else {
                        return "backward";
                    }
                }

                return (chanceToMove % 2 == 0) ?  "left" : "right";

            } else {
                return goAfterOpponent(matchState, arenaSide);
            }


        } else {
            return "none";
        }
    }

    string goAfterOpponent(State* matchState, string arenaSide){
        int opponentX = matchState->getOpponentPosition()->x;
        int opponentY = matchState->getOpponentPosition()->y;
        int myX = matchState->getKaratekaPosition()->x;
        int myY = matchState->getKaratekaPosition()->y;

        // Calculate difference in x and y coordinates
        int deltaX = myX - opponentX;
        int deltaY = myY - opponentY;

        //cout<<"Delta X = "<<deltaX<<endl;
        //cout<<"Delta Y = "<<deltaY<<endl;

        if (arenaSide == "right"){

            if (deltaX > 0) {
                return "forward";
                } else if (deltaX <= 45) {
                return "backward";
            } else {
                // No movement required
                return "none";
            }

            if (deltaY < 0) {
                return "right";
            } else if (deltaY > 0) {
                    return "left";
            } else {
                // No movement required
                return "none";
            }

        } else {
            if (deltaX > 0) {
                return "backward";
            } else if (deltaX <= 45) {
                return "forward";
            } else {
                // No movement required
                return "none";
            }

            if (deltaY < 0) {
                return "left";
            } else if (deltaY > 0) {
                    return "right";
            } else {
                // No movement required
                return "none";
            }
        }
    }


   


};





