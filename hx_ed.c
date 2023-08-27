#include "utils.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int flag=1;

    FILE* in_file = NULL;

    for(int i = 1; i < argc; i++)
    {
	if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
	{
	    print_help(argv[0]);
	    return 0;
	}
	else if (strcmp(argv[i], "-b2h") == 0 || strcmp(argv[i], "--binary_to_hex") == 0)
	{
	    flag = 1;    
	}
	else if(strcmp(argv[i], "-h2b") == 0 || strcmp(argv[i], "--hex_to_binary") == 0)
	{
	    flag = 0;
	}
	else
	{
	    if (in_file != NULL)
	    {
		error_infile(argv[0]);
		return 1;
	    }
	    in_file = fopen(argv[i], "r");
	    if (in_file == NULL)
	    {
		error_infile_open();
		return 2;
	    }
	}
    }
    if (flag)
	bin2hex(in_file, stdout);
    else hex2bin(in_file, stdout);

    fclose(in_file);
    return 0;
}
