#include <avr/pgmspace.h>
#include "A2_map.h"
#include "A3_map.h"

struct Node {
  uint8_t pos;
  int x, y;
  int pX, pY;
  unsigned long int t;
  bool isOn;
  bool isActive;

  Beat(){
    pos = 0;
    x = 0;
    y = 0;
    pX = 0;
    pY = 0;
    t = 0; 
    isOn = false;
    isActive = false;
  }
};

String fileNames[] = {"A2", "A3d"};
String songNames[] = {"Demon Slayer OP", "Stellar Stellar"};
uint8_t filesLen = 2;

//const PROGMEM int a2dPos[] = {50, 50, 100, 100, 150, 150, 200, 200, 250, 250, 200, 250, 150, 250, 150, 200, 150, 100, 150, 150, 100, 150, 200, 250, 100, 150, 250, 100, 100, 250};
//const PROGMEM unsigned long int a2dTime[] = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};
//const PROGMEM int a3dPos[] = {200, 200, 150, 200, 100, 200};
//const PROGMEM unsigned long int a3dTime[] = {1000, 2000, 3000};
//const PROGMEM uint8_t a3dPos[] = {7, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6};
//const PROGMEM int a3dPos[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//const PROGMEM unsigned long int a3dTime[] = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};

uint8_t* posList[] = {&a2dPos[0], &a3dPos[0]};
unsigned long int* timeList[] = {&a2dTime[0], &a3dTime[0]};
uint8_t songLen[] = {135, 170};
//uint8_t songLen[] = {135, 171};


//const Song
