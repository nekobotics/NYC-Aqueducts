#include <Adafruit_NeoPixel.h>

#define Pixel_Pin 9
#define Num_Pixels 328
#define BRIGHTNESS 25

struct Color{
  int Red;
  int Green;
  int Blue;
};

Color ColorOne = {30,160,200};
Color ColorTwo = {30,200,200};
Color ColorThree = {10,120,200};
Color ColorFour = {30,255,250};
Color ColorFive = {10,210,210};
Color CurrentPixel = {0,0,0};

long colorchoice = 0;

int delayed = 60;

int CurrentColor[Num_Pixels];


Adafruit_NeoPixel strip(Num_Pixels, Pixel_Pin, NEO_GRBW + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  
  strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);

  for(int x=0; x < (Num_Pixels); x++){
    CurrentColor[x]=random(1,5);
    delay(10);
  }
}

void loop() {
  for(int x=0; x < (Num_Pixels); x++){
    if(CurrentColor[x] == 1){CurrentPixel = ColorOne;}
    else if(CurrentColor[x] == 2){CurrentPixel = ColorTwo;}
    else if(CurrentColor[x] == 3){CurrentPixel = ColorThree;}
    else if(CurrentColor[x] == 4){CurrentPixel = ColorFour;}
    else if(CurrentColor[x] == 5){CurrentPixel = ColorFive;}
    else if(CurrentColor[x] == 0){CurrentPixel = {0,0,0};}
   
    strip.setPixelColor(x,CurrentPixel.Red,CurrentPixel.Green,CurrentPixel.Blue);
  }
  
  strip.show();
  delay(delayed);
  for(int x=Num_Pixels; x >= 0; x--){
    if(x == 0){CurrentColor[x] = random(1,5);}
    else if(x >= 5 && x <10 ){CurrentColor[x] = CurrentColor[x-2];}
    else {CurrentColor[x] = CurrentColor[x-1];}
  }
  for(int x= 138 ; x < Num_Pixels; x++){
    strip.setPixelColor(x,0,0,0);
  }
}
