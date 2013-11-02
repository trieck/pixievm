// chargen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void print_row(char c)
{
	for (int i = 7; i >= 0; --i) {
		if (c & (1 << i))
			putchar('*');
		else
			putchar(' ');
	}
}

void print_char(char *buf)
{
	for (int i = 0; i < 8; ++i) {
		print_row(buf[i]);
		putchar('\n');
	}
	putchar('\n');
}

int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp;
	if ((fp = fopen("chargen.rom", "rb")) == NULL) {
		fprintf(stderr, "can't open chargen.rom.\n");
		exit(1);
	};

	// there are 256 characters in the chargen.rom
	// each character takes 8 bytes to store
	char buf[8];
	for (int i = 1; i <= 256; ++i) {
		if (fread(buf, sizeof(buf), 1, fp) != 1) {
			fprintf(stderr, "error reading char#%d from chargen.rom.\n", i);
			break;
		}
		print_char(buf);
	}

	fclose(fp);

	return 0;
}

