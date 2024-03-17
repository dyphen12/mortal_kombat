#include "karateka.h"

Karateka::Karateka(int i) {
    this->id = i;
    this->points = 0;
    this->opponent = NULL;
    this->speed = 1;
    this->MatchState = new State(); // Initialize MatchState
    this->MatchState->setKaratekaMovement("stand-up");
    this->arenaSide = "Null";
}

int Karateka::getID() {
    return this->id;
}

void Karateka::setName(string name) {
    this->name = name;
}

string Karateka::getName() {
    return this->name;
}

void Karateka::setStyle(string style) {
    if (style == "Shotokan" || style == "shotokan") {
        this->style = "Shotokan";
    } else if (style == "Goju-Ryu" || style == "goju-ryu") {
        this->style = "Goju-Ryu";
    }
}

string Karateka::getStyle() {
    return this->style;
}

void Karateka::setPoints(string movementType) {
    if (movementType == "yuko"){
        this->points++;
    } else if(movementType == "wazari"){
        this->points = this->points + 2;
    } else {
        this->points = this->points + 3;
    }
}

int Karateka::getPoints() {
    return this->points;
}

void Karateka::initialize(Karateka *opponent) {
    this->points = 0;
    this->opponent = opponent;
}

void Karateka::printOpponent() {
    cout << "Hello, my name is " << this->name << endl;
    if (opponent == NULL) {
        cout << "I haven't been assigned an opponent." << endl;
    } else {
        cout << "My opponent is " << opponent->name << endl;
    }
}

void Karateka::updatePosition(string movement) {
    if (movement == "right") {
        this->posvec->y -= speed; // Update y-coordinate for up movement
    } else if (movement == "left") {
        this->posvec->y += speed; // Update y-coordinate for down movement
    } else if (movement == "backward") {
        this->posvec->x += speed; // Update x-coordinate for left movement
    } else if (movement == "forward") {
        this->posvec->x -= speed; // Update x-coordinate for right movement
    } else {
        cerr << "Invalid movement direction: " << movement << endl; // Log error message
        // Optionally: throw an exception for further handling
    }
}

void Karateka::updatePositionRecoil(string movement) {
    if (movement == "right") {
        this->posvec->y += 8; // Update y-coordinate for up movement
    } else if (movement == "left") {
        this->posvec->y -= 8; // Update y-coordinate for down movement
    } else if (movement == "backward") {
        this->posvec->x -= 8; // Update x-coordinate for left movement
    } else if (movement == "forward") {
        this->posvec->x += 8; // Update x-coordinate for right movement
    } else {
        cerr << "Invalid movement direction: " << movement << endl; // Log error message
        // Optionally: throw an exception for further handling
    }
}

void Karateka::receiveAttack() {
    // Handle receiving an attack
}

void Karateka::setPosition(PositionVector *posvec) {
    this->posvec = posvec;
}

PositionVector *Karateka::getPositionVector() {
    return this->posvec;
}

State *Karateka::getMatchState() {
    return this->MatchState;
}

void Karateka::setMatchStateMovement(string movement) {
    this->MatchState->setKaratekaMovement(movement);
}

bool Karateka::checkCollision(SDL_Rect a, SDL_Rect b) {
    // Check collision between two rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }

    return true;
}

float Karateka::getRotationAngle() {
    // Calculate rotation angle based on opponent's position
    if (this->arenaSide == "right") {
        float deltaX = this->getPositionVector()->x - this->opponent->getPositionVector()->x;
        float deltaY = this->getPositionVector()->y - this->opponent->getPositionVector()->y;
        float angleInRadians = atan2f(deltaY, deltaX);
        float angleInDegrees = angleInRadians * 180.0f / M_PI;
        return angleInDegrees;
    } else {
        float deltaX = this->opponent->getPositionVector()->x - this->getPositionVector()->x;
        float deltaY = this->opponent->getPositionVector()->y - this->getPositionVector()->y;
        float angleInRadians = atan2f(deltaY, deltaX);
        float angleInDegrees = angleInRadians * 180.0f / M_PI;
        return angleInDegrees;
    }
}

void Karateka::setArenaSide(string side) {
    this->arenaSide = side;
}

string Karateka::getArenaSide() {
    return this->arenaSide;
}

void Karateka::setKaratekaRect(SDL_Rect *rect) {
    this->karatekaRect = rect;
}

SDL_Rect *Karateka::getKaratekaRect() {
    return this->karatekaRect;
}

void Karateka::updateMatchState() {
    // Update match state with current information
    this->MatchState->setKaratekaLastAction(this->MatchState->getKaratekaMovement());
    this->MatchState->setKaratekaPositionVector(this->getPositionVector());
    this->MatchState->setKaratekaPoints(this->getPoints());

    this->MatchState->setOpponentLastAction(this->opponent->MatchState->getKaratekaMovement());
    this->MatchState->setOpponentPosition(this->opponent->getPositionVector());
    this->MatchState->setOpponentPoints(this->opponent->getPoints());

    SDL_Rect *opponentRect = this->opponent->getKaratekaRect();
    this->MatchState->setIsColliding(this->checkCollision(*karatekaRect, *opponentRect));

    this->MatchState->setDistanceToOpponent(this->MatchState->calculateDistanceToOpponent());
}

string Karateka::punch(string option) {
    // Provide an implementation (e.g., basic punch)
    return "Basic punch";
}

string Karateka::manualkick(string option) {
    // Provide an implementation (e.g., basic punch)
    return "Basic punch";
}

string Karateka::kick(string option) {
    // Provide an implementation (e.g., basic punch)
    return "Basic punch";
}


string Karateka::block() {
    // Provide an implementation (e.g., basic punch)
    return "Basic punch";
}

DecisionMaker* Karateka::getDecisionMaker(){
    return this->decisionMaker;
}

string Karateka::getDecision(){
    string decision = this->decisionMaker->getDecision(this->getMatchState());
    return decision;
}

string Karateka::getMovement(){
    string movement = this->decisionMaker->getMovement(this->getMatchState());
    return movement;
}


Shotokan::Shotokan(int i) : Karateka(i) {
    this->setStyle("shotokan");
    this->decisionMaker = new DecisionMaker(this->getStyle());
}

string Shotokan::punch(string option) {
    

    if (option == "oi-zuki") {
        this->setMatchStateMovement("oi-zuki");
        return "oi-zuki";
    } else if (option == "gyaku-zuki") {
        this->setMatchStateMovement("gyaku-zuki");
        return "gyaku-zuki";
    } else {
        return "fail";
    }
}

string Shotokan::kick(string option) {
    

    if (option == "mae-geri") {
        this->setMatchStateMovement("mae-geri");
        return "mae-geri";
    } else if (option == "yoko-geri") {
        this->setMatchStateMovement("yoko-geri");
        return "yoko-geri";
    } else {
    return "fail";
    }
}

string Shotokan::manualkick(string option) {

    if (option == "mae-geri") {
        this->setMatchStateMovement("mae-geri");
        return "mae-geri";
    } else if (option == "yoko-geri") {
        this->setMatchStateMovement("yoko-geri");
        return "yoko-geri";
    } else {
        return "fail";
    }
}

string Shotokan::block() {
    
    this->setMatchStateMovement("block");
    return "block";

}




