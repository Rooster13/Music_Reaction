/*
 *  Music Wear
 *  Kristen Villemez
 *  
 *  Digital revision of the original Party Sunglasses.
 *  This move to a DSP approach to audio processing allows
 *  for more flexibility and consistency, as well as
 *  reliability. This also introduces a move to LEDs
 *  as opposed to EL wire, which is simpler and opens the
 *  possibility to use digital addressable LEDs and create
 *  color effects as opposed to just brightness.
 *
 *  DSP Filter Cutoff Frequency: 512Hz
 *  Sample Rate: 40kHz (25us between samples)
 *
 *  The algorithm used in this code emulates an RC lowpass
 *  filter (single pole). It can be found on Wikipedia with
 *  its derivation from the simple RC filter example here:
 *  http://en.wikipedia.org/wiki/Low-pass_filter
 *
 *  The microphone circuit used in this code is available
 *  on Sparkfun here:
 *  https://www.sparkfun.com/datasheets/BreakoutBoards/Amplified-Mic-Electret-v14.pdf
 *
 *  TimerOne is used to capture samples at a consistent time
 *  interval. The ISR also keeps track of how many samples
 *  have been collected so that the loop routine can
 *  generate the next output after the array of samples has
 *  been completed.
 */
 
#include <TimerOne.h>
#define MIC_PIN A5
#define ALPHA 0.074438

float in[40] = {0};
float out[40] = {0};
volatile int sampleCount = 0;

void setup()
{
  Timer1.initialize(25); // Initialize timer interrupt to run every 25us
  Timer1.attachInterrupt(takeSample); // Attach interrupt to the takeSample() function
  Serial.begin(9600);
}

void loop()
{
  if (sampleCount == 40)
  {
    out[0] = in[0];
    Serial.println(out[0]);
    for (int i; i < 40; i++)
    {
      out[i] = out[i-1] + ALPHA * (in[i] - out[i-1]);
      Serial.println(out[i]);
    }
  }
}

void takeSample()
{
  in[sampleCount] = analogRead(MIC_PIN);
  sampleCount++;
}
