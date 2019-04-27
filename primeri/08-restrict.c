// Prevesti sa gcc 08-restrict.c -o 08 -O2 [-DRESTRICT]
// Koristeci gdb ispitati razliku izmedju verzije koja koristi kvalifikator tipa
// restrict i koje ne koristi

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef RESTRICT
#define restrict
#endif

void f(int * restrict a, int * restrict b, int * restrict c) {
	*a += *c;
	*b += *c;
}

int main() {
	int a = 5, b = 6, c = -2;
	f(&a, &b, &c);

	printf("%d %d\n", a, b);

	uint8_t x = 5;
	printf("%" PRIu8, x);

	return 0;
}
