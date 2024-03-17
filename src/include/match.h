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

        //cout<<"The Winner is "<<match->getKaratekaA()->getName()<<endl;
        return match->getKaratekaB();
      } else {
        return NULL;
      }
   
    }

    string callPenalty(){
      return "Penalty";
    }

    
};
