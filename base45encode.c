/*

Otmar Lendl <ol@bofh.priv.at>

License: GPL 3

This is a trivial implementation of https://datatracker.ietf.org/doc/draft-faltstrom-base45/

This is not optimized at all, but should be good enough for QR codes.

*/

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void base256tobase45(uint8_t *in, uint8_t *out, int bytes) {
	uint32_t value = 0;

	if (bytes == 2) {
		value = 256 * in[0] + in[1];
	} else if (bytes == 1) {
		value = in[0];
	} else { assert(0); }

	out[0] = value % 45;
	value /= 45;

	out[1] = value % 45;
	value /= 45;

	out[2] = value % 45;
	assert(value < 45);
}

int read_max2(uint8_t *buf) {
	return(fread(buf, 1, 2, stdin));
}

uint8_t *alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";

void printbase45(uint8_t *buf, int num) {
	int i;

	for(i=0; i<num; i++) {
		assert(buf[i] < 45);
		fwrite(&alphabet[buf[i]],1,1,stdout);
	}
}


void main() {
	uint8_t  input[10];
	uint8_t  output[10];
	int got_bytes;

	assert(strlen(alphabet) == 45);

	while (1) {
		input[0] = 0;
		input[1] = 0;
		input[2] = 0;

		got_bytes = read_max2(input);

		if (got_bytes <= 0) break;	/* EOF */
		if (got_bytes == 1) {
			base256tobase45(input, output, 1);
			printbase45(output, 2);
			break;
		} else if (got_bytes == 2){
			base256tobase45(input, output, 2);
			printbase45(output, 3);
		} else { assert(0); }	 /* not reached */
	}
}



