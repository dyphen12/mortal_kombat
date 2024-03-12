#include <iostream>
#include <random>
#include <cmath>


using namespace std;

int rng(){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, 30); // Generates numbers between 1 and 10
    int random_number = distribution(generator);
    return random_number;
}