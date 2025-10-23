#include <stdio.h>
#include <stdlib.h>
#include "osc.h"
#include "wav.h"

void play();

void select_wave(int *wave) {
  printf("select a wave. 0 for sine, 1 for saw and 2 for square\n");
  scanf("%d", wave);
  printf("selected ");
  switch (*wave) {
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
}

void select_note(char *note_select) {
  printf("select a note, press w to change wave, press q to kill program\n");
  scanf(" %c", note_select);
}

int main() {
  int mode;
  printf("select mode:\n");
  printf("1. live play\n");
  printf("2. generate wav samples\n");
  printf("enter choice: ");
  scanf("%d", &mode);
  
  if (mode == 1) {
    play();
    return 0;
  }
  
  Oscillator osc;
  // int freq = 440;
  char note_select = '0';
  int wave = -1;
  select_wave(&wave);
  while (note_select != 'q') {
    select_note(&note_select);
    if (note_select == 'w'){
      select_wave(&wave);
      continue;
    }
    if (! ('a' <= note_select && note_select <= 'g' )) {
      note_select == 'q' ? printf("quiting\n") : printf("invalid select. try again\n");
      continue;
    }
    double freq = note_to_freq(note_select);
    printf("Selected Note %c with a frequency of %lf\n", (char)note_select - 'a' + 'A', freq);
    oscillator_init(&osc, wave, freq );

    int dur = 1;
    int total_samples = dur * RATE;
    int16_t *samples = (int16_t*)malloc(total_samples * sizeof(int16_t));
    for (int i = 0; i < total_samples; i++) {
      double float_sample = oscillator_next(&osc);
      samples[i] = (int16_t)(float_sample * FLOAT_TO_INT);
    }
    // generate wav
    write_wav_file("output.wav", samples, total_samples);
    system("afplay output.wav");
    free(samples);
  }
  return 0;
}
