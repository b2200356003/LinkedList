#ifndef ASSIGNMENT2_APARTMENT_H
#define ASSIGNMENT2_APARTMENT_H
#include "Flat.h"
#include "iostream"
using namespace std;

class Apartment {
public:
    Apartment* nextA;

    // flat_list of newly added apartment must be Null
    Flat* headF = nullptr;
    int max_bandwidth;
    string name;

    // all operations exactly like introductions.

    static Apartment* add_apartment(Apartment* head,string name,string place,int max_bandwidth);

    static Apartment* add_flat(Apartment* head,string apartName,int flatIndex,int bandwidth,int flatNo);

    static Apartment* remove_apartment(Apartment* head,string name);

    static Apartment* make_flat_empty(Apartment* head,string name,int flatID);

    static int find_sum_of_max_bandwidths(Apartment* head,string file);

    static Apartment* merge_two_apartments(Apartment* head,string Name1,string Name2);

    static Apartment* relocate_flats_to_same_apartment(Apartment* head,string aptName,string beforethisFlat,string addList);

    static void list_apartments(Apartment* head,string file);
};

#endif //ASSIGNMENT2_APARTMENT_H
