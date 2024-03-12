#include "karateka.hpp"

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
