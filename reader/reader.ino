
// Adapted from Aaron ALAI EMF Detector May 28th 2009 VERSION 1.1
// The original part is the 50 Hz signal detection algorithm
#include <Wire.h>
#include <Math.h>

// #define sample 500  //this is how many samples the device takes per reading
#define sample 100 // this is how many samples the device takes per reading
float val;         // where to store info from analog 6
int pin3 = 3;      // output led

// static const unsigned long REFRESH_INTERVAL = 1000;  // ms,
static const unsigned long REFRESH_INTERVAL = 100; // ms
static unsigned long lastRefreshTime = 0;

void setup()
{
  Serial.begin(115200);
}

void loop(void)
{
  long average = 0;
  float c, s;
  while (1)
  {

    if (millis() - lastRefreshTime <= REFRESH_INTERVAL)
    {
      continue;
    };

    lastRefreshTime += REFRESH_INTERVAL;

    // Please note that the sampling rate is quite high, hopefully it's slowed by the trigonometric calculations,
    // the analog to digital conversion and the LCD display commands. In another application, you might do it
    // differently since a minimal 100 Hz sampling rate is enough (Nyquist theorem).
    // Note also that the response speed depends on the number of samples in the window (and process time of one sample of course).
    int16_t adc0;
    // Variable "t" in the formula for calculating "phi". I suppose it must be declared
    // in microseconds because you divide by one million
    long sum, t, top;
    // The Fourier transform gives you an estimate of the amplitude
    // and phase of the 50 Hz signal (c and s are indeed the two Fourier components).
    double amplitude, cp, sp, phi;
    int i;
    sum = 0;
    i = 0;
    c = 0;
    s = 0;
    while (i < sample)
    {
      int16_t reading = analogRead(A0);
      // The sum/average is simply an estimate of the DC component and my code is a bit
      // awkward with the 3/5*1024 substracted, it should just use this for the initial
      // estimate of average.
      adc0 = reading - 1023 * 3 / 5;
      // Serial.println(reading);
      t = micros();
      phi = 6.2831853 * t / 1.0e6 * 60.0;
      c += (adc0 - average) * cos(phi);
      s += (adc0 - average) * sin(phi);
      sum += adc0;
      i++;
    }
    // The average is a very low frequency signal that gets zeroed by the Fourier transform,
    // so it doesn't make any difference to substract it, except if you have rounding/overflow
    // problems (I don't think that's the case). The average is relative to a 3V reference and
    // is calculated with the sum (simple average). It might be that I had to do this to avoid
    // an overflow when using many samples (but with a long integer, I feel rather safe?).
    average = (sum / sample);
    i = 0;
    cp = c / sample;
    sp = s / sample;
    amplitude = 2 * sqrt(cp * cp + sp * sp);

    // Serial.printf(amplitude);         //For test and scaling
    val = amplitude;             // here the program takes the sum of all numbers in array1, and divides by the number of elements "sample"
    val = constrain(val, 0, 20); // tweak it from experience, 10 works for me
    val = (val / 20.0 * 255.0);

    // Serial.println(average);
    // Serial.printf("amp=%f, avg=%6ld \n", amplitude, average);
    Serial.print(val);
    // Serial.print(" ");
    // Serial.print(sum);
    // Serial.print(" ");
    // Serial.print(average);
    Serial.print("\n");

    // analogWrite(pin3, );
  }
}
