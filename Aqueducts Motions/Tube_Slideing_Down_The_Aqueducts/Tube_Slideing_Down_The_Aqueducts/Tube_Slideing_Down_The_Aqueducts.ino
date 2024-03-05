#include <Adafruit_NeoPixel.h>

#define Pixel_Pin 9
#define NUMPIXELS 156
#define BRIGHTNESS 255

const int Length = 20;

struct Color {
  int RedHue[Length];
  int GreenHue[Length];
  int BlueHue[Length];
  int LastRed;
  int LastGreen;
  int LastBlue;
};

Color StreamOne;
Color StreamTwo;

const int StripTwoLength = 36;
const int StripOneLength = 125;

unsigned long time;

struct Time{
  unsigned long LastTriggered;
  long Delay;
};

Time StreamOneTime = {0,10};
Time StreamTwoTime = {0,7};

int NumStripsOne;
int NumStripsTwo;

Adafruit_NeoPixel strip(NUMPIXELS, Pixel_Pin, NEO_GRBW + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  strip.setBrightness(255);
  Serial.begin(9600);

  NumStripsOne = StripOneLength/Length;
  NumStripsTwo = StripTwoLength/Length;

  for(int x=0; x < Length; x++){
    StreamOne.BlueHue[x]= (200/2)-((200/2) * sin(x * ((3.14)/Length)));
    StreamTwo.GreenHue[x]= (206/2)-((206/2) * sin(x * ((3.14)/Length)));
    StreamTwo.RedHue[x]= (135/2)-((135/2) * sin(x * ((3.14)/Length)));
    StreamTwo.BlueHue[x]= (220/2)-((220/2) * sin(x * ((3.14)/Length)));
    //Serial.println(ColorHue[x]);
  }
}

void StripOne(){
  for(int  i= 0; i < NumStripsOne+1; i++){
    for(int x = 0; x < Length; x++){
      if((i*Length)+x <= StripOneLength){strip.setPixelColor((x+(i*(Length))),0,0,StreamOne.BlueHue[x]+30);}
    }
  }
}

void StripTwo(){
 for(int  i= 0; i < NumStripsTwo+1; i++){
    for(int x = 0; x < Length; x++){
      strip.setPixelColor((x+(i*(Length)))+125,StreamTwo.RedHue[x],StreamTwo.GreenHue[x],StreamTwo.BlueHue[x]+30);
    }
  }
}

void loop() {
  time = millis();

  if(time >= StreamOneTime.LastTriggered + StreamOneTime.Delay){
    StripOne();


    StreamOne.LastBlue = StreamOne.BlueHue[Length-1];
    StreamOne.LastGreen = StreamOne.GreenHue[Length-1];
    StreamOne.LastRed = StreamOne.RedHue[Length-1];
    for(int x = (Length-1); x >= 0; x--){
      if(x!=0){
        StreamOne.BlueHue[x]=StreamOne.BlueHue[x-1];
        StreamOne.GreenHue[x]=StreamOne.GreenHue[x-1];
        StreamOne.RedHue[x]=StreamOne.RedHue[x-1];
      } 
      else {
        StreamOne.BlueHue[x]=StreamOne.LastBlue;
        StreamOne.GreenHue[x]=StreamOne.LastGreen;
        StreamOne.RedHue[x]=StreamOne.LastRed;
      }
    }

    StreamOneTime.LastTriggered = time;
  }

  if(time >= StreamTwoTime.LastTriggered + StreamTwoTime.Delay){
    StripTwo();


    StreamTwo.LastBlue = StreamTwo.BlueHue[Length-1];
    StreamTwo.LastGreen = StreamTwo.GreenHue[Length-1];
    StreamTwo.LastRed = StreamTwo.RedHue[Length-1];
    for(int x = (Length-1); x >= 0; x--){
      if(x!=0){
        StreamTwo.BlueHue[x]=StreamTwo.BlueHue[x-1];
        StreamTwo.GreenHue[x]=StreamTwo.GreenHue[x-1];
        StreamTwo.RedHue[x]=StreamTwo.RedHue[x-1];
      } 
      else {
        StreamTwo.BlueHue[x]=StreamTwo.LastBlue;
        StreamTwo.GreenHue[x]=StreamTwo.LastGreen;
        StreamTwo.RedHue[x]=StreamTwo.LastRed;
      }
    }

    StreamTwoTime.LastTriggered = time;
  }

  strip.show();
}