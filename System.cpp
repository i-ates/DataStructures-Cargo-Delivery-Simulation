//
// Created by Ates on 12/16/2020.
//
#include <sstream>
#include <string>
#include "System.h"
#include <iostream>
using namespace  std;

struct IndicesPackages{
    string package;
    IndicesPackages *next;
};
IndicesPackages *indicesHead;

void addIndicesPackage(string data){
    auto *temp=new IndicesPackages();
    IndicesPackages *last=indicesHead;
    temp->package=data;
    temp->next= nullptr;
    if (indicesHead== nullptr){
        indicesHead=temp;
    }else{
        while (last->next!= nullptr)
            last=last->next;
        last->next=temp;
    }
};

System::System(char *dests_file, char *packages_file, char *trucks_file, char *missions_file, char *result_file) {
    destsFile.open(dests_file,std::ios::in);
    packagesFile.open(packages_file,std::ios::in);
    trucksFile.open(trucks_file,std::ios::in);
    missionsFile.open(missions_file,std::ios::in);
    resultFile.open(result_file,std::ios::out);
    indicesHead= nullptr;
}

System::~System() = default;

void System::addCity() {
    string line;
    if (destsFile.is_open()){
        while (getline(destsFile,line)){
            if (!checkDest(line)){
                City *temp=new City();
                temp->name=line;
                if (city== nullptr){
                    temp->next=temp;
                    city=temp;
                }else{
                    temp->next=city->next;
                    city->next=temp;
                    city=temp;
                }
            }
        }
    }
}

void System::addPackage() {
    int counter=1;
    string line;
    string packageName;
    if (packagesFile.is_open()){
        while (getline(packagesFile,line)){
            istringstream iss(line);
            string token;
            while (getline(iss,token,' ')){
                if (counter%2==1){
                    packageName=token;
                }
                if (counter%2==0){
                    if (checkDest(token)){
                        City *temp=city->next;
                        do {
                            if (temp->name==token){
                                temp->packages.push(packageName);
                                break;
                            }
                            temp=temp->next;
                        }while (temp!=city->next);
                    }
                }
                counter++;
            }
        }
    }
}

void System::addTruck() {
    int counter=1;
    string truckName;
    string line;
    if (trucksFile.is_open()){
        while (getline(trucksFile,line)){
            istringstream iss(line);
            string token;
            while (getline(iss,token,' ')){
                if (counter%3==1){
                    truckName=token;
                }
                if (counter%3==2){
                    if (checkDest(token)){
                        City *temp=city->next;
                        do {
                            if (temp->name==token){
                                temp->trucks.enqueue(truckName);
                                break;
                            }
                            temp=temp->next;
                        }while (temp!=city->next);
                    }
                }
                counter++;
            }
        }
    }
}
void System::addMission() {
    string line;
    int counter=1;
    int missionNum=1;
    if (missionsFile.is_open()){
        while (getline(missionsFile,line)){
            MissionList *temp=new MissionList();
            istringstream iss(line);
            string token;
            while (getline(iss,token,'-')){
                if (counter%6==1){
                    temp->startStation=token;
                } else if (counter%6==2){
                    temp->midwayStation=token;
                } else if(counter%6==3){
                    temp->targetStation=token;
                }else if(counter%6==4){
                    temp->numPackageStart=token;
                }else if(counter%6==5){
                    temp->numPackageMid=token;
                } else if(counter%6==0){
                    temp->indices=token;
                }
                counter++;
            }
            temp->missionNum=missionNum;
            missionNum++;
            if (missionList== nullptr){
                temp->next=temp;
                missionList=temp;
            }else{
                temp->next=missionList->next;
                missionList->next=temp;
                missionList=temp;
            }
        }
    }

}
void System::deleteMission(int missionNum,string packageName) {
    MissionList *tempList=missionList->next;
    do {
        if (tempList->missionNum==missionNum)
            break;
        tempList=tempList->next;
    }while (tempList!=missionList->next);

    Mission *tempMission=tempList->mission;
    while (tempMission!= nullptr){
        if (tempMission->data==packageName)
            break;
        tempMission=tempMission->next;
    }

    if (tempMission->next!= nullptr){
        tempMission->next->prev=tempMission->prev;
    }
    if (tempMission->prev!= nullptr){
        tempMission->prev->next=tempMission->next;
    }

}
void System::addPackageToMission(string data,int missionNum) {
    MissionList *tempList=missionList->next;
    do {
        if (tempList->missionNum==missionNum)
            break;
        tempList=tempList->next;
    }while (tempList!=missionList->next);

    auto *temp=new Mission();
    Mission *last=tempList->mission;
    temp->data=data;
    temp->next= nullptr;

    if (tempList->mission== nullptr){
        temp->prev= nullptr;
        tempList->mission=temp;
    }else{
        while (last->next!= nullptr){
            last=last->next;
        }
        last->next=temp;
        temp->prev=last;
    }
}
void System::executeIndices(int missionNum,string cityName) {

    MissionList *tempList=missionList->next;
    do {
        if (tempList->missionNum==missionNum)
            break;
        tempList=tempList->next;
    }while (tempList!=missionList->next);

    City *tempCity=city->next;
    do {
        if (tempCity->name==cityName)
            break;
        tempCity=tempCity->next;
    }while (tempCity!=tempCity->next);
    string indice;
    istringstream iss(tempList->indices);
    while (getline(iss,indice,',')){
        Mission *tempMission=tempList->mission;
        for (int i = 0; i <stoi(indice)+1 ; ++i) {
            tempMission=tempMission->next;
        }

        addIndicesPackage(tempMission->data);
    }
    IndicesPackages *tempHead=indicesHead;
    while (tempHead!= nullptr){
        deleteMission(tempList->missionNum,tempHead->package);
        tempCity->packages.push(tempHead->package);
        tempHead=tempHead->next;
    }
}

