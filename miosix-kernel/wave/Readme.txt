This folder contains the main program for generating a sine wave
Commands to compile
gcc -o sound main.c endian.c wave.c -lm
./sound
ffplay mono.wav

./a.out -- this was for an old raw file
ffplay -autoexit -f u16be -ar 44100 -ac 1 out.raw


The following are cheat sheets for generating a header file from wav/raw file containing the audio data
Commands for sad_trombone
g++ -O2 -o convert convert.cpp adpcm.c
./convert <name ofgenerated raw file>
