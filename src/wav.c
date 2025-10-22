#include <stdio.h>
#include <stdint.h>
#include "wav.h"
#define RATE 44100

void write_wav_header(FILE *file, int sample_rate, int channels,
                      int bit_depth, int num_samples) {
    int data_size = num_samples * channels * (bit_depth / 8);
    int file_size = 36 + data_size;
    // RIFF header
    fwrite("RIFF", 1, 4, file);
    fwrite(&file_size, 4, 1, file);
    fwrite("WAVE", 1, 4, file);
    // fmt chunk
    fwrite("fmt ", 1, 4, file);
    int fmt_size = 16;
    fwrite(&fmt_size, 4, 1, file);
    int16_t audio_format = 1;  // PCM
    fwrite(&audio_format, 2, 1, file);
    int16_t num_channels = channels;
    fwrite(&num_channels, 2, 1, file);
    fwrite(&sample_rate, 4, 1, file);
    int byte_rate = sample_rate * channels * bit_depth / 8;
    fwrite(&byte_rate, 4, 1, file);
    int16_t block_align = channels * bit_depth / 8;
    fwrite(&block_align, 2, 1, file);
    int16_t bits_per_sample = bit_depth;
    fwrite(&bits_per_sample, 2, 1, file);
    // data chunk
    fwrite("data", 1, 4, file);
    fwrite(&data_size, 4, 1, file);
}

void write_wav_file(const char *filename, int16_t *samples, int num_samples) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("couldnt open file, return\n");
        return;
    }
    write_wav_header(file, RATE, 1,16, num_samples);
    fwrite(samples, sizeof(int16_t), num_samples, file);
    fclose(file);
    printf("Succesfully wrote %d samples to %s\n", num_samples, filename);


}