void System::executeMissions() {
    MissionList *tempList=missionList->next;
    do {
        City *tempCity=city->next;
        do {
            //start station paketleri al, misyon doubly ekle, starttan sil
            if (tempCity->name==tempList->startStation){
                if (tempCity->packages.size()>=stoi(tempList->numPackageStart) && tempCity->trucks.size()>0){
                    string truckName=tempCity->trucks.front();
                    addPackageToMission(truckName,missionList->missionNum);
                    tempCity->trucks.dequeue();
                    string packageName;
                    for (int i = 0; i <stoi(tempList->numPackageStart); ++i) {
                        packageName=tempCity->packages.top();
                        tempCity->packages.pop();
                        addPackageToMission(packageName,missionList->missionNum);
                    }
                }
            }
            //midwaye gel midwayden kargoları al sonra indicates kadarı midwaye ekle, linkedlist missionu güncelle
            if (tempCity->name==tempList->midwayStation){
                if (tempCity->packages.size()>=stoi(tempList->numPackageMid)){
                    string packageName;
                    for (int i = 0; i <stoi(tempList->numPackageMid); ++i) {
                        packageName=tempCity->packages.top();
                        tempCity->packages.pop();
                        addPackageToMission(packageName,missionList->missionNum);
                    }
                    executeIndices(missionList->missionNum,tempCity->name);
                }
            }
            //target station gel mission list paketleri boşalt truckı koy
            if (tempCity->name==tempList->targetStation){
                Mission *tempMission=tempList->mission;
                tempCity->trucks.enqueue(tempMission->data);

                tempMission=tempMission->next;
                while (tempMission!= nullptr){
                    tempCity->packages.push(tempMission->data);
                    tempMission=tempMission->next;
                }
            }
            tempCity=tempCity->next;
        }while (tempCity!=city->next);
        tempList=tempList->next;
    }while (tempList!=missionList->next);
//    //print mission list
//    Mission *temp=missionList->mission;
//    while (temp!= nullptr){
//        temp=temp->next;
//    }
}

bool System::checkDest(const basic_string<char>& destName) const {
    //false city doesn't exist, true city already exist
    if (city!= nullptr){
        City *temp=city->next;
        do {
            if (temp->name==destName){
                return true;
            }
            temp=temp->next;
        }while (temp!=city->next);
    }
    return false;
}

void System::printBoard() {
    City *temp=city->next;
    do {
        resultFile<<temp->name<<endl;
        resultFile<<"Packages:"<<endl;
        temp->packages.printStack(resultFile);
        resultFile<<"Trucks:"<<endl;
        temp->trucks.printQueue(resultFile);
        resultFile<<"-------------"<<endl;
        temp=temp->next;
    }while (temp!=city->next);
}















