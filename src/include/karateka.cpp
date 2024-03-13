#include "karateka.h"

Karateka::Karateka(int i) {
    this->id = i;
    this->points = 0;
    this->opponent = NULL;
    this->speed = 1;
    this->MatchState = new State(); // Initialize MatchState
    this->MatchState->movement = "stand-up";
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

void Karateka::setPoints() {
    this->points++;
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
        this->posvec->x -= speed; // Update x-coordinate for left movement
    } else if (movement == "forward") {
        this->posvec->x += speed; // Update x-coordinate for right movement
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
    this->MatchState->movement = movement;
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
    this->MatchState->karatekaLastAction = this->MatchState->movement;
    this->MatchState->karatekaPos = this->getPositionVector();
    this->MatchState->karatekaPoints = this->getPoints();

    this->MatchState->opponentLastAction = this->opponent->MatchState->movement;
    this->MatchState->opponentPos = this->opponent->getPositionVector();
    this->MatchState->opponentPoints = this->opponent->getPoints();

    SDL_Rect *opponentRect = this->opponent->getKaratekaRect();
    this->MatchState->isColliding = this->checkCollision(*karatekaRect, *opponentRect);

    this->MatchState->distanceToOpponent = this->MatchState->calculateDistanceToOpponent();
}

Shotokan::Shotokan(int i) : Karateka(i) {
    this->setStyle("shotokan");
}

string Shotokan::punch(string option, int rn) {
    int random_number = rn;

    if (option == "oi-zuki" && random_number == 2) {
        this->setMatchStateMovement("oi-zuki");
        return "oi-zuki";
    } else if (option == "gyaku-zuki" && random_number == 4) {
        this->setMatchStateMovement("gyaku-zuki");
        return "gyaku-zuki";
    } else {
        return "fail";
    }
}

string Shotokan::kick(string option, int rn) {
    int random_number = rn;

    if (option == "mae-geri" && random_number == 2) {
        this->setMatchStateMovement("mae-geri");
        return "mae-geri";
    } else if (option == "yoko-geri" && random_number == 4) {
        this->setMatchStateMovement("yoko-geri");
        return "yoko-geri";
    } else {
    return "fail";
    }
}

string Shotokan::manualkick(string option) {
    int random_number = 2;
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

string Shotokan::block(int rn) {
    int random_number = rn;
    if (random_number == 2) {
        this->setMatchStateMovement("block");
        return "block";
    } else {
        return "fail";
    }
}


