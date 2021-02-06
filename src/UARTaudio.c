/*
 ============================================================================
 Name        : UARTaudio.c
 Author      : Akos Mate
 Version     : 0.1
 Copyright   : You can copy or do whatever you want.
 Description : Program to convert a stream of 16 bit mono audio samples into
               a byte-stream to play through a serial port.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define FRACTION_BITS ((uint32_t) 31)
#define TMR_INT_MASK ((uint32_t) (1<<FRACTION_BITS))
#define TMR_FRAC_MASK ((uint32_t) (TMR_INT_MASK - 1))

int main(int argc, char **argv) {
	uint32_t timer;		//When this reaches TMR_INT_MASK it is time to read a new sample
	uint32_t time_inc;	//timer increment (bit time)
	int16_t sample;
	int32_t prev_err;
	int32_t expected;
	uint8_t b;
	uint8_t n;

	if (argc < 3)
		printf("Usage:\n\t%s <sample rate> <baud rate>\n", argv[0]);

	time_inc = (uint32_t)((((uint64_t) atoi(argv[1])) << FRACTION_BITS) / ((uint64_t)atoi(argv[2])));

	prev_err = 0;
	n = 0;
    timer = TMR_INT_MASK;

	while (1) {
		//read next sample
		if (timer & TMR_INT_MASK) {
			if (fread(&sample, sizeof(sample), 1, stdin) != 1)
				break;
		}
		//increment timer
		timer = (timer & TMR_FRAC_MASK) + time_inc;
		//determine output
		expected = (int32_t) sample - prev_err;
		if (n == 0) {
			//This is the start bit (always low)
			prev_err = -32768 - expected;
			//initialize a new byte to 0
			b = 0;
			n = 1;
		} else if (n == 9) {
			//This is the stop bit (always high)
			prev_err = 32767 - expected;
			//send the finished byte
			fwrite(&b, 1, 1, stdout);
			n = 0;
		} else {
			if (expected >= 0) {
				//send high
				prev_err = 32767 - expected;
				b = ((b>>1) | 0x80);
			} else {
				//send low
				prev_err = -32768 - expected;
				b = (b>>1);
			}
			n++;
		}
	}
	return EXIT_SUCCESS;
}
