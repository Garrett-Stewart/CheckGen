#ifndef TABLE_H
#define TABLE_H

#include <string.h>
#include <bitset>
#include <stdlib.h>

typedef unsigned long long int syze64; // represents bit length of string in 64 bits
typedef unsigned long syze; // represents bit length of string
typedef int csyze; // represents binary-operation-friendly syze
typedef char bit; // holds character bit value

typedef unsigned int tb; // table bounds, represents size of array

static int c_words[4] = {0x10325476, 0x98badcfe, 0xefcdab89, 0x67452301};

void compute_k_table(unsigned int *k)
{
	for (int i = 0; i < 64; i++)
		k[i] = floor(pow(2, 32) * abs(sin(i + 1)));
}

// Converts decimal number (ideally syze64) to binary string
char* compose_nstr(syze64 _t)
{
	// Allocate bit string with 64 bits
	// Then, fill all bits with 0's
	char* str = new char[64];
	for (int i = 0; i < 64; i++)
		str[i] = '0';

	// Perform _t mod 2 to find activated bits
	// Resolve numeric value to corresponding character
	for (int i = 0; _t > 0; i++)
	{
		(_t % 2 == 0) ? str[i] = '0' : str[i] = '1';
		_t /= 2;
	}

	// Flip bit string to allign with propery binary string
	for (int u = 0; u < 64 / 2; u++)
	{
		// Lower end (from front of string) bit
		bit lend = str[u];
		str[u] = str[63 - u];
		str[63 - u] = lend;
	}

	return str;
}

// Appends single character to string (bit string)
char* append(char *bitstr, char bit)
{
	// Compute original size of bit string
	// Allocate new array with 2 extra characters (one for new character, one for null char)
	syze bs_syze = strlen(bitstr);
	char *app = new char[bs_syze + 2];

	// Copy original bit string into array
	// Append new character and null char
	strcpy(app, bitstr);
	app[bs_syze] = bit; app[bs_syze + 1] = '\0';

	// Return new string
	return app;
}

// Appends single bit to bistring without null chars
char *clip(char* bitstr, char bit)
{
	// Compute original size of bit string
	// Allocate new array with 2 extra characters (one for new character, one for null char)
	syze bs_syze = strlen(bitstr);
	char *app = new char[bs_syze + 2];

	// Copy original bit string into array
	// Append new character and null char
	strcpy(app, bitstr);
	app[bs_syze] = bit;

	// Return new string
	return app;
}

char *stackappend(char* bitstr, const char *str)
{
	char *app = bitstr;
	for (int i = 0; i < strlen(str); i++) {
		app = append(app, str[i]);
	}
	return app;
}

// Appends full string without null chars
char *clasp(char* bitstr, const char* str)
{
	char *app = bitstr;
	for (int i = 0; i < strlen(str); i++) {
		app = clip(app, str[i]);
	}
	return app;
}

// Creates new const char* bit string
// From original bitstring and str to concatenate
const char* fork(char* bitstr, const char* str)
{
	char stick[strlen(bitstr) + strlen(str)];
	sprintf(stick, "%s%s", bitstr, str);
	const char* dig = stick;
	return dig;
}

// Uses append function to append to bitstr taking bitstr as reference
// Avoids reassignment of bitstr
void fly_append(char &bitstr, char bit)
{
	bitstr = *(append(&bitstr, bit));
}

char* merch(char *bitstr)
{
	char *m = new char[strlen(bitstr) * 8];
	for (int i = 0; i < strlen(bitstr); i++) {
		m = stackappend(m, std::bitset<8>(bitstr[i]).to_string().c_str());
	}
	return m;
}

// Returns const char* string as char*
// Use for inline char* string assignment
char* line(const char* str)
{
	char *sstr = (char*) str;
	return sstr;
}

#endif