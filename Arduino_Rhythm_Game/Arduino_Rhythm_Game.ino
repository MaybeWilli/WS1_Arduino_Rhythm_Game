#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "beatmaps.h"
#include "Mascot.h"

#define TFT_CS 10 //chip select
#define TFT_DC 7 //data/command
#define TFT_RST 8 //reset
#define X_PIN A3 //joystick x
#define Y_PIN A2 //joystick y
#define B_PIN A1 //button

//general menu things
String userInput;
unsigned long int t1;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
int cursorX = 100; //position of cursor
int cursorY = 100;
uint8_t cSpeed = 15; //speed of cursor
uint8_t cRadius = 8;
uint8_t state = 0; //0 = menu, 1 = settings, 2 = song select, 3 = playing, 4 = endcard, 5 = developer testing
int8_t cState = 0; //cursor state
uint8_t pBState = 0; //previous button state
uint8_t pcmVolume = 4;
uint8_t pPcmVolume = 4; //previous pPcmVolume
bool canChange = false;
bool isNormalMode = true;

//game cursor variables
const uint8_t mapRadius = 100;
const uint8_t buttonRadius = 8;
const uint8_t cXList[] = {0+120, sin(3.14/4)*mapRadius+120, mapRadius+120, sin(3.14/4)*mapRadius+120, 0+120, -sin(3.14/4)*mapRadius+120, -mapRadius+120, -sin(3.14/4)*mapRadius+120};
const int cYList[] = {-mapRadius+160, -sin(3.14/4)*mapRadius+160, 0+160, sin(3.14/4)*mapRadius+160, mapRadius+160, sin(3.14/4)*mapRadius+160, 0+160, -sin(3.14/4)*mapRadius+160};
int8_t buttonIndex = 0;
int8_t pButtonIndex = 0;


//buffer and buffer helpers
uint8_t songIndex = 0; //currently selected song
const uint8_t buffSize = 10;
Node nodes[buffSize];
uint8_t currentBeat; //current circle, also the least recent circle on the screen
uint8_t freeBeat; //next available free buffer position
unsigned long int startTime = 0; //time that the song starts
uint8_t circleRadius = 45;
bool hasFreeSpot = false;
const uint8_t margin = 200;
const int appearMargin = 500;
const int waitMargin = 800;
const uint8_t greyRadius = buttonRadius; //probably change later
const uint8_t lightRadius = 40;
const uint8_t diff = 20;
const uint8_t divFactor = appearMargin/diff;
const uint8_t checkRadius = 30;
int currentMapPos = 0; //the current circle to read from the map
uint8_t buffUsage = buffSize;
int score = 0;
const int bXList[] = {0, sin(3.14/4)*mapRadius, mapRadius, sin(3.14/4)*mapRadius, 0, -sin(3.14/4)*mapRadius, -mapRadius, -sin(3.14/4)*mapRadius};
const int bYList[] = {-mapRadius, -sin(3.14/4)*mapRadius, 0, sin(3.14/4)*mapRadius, mapRadius, sin(3.14/4)*mapRadius, 0, -sin(3.14/4)*mapRadius};

//deal with cursor color
bool cIsBlue = true;
uint16_t cColor = ST77XX_MAGENTA;
unsigned long int colorStartTime;
int cWaitTime = 300;


