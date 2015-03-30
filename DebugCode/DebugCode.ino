#include <ADC.h>

ADC *adc = new ADC();

void setup()
{
}

void loop()
{
  int in = adc->analogRead(A6);
  Serial.println(in);
  digitalWrite(6, HIGH);
  delay(100);
}
