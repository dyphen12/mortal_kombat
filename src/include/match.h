#include "karateka.h"



class Match {

private:
  Karateka *k1;
  Karateka *k2;
  Karateka *winner; // Assuming winner is determined later
  int k1R;
  int k2R;
  int duration;
  double timeLeft;


public:
  Match(Karateka *k1, Karateka *k2);
  ~Match(); // Destructor declaration

  void simulateMatch();
  void printMatchNames();
  Karateka* getKaratekaA();
  Karateka* getKaratekaB();
  void setTimeLeft(double remainingTime);
  double getTimeLeft();
  void setWinner(Karateka* winner);
  Karateka* getWinner();
};


class Referee {
private:
  Match *match;
  bool isYuko;
  bool isWazari;
  bool isIppon;
public:
    Referee(Match* match){
      this->match = match;

    } 

    string callMovement(string movement){
      if (movement == "yuko"){
        return "yuko";
      } else if (movement == "wazari"){
        return "wazari";
      } else if (movement == "ippon"){
        return "ippon";
      }
      
    }

    Karateka* declareWinner(){

      if(this->match->getKaratekaA()->getPoints() - this->match->getKaratekaB()->getPoints() >= 8){

        //cout<<"The Winner is "<<match->getKaratekaA()->getName()<<endl;
        return match->getKaratekaA();
      } else if (this->match->getTimeLeft() <= 0.0) {

        if(this->match->getKaratekaA()->getPoints() > this->match->getKaratekaB()->getPoints()){
          return match->getKaratekaA();

        } else {
          return match->getKaratekaB();
        }
      } else if(this->match->getKaratekaB()->getPoints() - this->match->getKaratekaA()->getPoints() >= 8){

        return match->getKaratekaB();
      } else if(this->match->getKaratekaB()->getFouls() >= 3){


        return match->getKaratekaA();
      } else if(this->match->getKaratekaA()->getFouls() >= 3){


        return match->getKaratekaB();
      } else {
        return NULL;
      }
   
    }

    Karateka* callPenalty(){
      //cout<<"Position of Karateka on X: "<<this->match->getKaratekaA()->getPositionVector()->x<<endl;
      //cout<<"Position of Karateka on Y: "<<this->match->getKaratekaA()->getPositionVector()->y<<endl;

      if(match->getKaratekaA()->getPositionVector()->x >= 870 || match->getKaratekaA()->getPositionVector()->x <= 399 || match->getKaratekaA()->getPositionVector()->y <= 120 || match->getKaratekaA()->getPositionVector()->y >= 575){
        cout<<"Step out of Tatami! Penalty for "<<match->getKaratekaA()->getName()<<endl;
        match->getKaratekaA()->setFoul();
        return match->getKaratekaA();
      } else if(match->getKaratekaB()->getPositionVector()->x >= 870 || match->getKaratekaB()->getPositionVector()->x <= 399 || match->getKaratekaB()->getPositionVector()->y <= 120 || match->getKaratekaB()->getPositionVector()->y >= 575){
        cout<<"Step out of Tatami! Penalty for "<<match->getKaratekaB()->getName()<<endl;
        match->getKaratekaB()->setFoul();
        return match->getKaratekaB();
      } else {
        return NULL;
      }

      


    }

    

    
};
