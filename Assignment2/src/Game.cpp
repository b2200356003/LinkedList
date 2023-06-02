#include "Game.h"
#include "Apartment.h"
#include <iostream>
#include <fstream>
using namespace std;

void Game::PlayGame(string file,string file2,Apartment* head){
    ifstream inFile(file);
    string line;
    string temp;
    string lineList[10];
    int count = 0;
    while (getline(inFile, line)){
        line+="\t";
        for (int i = 0; i < line.length(); i++) {
            if (string(1, line[i]) != "\t") {
                temp += line[i];
            }
            else {
                lineList[count]=temp;
                temp="";
                count++;
            }
        }

        if (lineList[0]=="add_apartment"){head=Apartment::add_apartment(head,lineList[1],lineList[2], stoi(lineList[3]));}
        if (lineList[0]=="add_flat"){head=Apartment::add_flat(head,lineList[1], stoi(lineList[2]), stoi(lineList[3]),stoi(lineList[4]));}
        if (lineList[0]=="remove_apartment"){head=Apartment::remove_apartment(head,lineList[1]);}
        if (lineList[0]=="make_flat_empty"){head=Apartment::make_flat_empty(head,lineList[1], stoi(lineList[2]));}
        if (lineList[0]=="find_sum_of_max_bandwidths"){Apartment::find_sum_of_max_bandwidths(head,file2);}
        if (lineList[0]=="merge_two_apartments"){head=Apartment::merge_two_apartments(head,lineList[1],lineList[2]);}
        if (lineList[0]=="relocate_flats_to_same_apartment"){head=Apartment::relocate_flats_to_same_apartment(head,lineList[1],lineList[2],lineList[3]);}
        if (lineList[0]=="list_apartments"){Apartment::list_apartments(head,file2);}
        lineList->clear();
        count=0;
    }

    inFile.close();

}
