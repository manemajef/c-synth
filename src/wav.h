
#ifndef WAV_H

#define WAV_H
#include <stdint.h>
void write_wav_file(const char *filename, int16_t *samples, int num_samples);

#endif
