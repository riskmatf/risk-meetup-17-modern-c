/* Prevesti sa:
 *	gcc inline-gcd.c -o static-inline # za static inline
 *	gcc inline-gcd.c gcd.c -o extern-inline -DEXTERN # za extern inline
 *
 * Da bi funkcije zapravo bile inline-ovane, potrebno je dodati -O2 flag.
 * Ispitati gdb-om.
 */

#include <stdio.h>

#include "gcd.h"

int main() {
	unsigned a, b;
	scanf("%u%u", &a, &b);
	printf("%u\n", gcd(a, b));
	return 0;
}
