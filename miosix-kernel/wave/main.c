#include "wave.h"
#include <math.h>

// -------------------------------------------------------- [ Section: Main ] -
int main(){
    // Define some variables for the sound
    float sampleRate = 44100.0; // hertz
    float freq = 1000.0;         // hertz
    float duration = 1;       // seconds

    int nSamples = (int)(duration*sampleRate);
    
    // Create a mono (1), 16-bit sound and set the duration
    Wave mySound = makeWave((int)sampleRate,1,16);
    waveSetDuration( &mySound, duration );

    // Add all of the data
    int i;
    float frameData[1];
    for(i=0; i<nSamples; i+=1 ){
        frameData[0] = cos(freq*(float)i*3.14159/sampleRate);
        waveAddSample( &mySound, frameData );
    }

    // Write it to a file and clean up when done
    waveToFile( &mySound, "mono.wav");
    waveDestroy( &mySound );

    return 0;
}
