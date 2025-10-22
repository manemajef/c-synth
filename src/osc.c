
#include "osc.h"
#include <math.h>

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

// ==  nice idea but works with semitones == //

// int note_to_freq(char note) {
//   int steps = (int) note - 'a';
//   return A*(pow(2, (double)steps/12));
// }

int note_to_freq(char note) {
  int steps;
  switch(note) {
    case 'a': steps = 0; break;
    case 'b': steps = 2; break;
    case 'c': steps = 3; break;
    case 'd': steps = 5; break;
    case 'e': steps = 7; break;
    case 'f': steps = 8; break;
    case 'g': steps = 10; break;
    default: steps = 0;
  }
  return A * pow(2, (double)steps/12.0);
}
