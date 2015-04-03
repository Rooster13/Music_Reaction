#include <Adafruit_NeoPixel.h>
#include <ADC.h>

#define NUMPIX 5
#define PIXPIN 5

//Adafruit_NeoPixel testStrand = Adafruit_NeoPixel(NUMPIX, PIXPIN, NEO_GRB + NEO_KHZ800);
ADC *adc = new ADC();

void setup()
{
  //testStrand.begin();
  pinMode(A6, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  int in = adc->analogRead(A6);
  Serial.println(in);
  if (in > 580 || in < 420)
  {
    for(int i = 0; i < NUMPIX; i++)
    {
      digitalWrite(13, HIGH);
      //testStrand.setPixelColor(i, testStrand.Color(100, 100, 100));
    } 
  }
  else
  {
    for(int i = 0; i < NUMPIX; i++)
    {
      digitalWrite(13, LOW);
      //testStrand.setPixelColor(i, testStrand.Color(0, 0, 0));
    }
  }
}
