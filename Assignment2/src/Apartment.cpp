#include "Apartment.h"
#include <iostream>
#include <fstream>
using namespace std;

Apartment* Apartment::add_apartment(Apartment* head,string name,string place,int max_bandwidth) {
    Apartment* tail;
    tail=head;

    if (place=="head"){
        head=new Apartment;
        head->name=name;
        head->max_bandwidth=max_bandwidth;
        head->nextA= head;

    }

    else {
        if (string (1,place[0]) == "a") {
            Apartment *ap = head;
            Apartment *add = new Apartment;

            while (ap->name != string (1,place.back())) {
                ap = ap->nextA;
            }

            add->nextA = ap->nextA;
            ap->nextA = add;
            add->name = name;
            add->max_bandwidth = max_bandwidth;

            tail=head;
            while (tail->nextA!= head){
                tail=tail->nextA;
            }
            tail->nextA=head;
        }
        else if (string(1,place[0])=="b"){
            Apartment *ap = head;
            Apartment *add = new Apartment;
            while (ap->nextA->name != string(1,place.back())) {
                ap = ap->nextA;
            }
            add->nextA=ap->nextA;
            ap->nextA=add;
            add->name = name;
            add->max_bandwidth = max_bandwidth;

            if (string(1,place.back())==head->name){
                head=add;
            }
            while (tail->nextA!= head){
                tail=tail->nextA;
            }
            tail->nextA=head;
        }
    }
    return head;
}

Apartment* Apartment::add_flat(Apartment* head,string apartName,int flatIndex,int bandwidth,int flatNo) {
    Apartment* tempA=head;
    Flat* tempf = new Flat;
    Flat* tempb ;
    Flat* add = new Flat;
    int totalBandwidth=0;
    int bandLimit;

    while (tempA->name!=apartName){
        tempA=tempA->nextA;
    }

    tempb = tempA->headF;
    while(tempb!= nullptr){
        totalBandwidth+=tempb->initial_bandwidth;
        tempb=tempb->nextF;
    }

    bandLimit=tempA->max_bandwidth-totalBandwidth;

    if (tempA->headF== nullptr){
        tempA->headF=new Flat;

        if (bandLimit>bandwidth) {
            tempA->headF->initial_bandwidth = bandwidth;
        } else {
            tempA->headF->initial_bandwidth = bandLimit;
        }

        tempA->headF->nextF= nullptr;
        tempA->headF->beforeF= nullptr;

        if (bandLimit==0){
            tempA->headF->is_Empty=1;
        }
        else{
            tempA->headF->is_Empty=0;
        }

        tempA->headF->ID=flatNo;
    }

    else{
        // checking are we making headFlat

        if (flatIndex==0){
            tempf=tempA->headF;
            tempf->beforeF=add;
            add->nextF=tempf;
            tempA->headF=add;
            if (bandLimit>bandwidth) {
                add->initial_bandwidth = bandwidth;
            } else {
                add->initial_bandwidth = bandLimit;
            }
            if (bandLimit==0){
                add->is_Empty=1;
            }
            else {
                add->is_Empty = 0;
            }
            add->ID=flatNo;
        }
        else
        {
            int count = 1;
            tempf=tempA->headF;
            while (count!=flatIndex){
                tempf=tempf->nextF;
                count++;
            }
            add->nextF=tempf->nextF;
            tempf->nextF=add;
            add->beforeF=tempf;
            if(add->nextF!= nullptr) {
                add->nextF->beforeF = add;
            }
            if (bandLimit>bandwidth) {
                add->initial_bandwidth = bandwidth;
            } else {
                add->initial_bandwidth = bandLimit;
            }
            if (bandLimit==0){
                add->is_Empty = 1;
            }
            else {
                add->is_Empty = 0;
            }
            add->ID=flatNo;
        }
    }
    return head;
}

Apartment* Apartment::remove_apartment(Apartment* head,string name) {
    Apartment* temp = head;
    Apartment* temp2 ;
    while(temp->nextA->name!=name){
        temp=temp->nextA;
    }

    temp2=temp->nextA;
    temp->nextA = temp->nextA->nextA;

    delete temp2;

    if (temp==head){
        return nullptr;
    }
    else{
        return head;
    }

}

Apartment* Apartment::make_flat_empty(Apartment* head,string name,int flatID) {
    Apartment* temp = head;
    Flat * tempF;
    while (temp->name!=name){
        temp=temp->nextA;
    }

    tempF=temp->headF;

    while (tempF->ID!=flatID){
        tempF=tempF->nextF;
    }

    tempF->is_Empty=1;
    tempF->initial_bandwidth=0;
    return head;
}

