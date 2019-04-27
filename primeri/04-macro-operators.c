/* Napomena: koristimo gcc -E 04-macro-operators.c da bismo videli izvorni kod
   posle faze preprocesuiranja */

#include <stdio.h>
#include <stdlib.h>

#define $(x) #x
#define print_macro(mcr) printf("%s = %s\n", #mcr, $(mcr))

#define PI 3.14
#define E  2.71
#define max(a, b) ((a) < (b) ? (a) : (b))


struct person {
	char *name;
	char *surname;
	unsigned short age;
};

#define T(x) \
	struct x x##_new(); \
	struct x x##_destroy(); \

T(person)

T(point)

#undef T


int main() {
	printf("%s\n", $(hello));
	print_macro(PI);
	print_macro(E);
	print_macro(max(x, y));
	return 0;
}
