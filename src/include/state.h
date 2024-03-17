#include "positionvector.h"
#include <iostream>
#include <string>
#include <cmath>
#include <string>

class State {
private:
    PositionVector *karatekaPos;
    PositionVector *opponentPos;
    int karatekaPoints;
    int opponentPoints;
    std::string movement;
    std::string opponentMovement;
    bool isColliding;
    float distanceToOpponent;
    std::string karatekaLastAction;
    std::string opponentLastAction;

public:
    void printState() const {
        std::cout << "** Match State **" << std::endl;
        std::cout << "Karateka Position: (" << karatekaPos->x << ", " << karatekaPos->y << ")" << std::endl;
        std::cout << "Opponent Position: (" << opponentPos->x << ", " << opponentPos->y << ")" << std::endl;
        std::cout << "Karateka Points: " << karatekaPoints << std::endl;
        std::cout << "Opponent Points: " << opponentPoints << std::endl;
        //std::cout << "Karateka Movement: " << movement << std::endl;
        //std::cout << "Opponent Movement: " << opponentMovement << std::endl;
        std::cout << "Is Colliding: " << (isColliding ? "Yes" : "No") << std::endl;
        std::cout << "Distance to Opponent: " << distanceToOpponent << std::endl;
        std::cout << "Karateka Last Action: " << karatekaLastAction << std::endl;
        std::cout << "Opponent Last Action: " << opponentLastAction << std::endl;
    }

    float calculateDistanceToOpponent() const {
        // Calculate the difference in x and y coordinates
        float deltaX = karatekaPos->x - opponentPos->x;
        float deltaY = karatekaPos->y - opponentPos->y;

        // Use the Pythagorean theorem to calculate the distance
        return sqrt(deltaX * deltaX + deltaY * deltaY);
    }

    string getKaratekaLastAction(){
        return this->karatekaLastAction;
    }

    string getKaratekaMovement(){
        return this->movement;
    }

    void setKaratekaLastAction(string lastAction){
        this->karatekaLastAction = lastAction;
    }

    void setKaratekaMovement(string movement){
        this->movement = movement;
    }

    void setKaratekaPositionVector(PositionVector* posvec)
    {
        this->karatekaPos = posvec;
    }

    void setKaratekaPoints(int points){
        this->karatekaPoints = points;

    }

    void setOpponentLastAction(string lastAction){
        this->opponentLastAction = lastAction;
    }

    void setOpponentPosition(PositionVector* posvec){
        this->opponentPos = posvec;
    }

    PositionVector* getKaratekaPosition(){
        return this->karatekaPos;
    }

    void setOpponentPoints(int points){
        this->opponentPoints = points;

    }

    void setIsColliding(bool isColliding){
        this->isColliding = isColliding;

    }

    void setDistanceToOpponent(float distance){
        this->distanceToOpponent = distance;

    }

    
};