int Apartment::find_sum_of_max_bandwidths(Apartment* head,string file) {
    ofstream myfile ;
    myfile.open(file,ios::app);

    int sum = 0;
    if (head== nullptr){
        myfile << "Sum of bandwidth: " << sum << endl << endl;
        return sum;
    }
    else {
        Apartment *temp = head;

        while (temp->nextA != head) {
            sum += temp->max_bandwidth;
            temp = temp->nextA;
        }
        sum += temp->max_bandwidth;
        myfile << "Sum of bandwidth: " << sum << endl << endl;
        return sum;
    }
}

Apartment* Apartment::merge_two_apartments(Apartment* head,string Name1,string Name2) {
    Apartment* temp1 = head;
    Apartment* temp2 = head;
    while(temp1->name!=Name1){
        temp1=temp1->nextA;
    }
    while (temp2->name!=Name2){
        temp2=temp2->nextA;
    }


    if (temp1->headF == nullptr){
        temp1->headF=temp2->headF;
        temp1->max_bandwidth+=temp2->max_bandwidth;
        remove_apartment(head,Name2);
    }

    else if (temp2->headF == nullptr){
        temp1->max_bandwidth+=temp2->max_bandwidth;
        remove_apartment(head,Name2);
    }

    else{
        Flat* lastF = temp1->headF;
        while (lastF->nextF != nullptr){
            lastF=lastF->nextF;
        }
        lastF->nextF=temp2->headF;
        lastF->nextF->beforeF=lastF;
        temp1->max_bandwidth+=temp2->max_bandwidth;
        remove_apartment(head,Name2);
    }

    return head;
}

Apartment* Apartment::relocate_flats_to_same_apartment(Apartment* head,string aptName,string beforethisFlat,string addList) {
    Apartment* tempA = head;
    Apartment* tempA2 = head;
    Flat* tempF;
    Flat* tempF2;
    int quit = 0;
    addList=addList.substr(1,addList.size()-2);
    addList+=",";
    string temp;
    int tempI;
    for (int i = 0; i < addList.size()+1; i++) {
        if (string(1,addList[i])!=","){
            temp+=addList[i];
        }
        else{
            tempI= stoi(temp);
            // find the flat will be included
            while (tempA->nextA!=head){
                tempF=tempA->headF;
                while (tempF->ID!=tempI){
                    tempF=tempF->nextF;
                    if (tempF== nullptr){
                        break;
                    }
                    if (tempF->ID==tempI){
                        quit=1;
                        break;
                    }
                }
                if (quit==1){
                    break;
                }
                tempA=tempA->nextA;
            }

            // find the flat which we include before that
            while (tempA2->name!=aptName){
                tempA2=tempA2->nextA;
            }
            tempF2=tempA2->headF;
            while (tempF2->ID!= stoi(beforethisFlat)){
                tempF2=tempF2->nextF;
            }

            tempA->max_bandwidth-=tempF->initial_bandwidth;
            tempA2->max_bandwidth+=tempF->initial_bandwidth;

            // deleting
            if (tempA->headF==tempF){
                tempA->headF= nullptr;
            }
            else{
                tempF->beforeF->nextF=tempF->nextF;
                if (tempF->nextF!= nullptr){
                    tempF->nextF->beforeF=tempF->beforeF;
                }
            }

            // adding
            if (tempA2->headF==tempF2){
                tempA2->headF=tempF;
                tempF2->beforeF=tempF;
                tempF->nextF=tempF2;
            }
            else{
                tempF2->beforeF->nextF=tempF;
                tempF->nextF=tempF2;
                tempF->beforeF=tempF2->beforeF;
                tempF2->beforeF=tempF;
            }


            tempA = head;
            tempA2=head;
            temp="";
            quit=0;
        }
    }
    return head;
}

void Apartment::list_apartments(Apartment* head,string file) {
    ofstream myfile ;
    myfile.open(file,ios::app);

    Apartment* temp = head;
    Flat* tempF = head->headF;
    while (temp->nextA!=head){
        myfile << temp->name << "(" << temp->max_bandwidth << ")" << "\t";
        while (tempF != nullptr){
            myfile << "Flat" << tempF->ID << "(" << tempF->initial_bandwidth << ")" << "\t";
            tempF=tempF->nextF;
        }
        temp=temp->nextA;
        tempF=temp->headF;
        myfile << endl ;
    }

    // for the last one
    myfile << temp->name << "(" << temp->max_bandwidth << ")" << "\t";
    while (tempF!= nullptr){
        myfile << "Flat" << tempF->ID << "(" << tempF->initial_bandwidth << ")" << "\t";
        tempF=tempF->nextF;
    }
    myfile << endl << endl;
}
