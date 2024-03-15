#include "karateka.h"



class Match {

private:
  Karateka *k1;
  Karateka *k2;
  Karateka *winner; // Assuming winner is determined later
  int k1R;
  int k2R;
  int duration;


public:
  Match(Karateka *k1, Karateka *k2);
  ~Match(); // Destructor declaration

  void simulateMatch();
  void printMatchNames();
  Karateka* getKaratekaA();
  Karateka* getKaratekaB();
};


class Referee {
private:
  Match *match;
  bool isYuko;
  bool isWazari;
  bool isIppon;
public:
    Referee(); 

    string callMovement(string movement){
      if (movement == "yuko"){
        return "yuko";
      } else if (movement == "wazari"){
        return "wazari";
      } else if (movement == "ippon"){
        return "ippon";
      }
      
    }

    string declareWinner(){
      return "winner";
    }

    string callPenalty(){
      return "Penalty";
    }

    
};
