#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>
#include <math.h>

#define RATE 44100
#define FREQ 440.0
#define BASE 440.0

typedef struct {
  float phase;
  // float freq;
  // int isPlaying;
  float phase_inc;
} TestOsc;

float semitones_to_freq(int steps) {
  return (float) BASE*pow(2, (double)steps/12);
}

float note_to_freq(char note) {
  int steps;
  switch(note) {
    case 'a' : steps =  0;break;
    case 'b' : steps = 2;break;
    case 'c' : steps = 3;break;
    case 'd' : steps = 5;break;
    case 'e' : steps = 7;break;
    case 'f' : steps = 8;break;
    case 'g' : steps = 10;break;
    default: steps = 0; break;
  }
  return semitones_to_freq(steps);
}

void audio_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 framecount) {

  static int count = 0;
   if (count++ < 5) {  // Only print first 5 times
       printf("Callback called! frameCount=%d\n", (int)framecount);
   }

  float *out = (float*)pOutput;
  TestOsc *osc = (TestOsc*)pDevice -> pUserData;

  (void)pInput;
  for (int i =0; i< framecount; i++) {
    out[i] = (float)(sin(osc->phase * 2.0 * M_PI)*0.3);
    osc -> phase += osc -> phase_inc;
    if (osc -> phase >= 1.0) {
      osc-> phase -= 1.0;
    }
  }
}



int main() {
  TestOsc osc;
  osc.phase = 0.0;
  char note = 'a';
  // printf("press a note from 'A' to 'G'. press q to quit\n");
  // scanf("%c", &note);
  // if (note == 'q') {
  //   printf("quiting");
  //   return 0;
  // }
  float freq = note_to_freq(note);
  osc.phase_inc = freq/ RATE;

  ma_device_config config = ma_device_config_init(ma_device_type_playback);

  config.playback.format = ma_format_f32;
  config.playback.channels = 1;
  config.sampleRate = RATE;
  config.dataCallback = audio_callback;
  config.pUserData = &osc;

  ma_device device;
  if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
      printf("Failed to initialize device\n");
      return 1;
  }
  if (ma_device_start(&device) != MA_SUCCESS) {
      printf("Failed to start device\n");
      ma_device_uninit(&device);
      return 1;
  }


  printf("playing\n");
  getchar();
  ma_device_uninit(&device);
  printf("stopped\n");
  return 0;
}