//const PROGMEM int test[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  Wire.onReceive(testInput);

  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(B_PIN, INPUT);

  tft.init(240, 320, SPI_MODE0);
  tft.fillScreen(ST77XX_BLACK);
  drawInitMenu();
  /*Serial.println(pgm_read_dword_near(timeList[1]+97));
  Serial.println(pgm_read_dword_near(timeList[1]+98));
  Serial.println(pgm_read_dword_near(timeList[1]+99));*/
  //Serial.println(bXList[7]);
  //Serial.println(-sin(3.14/4)*mapRadius);
  /*for (int i = 0; i < 8; i++)
  {
    Serial.println(bXList[i]);
  }*/
  /*songIndex = 1;
  loadInitBuffer();
  for (int i = 0; i < buffSize; i++)
  {
    Serial.print(nodes[i].pos);
    Serial.print(" ");
    Serial.print(nodes[i].t);
    Serial.print("\n");
  }*/

  //temp
  //drawInitArena();
  /*tft.drawCircle(100, 150, 50, ST77XX_BLUE);
  for (int i = 0; i < 100; i++)
  {
    tft.drawCircle(100, 150, 50+i, ST77XX_BLUE);
    tft.drawCircle(100, 150, 50+i-1, ST77XX_BLACK);

    //tft.drawCircle(100, 175, 50+i-1, ST77XX_BLACK);
    //tft.drawCircle(100, 175, 50+i, ST77XX_YELLOW);

    //tft.drawCircle(100, 150+i, 50, ST77XX_BLUE);
    //tft.drawCircle(100, 150+i-1, 50, ST77XX_BLACK);

    delay(30);
  }//*/
  //delay(1000);
  //tft.fillScreen(ST77XX_YELLOW);

  /*Wire.beginTransmission(8);
  Wire.write("AAA");
  Wire.endTransmission();
  t1 = millis();*/
  /*for (int i = 0; i < 6; i++)
  {
    Serial.println(pgm_read_word_near(posList[0]+i));
  }*/
  //songIndex = 0;
  //loadInitBuffer();
  //printBuffer();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available())
  {
    userInput = Serial.readString();
    Wire.beginTransmission(8);
    Wire.write(userInput.c_str());
    Wire.endTransmission();
    Serial.println("Lalalala!");
  }

  /*Serial.print("X = ");
  Serial.print(x);
  Serial.print(" Y = ");
  Serial.print(y);
  Serial.print("\n");*/
  if (state == 0)
  {
    readMenu();
  }
  else if (state == 1)
  {
    readSettings();
  }
  else if (state == 2)
  {
    readSongMenu();
  }
  else if (state == 3)
  {
    /*Serial.print(currentMapPos);
    Serial.print(" ");
    Serial.print(currentBeat);
    Serial.print(" ");
    Serial.print(pgm_read_byte_near(posList[songIndex]+currentMapPos));
    Serial.print(" ");
    Serial.print(pgm_read_dword_near(timeList[songIndex]+currentMapPos));
    Serial.print(" ");
    Serial.print(buffUsage);
    Serial.print("\n");*/
    /*for (int i = 0; i < buffSize; i++)
    {
      Serial.print(currentMapPos);
      Serial.print(" ( ");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(nodes[i].t);
      Serial.print(" ");
      Serial.print(nodes[i].pX);
      Serial.print(" ");
      Serial.print(nodes[i].pY);
      Serial.print(" ");
      Serial.print(nodes[i].pos);
      Serial.print(" ");
      Serial.print(nodes[i].isOn);
      Serial.print(" ");
      Serial.print(nodes[i].isActive);
      Serial.print(" ");
      Serial.print(")");
    }
    Serial.print("\n");//*/
    
    updateCircles();
    readCursor();
    //readCursor2();
    if (!isNormalMode)
    {
      readButtonInput2();
    }
    if (!cIsBlue)
    {
      if (millis() - colorStartTime > cWaitTime)
      {
        cIsBlue = true;
        cColor = ST77XX_MAGENTA;
        //tft.drawCircle(cursorX, cursorY, cRadius, cColor);
        tft.drawCircle(cXList[buttonIndex], cYList[buttonIndex], buttonRadius, cColor);
      }
    }
  }
  else if (state == 4) //end of song screen
  {
    readEndcard();
  }
  else
  {
    //readCursor2();
  }
  delay(100);
}

void tftPrint(int x, int y, int tSize, uint16_t tColor, String s)
{
  tft.setTextColor(tColor);
  tft.setTextSize(tSize);
  tft.setCursor(x, y);
  tft.print(s);
}

