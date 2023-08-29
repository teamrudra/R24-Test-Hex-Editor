#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdio.h>

#define OFFSET 18
#define LEN_LINE 16

void print_help(const char* target);
void error_infile(const char* filename);
void error_infile_open(void);

void print_pretty(char offset, int act_read_bytes, const uint8_t* buffer, FILE* out_file);
void bin2hex(FILE* in_file, FILE* out_file);
void hex2bin(FILE* in_file, FILE* out_file);

#endif
