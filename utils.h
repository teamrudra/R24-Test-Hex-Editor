#ifndef utils_h
#define utils_h

#include <stdint.h>
#include <stdio.h>

#define OFFSET 18
#define LEN_LINE 16

void print_help(char*);
void error_infile(char*);
void error_infile_open();

void print_pretty(char offset, int act_read_bytes, uint8_t* buffer, FILE* out_file);
void bin2hex(FILE*, FILE*);
void hex2bin(FILE*, FILE*);

#endif
