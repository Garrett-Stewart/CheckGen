#include <stdio.h>
#include <math.h>
#include <string>
#include <table.h>

unsigned int k[64];

char* consume, digested;
syze consume_length;

void digest_message(char *pcon);

const char* digest_message_pad();
void digest_process(const char* dig);

void byte_array(unsigned int* k, unsigned int size);

int main(int argc, char** argv) {
	compute_k_table(k);

	if (argv[1] == nullptr)
		digest_message(line("heyencryptthisheyencryptthisheyencryptthisheyencryptthisheyencryptthis"));
	else
		digest_message(argv[1]);

	return (0);
}

void digest_message(char *pcon)
{
	// Merch converts input to binary string
	// Appends required padding bit '1'
	// Consume length calculates bit length of input string  
	consume = append(merch(pcon), '1');
	consume_length = (strlen(consume));

	const char* dig = digest_message_pad();
	digest_process(dig);
}

const char* digest_message_pad()
{
	// '1' has already been padded
	// Appends 0's until bit length of input string
	// mod 512 is equal to 448 (64 less than some multiple
	// of 512). The 64 remaining bits are reserved
	// for padding 64-bit representation of original length
	// of message mod 2^64
	for (int i = consume_length; i % 512 != 448; i++)
		consume = append(consume, '0');

	// Original syze of input string
	// Stack append original length as 64-bits
	// Return new const char* digest string
	syze64 osyze = (syze64) consume_length;
	return fork(consume, compose_nstr(osyze));
}

void digest_process(const char* dig)
{
	// Create dictionary array containing
	// 16 32-bit words for each 512-bit chunk
	// of message
	tb dsize = strlen(dig) / 512 * 16;
	char *dict[dsize];
	for (int i = 0; i < dsize; i++)
	{
		char *word;
		for (int j = 0; j < 32; j++)
		{
			word[j] = dig[j + i * 32];
		}
		word[32] = '\0';
		dict[i] = word;
	}

	printf("%d\n", strlen(dict[0]));
	// for (int i = 0; i < dsize; i++)
	// {
	// 	printf("%d", i);
	// }
}

void byte_array(unsigned int* k, unsigned int size) {
	for (int i = 0; i < size; i++)
		(i < size - 1) ? printf("%02X, ", k[i]) : printf("%02X\n", k[i]);
}