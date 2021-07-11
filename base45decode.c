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

uint8_t *alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";

void main() {
	uint8_t  *match;
	int got_bytes;
	int new, offset;
	uint32_t value = 0;

	assert(strlen(alphabet) == 45);

	while (!feof(stdin)) {
		value = 0;
		got_bytes = 0;

		while(got_bytes < 3) {
			new = fgetc(stdin);
			if (new == EOF) break;
			if (new == 0) continue;		/* don't want to deal with null bytes here */

			match = strchr(alphabet, new);
			if (match == NULL) continue;	/* not found */

			offset = match - alphabet;

			if (got_bytes == 0) {
					value += offset;
			} else if (got_bytes == 1) {
					value += offset * 45;
			} else if (got_bytes == 2) {
					value += offset * 45 *45;
			} else assert(0);

			got_bytes++;
		}
		assert (value <= 65535);	/* see Security Considerations */
		assert (got_bytes != 1);
		assert ((got_bytes == 3) || (value <= 255));

		if (got_bytes == 2) printf("%c", value);
		if (got_bytes == 3) printf("%c%c", value >> 8, value & 255);
	}
}
