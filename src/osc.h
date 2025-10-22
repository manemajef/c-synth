#ifndef OSC_H

#define OSC_H
#define RATE 44100
#define A 440
#define FLOAT_TO_INT 32767

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
void oscillator_init(Oscillator *osc, WaveType wave, double freq);
double oscillator_next(Oscillator *osc);
int note_to_freq(char note);

#endif
