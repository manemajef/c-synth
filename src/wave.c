#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RATE 441



double *sine_wave(int freq) {
double phase = 0.0;
  double diff = (double)freq / RATE;
  int total = dur_sec * RATE;
  double *samples = (double *)malloc(sizeof(double) * total);
  double *samp = samples;
  for (int i = 0; i < total; i++) {
    if (phase > 1) phase -= 1;
    *samp = sin(phase * M_PI  * 2);
    phase += diff;
  }
  return samples;
}

double
