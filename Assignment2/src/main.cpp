#include <iostream>
#include "Game.h"
#include "Apartment.h"
int main(int argc, char *argv[]) {
    Apartment* head = nullptr;
    Game::PlayGame(argv[1],argv[2],head);
    delete head;
}
