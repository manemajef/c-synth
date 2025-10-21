#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define RATE 44100
#define A 440

typedef enum {
  sine, saw,square
} WaveType;

typedef enum {
  a, s, d, f, g, h, j, k, l
} NoteFreq;

typedef struct {
  double phase;
  double diff;
  WaveType wave;
} Oscillator;

void oscillator_init(Oscillator *osc, WaveType wave, double freq) {
  osc -> phase = 0.0;
  osc -> diff = (double) freq / RATE;
  osc -> wave = wave;
}

double oscillator_next(Oscillator *osc) {
  double sample;
  double phase = osc->phase;
  switch(osc -> wave) {
    case sine:
      sample = sin(phase * 2 * M_PI );
      break;
    case saw:
      sample = 1.0 - (2.0 * phase);
      break;
    case square:
      sample = phase < 0.5 ? 0.1 : -0.1;
      break;
    default:
      sample = 0.0;
  }
  osc -> phase += osc -> diff;
  if (osc -> phase >= 1.0) osc->phase -= 1.0;
  return sample;
}

int note_to_freq(char note) {
  int steps = (int) note - 'a';
  return A*(pow(2, (double)steps/12));
}



int main() {
  Oscillator osc;
  // int freq = 440;
  char note_select;
  int wave;
  printf("select wave, 0 for sine, 1 for saw, 2 for square\n");
  scanf("%d", &wave);
  printf("selected ");
  switch (wave) {
    case 0:
      printf("Sine");
      break;
    case 1:
      printf("Saw");
      break;
    case 2:
      printf("Square");
    default:
      printf("invalid");
      break;
  }
  printf("\nSelect a note from A - G\n");

  scanf(" %c", &note_select);
  if (! ('a' <= note_select && note_select <= 'g' )) {
    printf("invalid note, exiting.\n");
    return 0;
  }
  double freq = note_to_freq(note_select);
  printf("Selected Note %c with a frequency of %lf", (char)note_select - 'a' + 'A', freq);
  return 0;
}
