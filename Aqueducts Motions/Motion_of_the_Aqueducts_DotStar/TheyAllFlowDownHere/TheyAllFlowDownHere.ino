#include <FastLED.h>

#define DATA_PIN 9
#define CLOCK_PIN 19
#define NUMPIXELS 864

const int Length = 80;
int ColorHue[Length];

struct Color {
  int RedHue[Length];
  int GreenHue[Length];
  int BlueHue[Length];
  int WhiteHue[Length];
  int LastRed;
  int LastGreen;
  int LastBlue;
  int LastWhite;
};

Color CatskillsHue;
Color CrotonHue;
Color DelawareHue;

const int CatskillsLength = 36;
const int CrotonLength = 119;
const int DelawareLength = 200;

unsigned long Currenttime;

struct Time{
  unsigned long LastTriggered;
  long Delay;
};

Time CatskillsUpdate = {0,10};
Time CrotonUpdate = {0,7};
Time DelawareUpdate = {0,9};

CRGB leds[NUMPIXELS];

void WaveSetUp(){
  for(int x = 0; x < Length; x++){
    CatskillsHue.BlueHue[x]= (200/2)-((200/2) * sin(x * ((3.14)/Length)));

    CrotonHue.GreenHue[x]= (206/2)-((206/2) * sin(x * ((3.14)/Length)));
    CrotonHue.RedHue[x]= (135/2)-((135/2) * sin(x * ((3.14)/Length)));
    CrotonHue.BlueHue[x]= (220/2)-((220/2) * sin(x * ((3.14)/Length)));

    DelawareHue.BlueHue[x] = (220/2)-((220/2) * sin(x * ((3.14)/Length)));
    DelawareHue.GreenHue[x] = (220/2)-((220/2) * sin(x * ((3.14)/Length)));
  }
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB,DATA_RATE_MHZ(10)>(leds, NUMPIXELS);  // BGR ordering is typical
  FastLED.setBrightness(255);

  WaveSetUp();
}

void Catskills(int Start){
  for(int  x= Start; x < Start + CatskillsLength; x++){leds[x] = CRGB(CatskillsHue.BlueHue[x - (Length*(x/Length))]+10,0,0);}

  CatskillsHue.LastBlue = CatskillsHue.BlueHue[Length-1];
  for(int x = (Length -1); x >= 0; x--){
    if(x != 0){CatskillsHue.BlueHue[x] = CatskillsHue.BlueHue[x-1];}
    else{CatskillsHue.BlueHue[x] = CatskillsHue.LastBlue;}
  }
}

void Croton(int Start){
  for(int  x = Start; x < Start + CrotonLength; x++){leds[x] = CRGB(CrotonHue.BlueHue[x - (Length*(x/Length))]+10,CrotonHue.GreenHue[x - (Length*(x/Length))],CrotonHue.RedHue[x - (Length*(x/Length))]);}

  CrotonHue.LastBlue = CrotonHue.BlueHue[Length-1];
  CrotonHue.LastGreen = CrotonHue.GreenHue[Length-1];
  CrotonHue.LastRed = CrotonHue.RedHue[Length-1];
  for(int x = Length-1; x >= 0; x--){
    if(x!=0){
      CrotonHue.BlueHue[x] = CrotonHue.BlueHue[x-1];
      CrotonHue.GreenHue[x] = CrotonHue.GreenHue[x-1];
      CrotonHue.RedHue[x] = CrotonHue.RedHue[x-1];
    }
    else{
      CrotonHue.BlueHue[x] = CrotonHue.LastBlue;
      CrotonHue.GreenHue[x] = CrotonHue.LastGreen;
      CrotonHue.RedHue[x] = CrotonHue.LastRed;
    }
  }
}

void Delaware(int Start){
  for(int  x= Start; x < Start + DelawareLength; x++){leds[x] = CRGB(DelawareHue.GreenHue[x - (Length*(x/Length))]+10,DelawareHue.GreenHue[x - (Length*(x/Length))],0);}

  DelawareHue.LastBlue = DelawareHue.BlueHue[Length-1];
  DelawareHue.LastGreen = DelawareHue.GreenHue[Length-1];
  for(int x = Length-1; x >= 0; x--){
    if(x!=0){
      DelawareHue.BlueHue[x]= DelawareHue.BlueHue[x-1];
      DelawareHue.GreenHue[x]= DelawareHue.GreenHue[x-1];
    }
    else{
      DelawareHue.BlueHue[x] = DelawareHue.LastBlue;
      DelawareHue.GreenHue[x] = DelawareHue.LastGreen;
    }
  }
}

void loop() {
  Currenttime = millis();
  
  if(Currenttime >= CatskillsUpdate.Delay + CatskillsUpdate.LastTriggered){
    Catskills(0);
    CatskillsUpdate.LastTriggered = Currenttime;
  }
  
  if(Currenttime >= CrotonUpdate.Delay + CrotonUpdate.LastTriggered){
    Croton(CatskillsLength);
    CrotonUpdate.LastTriggered = Currenttime;
  }

  if(Currenttime >= DelawareUpdate.Delay + DelawareUpdate.LastTriggered){
    Delaware(CrotonLength + CatskillsLength);
    DelawareUpdate.LastTriggered = Currenttime;
  }

  FastLED.show();
}
