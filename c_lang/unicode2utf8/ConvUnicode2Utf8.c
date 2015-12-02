#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int conv2org(unsigned long, unsigned char *, int);

int main(int argc, char* argv[])
{
	unsigned char output[20];
	unsigned long unic=0x3042;
	int outSize=6,sts=0;
	
	sts = conv2org( unic, output, outSize);
	
	printf("\n pOutput:%s[sts=%d]\n",output,sts);

	exit(0);
}

int conv2org(unsigned long unic, unsigned char *pOutput, int outSize)
{
	assert(pOutput != NULL);
	assert(outSize >= 6);

	if( unic <= 0x0000007F )
	{
		// * U-00000000 - U-0000007F : 0xxxxxxx
		*pOutput = (unic & 0x7F);
		return 1;
	}
	else if ( unic >= 0x00000080 && unic <= 0x000007FF )
	{
		// * U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
		*(pOutput+1) = (unic & 0x3F) | 0x80;
		*pOutput = ( (unic >> 6) & 0x1F ) | 0xC0; 
		return 2;
	}
	else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
	{
		// * U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		*(pOutput+2) = (unic & 0x3F) | 0x80;
		*(pOutput+1) = ( (unic >> 6) & 0x3F ) | 0x80; 
		*pOutput = ( (unic >> 12) & 0x0F ) | 0xE0; 
		return 3;
	}
	else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
	{
		// * U-00010000 - U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxxx 10xxxxxx
		*(pOutput+3) = (unic & 0x3F) | 0x80;
		*(pOutput+2) = ( (unic >> 6) & 0x3F ) | 0x80; 
		*(pOutput+1) = ( (unic >> 12) & 0x3F ) | 0x80; 
		*pOutput = ( (unic >> 18) & 0x07 ) | 0xF0; 
		return 4;
	}
	else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
	{
		// * U-00200000 - U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxxx 10xxxxxx 10xxxxxx
		*(pOutput+4) = (unic & 0x3F) | 0x80;
		*(pOutput+3) = ( (unic >> 6) & 0x3F ) | 0x80; 
		*(pOutput+2) = ( (unic >> 12) & 0x3F ) | 0x80; 
		*(pOutput+1) = ( (unic >> 18) & 0x3F ) | 0x80; 
		*pOutput = ( (unic >> 24) & 0x03 ) | 0xF8; 
		return 5;
	}
	else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
	{
		// * U-04000000 - U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
		*(pOutput+5) = (unic & 0x3F) | 0x80;
		*(pOutput+4) = ( (unic >> 6) & 0x3F ) | 0x80; 
		*(pOutput+3) = ( (unic >> 12) & 0x3F ) | 0x80; 
		*(pOutput+2) = ( (unic >> 18) & 0x3F ) | 0x80; 
		*(pOutput+1) = ( (unic >> 24) & 0x3F ) | 0x80; 
		*pOutput = ( (unic >> 30) & 0x01 ) | 0xFC; 
		return 6;
	}
	return 0;
	
}
