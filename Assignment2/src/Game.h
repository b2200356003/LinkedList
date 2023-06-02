#include "iostream"
#include "Apartment.h"
#ifndef ASSIGNMENT2_GAME_H
#define ASSIGNMENT2_GAME_H
using namespace std;


class Game {
public:
    // This function reads the input.txt and runs the proper functinos
    static void PlayGame(string file,string file2,Apartment* head);
};



#endif //ASSIGNMENT2_GAME_H
