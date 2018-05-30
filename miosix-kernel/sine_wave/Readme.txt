This folder contains the main program for generating a sine wave
Commands to compile
gcc -std=c99 sine_wave.c -lm
./a.out
ffplay -autoexit -f u16be -ar 44100 -ac 1 out.raw


The following are cheat sheets for generating a header file from wav/raw file containing the audio data
Commands for sad_trombone
g++ -O2 -o convert convert.cpp adpcm.c
./convert <name ofgenerated raw file>
