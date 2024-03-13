#include <iostream>

using namespace std;

struct PositionVector {
    int x;
    int y;

    void loadPosition(int xi, int yi){
        x = xi;
        y = yi;
    }
};