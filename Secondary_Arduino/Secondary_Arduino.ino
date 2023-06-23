#include <Wire.h>
#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch
String file = "WS1/";
String format = ".wav";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);
  
  Wire.begin(8);
  Wire.onReceive(readInput);


  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(4);
  if (!SD.begin(8)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  /*tmrpcm.play("WS1/s.wav"); //cuts static
  delay(8000);
  tmrpcm.stopPlayback();//*/
  //tmrpcm.play("WS1/A2d.wav");
  //tmrpcm.play("WS1/A3d.wav");
  /*delay(1000);
  tmrpcm.disable();
  tmrpcm.setVolume(0);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(tmrpcm.isPlaying());
  delay(500);
}

void readInput(int num)
{
  //Serial.println(millis());
  String str;
  while(Wire.available()) {
        str.concat((char)Wire.read());    // Receive a byte as character
        //Serial.print(c);         // Print the character
    }
  //Serial.write(str.c_str());
  if (str.charAt(0) == 'A')
  {
    str.trim();
    String s = file + str + format;
    //Serial.println(s.c_str());
    tmrpcm.play(s.c_str());
  }
  else if (str.charAt(0) == 's')
  {
    tmrpcm.stopPlayback();
  }
  else if (str.charAt(0) == 'v')
  {
    str.trim();
    tmrpcm.setVolume((int)(str.charAt(1)-'0')); //set volume
  }
  //Serial.println(millis());
}
