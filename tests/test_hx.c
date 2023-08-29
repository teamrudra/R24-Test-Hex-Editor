#include "utils.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>

int compareFiles(FILE* fp1, FILE* fp2) {
    
    rewind(fp1);
    rewind(fp2);
    if (fp1 == NULL || fp2 == NULL) {
        return 0;
    }

    int bufferSize = 10;
    char buffer1[bufferSize], buffer2[bufferSize];
    int file1Bytes, file2Bytes;
    int difference = 0;

    do {
        file1Bytes = fread(buffer1, sizeof(char), bufferSize, fp1);
        file2Bytes = fread(buffer2, sizeof(char), bufferSize, fp2);

        if (file1Bytes != file2Bytes || memcmp(buffer1, buffer2, file1Bytes) != 0) {
            difference = 1;
            break;
        }
    } while (file1Bytes > 0 && file2Bytes > 0);

    if (difference == 0 && file1Bytes == 0 && file2Bytes == 0) {
        return 1;
    } else {
        return 0;
    }
}

void test_bin2hex(void) {
    FILE* hexdump = fopen("hexdump.txt", "w+");
    FILE* test_hex2bin = fopen("test_hex2bin.txt", "r");
    FILE* test_bin2hex = fopen("test_bin2hex.txt", "r");

    bin2hex(test_hex2bin, hexdump);
    fflush(hexdump); // Flush the file buffer to ensure data is written

    TEST_ASSERT_EQUAL(1, compareFiles(hexdump, test_bin2hex));

    fclose(test_hex2bin);
    fclose(test_bin2hex);
    fclose(hexdump);
    remove("hexdump.txt");
}

void test_hex2bin(void) {
    FILE* binary = fopen("binary.txt", "w+");
    FILE* test_bin2hex = fopen("test_bin2hex.txt", "r");
    FILE* test_hex2bin = fopen("test_hex2bin.txt", "r");

    hex2bin(test_bin2hex, binary);
    fflush(binary); // Flush the file buffer to ensure data is written

    TEST_ASSERT_EQUAL(1, compareFiles(binary, test_hex2bin));

    fclose(binary);
    fclose(test_hex2bin);
    fclose(test_bin2hex);
    remove("binary.txt");
}
void setUp() {}
void tearDown() {}

int main(void)
{
UNITY_BEGIN();
RUN_TEST(test_hex2bin);
RUN_TEST(test_bin2hex);
return UNITY_END();
}