void testInput(int num)
{
  String str;
  while(Wire.available()) {
        str.concat((char)Wire.read());    // Receive a byte as character
        //Serial.print(c);         // Print the character
    }
  
  Serial.write(millis()-t1);
}

void drawCursor()
{
  tft.drawCircle(cXList[buttonIndex], cYList[buttonIndex], buttonRadius, cColor);
  tft.drawCircle(cXList[pButtonIndex], cYList[pButtonIndex], buttonRadius, ST77XX_BLUE);
  //tft.drawCircle(xpos, ypos, cRadius, cColor);
}

void readCursor()
{
  int x = analogRead(X_PIN);
  int y = analogRead(Y_PIN);
  uint8_t i = 0;

  if (x < 300)
  {
    if (y < 300)
    {
      i = 7;
    }
    else if (y > 700)
    {
      i = 5;
    }
    else
    {
      i = 6;
    }
  }
  else if (x > 700)
  {
    if (y < 300)
    {
      i = 1;
    }
    else if (y > 700)
    {
      i = 3;
    }
    else
    {
      i = 2;
    }
  }
  else if (y < 300)
  {
    i = 0;
  }
  else if (y > 700)
  {
    i = 4;
  }
  else
  {
    i = 255;
  }

  if (i != pButtonIndex && i!= 255)
  {
    //Serial.println(i);
    buttonIndex = i;
    drawCursor();
    pButtonIndex = buttonIndex;
  }
}

void drawInitMenu()
{
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(35, 40);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(3);
  tft.print("W(innik)S1\n    V 0.1");//*/
  //tftPrint(35, 40, 3, ST77XX_BLUE, "W(innik)S1\n    V 0.1");

  tft.drawBitmap(31, 65, suisei, 176, 176, ST77XX_BLUE);

  tft.setCursor(100, 245);
  tft.setTextSize(2);
  tft.print("Play");

  tft.setCursor(75, 285);
  tft.print("Settings");//*/
  //tftPrint(100, 245, 2, ST77XX_BLUE, "Play");
  //tftPrint(75, 285, 2, ST77XX_BLUE, "Settings");

  drawMenuCursor(cState);
}

void drawMenuCursor(int state)
{
  tft.setTextSize(2);
  if (state==0)
  {
    tft.setTextColor(ST77XX_BLUE);
    tft.setCursor(145, 245);
    tft.print("<");
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(170, 285);
    tft.print("<");//*/
    //27372
    //tftPrint(145, 245, 2, ST77XX_BLUE, "<");
    //tftPrint(170, 285, 2, ST77XX_BLACK, "<");
  }
  else
  {
    tft.setTextColor(ST77XX_BLUE);
    tft.setCursor(170, 285);
    tft.print("<");
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(145, 245);
    tft.print("<");
  }
}

void drawInitSettings()
{
  tft.setTextColor(ST77XX_BLUE);
  tft.setCursor(50, 50);
  tft.setTextSize(3);
  tft.print("Settings");

  tft.setTextSize(2);
  tft.setCursor(100, 100);
  tft.print("Back");

  tft.setCursor(65, 175);
  tft.print("Volume: ");
  tft.setCursor(155, 175);
  tft.print((char)(pcmVolume+'0'));
  tft.setCursor(40, 225);
  tft.print("Higher volume");
  tft.setCursor(55, 250);
  tft.print("Lower volume");
  if (isNormalMode)
  {
    tft.setCursor(55, 275);
    tft.print("Mode: Normal");
  }
  else 
  {
    tft.setCursor(55, 275);
    tft.print(" Mode: Hard");
  }

  drawSettingsCursor(cState);
}

