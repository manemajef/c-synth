#!/bin/bash
gcc -o synth src/main.c src/osc.c src/wav.c -lm && ./synth
