//
// Created by Ates on 12/16/2020.
//

#ifndef ASSIGNMENT3_SYSTEM_H
#define ASSIGNMENT3_SYSTEM_H
#include "Queue.h"
#include "Stack.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct City{
    string name;
    Queue<string> trucks;
    Stack<string> packages;
    City* next;
};
struct Mission{
    //mission doubly linked list
    string data;    //package
    Mission *next;
    Mission *prev;
};

struct MissionList{
    //A-B-C-x-y-z1,z2
    Mission *mission;    //doubly linked list head
    string startStation; //A
    string midwayStation; //B
    string targetStation; //C
    string numPackageStart; //x
    string numPackageMid;  //y
    string indices;    //z1,z2..
    int missionNum;
    MissionList *next;
};

class System {
    public:
    ifstream  destsFile;
    ifstream  packagesFile;
    ifstream  trucksFile;
    ifstream  missionsFile;
    ofstream  resultFile;

    City *city= nullptr;
    MissionList *missionList= nullptr;

    System(char *dests_file, char *packages_file, char *trucks_file, char *missions_file, char *result_file);
    ~System();
    void addCity();
    void addPackage();
    void addTruck();
    void addMission();
    void deleteMission(int missionNum,string packageName);
    void addPackageToMission(string data,int missionNum);
    void executeMissions();
    void printBoard();
    bool checkDest(const basic_string<char>& destName) const;
    void executeIndices(int missionNum, string cityName);
};


#endif //ASSIGNMENT3_SYSTEM_H
