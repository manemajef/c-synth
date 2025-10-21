#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RATE 441


double *get_samples() {
  double *res = (double*)malloc(sizeof(double) * RATE);
  if (!res) {
    printf("error, exiting\n");
  }
  return res;
}


double *sine_wave(int freq) {
  double dur_sec = 1.0;
  double phase = 0.0;
  double diff = (double)freq / RATE;
  int total = dur_sec * RATE;
  double *samples = get_samples();
  double *samp = samples;
  for (int i = 0; i < total; i++) {
    if (phase > 1) phase -= 1;
    *(samp++) = sin(phase * M_PI  * 2);
    phase += diff;

  }
  return samples;
}

double *saw_wave(int freq) {
  double phase = -1.0;
  double diff = (double)freq/ RATE;
  double *samples = get_samples();
  double *samp = samples;
  for (int i = 0; i< RATE; i++) {
    if (phase >= 1) phase -= 2.0;
    *(samp++) = phase;
    phase += diff;
  }
  return samples;
}

double *sqaure_wave(int freq) {
  double phase = 1.0;
  double diff = (double) freq/RATE;
  double *samples = get_samples();
  double *samp = samples;
  for (int i = 0; i < RATE; i++){
    if (phase > 1) phase --;
    *(samp++) = phase > 0.5 ? 1.0 : -1.0;
    phase += diff;
  }
  return samples;
}
