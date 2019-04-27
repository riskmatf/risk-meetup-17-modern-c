#include <stdio.h>
#include <stdlib.h>

int apply_and_add(int x, int y, int (*f)(int)) {
	return f(x) + f(y);
}

int main(int argc, char *argv[]) {
	int k = 4;
	int n = -5;

	int linear(int x) { return k * x + n; }

	printf("%d\n", apply_and_add(3, 4, linear));

	return 0;
}
