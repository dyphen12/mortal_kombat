#include "match.h"


Match::Match(Karateka *k1, Karateka *k2) {  
  this->k1 = k1;
  this->k2 = k2;
  this->k1->initialize(k2);
  this->k2->initialize(k1);
}

Match::~Match() {
  // Add implementation to free memory or perform cleanup if needed
}

void Match::printMatchNames() {
  std::cout << k1->getName() << std::endl;
  std::cout << k2->getName() << std::endl;
}

void Match::simulateMatch() {
  // Implement the logic to simulate the fight here
  // This currently only prints basic information
  std::cout << "Simulating Match" << std::endl;
  std::cout << k1->getName() << " VS " << k2->getName() << std::endl;
}

Karateka* Match::getKaratekaA(){
  return this->k1;
}

Karateka* Match::getKaratekaB(){
  return this->k2;
}

void Match::setTimeLeft(double remainingTime){
  this->timeLeft = remainingTime;

}

double Match::getTimeLeft(){
  return this->timeLeft;
}

void Match::setWinner(Karateka* winner){
  this->winner = winner;
}

Karateka* Match::getWinner(){
  return this->winner;
}
