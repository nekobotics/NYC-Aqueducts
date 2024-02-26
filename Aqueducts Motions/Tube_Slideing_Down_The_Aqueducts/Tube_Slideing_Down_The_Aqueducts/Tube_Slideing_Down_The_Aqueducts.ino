#include <Adafruit_NeoPixel.h>

#define Pixel_Pin 9
#define NUMPIXELS 180
#define BRIGHTNESS 80

const int Length = 20;
int ColorHue[Length];

int StripLength;
int NumStrips;

int LastPixel;

Adafruit_NeoPixel strip(NUMPIXELS, Pixel_Pin, NEO_GRBW + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  strip.setBrightness(255);
  Serial.begin(9600);

  NumStrips = NUMPIXELS/Length;
  StripLength = NUMPIXELS/NumStrips;

  for(int x=0; x < Length; x++){
    ColorHue[x]= (180/2)-((180/2) * sin(x * ((3.14)/Length)));
    Serial.println(ColorHue[x]);
  }
}

void loop() {
  for(int  i= 0; i < NumStrips+1; i++){
    for(int x = 0; x < StripLength; x++){strip.setPixelColor((x+(i*(StripLength-1))),0,ColorHue[x],180);}
  }

  strip.show();
  delay(15);

  LastPixel = ColorHue[Length-1];
  for(int x = (Length-1); x >= 0; x--){
    if(x!=0){ColorHue[x]=ColorHue[x-1];} 
    else {ColorHue[x]=LastPixel;}
  }
  
}