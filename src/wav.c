#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RATE 44100
#define A 440

double *get_samples() {
  double *res = (double*)malloc(sizeof(double) * RATE);
  if (!res) {
    printf("error, exiting\n");
    exit(1);
  }
  return res;
}

double *sine_wave(int freq) {
  double phase = 0.0;
  double diff = (double)freq/RATE;
  double *samples = get_samples();
  for (int i = 0; i < RATE; i++) {
    samples[i] = sin(phase*M_PI*2);
    phase += diff;
    if (phase >= 1.0) phase -= 1.0;
  }
  return samples;
}


double *saw_wave(int freq) {
  double phase = 0.0;
  double diff = (double)freq/RATE;
  double *samples = get_samples();
  for (int i = 0; i < RATE; i++) {
    samples[i] = 1.0 - (2.0 * phase);
    phase += diff;
    if (phase >= 1.0) phase -= 1.0;
  }
  return samples;
}

double *square_wave(int freq) {
  double phase = 0.0;
  double diff = (double) freq/RATE;
  double *samples = get_samples();
  for (int i = 0; i < RATE; i++){
    samples[i] = phase < 0.5 ? 1.0: -1.0;
    phase += diff;
    if (phase >= 1.0) phase -= 1.0;
  }
  return samples;
}
