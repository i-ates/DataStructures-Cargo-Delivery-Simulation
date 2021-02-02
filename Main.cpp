#include "System.h"
using namespace  std;
int main(int argc, char ** argv) {
    System mySystem(argv[1],argv[2],argv[3],argv[4],argv[5]);
    mySystem.addCity();
    mySystem.addTruck();
    mySystem.addPackage();
    mySystem.addMission();
    mySystem.executeMissions();
    mySystem.printBoard();
    return 0;
}