void drawSettingsCursor(uint8_t cState)
{
  tft.setTextSize(2);
  if (cState == 0)
  {
    tft.setTextColor(ST77XX_BLUE);
  }
  else
  {
    tft.setTextColor(ST77XX_BLACK);
  }
  tft.setCursor(145, 100);
  tft.print("<");
  if (cState == 1)
  {
    tft.setTextColor(ST77XX_BLUE);
  }
  else
  {
    tft.setTextColor(ST77XX_BLACK);
  }
  tft.setCursor(195, 225);
  tft.print("<");
  if (cState == 2)
  {
    tft.setTextColor(ST77XX_BLUE);
  }
  else
  {
    tft.setTextColor(ST77XX_BLACK);
  }
  tft.setCursor(200, 250);
  tft.print("<");
  if (cState == 3)
  {
    tft.setTextColor(ST77XX_BLUE);
  }
  else
  {
    tft.setTextColor(ST77XX_BLACK);
  }
  tft.setCursor(200, 275);
  tft.print("<");
  
}

void redrawVolume(uint8_t v)
{
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.setCursor(155, 175);
  tft.print((char)(v+'0'));
  tft.setTextColor(ST77XX_BLUE, 0x0000);
}

void redrawMode(bool mode)
{
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  if (mode)
  {
    tft.setCursor(55, 275);
    tft.print("Mode: Normal");
  }
  else
  {
    tft.setCursor(55, 275);
    tft.print(" Mode: Hard ");
  }
  tft.setTextColor(ST77XX_BLUE, 0x0000);
}

void readSettings()
{
  int y = analogRead(Y_PIN);
  bool needsUpdate = false;
  bool bState = digitalRead(B_PIN);
  bool isPress = (bState == 1 && pBState == 0);
  pBState = bState;
  //Serial.println(bState);

  if (y > 700 && cState < 3)
  {
    needsUpdate = true;
    cState += 1;
  }
  else if (y < 300 && cState > 0)
  {
    needsUpdate = true;
    cState -= 1;
  }

  if (needsUpdate)
  {
    drawSettingsCursor(cState);
  }

  if (isPress)
  {
    if (cState == 0)
    {
      //go back to main menu
      Serial.println(pPcmVolume);
      Serial.println(pcmVolume);
      if (pcmVolume != pPcmVolume) //update volume if needed
      {
        //String s = 'v'+(char)(pcmVolume+'0');
        String s = "v";
        s.concat((char)(pcmVolume+'0'));
        Serial.println(s);
        Wire.beginTransmission(8);
        Wire.write(s.c_str());
        Wire.endTransmission();
        pPcmVolume = pcmVolume;
      }
      state = 0;
      drawInitMenu();
    }
    else if (cState == 1)
    {
      //more volume
      pcmVolume++;
      redrawVolume(pcmVolume);
      
    }
    else if (cState == 2)
    {
      pcmVolume--;
      redrawVolume(pcmVolume);
    }
    else
    {
      isNormalMode = !isNormalMode;
      redrawMode(isNormalMode);
    }
  }
}

void readMenu()
{
  int y = analogRead(Y_PIN);
  bool needsUpdate = false;
  bool bState = digitalRead(B_PIN);
  bool isPress = (bState == 1 && pBState == 0);
  pBState = bState;
  //Serial.println(bState);

  if (y > 700 && cState == 0)
  {
    needsUpdate = true;
    cState = 1;
  }
  else if (y < 300 && cState == 1)
  {
    needsUpdate = true;
    cState = 0;
  }

  if (needsUpdate)
  {
    drawMenuCursor(cState);
  }

  if (isPress)
  {
    if (cState == 0)
    {
      //open play menu
      state = 2;
      tft.fillScreen(ST77XX_BLACK);
      drawInitSongMenu();
    }
    else
    {
      //open settings
      cState = 0;
      tft.fillScreen(ST77XX_BLACK);
      drawInitSettings();
      state = 1;
    }
  }
}

