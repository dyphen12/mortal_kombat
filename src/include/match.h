#include "karateka.h"

class Match {
public:
  Match(Karateka *k1, Karateka *k2);
  ~Match(); // Destructor declaration

  void simulateMatch();
  void printMatchNames();

private:
  Karateka *k1;
  Karateka *k2;
  Karateka *winner; // Assuming winner is determined later
  int k1R;
  int k2R;
};


class Referee : public Match { 
public:
    Referee(Karateka *k1, Karateka *k2) : Match(k1, k2) { 
    }

    string declareWinner(){
      return "winner";
    }

    string callFoul(){
      return "foul";
    }
};
