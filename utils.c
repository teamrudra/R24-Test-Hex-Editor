#include "utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print_help(const char* target)
{
    printf("Hex Editor\n");
    printf("Usage: %s [-b2h] [input]\n\n", target);

    printf("Arguments:\n");
    printf("================================================\n");
    printf(" -h   | --help              : Print this message\n");
    printf(" -b2h | --binary_to_hex     : Mode to dump hex\n");
    printf(" -h2b | --hex_to_binary     : Mode to save binary\n");
}

void error_infile(const char* target)
{
    fprintf(stderr, "Usage: %s [-b2h] [input]\n", target);
}

void error_infile_open()
{
    fprintf(stderr, "Couldn't open the input file\n");
}

void print_pretty(char offset, int act_read_bytes, const uint8_t* buffer, FILE* out_file)
{
    // prints read bytes and hex in an intuitive format
    fprintf(out_file, "%016lld ", (long long)offset);

    for (int i = 0; i < LEN_LINE; i++)
    {
        if (i < act_read_bytes)
        {
            fprintf(out_file, " %02X", buffer[i]);
        }
        else
        {
            fprintf(out_file, "   ");
        }
    }

    fprintf(out_file, " |");
    for (int i = 0; i < act_read_bytes; i++)
    {
        if (buffer[i] > 31 && buffer[i] < 127) 
            fprintf(out_file, "%c", buffer[i]);
        else
            fprintf(out_file, ".");
    }

    fprintf(out_file, "|\n");
}

void bin2hex(FILE* in_file, FILE* out_file)
{
    // allocate appropriate memory for buffer 
    uint8_t* buffer = (uint8_t*)malloc(LEN_LINE);

    int64_t offset = 1;
    while (!feof(in_file))
    {
        int read_bytes = LEN_LINE;

        int act_read_bytes = fread(buffer, sizeof(uint8_t), read_bytes, in_file);
        if (act_read_bytes > 0)
        {
            print_pretty(offset, act_read_bytes, buffer, out_file);
            offset += act_read_bytes;
        }
        else
        {
            break;
        }
    }

    free(buffer);
}

void hex2bin(FILE* in_file, FILE* out_file)
{
    int count = 0;
    char curr_char, curr_char_value, curr_byte = 0;

    fseek(in_file, OFFSET, SEEK_CUR);
    while (!feof(in_file))
    {
        int n = fread(&curr_char, sizeof(char), 1, in_file);
        if (n == 0)
        {
            break;
        }

        if (curr_char == '\n')
        {
            fseek(in_file, OFFSET, SEEK_CUR);
        }
        else if (curr_char == '|')
        {
            fseek(in_file, 16 + 1, SEEK_CUR);
            continue;
        }
        else if (curr_char >= '0' && curr_char <= '9')
        {
            curr_char_value = curr_char - '0';
        }
        else if (curr_char >= 'A' && curr_char <= 'F')
        {
            curr_char_value = curr_char - 'A' + 0xa;
        }
        else
        {
            continue;
        }

        curr_byte = (curr_byte << 4) | curr_char_value;

        if (count)
        {
            fprintf(out_file, "%c", curr_byte);
        }

        count = !count;
    }
}