void printSongName(uint8_t num)
{
  tft.setTextColor(ST77XX_BLUE, ST77XX_BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 150);
  tft.print("                 ");
  tft.setTextColor(ST77XX_BLUE, 0x0000);
  if (num == filesLen)
  {
    tft.setCursor(100, 150);
    tft.print("Back");
  }
  else
  {
    int xPos = 110 - songNames[num].length()/2*10;
    //Serial.println(xPos);
    //Serial.println(songNames[num].length()/2);
    tft.setCursor(xPos, 150);
    tft.print(songNames[num].c_str());
  }
}

void drawInitSongMenu()
{
  tft.drawRect(15, 15, 210, 290, ST77XX_BLUE);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.setCursor(0, 150);
  tft.print("<");
  tft.setCursor(225,150);
  tft.print(">");
  printSongName(0);
}

void readSongMenu()
{
  int x = analogRead(X_PIN);
  bool needsUpdate = false;
  bool bState = digitalRead(B_PIN);
  bool isPress = (bState == 1 && pBState == 0);
  pBState = bState;
  //Serial.println(bState);

  if (x > 700 && canChange)
  {
    needsUpdate = true;
    cState++;
    canChange = false;
    if (cState > filesLen)
    {
      cState = 0;
    }
  }
  else if (x < 300 && canChange)
  {
    needsUpdate = true;
    cState--;
    if (cState < 0)
    {
      cState = filesLen;
    }
    canChange = false;
  }
  else
  {
    canChange = true;
  }

  if (needsUpdate)
  {
    printSongName(cState);
  }

  if (isPress)
  {
    if (cState == filesLen)
    {
      //back to main menu
      cState = 0;
      state = 0;
      tft.fillScreen(ST77XX_BLACK);
      drawInitMenu();
    }
    else
    {
      //start playing a song (finally lol)
      state = 3;
      tft.fillScreen(ST77XX_BLACK);
      drawInitArena();
      songIndex = cState;
      currentMapPos = 0;
      currentBeat = 0;
      loadInitBuffer();
      cState = 0;
      cColor = ST77XX_MAGENTA;
      buffUsage = buffSize;
      score = 0;
      //temp
      //startTime = millis();
      startSong();
    }
  }
}

void loadInitBuffer() //assuming that the buffer is empty, load 10 circles into it. Assumes that the song is longer than 10 circles
{
  for (int i = 0; i < buffSize; i++)
  {
    //nodes[i] = new Node(pgm_read_word_near(posList[songIndex]+j), pgm_read_word_near(posList[songIndex]+j+1), pgm_read_word_near(timeList[songIndex]+i));
    nodes[i].pos = pgm_read_byte_near(posList[songIndex]+i);
    nodes[i].t = pgm_read_dword_near(timeList[songIndex]+i);
    //nodes[i].pPhase = lightRadius;
  }

  currentMapPos += buffSize;
}

void startSong()
{
  Serial.println(millis());
  Wire.beginTransmission(8);
  Wire.write("s");
  Wire.endTransmission();
  delay(2000);
  Wire.beginTransmission(8);
  Wire.write(fileNames[songIndex].c_str());
  Wire.endTransmission();
  startTime = millis();
  Serial.println(startTime);
}

/*void printBuffer()
{
  for (int i = 0; i < buffSize; i++)
  {
    Serial.print(nodes[i].x);
    Serial.print(" ");
    Serial.print(nodes[i].y);
    Serial.print(" ");
    Serial.print(nodes[i].t);
    Serial.print("\n");
  }
}*/

void loadNewIntoBuffer(int buffPos)
{
  nodes[buffPos].pos = pgm_read_byte_near(posList[songIndex]+currentMapPos);
  nodes[buffPos].t = pgm_read_dword_near(timeList[songIndex]+currentMapPos);
  nodes[buffPos].isActive = false;
  currentMapPos++;
}

