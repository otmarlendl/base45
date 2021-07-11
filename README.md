# base45
Simple programs to encode and decode according to the base45 standard

The EU Green Pass for proving that you got your Covid-19 shots is using a QR-Code that contains base45-encoded data according to https://datatracker.ietf.org/doc/draft-faltstrom-base45/ 

This package contains two very basic C programs that act as a unix-style filter, converting stdin to stdout.

I consider this a stop-gap code for decoding such QR-codes. Long term, base45 should probably be integrated into GNU Coreutils.

# Fetch & Compile
These are very basic POSIX C programs, a simple

`git clone https://github.com/otmarlendl/base45`

`cd base45`

`make all`

should suffice. No script is provided to install the resulting binaries. I recommend copying them to /usr/local/bin.
