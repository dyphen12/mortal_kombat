#ifndef KARATEKA_H
#define KARATEKA_H

#include <iostream>
#include <string>
#include <cmath>
#include <SDL2/SDL.h>
#include "state.h"

using namespace std;


class Karateka {
protected:
    int id;
    int points;
    Karateka *opponent;
    int medal;
    string name;
    string style;
    PositionVector *posvec;
    int speed;
    State *MatchState;
    string arenaSide;
    SDL_Rect *karatekaRect;

public:
    Karateka(int i);

    int getID();

    void setName(string name);

    string getName();

    void setStyle(string style);

    string getStyle();

    void setPoints(string movementType);

    int getPoints();

    void initialize(Karateka *opponent);

    void printOpponent();

    void updatePosition(string movement);

    void receiveAttack();

    void setPosition(PositionVector *posvec);

    PositionVector *getPositionVector();

    State *getMatchState();

    void setMatchStateMovement(string movement);

    bool checkCollision(SDL_Rect a, SDL_Rect b);

    float getRotationAngle();

    void setArenaSide(string side);

    string getArenaSide();

    void setKaratekaRect(SDL_Rect *rect);

    SDL_Rect *getKaratekaRect();

    void updateMatchState();

    virtual string punch(string option, int rn);

    virtual string kick(string option, int rn);

    virtual string manualkick(string option);

    virtual string block(int rn);
};

class Shotokan : public Karateka {
public:
    Shotokan(int i);

    string punch(string option, int rn);

    string kick(string option, int rn);

    string manualkick(string option);

    string block(int rn);
};

class K20 : public Karateka {
public:
    K20(int i);

    void veryHardKick();
};

#endif // KARATEKA_H
