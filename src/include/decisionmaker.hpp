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

    string getDecision(State* matchState, string arenaSide, int rn) {
    int chanceToMove = rn;
    int chanceToHit = rn;
    int chanceToGoAfterOpponent = rn;
    int chanceToCollide = rn;
    int chanceToGoRight = rn;
    int chanceToGoLeft = rn;
    int chanceToBlock = rn;
    int chanceToRetreat = rn;

    //cout<<"Rotation angle "<<arenaSide<<" : "<<matchState->getRotationAngle()<<endl;

    if(this->style == "Shotokan"){

        if (matchState->getIsColliding()) {
        // Adjust decision probabilities based on opponent's points and match state
        if (matchState->getOpponentPoints() > matchState->getKaratekaPoints() + 3) {
            if (chanceToHit < 12) {
                return "yoko-geri";
            } else if (chanceToHit < 16) {
                return "mae-geri";
            }
        } else if (matchState->getKaratekaPoints() > matchState->getOpponentPoints()) {
            if (chanceToBlock < 30) {
                return "block";
            } else{
                goAwayFromOpponent(matchState, arenaSide);
            }
        } else {
            // Adjust probabilities for different attacks or blocking
            if (chanceToHit < 10) {
                return "yoko-geri";
            } else if (chanceToHit < 15) {
                return "heiko-zuki";
            } else if (chanceToHit < 20) {
                return "mae-geri";
            } else if (chanceToHit < 25) {
                return "ura-zuki";
            } else {
                return "block";
            }
        }
    } else if (matchState->getKaratekaPoints() > matchState->getOpponentPoints() && matchState->calculateDistanceToOpponent() <= 60) {
        if (chanceToRetreat < 50){
            return goAwayFromOpponent(matchState, arenaSide);
        }
        
    } else if (chanceToCollide < 2) {
        return goAfterOpponent(matchState, arenaSide);
    } else if (matchState->getRotationAngle() > 88 && matchState->getRotationAngle() < 93) {
        // Adjust probabilities based on rotation angle and arena side
        //cout<<"Vertical Problem!"<<endl;
        return (chanceToMove % 2 == 0) ?  "backward-right" : "forward-left";
        
        
    } else if (matchState->getRotationAngle() >-93  && matchState->getRotationAngle() < -88) {
        // Adjust probabilities based on rotation angle and arena side
        //cout<<"Vertical Problem!"<<endl;
        return (chanceToMove % 2 == 0) ?  "forward-right" : "backward-left";
        
        
    } else if (chanceToGoAfterOpponent < 20) {
        // Adjust probabilities based on distance to opponent
        if (matchState->calculateDistanceToOpponent() <= 90) {
            return (chanceToMove % 2 == 0) ?  "left" : "right";
        } else {
            return goAfterOpponent(matchState, arenaSide);
        }
    } else if (matchState->calculateDistanceToOpponent() <= 48) {
        // Adjust probabilities for blocking based on distance to opponent
        if (chanceToBlock < 60) {
            return "block";
        } else {
            return "none";
        }
    } else {
        return "none";
    }
    return "none";

    } else {

        if (matchState->getIsColliding()) {
        // Adjust decision probabilities based on opponent's points and match state
        if (matchState->getOpponentPoints() > matchState->getKaratekaPoints() + 3) {
            if (chanceToHit < 12) {
                return "yoko-geri";
            } else if (chanceToHit < 16) {
                return "mae-geri";
            }
        } else if (matchState->getKaratekaPoints() > matchState->getOpponentPoints()) {
            if (chanceToBlock < 30) {
                return "block";
            } else {
                goAwayFromOpponent(matchState, arenaSide);
            }
        } else {
            // Adjust probabilities for different attacks or blocking
            if (chanceToHit < 4) {
                return "yoko-geri";
            } else if (chanceToHit < 6) {
                return "mawashi-zuki";
            } else if (chanceToHit < 8) {
                return "gyaku-zuki";
            } else if (chanceToHit < 12) {
                return "mae-geri";
            } else if (chanceToHit < 20) {
                return "oi-zuki";
            } else {
                return "block";
            }
        }
    } else if (matchState->getKaratekaPoints() > matchState->getOpponentPoints() && matchState->calculateDistanceToOpponent() <= 60) {
        if (chanceToRetreat < 50){
            return goAwayFromOpponent(matchState, arenaSide);
        }
    } else if (chanceToCollide < 2) {
        return goAfterOpponent(matchState, arenaSide);
    } else if (matchState->getRotationAngle() > 88 && matchState->getRotationAngle() < 93) {
        // Adjust probabilities based on rotation angle and arena side
        //cout<<"Vertical Problem!"<<endl;
        return (chanceToMove % 2 == 0) ?  "forward-right" : "backward-left";
        
        
    } else if (matchState->getRotationAngle() > -88 && matchState->getRotationAngle() < -93) {
        // Adjust probabilities based on rotation angle and arena side
        //cout<<"Vertical Problem!"<<endl;
        return (chanceToMove % 2 == 0) ?  "forward-left" : "backward-right";
        
        
    } else if (chanceToGoAfterOpponent < 20) {
        // Adjust probabilities based on distance to opponent
        if (matchState->calculateDistanceToOpponent() <= 90) {
            return (chanceToMove % 2 == 0) ?  "left" : "right";
        } else {
            return goAfterOpponent(matchState, arenaSide);
        }
    } else if (matchState->calculateDistanceToOpponent() <= 48) {
        // Adjust probabilities for blocking based on distance to opponent
        if (chanceToBlock < 90) {
            return "block";
        } else {
            return "none";
        }
    } else {
        return "none";
    }
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

    string goAwayFromOpponent(State* matchState, string arenaSide){
        int opponentX = matchState->getOpponentPosition()->x;
        int opponentY = matchState->getOpponentPosition()->y;
        int myX = matchState->getKaratekaPosition()->x;
        int myY = matchState->getKaratekaPosition()->y;

        // Calculate difference in x and y coordinates
        int deltaX = myX - opponentX;
        int deltaY = myY - opponentY;

        if (arenaSide == "right"){

            if (deltaX > 0) {
                return "backward";
                } else if (deltaX >= 70) {
                return "forward";
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
                return "forward";
            } else if (deltaX >= 70) {
                return "backward";
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





