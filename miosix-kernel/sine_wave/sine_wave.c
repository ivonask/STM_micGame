#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    FILE *f;
    const double PI2 = 2 * acos(-1.0);
    const double SAMPLE_FREQ = 44100;
    const unsigned int NSAMPLES = 2 * SAMPLE_FREQ;
    uint16_t ampl;
    uint8_t bytes[2];
    unsigned int t;

    f = fopen("out.raw", "wb");
    for (t = 0; t < NSAMPLES; ++t) {
        ampl = UINT16_MAX * 0.5 * (1.0 + sin(PI2 * t * 500.0 / SAMPLE_FREQ));
        bytes[0] = ampl >> 8;
        bytes[1] = ampl & 0xFF;
        fwrite(bytes, 2, sizeof(uint8_t), f);
    }
    fclose(f);
    return EXIT_SUCCESS;
}
