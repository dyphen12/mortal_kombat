#include <iostream>
#include <string>
#include <random>
#include <SDL2/SDL.h>

using namespace std;

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<int> distribution(1, 30); // Generates numbers between 1 and 10

struct PositionVector {
    int x;
    int y;

    void loadPosition(int xi, int yi){
        x = xi;
        y = yi;
    }

};

struct State {
    PositionVector *karatekaPos;
    PositionVector *opponentPos;
    int karatekaPoints;
    int opponentPoints;
    string movement;
    bool isColliding;
};

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
    State *karatekaState;
    string arenaSide;

public:
    Karateka(int i) { 
        this->id = i;
        this->points = 0;
        this->opponent = NULL;
        this->speed = 1;
        this->karatekaState = new State(); // Initialize karatekaState
        this->karatekaState->movement = "stand-up";
        this->arenaSide = "Null";
    }

    int getID(){
        return this->id;
    }

    void setName(string name){
        this->name = name;

    }
    string getName(){
        return this->name;

    }

    void setStyle(string style){
        if(style == "Shotokan" || style == "shotokan"){
            this->style = "Shotokan";
        } else if(style == "Goju-Ryu" || style == "goju-ryu"){
            this->style = "Goju-Ryu";
        }

    }

    string getStyle(){
        return this->style;
    }

    void setPoints() { 
        this->points++;
    }

    int getPoints() { 
        return this->points;
    }
    

    void initialize(Karateka *opponent) { 
        this->points = 0;
        this->opponent = opponent;
    }

    void printOpponent() { 
        cout << "Hello, my name is " << this->name << endl;
        if (opponent == NULL) {
            cout << "I haven't been assigned an opponent." << endl;
        } else {
            cout << "My opponent is " << opponent->name << endl;
        }
    }

    void updatePosition(string movement) {
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


    void receiveAttack(){

    }

    void setPosition(PositionVector *posvec){
        this->posvec = posvec;
    }

    PositionVector* getPositionVector(){
        return this->posvec;
    } 

    State* getKaratekaState(){
        return this->karatekaState;
    }

    void setKaratekaStateMovement(string movement){
        this->karatekaState->movement = movement;
    }

    bool checkCollision( SDL_Rect a, SDL_Rect b )
    {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
    }

    float getRotationAngle(){

        if (this->arenaSide == "right"){

            float deltaX =  this->getPositionVector()->x - this->opponent->getPositionVector()->x;
            float deltaY =  this->getPositionVector()->y - this->opponent->getPositionVector()->y;
            float angleInRadians = atan2f(deltaY, deltaX); // Calculate angle in radians

        // Convert to degrees if needed:
            float angleInDegrees = angleInRadians * 180.0f / M_PI;

            return angleInDegrees;

        } else {
            float deltaX =  this->opponent->getPositionVector()->x - this->getPositionVector()->x;
            float deltaY =  this->opponent->getPositionVector()->y - this->getPositionVector()->y;
            float angleInRadians = atan2f(deltaY, deltaX); // Calculate angle in radians

            // Convert to degrees if needed:
            float angleInDegrees = angleInRadians * 180.0f / M_PI;

            return angleInDegrees;
        }

        
    }

    void setArenaSide(string side){
        this->arenaSide = side;
    }

    string getArenaSide(){
        return this->arenaSide;
    }


};


//heredar con private, protected
//Cómo heredo de dos clases
//Cómo hago heredar a dos hijos



class Shotokan : public Karateka { 
public:
    Shotokan(int i) : Karateka(i) { 
        this->setStyle("shotokan");
    }

    string punch(string option) { 

        int random_number = distribution(generator);

        // Execute Oi-zuki OR
        if (option == "oi-zuki" && random_number == 2) {
            this->setKaratekaStateMovement("oi-zuki");
            return "oi-zuki";
        } else if (option == "gyaku-zuki" && random_number == 4) {
            this->setKaratekaStateMovement("gyaku-zuki");
            return "gyaku-zuki";
        } else {
            return "fail";
        }
        
        // Execute Gyaku-zuki OR

        // Execute Uraken

    }

    string kick(string option){
        // Execute Mae-geri OR

        int random_number = distribution(generator);

        if (option == "mae-geri" && random_number == 2) {
            this->setKaratekaStateMovement("mae-geri");
            return "mae-geri";
        } else if (option == "yoko-geri" && random_number == 4) {
            this->setKaratekaStateMovement("yoko-geri");
            return "yoko-geri";
        } else {
            return "fail";
        }

        // Execute Yoko-geri OR

        // Execute Mawashi-geri
    }

    string manualkick(string option){
        // Execute Mae-geri OR

        int random_number = distribution(generator);

        if (option == "mae-geri") {
            this->setKaratekaStateMovement("mae-geri");

            return "mae-geri";
        } else if (option == "yoko-geri") {
            this->setKaratekaStateMovement("yoko-geri");
            return "yoko-geri";
        } else {
            return "fail";
        }

        // Execute Yoko-geri OR

        // Execute Mawashi-geri
    }

    string block(){
        // Execute Age-uke OR (used against oi-zuki)

        int random_number = distribution(generator);

        if(random_number == 2){
            this->setKaratekaStateMovement("block");
            return "block";
        } else {
            return "fail";
        }

        // Execute Gedan-barai OR

        // Execute Soko-geri
    }
};

class K20 : public Karateka { 
public:
    K20(int i) : Karateka(i) { 
    }

    void veryHardKick() { 
        this->opponent; 
    }
};