void eraseCircle(uint8_t i)
{
  nodes[i].isActive = false;
  tft.drawCircle(nodes[i].pX, nodes[i].pY, greyRadius, ST77XX_BLACK);
  //tft.drawCircle(nodes[i].x, nodes[i].y, greyRadius, ST77XX_BLACK);
  //tft.drawCircle(nodes[i].x, nodes[i].y, nodes[i].pPhase, ST77XX_BLACK);
  Serial.print(currentMapPos);
  Serial.print(" ");
  Serial.print(songLen[songIndex]);
  Serial.print(" ");
  Serial.print(songIndex);
  Serial.print(" ");
  Serial.print(buffUsage);
  Serial.print("\n");//*/
  if (currentMapPos < songLen[songIndex]) //if there are more to read
  {
    //Serial.println("Why");
    loadNewIntoBuffer(currentBeat);
  }
  else
  {
    Serial.println("None to read");
    buffUsage -= 1;
    if (buffUsage <= 1)
    {
      Serial.println("End of song");
      Wire.beginTransmission(8);
      Wire.write("s");
      Wire.endTransmission();
      cState = 0;
      state = 4;
      tft.fillScreen(ST77XX_BLACK);
      tft.drawCircle(cXList[buttonIndex], cYList[buttonIndex], buttonRadius, ST77XX_BLACK);
      drawInitEndcard();
    }
  }//*/
  currentBeat++;
  if (currentBeat >= buffSize)
  {
    currentBeat = 0;
  }
}

void drawInitArena()
{
  tft.drawCircle(120, 160, mapRadius, ST77XX_BLUE);
  for (int i = 0; i < 8; i++)
  {
    tft.drawCircle(cXList[i], cYList[i], buttonRadius, ST77XX_BLUE);
  }
}

void updateCircles() //keep track of time, and update the songs
{
  //loop through buffer
  for (int i = 0; i < buffSize; i++)
  {
    if (nodes[i].isActive) //already appears on screen
    {
      if ((millis()-startTime)-nodes[i].t < 1000) //get rid of old circles (watch out for overflow)
      {
        if (isNormalMode)
        {
          if (nodes[i].pos == buttonIndex)
          {
            score++;
            cIsBlue = false;
            cColor = ST77XX_GREEN;
            colorStartTime = millis();
            tft.drawCircle(cXList[buttonIndex], cYList[buttonIndex], buttonRadius, cColor);
          }
        }
        //Serial.println("1");
        eraseCircle(i);
      }
      else //if the circle is supposed to still be there, draw a circle around it
      {
        //uint8_t rad = greyRadius + (nodes[i].t-(millis()-startTime)) / divFactor;
        float fact = 1.0f-(nodes[i].t-(millis()-startTime))/(waitMargin*1.0f);
        int x = fact*bXList[nodes[i].pos]+120;
        int y = fact*bYList[nodes[i].pos]+160;
        /*if (i == 6)
        {
          /*Serial.println(fact);
          Serial.print(" ");
          Serial.print(x);
          Serial.print(" ");
          Serial.print(y);
          Serial.print(" ");
          Serial.print(fact*bXList[nodes[i].pos]);
          Serial.print(" ");
          Serial.print(bXList[nodes[i].pos]);
          Serial.print(" ");
          Serial.print(nodes[i].pos);
          Serial.print("\n");
        }//*/
          /*Serial.print(greyRadius + (nodes[i].t-(millis()-startTime))/divFactor);
          Serial.print(" ");
          Serial.print(greyRadius);
          Serial.print(" ");
          Serial.print(nodes[i].t);
          Serial.print(" ");
          Serial.print(millis()-startTime);
          Serial.print(" ");
          Serial.print((nodes[i].t-(millis()-startTime)) / divFactor);
          Serial.print(" ");
          Serial.print(divFactor);
          Serial.print("\n");
        }//*/
        //Serial.println(greyRadius + (nodes[i].t-(millis()-startTime) / divFactor));
        //Serial.println(fact);
        tft.drawCircle(x, y, greyRadius, ST77XX_CYAN);
        tft.drawCircle(nodes[i].pX, nodes[i].pY, greyRadius, ST77XX_BLACK);
        nodes[i].pX = x;
        nodes[i].pY = y;
        //tft.drawCircle(nodes[i].x, nodes[i].y, rad, ST77XX_YELLOW);
        //nodes[i].pPhase = rad;
      }
    }
    else if (nodes[i].t-(millis()-startTime) < waitMargin) //if it is time to AWAKEN
    {
      float fact = 1.0f-(nodes[i].t-(millis()-startTime))/(waitMargin*1.0f);
      int x = fact*bXList[nodes[i].pos]+120;
      int y = fact*bYList[nodes[i].pos]+160;
      //Serial.println("2");
      tft.drawCircle(x, y, greyRadius, ST77XX_CYAN);
      nodes[i].pX = x;
      nodes[i].pY = y;
      //tft.drawCircle(nodes[i].x, nodes[i].y, lightRadius, ST77XX_YELLOW);
      nodes[i].isActive = true;
    }
  }
}

