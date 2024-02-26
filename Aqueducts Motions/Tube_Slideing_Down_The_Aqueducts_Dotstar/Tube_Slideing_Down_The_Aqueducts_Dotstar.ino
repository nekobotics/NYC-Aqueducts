#include <Adafruit_DotStar.h>
#include <SPI.h>

#define DATAPIN 9
#define CLOCKPIN 19
#define NUMPIXELS 288

const int Length = 40;
int ColorHue[Length];

int StripLength;
int NumStrips;

int LastPixel;

Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show();
  strip.setBrightness(80);
  Serial.begin(9600);

  NumStrips = NUMPIXELS/Length;
  StripLength = NUMPIXELS/NumStrips;

  for(int x=0; x < Length; x++){
    ColorHue[x]= (220/2)-((220/2) * sin(x * ((3.14)/Length)));
    Serial.println(ColorHue[x]);
  }
}

void loop() {
  for(int  i= 0; i < NumStrips+1; i++){
    for(int x = 0; x < StripLength; x++){strip.setPixelColor((x+(i*(StripLength-1))),ColorHue[x]+20,0,ColorHue[x]+10);}
  }

  strip.show();
  delay(25);

  LastPixel = ColorHue[Length-1];
  for(int x = (Length-1); x >= 0; x--){
    if(x!=0){ColorHue[x]=ColorHue[x-1];} 
    else {ColorHue[x]=LastPixel;}
  }
  
}