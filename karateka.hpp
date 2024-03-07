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

public:
    Karateka(int i) { 
        this->id = i;
        this->points = 0;
        this->opponent = NULL;
        this->speed = 1;
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

    string getKaratekaStateMovement(){
        return this->karatekaState->movement;
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
            return "oi-zuki";
        } else if (option == "gyaku-zuki" && random_number == 4) {
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
            return "mae-geri";
        } else if (option == "yoko-geri" && random_number == 4) {
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
            // Opponent was succesfully kicked?

            // If yes
            // return "ippon!"
            // else 
            // return "continue round"

            return "mae-geri";
        } else if (option == "yoko-geri") {
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
            //this->setKaratekaStateMovement("block");
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


void run_karateka_process(){

    // Create two Karateka objects with IDs 1 and 2
    Karateka* G1 = new Karateka(1);
    Karateka* G2 = new Karateka(2);

    // Create a K20 object with ID 3
    K20* A = new K20(3);

    // Assign G2 as the opponent for A
    A->initialize(G2);

    // Print information about A's opponent
    A->printOpponent();

    // Increase A's points four times
    //A->setPoints();
    //A->setPoints();
    //A->setPoints();
    //A->setPoints();

    // Print A's current points
    //cout << A->getPoints() << endl;

    // Call A's very hard kick method (likely needs implementation)
    //A->veryHardKick();

    /* Commented-out code:
    // Assign G2 as opponent for G1 and vice versa (would create circular references)
    G1->initialize(G2);
    G2->initialize(G1);

    // Print information about G1's and G2's opponents (would cause infinite loops)
    G1->printOpponent();
    G2->printOpponent();
    */

}