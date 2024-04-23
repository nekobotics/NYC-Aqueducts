#include <FastLED.h>

#define DATA_PIN 9
#define CLOCK_PIN 19
#define NUMPIXELS 945

CRGB leds[NUMPIXELS];

const int Length = 80;
// const int CrotonLength = 82;
// const int CatskillLength = 395;
// const int DelawareLength = 432;

struct StreamControls {
  int RedHue[Length];
  int GreenHue[Length];
  int BlueHue[Length];
  int LastRed;
  int LastGreen;
  int LastBlue;
  int DuctLength;
  int DuctStart;

  void update(){
    LastRed = RedHue[Length - 1];
    LastGreen = GreenHue[Length - 1];
    LastBlue = BlueHue[Length - 1];

    for(int x = Length - 1; x >= 0; x--){
      if(x != 0){
        RedHue[x] = RedHue[x-1];
        GreenHue[x] = GreenHue[x-1];
        BlueHue[x] = BlueHue[x-1];
      }
      else{
        RedHue[x] = LastRed;
        GreenHue[x] = LastGreen;
        BlueHue[x] = LastBlue;
      }
    }
  }

  void run(){
    for(int x = DuctStart; x < DuctStart+DuctLength; x++){
      leds[x] = CRGB(BlueHue[Length-1 - (x-(Length *(x/Length)))], GreenHue[Length-1 - (x - (Length *(x/Length)))], RedHue[Length-1 - (x- (Length *(x/Length)))]);
    }
    update();
  }
};

StreamControls Delaware;
StreamControls Catskills;
StreamControls Croton;

unsigned long CurrentTime;

struct Time{
  unsigned long LastTriggered;
  long Delay;
};

Time DelawareTime = {0,10};
Time CrotonTime = {0,7};
Time CatskillsTime = {0,15};

void setup() { 
  Delaware.DuctLength = 432;
  Delaware.DuctStart = 477;

  Catskills.DuctLength = 395;
  Catskills.DuctStart = 0;

  Croton.DuctLength = 82;
  Croton.DuctStart = 395;
  
  Serial.begin(9600);
  FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB,DATA_RATE_MHZ(10)>(leds, NUMPIXELS);  // BGR ordering is typical
  FastLED.setBrightness(255);

  for(int x=0; x < Length; x++){
    Croton.BlueHue[x]= (250/2)-((200/2) * sin(x * ((3.14)/Length)));
    
    Catskills.BlueHue[x]= (250/2)-((210/2) * sin(x * ((3.14)/Length)));
    Catskills.GreenHue[x]= (248/2)-((208/2) * sin(x * ((3.14)/Length)));
    Catskills.RedHue[x]= (105/2)-((95/2) * sin(x * ((3.14)/Length)));
    
    Delaware.BlueHue[x]= (250/2)-((220/2) * sin(x * ((3.14)/Length)));
    Delaware.GreenHue[x]= (250/2)-((220/2) * sin(x * ((3.14)/Length)));
    Serial.println(Delaware.GreenHue[x]);
  }

  for(int x = 909; x < NUMPIXELS; x++){
    leds[x] = CRGB(0,0,250);
  }
}

void loop() {
  CurrentTime = millis();
  //Delaware.run();
  //DelawareFlow();

  if(CurrentTime >= DelawareTime.LastTriggered + DelawareTime.Delay){
    Delaware.run();
    DelawareTime.LastTriggered = CurrentTime;
  }

  if(CurrentTime >= CatskillsTime.LastTriggered + CatskillsTime.Delay){
    Catskills.run();
    CatskillsTime.LastTriggered = CurrentTime;
  }

  if(CurrentTime >= CrotonTime.LastTriggered + CrotonTime.Delay){
    Croton.run();
    CrotonTime.LastTriggered = CurrentTime;
  }


  FastLED.show();
  delay(10);
}