void readButtonInput2() //check the position of the click, and figure out if it's inside of a circle
{
  int x = analogRead(X_PIN);
  bool bState = digitalRead(B_PIN);
  bool isPress = (bState == 1 && pBState == 0);
  pBState = bState;
  
  if (isPress)
  {
    Serial.print(nodes[currentBeat].t-(millis()-startTime));
    Serial.print(" ");
    Serial.print(buttonIndex);
    Serial.print(" ");
    Serial.print(nodes[currentBeat].pos);
    Serial.print(" ");
    Serial.print(margin);
    Serial.print(" ");
    Serial.print(currentBeat);
    Serial.print("\n");
    if (buttonIndex == nodes[currentBeat].pos && nodes[currentBeat].t-(millis()-startTime) < margin) //if it's close enough to the circle and within time
    {
      //Serial.println(dist);
      cIsBlue = false;
      cColor = ST77XX_GREEN;
      score++;
      colorStartTime = millis();
      tft.drawCircle(cXList[buttonIndex], cYList[buttonIndex], buttonRadius, cColor);
      //tft.drawCircle(cursorX, cursorY, cRadius, cColor);
      eraseCircle(currentBeat);
    }
    else
    {
      Serial.println("Too far");
      cIsBlue = false;
      cColor = ST77XX_RED;
      tft.drawCircle(cXList[buttonIndex], cYList[buttonIndex], buttonRadius, cColor);
      //tft.drawCircle(cursorX, cursorY, cRadius, cColor);
      colorStartTime = millis();
    }
  }
}

unsigned long int square(int x)
{
  return x*x;
}

void drawInitEndcard()
{
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(2);
  tft.setCursor(80, 100);
  tft.print("Score: ");
  tft.print(score);
  tft.setCursor(80, 150);
  tft.print("Rank: ");
  if (score/(songLen[songIndex]*1.0f) >= 0.90)
  {
    tft.print("S");
    tft.setCursor(80, 175);
    tft.print("Wowza!");
  }
  else if (score/(songLen[songIndex]*1.0f) >= 0.80)
  {
    tft.print("A");
    tft.setCursor(80, 175);
    tft.print("Nice!");
  }
  else if (score/(songLen[songIndex]*1.0f) >= 0.70)
  {
    tft.print("B");
    tft.setCursor(80, 175);
    tft.print("Lol");
  }
  else if (score/(songLen[songIndex]*1.0f) >= 0.60)
  {
    tft.print("C");
    tft.setCursor(80, 175);
    tft.print("Lmao git gud");
  }
  else
  {
    tft.print("D");
    tft.setCursor(80, 175);
    tft.print("Deez...");
  }

  tft.setCursor(55, 200);
  tft.print("Click to return");
}

void readEndcard()
{
  bool bState = digitalRead(B_PIN);
  bool isPress = (bState == 1 && pBState == 0);
  pBState = bState;

  if (isPress)
  {
    state = 0;
    tft.fillScreen(ST77XX_BLACK);
    drawInitMenu();
  }
}
