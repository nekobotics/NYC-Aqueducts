#include <FastLED.h>

#define DATA_PIN 9
#define CLOCK_PIN 19
#define NUMPIXELS 864

const int Length = 80;
int ColorHue[Length];

int StripLength;
int NumStrips;

int LastPixel;

//Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
CRGB leds[NUMPIXELS];

void setup() {
  // put your setup code here, to run once:
  // strip.begin();
  // strip.show();
  // strip.setBrightness(255);
  Serial.begin(9600);
  FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB,DATA_RATE_MHZ(10)>(leds, NUMPIXELS);  // BGR ordering is typical
  FastLED.setBrightness(50);

  for(int x=0; x < Length; x++){
    ColorHue[x]= (220/2)-((220/2) * sin(x * ((3.14)/Length)));
    Serial.println(ColorHue[x]);
  }
}

void loop() {
  for(int  x= 0; x < NUMPIXELS; x++){
    leds[x] = CRGB(ColorHue[x - (Length*(x/Length))]+5,ColorHue[x - (Length*(x/Length))]+10,0);
  }

  FastLED.show();
  delay(25);

  LastPixel = ColorHue[Length-1];
  for(int x = (Length-1); x >= 0; x--){
    if(x!=0){ColorHue[x]=ColorHue[x-1];} 
    else {ColorHue[x]=LastPixel;}
  }
  
}