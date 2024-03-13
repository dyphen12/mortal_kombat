#include "positionvector.h"
#include <iostream>
#include <string>
#include <cmath>

struct State {
    PositionVector *karatekaPos;
    PositionVector *opponentPos;
    int karatekaPoints;
    int opponentPoints;
    string movement;
    string opponentMovement;
    bool isColliding;
    float distanceToOpponent;
    string karatekaLastAction;
    string opponentLastAction;

    void printState() const {
        cout << "** Match State **" << endl;
        cout << "Karateka Position: (" << karatekaPos->x << ", " << karatekaPos->y << ")" << endl;
        cout << "Opponent Position: (" << opponentPos->x << ", " << opponentPos->y << ")" << endl;
        cout << "Karateka Points: " << karatekaPoints << endl;
        cout << "Opponent Points: " << opponentPoints << endl;
        //cout << "Karateka Movement: " << movement << endl;
        //cout << "Opponent Movement: " << opponentMovement << endl;
        cout << "Is Colliding: " << (isColliding ? "Yes" : "No") << endl;
        cout << "Distance to Opponent: " << distanceToOpponent << endl;
        cout << "Karateka Last Action: " << karatekaLastAction << endl;
        cout << "Opponent Last Action: " << opponentLastAction << endl;
    }

    float calculateDistanceToOpponent() const {
        // Calculate the difference in x and y coordinates
        float deltaX = karatekaPos->x - opponentPos->x;
        float deltaY = karatekaPos->y - opponentPos->y;

        // Use the Pythagorean theorem to calculate the distance
        return sqrt(deltaX * deltaX + deltaY * deltaY);
    }
};